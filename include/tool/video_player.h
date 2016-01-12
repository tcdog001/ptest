
#ifndef _VID_PLAYER_H_
#define _VID_PLAYER_H_

#ifdef __cplusplus
extern "C" {
#endif

//��ʼ����Ƶ����������av_engine
int open_video_player_module(void);
//�ر���Ƶ������
int close_video_player_module(void);
int filter_video_player_process(void);

//��ʼ���ļ�����
int start_single_file(char *filename, GrRegion *pRegion);
int stop_single_file(void);
int audio_channle_switch_video_player(void);
int pause_video_player(void);
int resume_video_player(void);

#ifdef __cplusplus
}
#endif

#endif

