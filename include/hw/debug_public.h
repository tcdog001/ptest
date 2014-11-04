/*! @file
********************************************************************************
<PRE>
ģ����       : �������ģ�鶨��ͷ�ļ�
�ļ���       : debugPublic.h
����ļ�     : ��
�ļ�ʵ�ֹ��� : ʵ�ְ���ģ�飬���յȼ�����Ϣ��ӡ�������
����         : macros.zhang
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         : ��
--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾     �޸���              �޸�����
2010/02/22   1.0      macros
</PRE>
*******************************************************************************/

#ifndef _DEBUG_PUBLIC_H_
#define _DEBUG_PUBLIC_H_

#ifdef __cplusplus
extern "C" {
#endif

//��ʼ���������ģ��
//�������������ǰ����
void tracePrintfInit(void);

//����ģ�����ô�ӡ�ļ�������:modifyTraceLevelByMode(FT_MODE, DEBUG_TRACE);
//�趨FT_MODEģ��Ĵ�ӡ����Ϊ���Լ���
void modifyTraceLevelByMode(int mode, int printLevel);

//��ӡ���ʵ�庯��
void tracePrintf(const char * funcN, int lineNo, char * pucFormat, ...);

enum
{
    SYS_MODE,
    GEN_MODE,
    HOT_MODE,
    UPGRADE_MODE,
    FB_MODE,

    NET_MODE,
    XML_MODE,
    FILE_MODE,

    IMG_MODE,
    PAGE_MODE,
    FT_MODE,
    SUB_MODE,

    TRACE_CNT
};

int traceModLevel[TRACE_CNT];

#define DEBUG_TRACE  30
#define WARING_TRACE 20
#define ERROR_TRACE  10
#define PRINT_TRACE  0

//��ӡ�����Ϣ������ַ�������
#define DEBUG_INFO_BUFFER_LEN	1024

//������Ϣ��ӡ���
#define M_TRACE(lvl, mode, pucFormat...) 	\
         if(lvl <= traceModLevel[mode]){\
            tracePrintf(__FUNCTION__, __LINE__, ##pucFormat);}

#ifdef __cplusplus
}
#endif

#endif

