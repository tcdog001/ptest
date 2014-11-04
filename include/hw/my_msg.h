#ifndef _MY_MSG_H_
#define _MY_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* �Ѿ�ע��Ŀ���ʹ�õĽ��̼�ͨ�Ŷ���ID */
enum
{
    RTC_ID,
    _RTC_ID,

    TMP_ID,
    _TMP_ID,

    AI_ID,
    _AI_ID,

    AV_ENGINE_ID,
    _AV_ENGINE_ID,

	REGISTER_MSG_ID_MAX
};

#define IPC_MSG_DATA_MIN_LENGTH 32
#define IPC_MSG_DATA_MAX_LENGTH 512
#define IPC_CHECK_MSG_QUEUE_INTERVAL 50

typedef struct IPC_MSG_QUEUE_DATA
{
	int msg_type;
	char msg_data[IPC_MSG_DATA_MAX_LENGTH];
}ipcMsgQueueData_t;

/*
    ��ʼ����Ϣ���п��ƺ���
*/
int initMsgQueue(void);

/*
    ������Ϣ����ID,������Ϣ����.
*/
int createMsgQueue(int registerMsgID);

/*
    ɾ����Ϣ����,�����ƶ��߳�ͨѶ���������ԭ���ϲ�Ҫ��.
*/
int deleteMsgQueue(int registerMsgID);

/*
    �����Ϣ����
*/
int clearMsgQueue(int registerMsgID);

/*
    ������Ϣ������Ϣ����id
*/
int sendMsgQueue(int registerMsgID, ipcMsgQueueData_t *pMsg);

int sendMsgQueueWithoutDrop(int registerMsgID, ipcMsgQueueData_t *pMsg);

/*
    �������ȴ���������Ϣ
*/
int recvMsgQueueWaitForever(int registerMsgID, ipcMsgQueueData_t *pMsg);

/*
    �趨�г�ʱ�ȴ�������Ϣ
    int msTimeout; 100ms���ȵĵȴ���ʱʱ���趨;
    �����Ҫ�ȴ�100ms
*/
int recvMsgQueueTimeOut(int registerMsgID, ipcMsgQueueData_t *pMsg, int msTimeout);

#ifdef __cplusplus
}
#endif

#endif


