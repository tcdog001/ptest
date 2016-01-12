#include "sys_include.h"
#include "networkPublic.h"

#define COM2_TCP_LISTEN_PORT 5555
static tcp_client_item_def tcpCom2Handle;

static char com2buf[1500];
static int com2buflength = 0;

static int com_sim_task_exit = 0;
static pthread_t pthread_com_sim_task = 0;

static int save_data_into_com2_buffer(char *pdata, int input_len)
{
    if ((com2buflength + input_len) < 1500)
    {
        memcpy(com2buf+com2buflength, pdata, input_len);

        com2buflength += input_len;
        return com2buflength;
    }

    return 0;
}

static int get_cmd_line_from_com2_buffer(char *cmdline, int *poutlength)
{
    int i;
    int j;

    if (com2buflength == 0)
    {
        *poutlength = 0;
        return 0;
    }

    for (i = 0; i < com2buflength; i++)
    {
        if (com2buf[i] == 0x0d)
        {
            i++;
            break;
        }
    }

    printf("i = %d, length = %d\n", i, com2buflength);

    if (i == 0)
    {
        if (com2buflength == 1)
        {
            com2buflength = 0;
        }
        else
        {
            for (j = 0; j < com2buflength-1; j++)
            {
                com2buf[j] = com2buf[j+1];
            }
        }

        *poutlength = 0;
        return 0;
    }

    if (i == 1)
    {
        for (j = 0; j < com2buflength-i; j++)
        {
            com2buf[j] = com2buf[j+i];
        }
        *poutlength = 0;
        return 0;
    }

    memcpy(cmdline, com2buf, i-1);
    *poutlength = i-1;

    if (com2buflength == i)
    {
        com2buflength = 0;
    }
    else
    {
        for (j = 0; j < com2buflength-i; j++)
        {
            com2buf[i] = com2buf[j+i];
        }
    }
    return 1;

    #if 0
    int length;
    int i, j;

    //find first 0x0d position
    for (i = 0; i < com2buflength; i++)
    {
        if (com2buf[i] == 0x0d)
        {
            i++;
            break;
        }
    }

    printf("[%d]i = %d\n",com2buflength, i);
    if (i >= com2buflength)
    {
        *poutlength = 0;
        return 0;
    }

    for (j = i; j < com2buflength; j++)
    {
        if (com2buf[j] == 0x0d)
        {
            break;
        }
    }

    printf("[%d]j = %d\n",com2buflength, j);
    memcpy(cmdline, com2buflength+i, (j-i));
    com2buflength = com2buflength - j;
    *poutlength = (j-i);
    if (com2buflength <= 0)
    {
        com2buflength = 0;
    }
    else
    {
        for (j = 0; j < com2buflength; j ++)
        {
            com2buf[j] = com2buf[i+j];
        }
    }


    return j;
    #endif

}

static int com2_data_save_process(char *pdata, int length)
{
#if 0
    char send_data[1500];
    int send_length;
    int recv_length = 0;

    if (length == 1)
    {
        pdata[0] = 0x0d;
        return 0;
    }


    if (pdata[length-1] == 0x0d)
    {
        pdata[length-1] = 0;
    }

    if (strncmp(pdata, "ok", strlen("ok")) == 0)
    {
        memset(send_data, 0, 1500);
        //length = 1500;
        sprintf(pdata, "\nok\n");
        send_length = strlen(pdata);
        recv_length = send_data_from_com2(send_data, send_length);

    }

    printf("\n|%s == %d\n", pdata, length);
#endif

    if (length == 1)
    {
        printf("save %x\n", pdata[0]);
        pdata[0] = 0x0d;
        return 0;
    }

    printf("recv|%s--%d\n", pdata, length);

    save_data_into_com2_buffer(pdata, length);
    return 1;
}

static int com2_cmdline_process(void)
{
    char cmdline[1500];
    int length = 0;

    char send_data[1500];
    int send_length;
    int recv_length;

    get_cmd_line_from_com2_buffer(cmdline, &length);
    if (length > 0)
    {
        printf("\n%s = %d\n", cmdline, length);
        if (strncmp(cmdline, "ok", strlen("ok")) == 0)
        {
            memset(send_data, 0, 1500);
            //length = 1500;
            sprintf(send_data, "ok\n");
            send_length = strlen(send_data);
            recv_length = send_data_from_com2(send_data, send_length);
            printf("recv length = %d\n", recv_length);
            set_recv_com2_ok();
        }

        return 1;
    }

    return 0;
}

//这个任务的时间间隔是50ms
static void* com_sim_task_func(void *arg)
{
    char data[1500];
    int length;
    int recvlength;
    int ret;

    printf("com sim task running\n");
    com_sim_task_exit = 1;
    while(com_sim_task_exit)
    {
        memset(data, 0, 1500);
        length = 1500;
        recvlength = tcp_client_recv_data(&tcpCom2Handle, data, &length);
        if (recvlength > 0)
        {
            //printf("data%s=%d\n", data, recvlength);
            com2_data_save_process(data, recvlength);

            while(1)
            {
                ret = com2_cmdline_process();
                if (ret == 0)
                {
                    break;
                }
            }

        }
        else
        {
            usleep(5*1000);
        }


    }


    return NULL;
}

static int init_com_sim_listen_task(void)
{
    pthread_create(&pthread_com_sim_task, NULL, com_sim_task_func, NULL);
    return 1;
}

int init_com2_module(void)
{
    int ret;
    memset(tcpCom2Handle.near_ip, 0, 32);
    memset(tcpCom2Handle.remote_ip, 0, 32);
    sprintf(tcpCom2Handle.remote_ip, "127.0.0.1", strlen("127.0.0.1"));

    tcpCom2Handle.near_port = COM2_TCP_LISTEN_PORT+1;
    tcpCom2Handle.remote_port = COM2_TCP_LISTEN_PORT;

    tcpCom2Handle.socket_fp = -1;

    ret = init_tcp_client_instance(&tcpCom2Handle);
    if (ret)
    {
        tcp_client_connect(&tcpCom2Handle);
        init_com_sim_listen_task();
    }

    return ret;
}


int send_data_from_com2(char *data, int length)
{
    int ret;
    int send_length = length;
    ret = tcp_client_send_data(&tcpCom2Handle, data, &send_length);

    return ret;

}




