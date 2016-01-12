
#include "sys_include.h"
#include "av_engine_if.h"

#define VID_WIN_W 1280
#define VID_WIN_H 720

#define VID_FILE_NAME_LEN 256

//播放方法的状态定义
typedef enum {

    single_file_mode,   //单文件播放
    dirctory_mode,      //目录方式播放
    playlist_mode,      //播放列表方式

    max_play_mode       //更多的播放方式

}play_mode_status;


//播放文件的运行状态
typedef enum {

    player_idle,

    player_start,

    player_running,

    player_stop,

    player_status_max

}play_running_status;

typedef struct {

    int                 bEnable;
    char                filename[VID_FILE_NAME_LEN];
    GrRegion            Region;

    play_mode_status    mode;
    play_running_status status;

}video_player_struct;

static video_player_struct video_player;

static int config_video_player_window_region(GrRegion *pconfig_region, GrRegion *pplayer_win_region)
{
    if (pconfig_region == NULL)
    {
        pplayer_win_region->x = pplayer_win_region->y = 0;
        pplayer_win_region->w = VID_WIN_W;
        pplayer_win_region->h = VID_WIN_H;
        return 1;
    }

    pplayer_win_region->x = pconfig_region->x;
    pplayer_win_region->y = pconfig_region->y;
    pplayer_win_region->w = pconfig_region->w;
    pplayer_win_region->h = pconfig_region->h;

    return 2;
}

//初始化视频播放器，打开av_engine
int open_video_player_module(void)
{

    video_player.bEnable = 0;
    video_player.Region.x = video_player.Region.y = 0;
    video_player.Region.h = 0;
    video_player.Region.w = 0;

    video_player.mode = single_file_mode;
    video_player.status = player_idle;

    memset(video_player.filename, 0, VID_FILE_NAME_LEN);

    open_av_engine();

    return 1;
}

//关闭视频播放器
int close_video_player_module(void)
{
    close_av_engine();
    return 1;
}

int filter_video_player_process(void)
{
    int                 ret;
    ipcMsgQueueData_t   msg;
    if (video_player.bEnable == 0)
    {
        return 0;
    }

    ret = filter_av_engine_msg_process(&msg);
    if (ret == 0)
    {
        return 0;
    }

    switch (msg.msg_type)
    {
    case _av_engine_open:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine opened\r\n");
        //video_player.status = player_running;
    }
    break;

    case _av_engine_close:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine closed\r\n");
    }
    break;

    case _av_engine_start:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine started\r\n");

        video_player.status = player_running;
        if (video_player.mode == single_file_mode)
        {
            M_TRACE(DEBUG_TRACE, AV_MODE, "single file mode\r\n");

        }
    }
    break;

    case _av_engine_stop:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine stoped\r\n");
        video_player.status = player_idle;
        if (video_player.mode == single_file_mode)
        {
            M_TRACE(DEBUG_TRACE, AV_MODE, "single file mode\r\n");
        }
    }
    break;

    case _av_engine_pause:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine paused\r\n");
    }
    break;

    case _av_engine_aud_switch:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine audio channel switched\r\n");
    }
    break;

    case _av_engine_info:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine stream info\r\n");
    }
    break;

    }

    return 1;
}

//开始单文件播放
int start_single_file(char *filename, GrRegion *pRegion)
{
    if (video_player.bEnable)
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "video player is running, must stop first\r\n");
        return 0;
    }

    config_video_player_window_region(pRegion, &(video_player.Region));

    memset(video_player.filename, 0, VID_FILE_NAME_LEN);
    memcpy(video_player.filename, filename, strlen(filename));

    video_player.mode = single_file_mode;
    video_player.status = player_start;

    video_player.bEnable = 1;
    start_av_engine(video_player.filename, &(video_player.Region));

    return 1;
}

int stop_single_file(void)
{
    if (video_player.bEnable == 0)
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "video player is not running\r\n");
        return 0;
    }

    stop_av_engine();
    video_player.bEnable = 0;

    return 1;
}

int audio_channle_switch_video_player(void)
{
    if (video_player.bEnable == 0)
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "video player is not running\r\n");
        return 0;
    }

    switch_aud_av_engine(-1);

    return 1;
}

int pause_video_player(void)
{
    if (video_player.bEnable == 0)
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "video player is not running\r\n");
        return 0;
    }

    pause_av_engine();

    return 1;
}

int resume_video_player(void)
{
    if (video_player.bEnable == 0)
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "video player is not running\r\n");
        return 0;
    }

    resume_av_engine();

    return 1;
}

