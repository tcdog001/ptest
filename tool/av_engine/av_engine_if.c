
#include "sys_include.h"
#include "my_msg.h"
#include "av_engine_if.h"


//����Ƶ����ģ��
int open_av_engine(void)
{
    int                 ret;
    ipcMsgQueueData_t   msg;

    memset(msg.msg_data, 0, IPC_MSG_DATA_MAX_LENGTH);
    msg.msg_type = av_engine_open;

    ret = sendMsgQueue(AV_ENGINE_ID, &msg);
    if (ret < 0)
    {
        M_TRACE(WARING_TRACE, AV_MODE, "%d\r\n", ret);
    }

    return ret;
}

//��ʼһ���ļ��Ĳ���
//filename �ļ����ƣ��������ӵȵ�
//pRegion  ��ʵ������
int start_av_engine(char *filename, GrRegion *pRegion)
{
    int                 ret;
    int                 length;
    int                 pos = av_engine_parameter_pos;
    ipcMsgQueueData_t   msg;

    length = strlen(filename);
    if (length > av_engine_parameter_pos)
    {
        M_TRACE(WARING_TRACE, AV_MODE, "filename too long %d\r\n", length);
        return -1;
    }

    memset(msg.msg_data, 0, IPC_MSG_DATA_MAX_LENGTH);
    memcpy(msg.msg_data, filename, length);

    if (pRegion)
    {
        memcpy(msg.msg_data+pos+0,  &(pRegion->x), 4);
        memcpy(msg.msg_data+pos+4,  &(pRegion->y), 4);
        memcpy(msg.msg_data+pos+8,  &(pRegion->w), 4);
        memcpy(msg.msg_data+pos+12, &(pRegion->h), 4);
    }

    msg.msg_type = av_engine_start;

    ret = sendMsgQueue(AV_ENGINE_ID, &msg);
    if (ret < 0)
    {
        M_TRACE(WARING_TRACE, AV_MODE, "%d\r\n", ret);
    }

    return ret;
}

//��ͣ����
int pause_av_engine(void)
{
    int                 ret;
    ipcMsgQueueData_t   msg;

    memset(msg.msg_data, 0, IPC_MSG_DATA_MAX_LENGTH);
    msg.msg_type = av_engine_pause;

    ret = sendMsgQueue(AV_ENGINE_ID, &msg);
    if (ret < 0)
    {
        M_TRACE(WARING_TRACE, AV_MODE, "%d\r\n", ret);
    }

    return ret;
}

//��������
int resume_av_engine(void)
{
    int                 ret;
    ipcMsgQueueData_t   msg;

    memset(msg.msg_data, 0, IPC_MSG_DATA_MAX_LENGTH);
    msg.msg_type = av_engine_resume;

    ret = sendMsgQueue(AV_ENGINE_ID, &msg);
    if (ret < 0)
    {
        M_TRACE(WARING_TRACE, AV_MODE, "%d\r\n", ret);
    }

    return ret;
}


//ֹͣ��������
int stop_av_engine(void)
{
    int                 ret;
    ipcMsgQueueData_t   msg;

    memset(msg.msg_data, 0, IPC_MSG_DATA_MAX_LENGTH);
    msg.msg_type = av_engine_stop;

    ret = sendMsgQueue(AV_ENGINE_ID, &msg);
    if (ret < 0)
    {
        M_TRACE(WARING_TRACE, AV_MODE, "%d\r\n", ret);
    }

    return ret;
}

//�رղ���������
int close_av_engine(void)
{
    int                 ret;
    ipcMsgQueueData_t   msg;

    memset(msg.msg_data, 0, IPC_MSG_DATA_MAX_LENGTH);
    msg.msg_type = av_engine_close;

    ret = sendMsgQueue(AV_ENGINE_ID, &msg);
    if (ret < 0)
    {
        M_TRACE(WARING_TRACE, AV_MODE, "%d\r\n", ret);
    }

    return ret;
}

//������Ƶ����
int switch_aud_av_engine(int index)
{
    int                 ret;
    int                 pos;
    ipcMsgQueueData_t   msg;

    pos = av_engine_parameter_pos;

    memset(msg.msg_data, 0, IPC_MSG_DATA_MAX_LENGTH);
    memcpy(msg.msg_data+pos, &index, 4);
    msg.msg_type = av_engine_aud_switch;

    ret = sendMsgQueue(AV_ENGINE_ID, &msg);
    if (ret < 0)
    {
        M_TRACE(WARING_TRACE, AV_MODE, "%d\r\n", ret);
    }

    return ret;
}


//��ȡ����������Ϣ
int get_info_av_engine(void)
{
    int                 ret;
    ipcMsgQueueData_t   msg;

    memset(msg.msg_data, 0, IPC_MSG_DATA_MAX_LENGTH);
    msg.msg_type = av_engine_info;

    ret = sendMsgQueue(AV_ENGINE_ID, &msg);
    if (ret < 0)
    {
        M_TRACE(WARING_TRACE, AV_MODE, "%d\r\n", ret);
    }

    return ret;
}

//�������źŴ���
int filter_av_engine_msg_process(ipcMsgQueueData_t *pmsg)
{
    int                 ret;

    ret = recvMsgQueueTimeOut(_AV_ENGINE_ID, pmsg, 0);
    if (ret <= 0)
    {
        return 0;
    }
#if 0
    switch (pmsg->msg_type)
    {
    case _av_engine_open:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine open\r\n");
    }
    break;

    case _av_engine_start:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine start\r\n");
    }
    break;

    case _av_engine_pause:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine pause\r\n");
    }
    break;

    case _av_engine_close:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine close\r\n");
    }
    break;

    case _av_engine_info:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine information\r\n");
    }
    break;

    case _av_engine_aud_switch:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "av engine audio channel switch\r\n");
    }
    break;

    default:
    {
        M_TRACE(DEBUG_TRACE, AV_MODE, "default msg type\r\n");
    }
    break;
    }
#endif
    return 1;
}



