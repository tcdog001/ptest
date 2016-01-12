#include "sys_include.h"
#include "networkPublic.h"
#include "rtc_public.h"

typedef struct {

	int year;
	int mouth;
	int day;
	int hour;
	int minute;
	int second;

}date_def;


typedef enum {

    wait_save_rtc,

    wait_save_sn,

    wait_save_mac,

    finish_save_info,

    max_info_status

}set_info_status_en;

static char stb_id[64];
static char mac_id[64];

static int save_rtc_success = 0;
static int save_sn_success  = 0;
static int save_mac_success = 0;

static set_info_status_en stb_info = wait_save_rtc;

static udp_item_def listenHandle;

static char local_ip[64];
static char remote_ip[64];

static int recv_com2_ok = 0;

static int config_test_ip_address(void)
{
    FILE *rfp;
    int length;

    memset(local_ip, 0, 64);
    memset(remote_ip, 0, 64);

    rfp = fopen("/tmp/setip.ini", "rb");
    if (rfp == NULL)
    {
        sprintf(local_ip, "192.168.4.80", strlen("192.168.4.80"));
        sprintf(remote_ip, "192.168.4.110", strlen("192.168.4.110"));
    }

    fgets(local_ip,  64, rfp);
    fgets(remote_ip, 64, rfp);

    length = strlen(local_ip);
    local_ip[length-1]  = 0;

    length = strlen(remote_ip);
    remote_ip[length-1] = 0;

    //printf("%s|\n", local_ip);
    //printf("%s|\n", remote_ip);

    fclose(rfp);

    return 1;
}

static int set_ip_address(void)
{
    char ip_address[32];
    char cmd[256];

    memset(cmd, 0, 256);

    memset(ip_address, 0, 32);
    sprintf(ip_address, "%s", local_ip);

    sprintf(cmd, "ifconfig eth0 %s netmask 255.255.255.0", ip_address);

    printf("%d\n", cmd);

    system(cmd);

    return 1;
}


static int init_listen_socket(void)
{
    listenHandle.multicast = 0;
    memset(listenHandle.near_ip, 0, 32);
    memset(listenHandle.remote_ip, 0, 32);
    listenHandle.near_port = 1006;
    listenHandle.remote_port = 1004;
    sprintf(listenHandle.remote_ip, remote_ip, strlen(remote_ip));

    init_udp_instance(&listenHandle);

    return 0;
}

static int listen_socket_filter(void)
{
    char data[1500];

    char cmd[256];

    int length;
    int recv_length;
    date_def date;

    memset(data, 0, 1500);
	length = 1500;
	recv_length = recv_data_by_udp_instance(&listenHandle, data, &length);
	if (recv_length <= 0 )
	{
		return 0;
	}

    printf("recv length = %d\n", recv_length);
    if (strncmp(data, "setSystemTime", strlen("setSystemTime")) == 0)
    {
        //*pdate = (date_def *) (data+100);
        memcpy(&date, data+100, sizeof(date_def));
        memset(cmd, 0, 256);

        sprintf(cmd, "date -s \"%4d-%02d-%02d %02d:%02d:%02d\"", date.year, date.mouth, date.day, date.hour, date.minute, date.second);
        //printf("%s", cmd);
        system(cmd);

        return 1;
    }

    return 0;
}

static int get_system_time(void)
{
    udp_item_def Handle;
    char data[100];
    int length;
    int ret = 0;

    memset(data, 0, 100);
    sprintf(data, "getSystemTime");

    Handle.multicast = 0;
    memset(Handle.near_ip, 0, 32);
    memset(Handle.remote_ip, 0, 32);
    Handle.near_port = 1000;
    Handle.remote_port = 1002;
    sprintf(Handle.remote_ip, remote_ip, strlen(remote_ip));

    init_udp_instance(&Handle);

    length = 32;
    ret = send_data_by_udp_instance(&Handle, data, length);
    //fprintf(stderr, "%d\n", ret);

    close_udp_instance(&Handle);

    return 1;
}

static int set_system_time_success(void)
{
    udp_item_def Handle;
    char data[100];
    int length;
    int ret = 0;

    memset(data, 0, 100);
    sprintf(data, "setSystemTimeSuccess");

    Handle.multicast = 0;
    memset(Handle.near_ip, 0, 32);
    memset(Handle.remote_ip, 0, 32);
    Handle.near_port = 1000;
    Handle.remote_port = 1002;
    sprintf(Handle.remote_ip, remote_ip, strlen(remote_ip));

    init_udp_instance(&Handle);

    length = 32;
    ret = send_data_by_udp_instance(&Handle, data, length);

    close_udp_instance(&Handle);

    return 1;
}

static int set_media_board_sn_success(void)
{
    udp_item_def Handle;
    char data[100];
    int length;
    int ret = 0;

    memset(data, 0, 100);
    sprintf(data, "setMediaBoardSNSuccess|%s", stb_id);

    Handle.multicast = 0;
    memset(Handle.near_ip, 0, 32);
    memset(Handle.remote_ip, 0, 32);
    Handle.near_port = 1000;
    Handle.remote_port = 1002;
    sprintf(Handle.remote_ip, remote_ip, strlen(remote_ip));

    init_udp_instance(&Handle);

    length = 100;
    ret = send_data_by_udp_instance(&Handle, data, length);

    close_udp_instance(&Handle);

    return 1;
}

static int set_media_board_mac_success(void)
{
    udp_item_def Handle;
    char data[100];
    int length;
    int ret = 0;

    memset(data, 0, 100);
    sprintf(data, "setMediaBoardMACSuccess|%s", mac_id);

    Handle.multicast = 0;
    memset(Handle.near_ip, 0, 32);
    memset(Handle.remote_ip, 0, 32);
    Handle.near_port = 1000;
    Handle.remote_port = 1002;
    sprintf(Handle.remote_ip, remote_ip, strlen(remote_ip));

    init_udp_instance(&Handle);

    length = 100;
    ret = send_data_by_udp_instance(&Handle, data, length);

    close_udp_instance(&Handle);

    return 1;
}

static int set_media_board_info_success(void)
{
    udp_item_def Handle;
    char data[100];
    int length;
    int ret = 0;

    memset(data, 0, 100);
    sprintf(data, "setMediaBoardInfomationSuccess");

    Handle.multicast = 0;
    memset(Handle.near_ip, 0, 32);
    memset(Handle.remote_ip, 0, 32);
    Handle.near_port = 1000;
    Handle.remote_port = 1002;
    sprintf(Handle.remote_ip, remote_ip, strlen(remote_ip));

    init_udp_instance(&Handle);

    length = 100;
    ret = send_data_by_udp_instance(&Handle, data, length);

    close_udp_instance(&Handle);

    return 1;
}


static int init_hard_device_task(void);

static int init_save_info_status(void)
{
    save_rtc_success = 0;
    save_sn_success = 0;
    save_mac_success = 0;

    return 0;
}

static int prepare_stb_info_status(void)
{
    if (save_rtc_success == 0)
    {
        stb_info = wait_save_rtc;
    }

    else if (save_sn_success == 0)
    {
        memset(stb_id, 0, 64);
        stb_info = wait_save_sn;
    }

    else if (save_mac_success == 0)
    {
        memset(mac_id, 0, 64);
        stb_info = wait_save_mac;
    }

    else
    {
        stb_info = finish_save_info;
        //system("touch /tmp/exit");
        //set_media_board_info_success();
        //printf("\nset media board information success\n");
    }

    return 1;
}

static void send_hello_from_seria(void)
{
    char data[32];
    int length;

    memset(data, 0, 32);
    sprintf(data, "hello COM2 send\n");
    length = strlen(data);
    send_data_from_com2(data, length);
}

static void send_hello_by_ser(int serfd)
{

    char data[32];
    int length;

    memset(data, 0, 32);
    sprintf(data, "hello COM2 send\n");
    length = strlen(data);
    SerialSend(serfd, data, length);
}

static void send_ok_by_ser(int serfd)
{
    char data[32];
    int length;

    memset(data, 0, 32);
    sprintf(data, "ok\n");
    length = strlen(data);
    SerialSend(serfd, data, length);

    printf("\nok\n");
}



static int set_stb_info_filter(void)
{
    char mac_id1[64];
    int sn_length;
    int mac_length;
    int ret;

    prepare_stb_info_status();

    if (stb_info == wait_save_rtc)
    {
        get_system_time();
    }
    else if (stb_info == wait_save_sn)
    {
        memset(stb_id, 0, 64);
        while (1)
        {

            printf("input sn:");
            scanf("%s", stb_id);

            sn_length = strlen(stb_id);
            if (sn_length == 21)
            {
                save_sn_success = 1;
                set_pcba_sn(stb_id, sn_length);
                printf("\ninput sn success\n");
                set_media_board_sn_success();
                break;
            }

            memset(stb_id, 0, 64);
        }

    }
    else if (stb_info == wait_save_mac)
    {

        memset(mac_id1, 0, 64);

        while(1)
        {
            printf("input mac:");
            scanf("%s", mac_id1);

            mac_length = strlen(mac_id1);
            if (mac_length == 12)
            {
                break;
            }

            memset(mac_id1, 0, 64);
        }

        {
            mac_id[0] = mac_id1[0];
            mac_id[1] = mac_id1[1];
            mac_id[2] = ':';
            mac_id[3] = mac_id1[2];
            mac_id[4] = mac_id1[3];
            mac_id[5] = ':';
            mac_id[6] = mac_id1[4];
            mac_id[7] = mac_id1[5];
            mac_id[8] = ':';
            mac_id[9] = mac_id1[6];
            mac_id[10] = mac_id1[7];
            mac_id[11] = ':';
            mac_id[12] = mac_id1[8];
            mac_id[13] = mac_id1[9];
            mac_id[14] = ':';
            mac_id[15] = mac_id1[10];
            mac_id[16] = mac_id1[11];

            save_mac_success = 1;
            set_pcba_mac(mac_id, mac_length);
            set_media_board_mac_success();
            printf("\ninput mac success\n");
        }

    }

    if (stb_info == wait_save_rtc)
    {

        ret = listen_socket_filter();
        if (ret)
        {
            char data[64];
            memset(data, 0, 64);

            save_time_into_rtc();
            get_time_info_string(data);

            printf("\nset rtc is success|%s\n", data);
            set_system_time_success();
            save_rtc_success = 1;
        }
    }
    else
    {

        usleep(5*1000);
    }


}


int main( int argc, char **argv )
{
    #if 0
    int ret;
    char ch;
    tcp_client_item_def tcpHandle;

    int serfd = -1;
    //调试输出单元
    tracePrintfInit();
    {
        //modifyTraceLevelByMode(SYS_MODE, DEBUG_TRACE);
        //modifyTraceLevelByMode(IMG_MODE, DEBUG_TRACE);
        //modifyTraceLevelByMode(NET_MODE, DEBUG_TRACE);
    }

    while(1)
    {
        ch  = getchar();

        if (ch == 'q')
        {
            break;
        }
        else if (ch  == 'w')
        {
            serfd = InitSerialCom(2,115200,'n',1, 8);
        }
        else if (ch  == 'e')
        {
            char data[32];
            int length;

            memset(data, 0, 32);
            sprintf(data, "\nhello COM2 send\n");
            length = strlen(data);
            SerialSend(serfd, data, length);
        }
        else if (ch == 'r')
        {
            char data[64];
            int length;

            memset(data, 0, 64);
            length = 64;
            ret = serialReceive(serfd, data, length);
            if (ret)
            {
                printf("data = %s| %d\n", data, ret);
            }
        }

#if 0
    while(1)
    {
        ch = getchar();
        if (ch == 'q')
        {
            break;
        }
        else if (ch == 'w')
        {
            memset(tcpHandle.near_ip, 0, 32);
            memset(tcpHandle.remote_ip, 0, 32);
            memcpy(tcpHandle.remote_ip, "127.0.0.1", strlen("127.0.0.1"));

            tcpHandle.near_port = 5556;
            tcpHandle.remote_port = 5555;
            tcpHandle.socket_fp = -1;

            init_tcp_client_instance(&tcpHandle);
        }
        else if (ch == 'e')
        {
            tcp_client_connect(&tcpHandle);
        }
        else if (ch == 'r')
        {
            char data[64];
            int length;
            sprintf(data, "dddeeee\n");
            length = strlen(data);

            tcp_client_send_data(&tcpHandle, data, &length);
        }
        else if (ch == 't')
        {
            char data[64];
            int length;

            memset(data, 0, 64);
            length = 64;
            ret = tcp_client_recv_data(&tcpHandle, data, &length);
            if (ret)
            {
                printf("%s", data);
            }
        }
        else if (ch == 'y')
        {
            tcp_client_close(&tcpHandle);
        }
        else if (ch == 'u')
        {
            init_com2_module();
        }
        else if (ch == 'i')
        {
            char data[32];
            int length;

            memset(data, 0, 32);
            sprintf(data, "\nhello COM2 send\n");
            length = strlen(data);
            send_data_from_com2(data, length);
        }
        #endif
    }
#endif

#if 1
    int i;
    int serfd;
    char data[64];
    int length;
    int ret;

    //调试输出单元
    tracePrintfInit();
    {
       //modifyTraceLevelByMode(SYS_MODE, DEBUG_TRACE);
       //modifyTraceLevelByMode(IMG_MODE, DEBUG_TRACE);
       //modifyTraceLevelByMode(NET_MODE, DEBUG_TRACE);
    }

    config_test_ip_address();

    set_ip_address();

    init_save_info_status();
    init_listen_socket();

    init_hard_device_task();
#if 1
    while(1)
    {
        if (stb_info != finish_save_info)
        {
            usleep(1000*1000);
        }
        else
        {
            serfd = InitSerialCom(2,115200,'n',1, 8);
            send_hello_by_ser(serfd);

            for (i = 0; i < 60; i++)
            {
                usleep(1000*1000);

                //send_hello_by_ser(serfd);

                memset(data, 0, 64);
                length = 64;
                ret = serialReceive(serfd, data, length);
                if (ret > 1)
                {
                    printf("| %d %02x%02x%02x\n", ret, data[0], data[1], data[2]);
                    if ((ret == 3) &&
                        (data[2] == 0x0d))
                    {
                        data[2] = 0;
                        //if (strncmp(data, "ok", strlen("ok")) == 0)
                        if ((data[0] == 0x6F) &&
                            (data[1] == 0x6B))
                        {
                            send_ok_by_ser(serfd);
                            break;

                        }
                    }
                    if ((ret == 3) &&
                        (data[2] == 0x0a))
                    {
                        data[2] = 0;
                        //if (strncmp(data, "ok", strlen("ok")) == 0)
                        if ((data[0] == 0x6F) &&
                            (data[1] == 0x6B))
                        {
                            send_ok_by_ser(serfd);
                            break;

                        }
                    }
                    else if (ret == 2)
                    {
                        printf("| %d %02x%02x%02x\n", ret, data[0], data[1], data[2]);
                        //if (strncmp(data, "ok", strlen("ok")) == 0)
                        if ((data[0] == 0x6F) &&
                            (data[1] == 0x6B))
                        {
                            send_ok_by_ser(serfd);
                            break;

                        }
                    }

                }
            }

            system("touch /tmp/exit");
            set_media_board_info_success();
            printf("\nset media board information success\n");
            break;
        }
    }
#endif

    while(1)
    {
        //ch = getchar();

        if (access("/tmp/exit", F_OK) == 0)
        {
            system("rm /tmp/exit");
            break;
        }
        else if (access("/tmp/w", F_OK) == 0)
        {
            system("rm /tmp/w");
            init_save_info_status();
        }
        else if (access("/tmp/e", F_OK) == 0)
        {
            system("rm /tmp/e");
            save_rtc_success = 0;
        }
        else if (access("/tmp/r", F_OK) == 0)
        {
            system("rm /tmp/r");
            save_sn_success = 0;
        }
        else if (access("/tmp/t", F_OK) == 0)
        {
            system("rm /tmp/t");
            save_mac_success = 0;
        }
        else if (access("/tmp/y", F_OK) == 0)
        {
            system("rm /tmp/y");
            printf("stb_info = %d\n",  stb_info);
        }

    }
#endif
    return 0;
}

static int bExitTimerTask = 0;

static pthread_t pthread_timer_task = 0;

//这个任务的时间间隔是50ms
static void* timer_task_func(void *arg)
{
    bExitTimerTask = 1;


    while(bExitTimerTask)
    {
        set_stb_info_filter();
    }

    return NULL;
}

static int init_hard_device_task(void)
{
    pthread_create(&pthread_timer_task, NULL, timer_task_func, NULL);
    return 1;
}

void set_recv_com2_ok(void)
{
    recv_com2_ok = 1;
}

