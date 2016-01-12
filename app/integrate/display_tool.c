#include "sys_include.h"
#include "img_public.h"
#include "temperature.h"

void prepare_bg(void)
{
    Pixel64 *pCanvas;
    int width;
    int height;
    GrPos Pos;
    GrRegion Region;

    decJpgFile("/tmp/res/bg_product.jpg", &pCanvas, &height, &width);
    Pos.x = Pos.y = 0;
    Region.x = Region.y = 0;
    Region.w = width;
    Region.h = height;

    paint_canvas_2_background(pCanvas, Pos, Region);

    refresh_background_2_device(Pos, Region);

    return ;
}

static struct timeval record_tm;
static struct timeval rtc_record_tm;

static struct timeval ai_record_tm;
static struct timeval ai_finish_tm;
static int bquit = 0;

void init_temperature_module(void)
{
    gettimeofday(&(record_tm), NULL);
    gettimeofday(&(rtc_record_tm), NULL);
    gettimeofday(&(ai_record_tm), NULL);
    gettimeofday(&(ai_finish_tm), NULL);
}

void show_temperature_filter(void)
{
    static struct timeval cur_tm;
    unsigned int distms = 0;
    int ret;
    float temp;
    char data[64];
    GrPos Pos;
    static GrRegion Region = {0, 0, 500, 40};
    Pixel64 FT;
    static int tmperature_cnt = 0;

    /*
    if (tmperature_cnt > 3)
    {
        return ;
    }
    */

    gettimeofday(&cur_tm, NULL);

    distms = ((cur_tm.tv_sec*1000+(cur_tm.tv_usec)/1000)-(record_tm.tv_sec*1000+(record_tm.tv_usec)/1000));
    if (distms >= 1*1000)
    {
        memset(data, 0, 64);
        temp = read_temperature();
        if ((temp <= 24) ||
            (temp >= 60))
        {
            FT.RGB.a = 255;
            FT.RGB.r = 255;
            FT.RGB.g = 0;
            FT.RGB.b = 0;

            set_test_status(temperature_failure);
            if (tmperature_cnt == 3)
            {
                printf("\ntemperature failure\n");
            }
            tmperature_cnt++;
        }
        else
        {
            FT.RGB.a = 255;
            FT.RGB.r = 255;
            FT.RGB.g = 255;
            FT.RGB.b = 255;
            if (tmperature_cnt == 3)
            {
                printf("\ntemperature success\n");
            }
            tmperature_cnt ++;
        }

        if (tmperature_cnt > 4)
        {
            tmperature_cnt = 4;
        }

        if (tmperature_cnt == 3)
        {
            printf("temperature %3.4fC\n", temp);
        }

        sprintf(data, "temperature %3.4fC", temp);

        Pos.x = 590;
        Pos.y = 50;

        Region.x = Region.y = 0;
        Region.w = 400;
        Region.h = 40;
        refresh_background_2_device(Pos, Region);
        //printf("44444444444444444444444\n");
        ft_Font_Str2Disp_return_region(data,
            FT,
            Pos,
            35,
            &Region);

        //printf("55555555555555555555555\n");
        record_tm = cur_tm;
    }
}

void show_rtc_filter(void)
{
    static struct timeval cur_tm;
    unsigned int distms = 0;
    int ret;
    float temp;
    char data[64];
    GrPos Pos;
    static GrRegion Region = {0, 0, 500, 40};
    Pixel64 FT;
    static int rtc_cnt = 0;

    gettimeofday(&cur_tm, NULL);


    /*
    if (rtc_cnt > 3)
    {
        return ;
    }
    */

    distms = ((cur_tm.tv_sec*1000+(cur_tm.tv_usec)/1000)-(rtc_record_tm.tv_sec*1000+(rtc_record_tm.tv_usec)/1000));
    if (distms >= 2*1000)
    {
        //printf("11111111\n");
        rtc_cnt ++;
        if (rtc_cnt > 4)
        {
            rtc_cnt = 4;
        }

        ret = sync_time_from_rtc();
        if (ret == 0)
        {
            FT.RGB.a = 255;
            FT.RGB.r = 255;
            FT.RGB.g = 0;
            FT.RGB.b = 0;
            if (rtc_cnt == 3)
            {
                printf("\nrtc failure\n");
            }
            set_test_status(rtc_failure);
        }
        else
        {
            FT.RGB.a = 255;
            FT.RGB.r = 255;
            FT.RGB.g = 255;
            FT.RGB.b = 255;
        }

        memset(data, 0, 64);
        ret = get_time_info_string(data);
        if (ret == 0)
        {
            FT.RGB.a = 255;
            FT.RGB.r = 255;
            FT.RGB.g = 0;
            FT.RGB.b = 0;
            if (rtc_cnt == 3)
            {
                printf("\nrtc failure\n");
            }
            set_test_status(rtc_failure);
        }
        else
        {
            FT.RGB.a = 255;
            FT.RGB.r = 255;
            FT.RGB.g = 255;
            FT.RGB.b = 255;
            if (rtc_cnt == 3)
            {
                printf("\nrtc ok|%s\n", data);
            }
        }

        Pos.x = 590;
        Pos.y = 90;

        Region.x = Region.y = 0;
        Region.w = 400;
        Region.h = 40;
        refresh_background_2_device(Pos, Region);
        ft_Font_Str2Disp_return_region(data,
            FT,
            Pos,
            35,
            &Region);

        rtc_record_tm = cur_tm;
    }
}

int get_ai_force_exit(void)
{
    return bquit;
}

void ai_display_filter(int flag)
{
    static struct timeval cur_tm;
    unsigned int distms = 0;
    int ret;
    float temp;
    char data[32];
    GrPos Pos;
    static GrRegion Region = {0, 0, 500, 40};
    Pixel64 FT;

    static int line_ok_disp = 0;
    static int mic_ok_disp = 0;

    if (bquit)
    {
        return ;
    }

    gettimeofday(&cur_tm, NULL);

    distms = ((cur_tm.tv_sec*1000+(cur_tm.tv_usec)/1000)-(ai_finish_tm.tv_sec*1000+(ai_finish_tm.tv_usec)/1000));
    if (distms >= 60*1000)
    {
        bquit = 1;

        if (access("/tmp/rightai_ok", F_OK) == 0)
        {
            memset(data, 0, 32);
            sprintf(data, "mic输入ok");
            Pos.x = 590;
            Pos.y = 130;
            FT.RGB.a = 255;
            FT.RGB.r = 255;
            FT.RGB.g = 255;
            FT.RGB.b = 255;
            Region.x = Region.y = 0;
            Region.w = 240;
            Region.h = 40;
            if (mic_ok_disp == 0)
            {
                mic_ok_disp = 1;
                printf("\nmic success\n");

            refresh_background_2_device(Pos, Region);
            ft_Font_Str2Disp_return_region(data,
                FT,
                Pos,
                35,
                &Region);
            }
        }
        else
        {
            printf("\nmic failure\n");
        }

        if (access("/tmp/leftai_ok", F_OK) == 0)
        {
            memset(data, 0, 32);
            sprintf(data, "LINE输入ok");
            Pos.x = 840;
            Pos.y = 130;
            FT.RGB.a = 255;
            FT.RGB.r = 255;
            FT.RGB.g = 255;
            FT.RGB.b = 255;
            Region.x = Region.y = 0;
            Region.w = 200;
            Region.h = 40;

            if (line_ok_disp == 0)
            {
                printf("\nline success\n");
                refresh_background_2_device(Pos, Region);
                ft_Font_Str2Disp_return_region(data,
                    FT,
                    Pos,
                    35,
                    &Region);
                line_ok_disp = 1;
            }
        }
        else
        {
            printf("\nline failure\n");
        }

        return ;
    }


    distms = ((cur_tm.tv_sec*1000+(cur_tm.tv_usec)/1000)-(ai_record_tm.tv_sec*1000+(ai_record_tm.tv_usec)/1000));
    if (flag == 1)
    {
        distms == 6000;
    }

    if (distms >= 5*1000)
    {
        if (access("/tmp/rightai_ok", F_OK) == 0)
        {
            memset(data, 0, 32);
            sprintf(data, "mic输入ok");
            Pos.x = 590;
            Pos.y = 130;
            FT.RGB.a = 255;
            FT.RGB.r = 255;
            FT.RGB.g = 255;
            FT.RGB.b = 255;
            Region.x = Region.y = 0;
            Region.w = 240;
            Region.h = 40;

            if (mic_ok_disp == 0)
            {
                mic_ok_disp = 1;

                printf("\nmic success\n");
                refresh_background_2_device(Pos, Region);
                ft_Font_Str2Disp_return_region(data,
                    FT,
                    Pos,
                    35,
                    &Region);
            }
        }

        if (access("/tmp/leftai_ok", F_OK) == 0)
        {
            memset(data, 0, 32);
            sprintf(data, "LINE输入ok");
            Pos.x = 840;
            Pos.y = 130;
            FT.RGB.a = 255;
            FT.RGB.r = 255;
            FT.RGB.g = 255;
            FT.RGB.b = 255;
            Region.x = Region.y = 0;
            Region.w = 200;
            Region.h = 40;

            if (line_ok_disp == 0)
            {
                line_ok_disp = 1;
                printf("\nline success\n");
                refresh_background_2_device(Pos, Region);
                ft_Font_Str2Disp_return_region(data,
                    FT,
                    Pos,
                    35,
                    &Region);
            }
        }

        ai_record_tm = cur_tm;
    }
}

void display_welcom(void)
{
    Pixel64 FT;

    GrPos Pos;
    GrRegion Region;
    int ret;
    char data[100];


    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 255;
    FT.RGB.b = 255;

    Pos.x = 520;
    Pos.y = 225;
    display_character_into_screen(WELLCOM_STR,
        FT,
        &Pos, &Region);

    Pos.x = 590;
    Pos.y = 130;
    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 0;
    FT.RGB.b = 0;
    Region.x = Region.y = 0;
    Region.w = 400;
    Region.h = 40;

    //refresh_background_2_device(Pos, Region);
    ft_Font_Str2Disp_return_region("请输入mic",
        FT,
        Pos,
        35,
        &Region);

    Pos.x = 840;
    Pos.y = 130;
    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 0;
    FT.RGB.b = 0;
    Region.x = Region.y = 0;
    Region.w = 200;
    Region.h = 40;

    ft_Font_Str2Disp_return_region("输入linein",
        FT,
        Pos,
        35,
        &Region);

}
static int fd_ser = -1;

void series_display(void)
{
    GrPos Pos;
    GrRegion Region;
    int ret;

    Pixel64 FT;
    unsigned char data[100];

    memset(data, 0, 100);
    sprintf(data, "hello COM2 send");

    fd_ser = InitSerialCom(2, 115200, 'n', 1, 8);
    SerialSend(fd_ser, data, 5);

    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 255;
    FT.RGB.b = 255;

    Pos.x = 520;
    Pos.y = 265;

    display_character_into_screen(CONFIRM_SERIES,
        FT,
        &Pos, &Region);

//    getchar();
    return ;
}

void display_msata(void)
{
    Pixel64 FT;

    GrPos Pos;
    GrRegion Region;
    int ret;

    ret = 1;
    Pos.x = 520;
    Pos.y = 305;
    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 255;
    FT.RGB.b = 255;

    ret = confirm_msata_running();
    if (ret)
    {
        display_character_into_screen(MSATA_OK,
            FT,
            &Pos, &Region);
    }
    else
    {
        FT.RGB.a = 255;
        FT.RGB.r = 255;
        FT.RGB.g = 0;
        FT.RGB.b = 0;

        display_character_into_screen(MSATA_FAILED,
            FT,
            &Pos, &Region);
    }

//    getchar();
}

void display_tfcard(void)
{
    Pixel64 FT;

    GrPos Pos;
    GrRegion Region;
    int ret;

    ret = confirm_tfcard_running();
    Pos.x = 520;
    Pos.y = 345;
    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 255;
    FT.RGB.b = 255;

    //ret = confirm_tfcard_running();

    if (ret)
    {
        display_character_into_screen(TFCARD_OK,
            FT,
            &Pos, &Region);
    }
    else
    {

        FT.RGB.a = 255;
        FT.RGB.r = 255;
        FT.RGB.g = 0;
        FT.RGB.b = 0;

        display_character_into_screen(TFCARD_FAILED,
            FT,
            &Pos, &Region);
    }

//    getchar();
}

void display_usb(void)
{
    Pixel64 FT;

    GrPos Pos;
    GrRegion Region;
    int ret;

    ret = confirm_usb_running();
    Pos.x = 520;
    Pos.y = 385;
    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 255;
    FT.RGB.b = 255;

    if (ret)
    {
        display_character_into_screen(USB_OK,
            FT,
            &Pos, &Region);
    }
    else
    {

        FT.RGB.a = 255;
        FT.RGB.r = 255;
        FT.RGB.g = 0;
        FT.RGB.b = 0;

        display_character_into_screen(USB_FAILED,
            FT,
            &Pos, &Region);
    }

//    getchar();
}


void display_info(void)
{
    Pixel64 FT;

    GrPos Pos;
    GrRegion Region;
    int ret;

    int id_length;
    int mac_length;

    char stb_id[64];
    char mac_id[64];
    char mac_id1[64];

    Pos.x = 520;
    Pos.y = 425;
    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 255;
    FT.RGB.b = 255;

    memset(stb_id, 0, 64);
    memset(mac_id, 0, 64);
    memset(mac_id1, 0, 64);
    display_character_into_screen(INFO_INPUT,
        FT,
        &Pos, &Region);

    while (1)
    {
        printf("input pcba sn:");
        scanf("%s", stb_id);
        printf("input pcba mac:");
        scanf("%s", mac_id);

        id_length = strlen(stb_id);
        mac_length = strlen(mac_id);

        M_TRACE(DEBUG_TRACE, SYS_MODE, "id = %d, mac = %d\n", id_length, mac_length);
        if ((id_length == 24) &&
            (mac_length == 12))
        {

            mac_id1[0] = mac_id[0];
            mac_id1[1] = mac_id[1];
            mac_id1[2] = ':';
            mac_id1[3] = mac_id[2];
            mac_id1[4] = mac_id[3];
            mac_id1[5] = ':';
            mac_id1[6] = mac_id[4];
            mac_id1[7] = mac_id[5];
            mac_id1[8] = ':';
            mac_id1[9] = mac_id[6];
            mac_id1[10] = mac_id[7];
            mac_id1[11] = ':';
            mac_id1[12] = mac_id[8];
            mac_id1[13] = mac_id[9];
            mac_id1[14] = ':';
            mac_id1[15] = mac_id[10];
            mac_id1[16] = mac_id[11];

            break;
        }

        memset(stb_id, 0, 64);
        memset(mac_id, 0, 64);
        memset(mac_id1, 0, 64);
    }


    /* 刘工bootm 怎么用*/
    set_pcba_mac(mac_id1);
    set_pcba_sn(stb_id);
}

void display_stb_info(void)
{
    char stb_id[64];
    char mac_id[64];

    Pixel64 FT;

    GrPos Pos;
    GrRegion Region;
    int ret;
    char data[100];

    //get stbinfo
    memset(stb_id, 0, 64);
    memset(mac_id, 0, 64);

    get_pcba_mac(mac_id, 64);
    get_pcba_sn(stb_id, 64);
    //sprintf(stb_id, "0100000000000001");
    //sprintf(mac_id, "01:23:45:67:89:00");

    memset(data, 0, 100);
    Pos.x = 50;
    Pos.y = 170;

    if (strlen(stb_id) < 21)
    {
        FT.RGB.a = 255;
        FT.RGB.r = 255;
        FT.RGB.g = 0;
        FT.RGB.b = 0;

        sprintf(data, "SN:NULL");

        printf("\nsn read failure\n");
    }
    else
    {
        FT.RGB.a = 255;
        FT.RGB.r = 255;
        FT.RGB.g = 255;
        FT.RGB.b = 255;

        sprintf(data, "SN:%s", stb_id);

        printf("\nsn read ok |%s\n", stb_id);
    }

    Region.x = Region.y = 0;
    Region.w = 500;
    Region.h = 32;
    refresh_background_2_device(Pos, Region);
    ft_Font_Str2Disp_return_region(data,
            FT,
            Pos,
            35,
            &Region);

    memset(data, 0, 100);

    if (strlen(mac_id) < 12)
    {
        FT.RGB.a = 255;
        FT.RGB.r = 255;
        FT.RGB.g = 0;
        FT.RGB.b = 0;

        sprintf(data, "MAC:NULL");

        printf("\nmac read failure\n");
    }
    else
    {
        FT.RGB.a = 255;
        FT.RGB.r = 255;
        FT.RGB.g = 255;
        FT.RGB.b = 255;

        sprintf(data, "MAC:%s", mac_id);

        printf("\nmac read ok |%s\n", mac_id);

    }
    Pos.x = 50;
    Pos.y = 220;

    Region.x = Region.y = 0;
    Region.w = 400;
    Region.h = 35;
    refresh_background_2_device(Pos, Region);

    //sprintf(data, "MAC:%s", mac_id);
    ft_Font_Str2Disp_return_region(data,
            FT,
            Pos,
            35,
            &Region);

}

void display_player(void)
{
    Pixel64 FT;

    GrPos Pos;
    GrRegion Region;
    Pos.x = 520;
    Pos.y = 465;
    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 255;
    FT.RGB.b = 255;

    display_character_into_screen(VIDEO_CONFIRM,
        FT,
        &Pos, &Region);
    setFramebufAlpha((unsigned char ) 128);
    system("/tmp/player /tmp/160001.MPG >/tmp/play.log");

}

void display_gpio_putdown(void)
{
    Pixel64 FT;

    GrPos Pos;
    GrRegion Region;
    Pos.x = 520;
    Pos.y = 425;
    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 0;
    FT.RGB.b = 0;

    Region.x = Region.y = 0;
    Region.w = 400;
    Region.h = 35;
    refresh_background_2_device(Pos, Region);

    display_character_into_screen(GPIO_PUTDOWN,
        FT,
        &Pos, &Region);

}

void display_gpio_test(void)
{
    Pixel64 FT;

    GrPos Pos;
    GrRegion Region;
    Pos.x = 520;
    Pos.y = 425;
    FT.RGB.a = 255;
    FT.RGB.r = 255;
    FT.RGB.g = 255;
    FT.RGB.b = 255;

    Region.x = Region.y = 0;
    Region.w = 400;
    Region.h = 35;
    refresh_background_2_device(Pos, Region);

    display_character_into_screen(GPIO_TEST,
        FT,
        &Pos, &Region);

}



