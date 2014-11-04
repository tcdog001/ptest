
#ifndef _FRAMEBUF_PUBLIC_H_
#define _FRAMEBUF_PUBLIC_H_

#ifdef __cplusplus
extern "C" {
#endif


//��������Ӧ�ý�����һ��������Ҫ����rend�ԵȺ���
int init_framebuf_module(void);

//��ȡһ�����õ��Դ��ַ
Pixel64 *getFramebuf(void);

//���ͼ���
void clearFramebuf(void);

//����framebuffer
void test_framebuf(void);

//����alpha
void setFramebufAlpha(unsigned char alpha);

//��ȡframebuffer�Ŀ��
int get_framebuf_width(void);

//��ȡframebuffer�ĸ߶�
int get_framebuf_height(void);

int init_logic_framebuf_module(void);

int close_logic_framebuf_module(void);

Pixel64 *get_background_canvas(void);

Pixel64 *get_logic_canvas(void);

//Region �ǻ���canvas�ľ��ι��
//Pos ������ƽ�����豸framebuffer�ϵ����λ��
void paint_canvas_2_device(Pixel64 *pCanvas, GrPos Pos, GrRegion Region);

void paint_canvas_2_background(Pixel64 *pCanvas, GrPos Pos, GrRegion Region);

void paint_canvas_2_logic_device(Pixel64 *pCanvas, GrPos Pos, GrRegion Region);

void refresh_background_2_device(GrPos Pos, GrRegion Region);

void refresh_logic_2_device(GrPos Pos, GrRegion Region);

//��������������������������������
int merge_two_region_2_device(Pixel64 *pSurface,
                Pixel64 *pCanvas,
                Pixel64 *pDevice,
                GrPos Pos, GrRegion Region);

int move_region_2_display(Pixel64 *pCanvas, GrPos Pos, GrRegion Region);

//��һ�����غϲ����豸�������һ����֪ͼ������
int merge_one_pixel_2_device(Pixel64 *pDevice, Pixel64 *pCanvas);

int refresh_one_pixel_2_main_display(Pixel64 *pDevice, GrPos Pos);
//���������غϲ���һ���µĻ�����
//surface�ǲο��ı����������ص�
int merge_two_pixel_2_canvas(Pixel64 *pSurface, Pixel64 *pCanvas, Pixel64 *pDevice);

#ifdef __cplusplus
}
#endif

#endif

