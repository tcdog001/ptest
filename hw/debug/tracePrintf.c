/*! @file
********************************************************************************
<PRE>
ģ����       : �������ģ��ʵ��ģ��
�ļ���       : tracePrintf.c
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

#include <sys_include.h>
#include <stdarg.h>
#include <sys/time.h>
#include "debug_public.h"

static char buffer[DEBUG_INFO_BUFFER_LEN];

//��ʼ��������Ϣ��ӡ���ģ��
//Ĭ�ϴ��󼶱�
void tracePrintfInit(void)
{
    int i = 0;

    for (i = 0; i < TRACE_CNT; i++)
    {
        traceModLevel[i] = ERROR_TRACE;
    }

    return ;
}

//����ģ���趨���Լ���
void modifyTraceLevelByMode(int mode, int printLevel)
{
    traceModLevel[mode] = printLevel;

    return ;
}

void tracePrintf(const char *funcN, int lineNo, char *pucFormat, ...)
{
    va_list         	va;
    struct timeval	tv;

    memset(buffer, 0, DEBUG_INFO_BUFFER_LEN);
    if(pucFormat != NULL)
    {
        va_start(va, pucFormat);
        vsprintf(buffer, pucFormat, va);
        va_end(va);

        gettimeofday(&tv, NULL);
        fprintf(stderr, "[%-8d:%-6d][%-15s][%-4d:] %s",	(int)(tv.tv_sec), (int)(tv.tv_usec), funcN, lineNo, buffer);
    }

    return ;
}

