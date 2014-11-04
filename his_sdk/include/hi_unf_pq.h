/******************************************************************************

  Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_pq.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/10/9
  Description   :
  History       :
  1.Date        : 2013/10/9
    Author      : l00206803
    Modification: Created file

 *******************************************************************************/

/**
 * \file
 * \brief Describes the information about picture quality (PQ). CNcomment: �ṩPQ�������Ϣ CNend
 */


#ifndef  __HI_UNF_PQ_H__
#define  __HI_UNF_PQ_H__

/* add include here */
#include "hi_type.h"
#include "hi_unf_common.h"
#include "hi_unf_disp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


/********************************Struct Definition********************************/
/** \addtogroup      PQ */
/** @{ */  /** <!-- [PQ] */

/**<Image Mode Set Different Parameters Under Different Mode*/
/**<CNcomment:ͼ��ģʽѡ���ڲ�ͬ��ģʽ�����ò�ͬ�Ĳ��� CNend*/
typedef enum hiUNF_PQ_IMAGE_MODE_E
{
    HI_UNF_OPTION_MODE_NATURAL = 0,  /**<Natural mode*/ /**<CNcomment:��Ȼģʽ CNend*/
    HI_UNF_OPTION_MODE_PERSON,       /**<Person mode*/ /**<CNcomment:����ģʽ CNend*/
    HI_UNF_OPTION_MODE_FILM,         /**<Film mode*/ /**<CNcomment:��Ӱģʽ CNend*/
    HI_UNF_OPTION_MODE_UD,           /**<User Defined mode*/ /**<CNcomment:�û��Զ���ģʽ CNend*/
    HI_UNF_OPTION_MODE_BUTT,
} HI_UNF_PQ_IMAGE_MODE_E;

/**<HD and SD Channels Parameter*/
/**<CNcomment:�߱���ͨ������ CNend*/
typedef struct hiUNF_PQ_OPT_CHAN_S
{
    HI_U32       u32Brightness;         /**<Brightness; Range:0~100; recommended: 50 */ /**<CNcomment:���ȣ���Χ: 0~100���Ƽ�ֵ: 50 CNend*/
    HI_U32       u32Contrast;           /**<Contrast; Range:0~100; recommended: 50 */ /**<CNcomment:�Աȶȣ���Χ: 0~100���Ƽ�ֵ: 50 CNend*/ 
    HI_U32       u32Hue;                /**<HuePlus; Range:0~100; recommended: 50 */ /**<CNcomment:ɫ������Χ: 0~100���Ƽ�ֵ: 50 CNend*/ 
    HI_U32       u32Saturation;         /**<Saturation; Range:0~100; recommended: 50 */ /**<CNcomment:���Ͷȣ���Χ: 0~100���Ƽ�ֵ: 50 CNend*/
    HI_U32       u32Colortemperature;   /**<Color temperature mode; Range:0~2 Cold,Middle,Warm */ /**<CNcomment: ɫ��ģʽ����Χ: 0~2 ��ɫ��,�м�ɫ��,ůɫ�� CNend*/
    HI_U32       u32GammaMode;          /**<Gamma mode; Range:0~4 Intension_1.8,Intension_2.5,Curve_Light,Curve_Dark, Disabled */ /**<CNcomment:٤��ģʽѡ�񣻷�Χ: 0~4 1.8ǿ��,2.5ǿ��,��,��,�ر� CNend*/
    HI_U32       u32DynamicContrast;    /**<Color Dynamic Contrast mode; Range:0~3 Low, Middle,High,Disabled */ /**<CNcomment:��̬�Աȶȣ���Χ: 0~3 ��,��,��,�ر� CNend*/
    HI_U32       u32IntelligentColor;   /**<Color Intelligent Color; Range:0~5 Blue,Green,BG,Skin,Vivid,Disabled */ /**<CNcomment:������ɫ������Χ: 0~5 ��ɫ,��ɫ,������ǿ,��ɫ,����,�ر� CNend*/    
} HI_UNF_PQ_OPT_CHAN_S;

/**<Common Parameter*/
/**<CNcomment:ͨ�ò��� CNend*/
typedef struct hiUNF_PQ_OPT_COMMON_S
{
    HI_U32       u32Sharpeness;      /**<Sharpeness; Range:0~100; recommended: 50 */ /**<CNcomment:��ǿ�ȣ���Χ:0~100���Ƽ�ֵ:50 CNend*/                
    HI_U32       u32Denoise;         /**<Denoise; Range:0~1 Disabled,Auto */ /**<CNcomment:����ʹ�ܣ���Χ:0~1 �ر�,�� CNend*/       
    HI_U32       u32FilmMode;        /**<FileMode; Range:0~1 Disabled,Auto */ /**<CNcomment:��Ӱģʽʹ��ѡ�񣻷�Χ:0~1 �ر�,�� CNend*/    
    
} HI_UNF_PQ_OPT_COMMON_S;

/**<Interface Type and Interface Ialue*/
/**<CNcomment:�ӿ����ͺ�ͨ������ CNend*/
typedef struct hiUNF_PQ_OPT_CHANS_S
{
    HI_UNF_DISP_E enChan;               /**<interface type */ /**<CNcomment:�ӿ����� CNend*/
    HI_UNF_PQ_OPT_CHAN_S stChanOpt;     /**<interface value*/ /**<CNcomment:ͨ������ CNend*/
} HI_UNF_PQ_OPT_CHANS_S;



/********************************API Declaration********************************/
/** \addtogroup      PQ */
/** @{ */  /** <!-- ��PQ�� */

/**
 \brief Initializes the picture quality unit (PQU). CNcomment: ��ʼ��PQ CNend
 \attention \n
Before calling the PQU, you must call this application programming interface (API).
CNcomment: ����PQģ��Ҫ�����ȵ��øýӿ� CNend
 \param[in] N/A CNcomment: �� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \retval ::HI_ERR_PQ_DEV_NOT_EXIST No PQ device exists. CNcomment: �豸������ CNend
 \retval ::HI_ERR_PQ_NOT_DEV_FILE The file is not a PQ file. CNcomment: �ļ����豸 CNend
 \retval ::HI_ERR_PQ_DEV_OPENED The PQ device fails to be started. CNcomment: ���豸ʧ�� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_Init(HI_VOID);

/**
 \brief Deinitializes the PQU. CNcomment: ȥ��ʼ��PQ CNend
 \attention \n
 \param[in] N/A CNcomment: �� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_DeInit(HI_VOID);

/**
 \brief Set PQ mode . CNcomment: ����ͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] enImageMode Destination DISP channel PQ mode CNcomment: Ŀ��ͨ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_SetImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E enImageMode);

/**
 \brief Get PQ mode . CNcomment: ��ȡͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] penImageMode  pointer of image mode CNcomment: ָ�����ͣ�ָ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_GetImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E* penImageMode);

/**
 \brief Init PQ mode . CNcomment: ��ʼ��ͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] penImageMode  pointer of image mode CNcomment: ָ�����ͣ�ָ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_InitImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E enImageMode);

/**
 \brief Set channel option. CNcomment: ����ͨ��optionֵ CNend
 \attention \n
 \param[in] pstChanOption pointer of channel option CNcomment: ָ�����ͣ�ָ��ͨ��optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_SetChanOption(const HI_UNF_PQ_OPT_CHANS_S* pstChanOption);

/**
 \brief Set channel option. CNcomment: ��ȡͨ��optionֵ CNend
 \attention \n
 \param[out] pstChanOption pointer of channel option CNcomment: ָ�����ͣ�ָ��ͨ��optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_GetChanOption(HI_UNF_PQ_OPT_CHANS_S * pstChanOption);

/**
 \brief Set channel common option. CNcomment: ����ͨ�� common optionֵ CNend
 \attention \n
 \param[in] pstCommOption pointer of channel common option CNcomment: ָ�����ͣ�ָ��ͨ��common optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_SetCommOption(const HI_UNF_PQ_OPT_COMMON_S* pstCommOption);

/**
 \brief Set channel option. CNcomment: ��ȡͨ��common optionֵ CNend
 \attention \n
 \param[out] pstChanOption pointer of channel option CNcomment: ָ�����ͣ�ָ��ͨ��common optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_GetCommOption(HI_UNF_PQ_OPT_COMMON_S* pstCommOption);


/**
 \brief Modifies the basic configuration information.  CNcomment:����PQ��������Ϣ CNend
	\attention \n
	\param[in] N/A CNcomment: �� CNend
	\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
	\see \n
 N/A CNcomment: �� CNend
	*/
	
HI_S32 HI_UNF_PQ_UpdatePqParam(HI_VOID);

/**
 \brief Set the default PQ configuration for video parameter test.  CNcomment: Ϊ����ָ���������PQ ��Ĭ��ֵCNend
	\attention \n
	\param[in] N/A CNcomment: �� CNend
	\retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
	\see \n
 N/A CNcomment: �� CNend
	*/
	
HI_S32 HI_UNF_PQ_SetDefaultParam(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif


