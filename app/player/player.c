#include "sys_include.h"
#include "my_msg.h"
#include "av_engine_if.h"
#include "video_player.h"
static int init_time_task_module(void);

int main(int argc, char **argv)
{
    int ret;
    fprintf(stderr, "hello world \r\n");

    tracePrintfInit();
    {
        modifyTraceLevelByMode(SYS_MODE, DEBUG_TRACE);
        modifyTraceLevelByMode(AV_MODE,  DEBUG_TRACE);
    }


    initMsgQueue();
    createMsgQueue(AV_ENGINE_ID);
    createMsgQueue(_AV_ENGINE_ID);

    init_time_task_module();
    while(1)
    {
        char ch;
        ch = getchar();
        if (ch == 'q')
        {
            break;
        }

        else if (ch == 'w')
        {
            start_single_file("/mnt/sd/160001.MPG", NULL);
        }
        else if (ch == 'e')
        {
            stop_single_file();
        }

        else if (ch == 'r')
        {
            system("/nfs/sample_localplay /mnt/sd/01000001.ts &");
        }

        else if (ch == 't')
        {
            pause_video_player();
        }
        else if (ch == 'y')
        {
            resume_video_player();
        }

    }

    //close_av_engine();

    fprintf(stderr, "byebye\r\n");

    return 1;
}


static int bExitTimerTask = 0;

static pthread_t pthread_timer_task = 0;

//这个任务的时间间隔是50ms
static void* timer_task_func(void *arg)
{
    open_video_player_module();

    while(bExitTimerTask)
    {
        filter_video_player_process();

        usleep(5*1000);
    }

}

static int init_time_task_module(void)
{
    if (bExitTimerTask == 1)
    {
        M_TRACE(WARING_TRACE, SYS_MODE, "init hard device task failure\r\n");
        return 0;
    }

    pthread_create(&pthread_timer_task, NULL, timer_task_func, NULL);

    bExitTimerTask = 1;
    return 1;
}



