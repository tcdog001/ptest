#include "sys_include.h"
#include "ft_Font.h"

static char display_char[MAX_DISP_CHARACTER][MAX_DISP_CHAR] = {

    {"�����Ӻ����£����س�����ʼ����"},

    {"���������ڹ�λ��0~90:"},

    {"����������ϣ����س�����ʼ����"},
    {"��������ʧ�ܣ����ϸ񣬲��Խ���"},

    {"���ڲ��Գɹ�"},
    {"���ڲ���ʧ��"},

    {"���ڲ��Գɹ�"},
    {"���ڲ���ʧ��"},

    {"Ӳ�̲��Գɹ�"},
    {"Ӳ�̲���ʧ��"},

    {"tfcard���Գɹ�"},
    {"tfcard����ʧ��"},

    {"��ȷ����Ƶ����Ƶ���"},
    {"����ý�����Ϣ�����س�������"},

    {"���������Ƿ�����������س�������"},

    //{"  "},
};

int display_character_into_screen(DISP_CHARACTER type,
        Pixel64 FT,
        GrPos *pPos, GrRegion *pRegion)
{

    ft_Font_Str2Disp_return_region(&(display_char[type][0]),
        FT,
        *pPos,
        35,
        pRegion);

    return 0;
}



