#include "sys_include.h"
#include "display_public.h"
#include "framebuf_public.h"
#include "img_public.h"
#include "ft_Font.h"
#include "temperature.h"
#include "networkPublic.h"

static unsigned int test_flag = 0;

static char stb_id[64];
static char mac_id[64];

static int init_hard_device_task(void);
static int fd_ser = -1;
static void exit_timer(void);

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
    sprintf(Handle.remote_ip, "192.168.4.110", strlen("192.168.4.110"));

    init_udp_instance(&Handle);
    length = 32;
    ret = send_data_by_udp_instance(&Handle, data, length);
    fprintf(stderr, "%d\n", ret);
    close_udp_instance(&Handle);
    return 1;
}


int main( int argc, char **argv )
{
    char ch;
    int serfd;
    char data[256];
    char recvdata[256];
    int length;
    int recvlength;
    int i;
    char cmdline[256];
    int ret;

    //调试输出单元
    tracePrintfInit();
    {
        //modifyTraceLevelByMode(SYS_MODE, DEBUG_TRACE);
        //modifyTraceLevelByMode(IMG_MODE, DEBUG_TRACE);
        //modifyTraceLevelByMode(FT_MODE, DEBUG_TRACE);
    }

    printf("begin integrate\n");

    serfd = InitSerialCom(2,115200,'n',1, 8);
    if (serfd == -1)
    {
        printf("COM2 open failure\n");
        return 0;
    }

    i = 0;
    while(1)
    {
        memset(data, 0, 256);
        sprintf(data, "hello\n");
        length = strlen(data);
        SerialSend(serfd, (unsigned char *)data, length);

        memset(recvdata, 0, 256);

        recvlength = serialReceive(serfd, recvdata, 256);
        if (recvlength)
        {
            printf("|%s|%d\n", recvdata, recvlength);
            if (recvlength == 2)
            {
                if (strncmp(recvdata, "ok", strlen("ok")) == 0)
                {
                    printf("COM2 OK\n");
                    break;

                }
            }

        }
        i++;

        if (i > 50)
        {
            printf("COM2 FAILURE\n");
            break;
        }

        usleep(1000*500);
    }

    while(1)
    {
        memset(cmdline, 0, 256);
        scanf("%s", cmdline);

        if (strncmp(cmdline, "getRTCTime", strlen("getRTCTime")) == 0)
        {
            memset(data, 0, 64);
            get_current_time_string(data);
        }
        else if (strncmp(cmdline, "setUSBTest", strlen("setUSBTest")) == 0)
        {
            ret = confirm_usb_running();
            if (ret)
            {
                printf("testUSBSuccess\n");
            }
            else
            {
                printf("testUSBFailure\n");
            }
        }
        else if (strncmp(cmdline, "getSN", strlen("getSN")) == 0)
        {
            memset(data, 0, 64);
            get_pcba_sn(data, 64);
            printf("reportSN|%s\n", data);
        }
        else if (strncmp(cmdline, "getMac", strlen("getMac")) == 0)
        {
            memset(data, 0, 64);
            get_pcba_mac(data, 64);
            printf("reportMAC|%s\n", data);
        }
        else if (strncmp(cmdline, "getMediaBoradTestReport", strlen("getMediaBoradTestReport")) == 0)
        {
            memset(data, 0, 64);
            get_pcba_idx99(data, 64);
            printf("reportMediaBoardTestInfo|%s\n", data);
        }

    }




    #if 0
    char ch;

    //调试输出单元
    tracePrintfInit();
    {
        //modifyTraceLevelByMode(SYS_MODE, DEBUG_TRACE);
        //modifyTraceLevelByMode(IMG_MODE, DEBUG_TRACE);
        //modifyTraceLevelByMode(FT_MODE, DEBUG_TRACE);
    }

    init_display_output_device(FMT_1080P_60);

    init_framebuf_module();

    ft_Font_Init();
    init_temperature_module();
    sync_time_from_rtc();

    prepare_bg();
/*
    system("mkdir -p /media");
    system("mkdir -p /media/tfcard");
    system("mkdir -p /media/usb");
    system("mkdir -p /media/msata");
*/
    init_hard_device_task();

    system("rm /tmp/leftai_ok /tmp/rightai_ok");
    system("/tmp/sample_ai >/tmp/ai.log &");
    display_welcom();

    usleep(3000*1000);
    //ai_display_filter(1);

    while(1)
    {
        #if 1
        if ((access("/tmp/leftai_ok", F_OK) == 0) &&
            (access("/tmp/rightai_ok", F_OK) == 0))
        {
            usleep(1000*1000);
            break;
        }
        #else

        if (access("/tmp/rightai_ok", F_OK) == 0)
        {
            break;
        }

        #endif

        ai_display_filter(0);

        if (get_ai_force_exit())
        {
            break;
        }

        usleep(1000*1000);

    }

    if ((access("/tmp/leftai_ok", F_OK) == 0) &&
        (access("/tmp/rightai_ok", F_OK) == 0))
    {
        set_test_status(audio_ok);
    }

    ai_display_filter(1);
    system("touch /tmp/exit_ai");


   // printf("aaaaaaa\n");

    display_stb_info();

    usleep(500*1000);
   // printf("dddddd\n");



    series_display();
    usleep(500*1000);

    display_msata();
    usleep(500*1000);

    display_tfcard();
    usleep(500*1000);

    display_usb();
    usleep(500*1000);

    while(1)
    {

        if (test_flag & gpio_test)
        {
            display_gpio_test();
            break;
        }
        else
        {
            display_gpio_putdown();
        }


        if (get_force_exit_gpio())
        {
            printf("\nGPIO failure\n");
            break;
        }
        usleep(1000*1000);
    }

    save_test_status();
    exit_timer();


    usleep(500*1000);
    printf("\nvideo play\n");
    display_player();
    //save_test_status();

#if 1
    while(1)
    {
        ch = getchar();
        if (ch == 'q')
        {
            break;
        }
        else if (ch == 'w')
        {
            test_framebuf();
        }
        else if (ch == 'e')
        {
            clearFramebuf();
        }
        else if (ch == 'r')
        {
            Pixel64 *pCanvas;
            int width;
            int height;
            GrPos Pos;
            GrRegion Region;

            decJpgFile("/nfs/wait4open.jpg", &pCanvas, &height, &width);
            Pos.x = Pos.y = 0;
            Region.x = Region.y = 0;
            Region.w = width;
            Region.h = height;

            paint_canvas_2_background(pCanvas, Pos, Region);

            refresh_background_2_device(Pos, Region);
        }
        else if (ch == 't')
        {
            Pixel64 *pCanvas;
            int width;
            int height;
            GrPos Pos;
            GrRegion Region;
            decPngFile("/nfs/ico_dir.png", &pCanvas, &width, &height);

            Pos.x = 100;
            Pos.y = 100;
            Region.x = 0;
            Region.y = 0;
            Region.w = width;
            Region.h = height;

            paint_canvas_2_logic_device(pCanvas, Pos, Region);
            pCanvas = get_logic_canvas();
            move_region_2_display(pCanvas, Pos, Region);

        }
        else if (ch == 'y')
        {
            GrPos Pos;
            Pixel64 FT;

            Pos.x = 137;
            Pos.y = 102;
            FT.RGB.a = 0xFF;
            FT.RGB.r = 0xD7;
            FT.RGB.g = 0xD7;
            FT.RGB.b = 0xD7;

            ft_Font_Str2Disp("hello world", FT, Pos, 40);
        }
        else if (ch == 'u')
        {
            fprintf(stderr, "开始装备测试\n");
            set_test_network(0);
        }
        else if (ch == 'i')
        {
            confirm_network_running(0);
        }
        else if (ch == 'o')
        {
            float temp;

            temp = read_temperature();
            printf("temperature %3.4f\n", temp);
        }
        else if (ch == 'p')
        {
            save_time_into_rtc();
        }
        else if (ch == 'a')
        {
            sync_time_from_rtc();
        }
        else if (ch == 's')
        {
            int value40;
            int value41;
            int value44;

            read_gpio_status(40, &value40);
            read_gpio_status(41, &value41);
            read_gpio_status(44, &value44);
            printf("40 = %d, 41 = %d, 44 = %d\n", value40, value41, value44);
        }
        else if (ch == 'd')
        {
            write_gpio_status(44, 0);
        }
        else if (ch == 'f')
        {
            write_gpio_status(44, 1);
        }
        else if (ch == 'g')
        {
            fd_ser = InitSerialCom(1,115200,'n',1, 8);
        }
        else if (ch == 'h')
        {
            unsigned char data[10];
            sprintf(data, "hello");
            SerialSend(fd_ser, data, 5);
        }
        else if (ch == 'j')
        {
            unsigned char data[10];
            memset(data, 0, 10);
            serialReceive(fd_ser, data, 10);
            printf("data\n", data);
        }
        else if (ch == 'k')
        {
            get_system_time();
        }
        else if (ch == 'l')
        {
            Pixel64 *pcanvas;
            Pixel64 FT;
            int i, j;
            FILE *wfp;
            pcanvas = getFramebuf();

            wfp = fopen("/nfs/screen.raw", "wb");
            for (i = 0; i < 720; i++)
            {
                for (j = 0; j < 1280; j++)
                {

                    FT.RGB.r = pcanvas[j].RGB.r;
                    FT.RGB.b = pcanvas[j].RGB.b;
                    FT.RGB.a = pcanvas[j].RGB.a;
                    FT.RGB.g = pcanvas[j].RGB.g;

                    fwrite(&(FT.RGB.r), 1, 1, wfp);
                    fwrite(&(FT.RGB.g), 1, 1, wfp);
                    fwrite(&(FT.RGB.b), 1, 1, wfp);
                }
                pcanvas += 1280;
            }
            fclose(wfp);
        }

    }
#endif

    close_logic_framebuf_module();
    ft_Font_Destroy();

    close_display_output_device();

    return 0;
    #endif

}

static int bExitTimerTask = 0;

static pthread_t pthread_timer_task = 0;

static void exit_timer(void)
{
    bExitTimerTask = 2;
}

//这个任务的时间间隔是50ms
static void* timer_task_func(void *arg)
{
    bExitTimerTask = 1;

    init_gpio_borad();
    printf("time task func\n");

    while(bExitTimerTask)
    {
        gpio_sharp_filter();
        show_temperature_filter();
        //ai_display_filter(0);
        show_rtc_filter();

        usleep(5*1000);
    }


    return NULL;
}

static int init_hard_device_task(void)
{
    pthread_create(&pthread_timer_task, NULL, timer_task_func, NULL);
    return 1;
}


void set_test_status(unsigned int flag)
{
    test_flag = test_flag|flag;
}

void save_test_status(void)
{
    char cmd[256];

    memset(cmd, 0, 256);
    sprintf(cmd, "bootm idx99=0x%x", test_flag);

    system(cmd);

    printf("\nproductTestFinish|0x%x\n", test_flag);
}

