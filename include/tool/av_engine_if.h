
#ifndef _AV_ENGINE_IF_H_
#define _AV_ENGINE_IF_H_
#include "my_msg.h"
#ifdef __cplusplus
extern "C" {
#endif
#define av_engine_parameter_pos 256

typedef enum {

    /*
        播放器控制部分信令消息代码
    */
    av_engine_idle = 0,

    av_engine_open,
    av_engine_start,
    av_engine_pause,
    av_engine_stop,
    av_engine_close,
    av_engine_aud_switch,
    av_engine_info,
    av_engine_resume,

    /*
        播放器播放部分响应信令消息代码
    */
    _av_engine_open = 101,
    _av_engine_start,
    _av_engine_pause,
    _av_engine_stop,
    _av_engine_close,
    _av_engine_aud_switch,
    _av_engine_info,
    _av_engine_resume,

    max_av_engine_msg

}av_engine_msg_type;

int open_av_engine(void);
int start_av_engine(char * filename, GrRegion * pRegion);
int pause_av_engine(void);
//继续播放
int resume_av_engine(void);
int stop_av_engine(void);
int close_av_engine(void);

//交互音频音轨
int switch_aud_av_engine(int index);

//播放器信号处理
int filter_av_engine_msg_process(ipcMsgQueueData_t *pmsg);


#ifdef __cplusplus
}
#endif

#endif

