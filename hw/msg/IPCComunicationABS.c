/***************************************************************************
  �ļ�:IPCComunicationABS.c
  ����:Macros.Zhang
  ����:2007-11-20
  �汾:1.0


  ����:���̼���Ϣͨ�Ź��ܳ���

  ����:
****************************************************************************/
#include "sys_include.h"
#include "my_msg.h"

static int msgqueueArray[REGISTER_MSG_ID_MAX];
static key_t baseKey = 0x8880;

static int bInit = 0;

/*
    ��ʼ����Ϣ���п��ƺ���
*/
int initMsgQueue(void)
{
    int i;

    if (bInit)
    {
        return 0;
    }

    bInit = 1;
    for (i = 0; i < REGISTER_MSG_ID_MAX; i++)
    {
        msgqueueArray[i] = -1;
    }

    return 0;
}

/*
    ������Ϣ����ID,������Ϣ����.
*/
int createMsgQueue(int registerMsgID)
{
    key_t key;
    int msgqueue_id;
    ipcMsgQueueData_t msg;
    int ret;

    if (registerMsgID >= REGISTER_MSG_ID_MAX)
    {
        return -2;
    }

    initMsgQueue();

    key = baseKey+registerMsgID;
    if (msgqueueArray[registerMsgID] == -1)
    {
        if ((msgqueue_id = msgget(key,IPC_CREAT | 0660 )) == -1 )
        {
            fprintf(stderr, "create msg queue is failed\r\n");
            return -1;
        }

        msgqueueArray[registerMsgID] = msgqueue_id;

        //����msg��������������Ϣ
        while(1)
        {
            ret = recvMsgQueueTimeOut(registerMsgID, &msg, 100);
            if (ret < 0)
            {
                break;
            }
        }
        return msgqueue_id;
    }

    return -3;

}

/*
    ɾ����Ϣ����,�����ƶ��߳�ͨѶ���������ԭ���ϲ�Ҫ��.
*/
int deleteMsgQueue(int registerMsgID)
{
    if (registerMsgID >= REGISTER_MSG_ID_MAX)
    {
        return -2;
    }

    if (msgqueueArray[registerMsgID] == -1)
    {
        return -3;
    }

    msgctl(msgqueueArray[registerMsgID], IPC_RMID, NULL);/*ɾ������*/

    return 0;
}

/*
    �����Ϣ����
*/
int clearMsgQueue(int registerMsgID)
{
    struct msqid_ds bufQidDs;

    ipcMsgQueueData_t Msg;
    int ret;

    if (registerMsgID >= REGISTER_MSG_ID_MAX)
    {
        return -2;
    }

    if (msgqueueArray[registerMsgID] == -1)
    {
        return -3;
    }

    if( msgctl( msgqueueArray[registerMsgID], IPC_STAT, &bufQidDs) == -1)
    {
        return(-1);
    }

    //printf("msgNum = %d\n", bufQidDs.msg_qnum);
    if (bufQidDs.msg_qnum > 0)
    {
        while(bufQidDs.msg_qnum)
        {

            ret = msgrcv(msgqueueArray[registerMsgID],
                                &Msg,
                                IPC_MSG_DATA_MAX_LENGTH,
                                0,
                                IPC_NOWAIT);

            if (ret == -1)
            {
                break;
            }
        }
    }

    return 0;
}

/*
    ������Ϣ������Ϣ����id
*/
int sendMsgQueue(int registerMsgID, ipcMsgQueueData_t *pMsg)
{
    int ret;
    struct msqid_ds msg_info;

    if (registerMsgID >= REGISTER_MSG_ID_MAX)
    {
        return -2;
    }

    if (msgqueueArray[registerMsgID] == -1)
    {
        return -3;
    }

    if (pMsg == NULL)
    {
        return -4;
    }

    msgctl(msgqueueArray[registerMsgID], IPC_STAT, &msg_info);
    if (msg_info.msg_qnum > 0)
    {
        //fprintf(stderr, "drop the msg %ld, %x\n", msg_info.msg_qnum, pMsg->msg_type);
        ret = -5;
    }
    else
    {
        //fprintf(stderr, "msg->type = %x\n", pMsg->msg_type);
        ret = msgsnd(msgqueueArray[registerMsgID], pMsg, IPC_MSG_DATA_MAX_LENGTH-4, 0);
    }

    return ret;
}

int sendMsgQueueWithoutDrop(int registerMsgID, ipcMsgQueueData_t *pMsg)
{
    int ret;

    if (registerMsgID >= REGISTER_MSG_ID_MAX)
    {
        return -2;
    }

    if (msgqueueArray[registerMsgID] == -1)
    {
        return -3;
    }

    if (pMsg == NULL)
    {
        return -4;
    }

    ret = msgsnd(msgqueueArray[registerMsgID], pMsg, IPC_MSG_DATA_MAX_LENGTH-4, 0);

    return ret;
}


/*
    �������ȴ���������Ϣ
*/
int recvMsgQueueWaitForever(int registerMsgID, ipcMsgQueueData_t *pMsg)
{
    int ret;
    if (registerMsgID >= REGISTER_MSG_ID_MAX)
    {
        return -2;
    }

    if (msgqueueArray[registerMsgID] == -1)
    {
        return -3;
    }

    if (pMsg == NULL)
    {
        return -4;
    }

    ret = msgrcv(msgqueueArray[registerMsgID],
                    pMsg,
                    IPC_MSG_DATA_MAX_LENGTH,
                    0,
                    0);

    return ret;
}

/*
    �趨�г�ʱ�ȴ�������Ϣ
    int msTimeout; 50ms���ȵĵȴ���ʱʱ���趨;
    �����Ҫ�ȴ�50ms�����趨50
*/
int recvMsgQueueTimeOut(int registerMsgID, ipcMsgQueueData_t *pMsg, int msTimeout)
{
    int ret = 0;
    int Time = 0;
    if (registerMsgID >= REGISTER_MSG_ID_MAX)
    {
        return -2;
    }

    if (msgqueueArray[registerMsgID] == -1)
    {
        return -3;
    }

    if (pMsg == NULL)
    {
        return -4;
    }

    do
    {
        ret = msgrcv(msgqueueArray[registerMsgID],
                        pMsg,
                        IPC_MSG_DATA_MAX_LENGTH,
                        0,
                        IPC_NOWAIT);
        if (ret < 0)
        {
//            printf("no msg");
        }
        else
        {
            break;
        }


        if (Time >= msTimeout)
        {
            ret = -1;
            break;
        }

        Time += IPC_CHECK_MSG_QUEUE_INTERVAL;
        usleep(IPC_CHECK_MSG_QUEUE_INTERVAL*1000);
    }while(1);

    return ret;
}


