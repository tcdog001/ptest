/******************************************************************************
  Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
  File Name     : hi_unf_sound.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/1/22
  Last Modified :
  Description   : header file for audio and video output control
  Function List :
  History       :
  1.Date        :
  Author        : z67193
  Modification  : Created file
******************************************************************************/
/**
 * \file
 * \brief Describes the information about the SOUND (SND) module. CNcomment:�ṩSOUND�������Ϣ CNend
 */

#ifndef  __HI_UNF_SND_H__
#define  __HI_UNF_SND_H__

#include "hi_unf_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/********************************Macro Definition********************************/
/** \addtogroup      SOUND */
/** @{ */  /** <!-- ��SOUND�� */

/**Maximum sound outputport*/
/**CNcomment:���sound����˿�*/
#define HI_UNF_SND_OUTPUTPORT_MAX 8

/** @} */  /** <!-- ==== Macro Definition end ==== */


/*************************** Structure Definition ****************************/
/** \addtogroup      SOUND */
/** @{ */  /** <!--  ��SOUND�� */

/**Defines the ID of the audio output (AO) device.*/
/**CNcomment:������Ƶ����豸��*/
typedef enum hiUNF_SND_E
{
    HI_UNF_SND_0,           /**<AO device 0*/ /**<CNcomment:��Ƶ����豸0 */
    HI_UNF_SND_1,           /**<AO device 1*/ /**<CNcomment:��Ƶ����豸1 */
    HI_UNF_SND_2,           /**<AO device 2*/ /**<CNcomment:��Ƶ����豸2 */
    HI_UNF_SND_BUTT
} HI_UNF_SND_E;

/**Audio volume attribute*/
/**CNcomment:��Ƶ��������*/
typedef struct hiHI_UNF_SND_GAIN_ATTR_S
{
    HI_BOOL bLinearMode; /**< gain type of volume*/ /**<CNcomment:����ģʽ */
    HI_S32  s32Gain; /**<Linear gain(bLinearMode is HI_TRUE) , ranging from 0 to 100*/ /**<CNcomment:��������: 0~100 */
                     /**<Decibel gain(bLinearMode is HI_FALSE) , ranging from -70dB to 0dB */ /**<CNcomment: dB����:-70~0*/
} HI_UNF_SND_GAIN_ATTR_S;

/**Audio L/R channel volume attribute*/
/**CNcomment:��Ƶ����������������*/
typedef struct hiHI_UNF_SND_ABSGAIN_ATTR_S
{
    HI_BOOL bLinearMode; /**< gain type of volume*/ /**<CNcomment:����ģʽ */
    HI_S32  s32GainL; /**<Linear left ch gain(bLinearMode is HI_TRUE) , ranging from 0 to 100*/ /**<CNcomment:��������������: 0~100 */
                     /**<Decibel left ch gain(bLinearMode is HI_FALSE) , ranging from -70dB to 0dB */ /**<CNcomment: ������dB����:-70~0*/
    HI_S32  s32GainR; /**<Linear right ch gain(bLinearMode is HI_TRUE) , ranging from 0 to 100*/ /**<CNcomment:��������������: 0~100 */
                  /**<Decibel right ch gain(bLinearMode is HI_FALSE) , ranging from -70dB to 0dB */ /**<CNcomment: ������dB����:-70~0*/
} HI_UNF_SND_ABSGAIN_ATTR_S;

/**Audio Track Type: Master, Slave, Virtual channel*/
/**CNcomment:��ƵTrack����:��ͨ�� ��ͨ�� ����ͨ��*/
typedef enum hiHI_UNF_SND_TRACK_TYPE_E
{
    HI_UNF_SND_TRACK_TYPE_MASTER = 0,
    HI_UNF_SND_TRACK_TYPE_SLAVE,
    HI_UNF_SND_TRACK_TYPE_VIRTUAL,
    HI_UNF_SND_TRACK_TYPE_BUTT
} HI_UNF_SND_TRACK_TYPE_E;

/**Audio output attribute */
/**CNcomment:��Ƶ�������*/
typedef struct hiHI_UNF_AUDIOTRACK_ATTR_S
{
    HI_UNF_SND_TRACK_TYPE_E     enTrackType;        /**<Track Type*/ /**<CNcomment:Track����*/
    HI_U32                      u32FadeinMs;        /**<Fade in time(unit:ms)*/ /**<CNcomment:����ʱ��(��λ: ms)*/
    HI_U32                      u32FadeoutMs;       /**<Fade out time(unit:ms)*/ /**<CNcomment:����ʱ��(��λ: ms)*/
    HI_U32                      u32OutputBufSize;   /**<Track output buffer size*/ /**<CNcomment:Track��������С*/
    HI_U32                      u32BufLevelMs;      /**<Output buffer data size control(ms)*/ /**<CNcomment:�������������������(ms)*/
} HI_UNF_AUDIOTRACK_ATTR_S;

/**Audio outputport: DAC0,I2S0,SPDIF0,HDMI0,ARC0*/
/**CNcomment:��Ƶ����˿�:DAC0,I2S0,SPDIF0,HDMI0,ARC0*/
typedef enum hiUNF_SND_OUTPUTPORT_E
{
    HI_UNF_SND_OUTPUTPORT_DAC0 = 0,

    HI_UNF_SND_OUTPUTPORT_I2S0,

    HI_UNF_SND_OUTPUTPORT_I2S1,

    HI_UNF_SND_OUTPUTPORT_SPDIF0,

    HI_UNF_SND_OUTPUTPORT_HDMI0,

    HI_UNF_SND_OUTPUTPORT_ARC0,

    HI_UNF_SND_OUTPUTPORT_ALL = 0x7fff,

    HI_UNF_SND_OUTPUTPORT_BUTT,
} HI_UNF_SND_OUTPUTPORT_E;

/**Defines internal Audio DAC outport attribute */
/**CNcomment:����������ƵDAC����˿�����*/
typedef struct hiUNF_SND_DAC_ATTR_S
{
    HI_VOID* pPara;
} HI_UNF_SND_DAC_ATTR_S;


/**Defines  Audio I2S outport attribute */
/**CNcomment:������ƵI2S����˿�����*/
typedef struct hiUNF_SND_I2S_ATTR_S
{
    HI_UNF_I2S_ATTR_S  stAttr;
}  HI_UNF_SND_I2S_ATTR_S;

/**Defines  S/PDIF outport attribute */
/**CNcomment:����S/PDIF����˿�����*/
typedef struct hiUNF_SND_SPDIF_ATTR_S
{
    HI_VOID* pPara;
}  HI_UNF_SND_SPDIF_ATTR_S;

/**Defines  HDMI Audio outport attribute */
/**CNcomment:����HDMI��Ƶ����˿�����*/
typedef struct hiUNF_SND_HDMI_ATTR_S
{
    HI_VOID* pPara;
} HI_UNF_SND_HDMI_ATTR_S;

/**Defines  HDMI ARC outport attribute */
/**CNcomment:����HDMI��Ƶ�ش�ͨ���˿�����*/
typedef struct hiUNF_SND_ARC_ATTR_S
{
    HI_VOID* pPara;
} HI_UNF_SND_ARC_ATTR_S;


/**Defines  Audio outport attribute */
/**CNcomment:������Ƶ����˿�����*/
typedef struct hiUNF_SND_OUTPORT_S
{
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    union
    {
        HI_UNF_SND_DAC_ATTR_S stDacAttr;
        HI_UNF_SND_I2S_ATTR_S stI2sAttr;
        HI_UNF_SND_SPDIF_ATTR_S stSpdifAttr;
        HI_UNF_SND_HDMI_ATTR_S stHDMIAttr;
        HI_UNF_SND_ARC_ATTR_S stArcAttr;
    } unAttr;
} HI_UNF_SND_OUTPORT_S;

/**Defines  Audio Sound device attribute */
/**CNcomment:����Sound�豸����*/
typedef struct hiHI_UNF_SND_ATTR_S
{
    HI_U32                    u32PortNum;  /**<Outport number attached sound*/ /**<CNcomment:�󶨵�Sound�豸������˿���*/
    HI_UNF_SND_OUTPORT_S stOutport[HI_UNF_SND_OUTPUTPORT_MAX];  /**<Outports attached sound*/ /**<CNcomment:�󶨵�Sound�豸������˿�*/
    HI_UNF_SAMPLE_RATE_E    enSampleRate;       /**<Sound samplerate*/ /**<CNcomment:Sound�豸���������*/
    HI_U32              u32MasterOutputBufSize; /**<Sound master channel buffer size*/ /**<CNcomment:Sound�豸�����ͨ�������С*/
    HI_U32              u32SlaveOutputBufSize;  /**<Sound slave channel buffer size*/ /**<CNcomment:Sound�豸�����ͨ�������С*/
} HI_UNF_SND_ATTR_S;

/**define SND CAST config  struct */
/**CNcomment:���������������ýṹ��*/
typedef struct hiUNF_SND_CAST_ATTR_S
{
    HI_U32  u32PcmFrameMaxNum;     /**<Max frame of the PCM data at cast buffer*/ /**<CNcomment: ���ɻ���֡��*/
    HI_U32  u32PcmSamplesPerFrame; /**<Number of sample of the PCM data*/ /**<CNcomment: PCM���ݲ���������*/
} HI_UNF_SND_CAST_ATTR_S;

/**HDMI MODE:AUTO,LPCM,RAW,HBR2LBR*/
/**CNcomment:HDMI ģʽ:AUTO,LPCM,RAW,HBR2LBR*/
typedef enum hiHI_UNF_SND_HDMI_MODE_E
{
    HI_UNF_SND_HDMI_MODE_LPCM = 0,       /**<HDMI LCPM2.0*/ /**<CNcomment: ������pcm*/
    HI_UNF_SND_HDMI_MODE_RAW,            /**<HDMI Pass-through.*/ /**<CNcomment: HDMI͸��*/
    HI_UNF_SND_HDMI_MODE_HBR2LBR,        /**<HDMI Pass-through force high-bitrate to low-bitrate.*/ /**<CNcomment: �����������Ƶ��������*/
    HI_UNF_SND_HDMI_MODE_AUTO,           /**<automatically match according to the EDID of HDMI */ /**<CNcomment: ����HDMI EDID�����Զ�ƥ��*/
    HI_UNF_SND_HDMI_MODE_BUTT
} HI_UNF_SND_HDMI_MODE_E;

/**SPDIF MODE:LPCM,RAW*/
/**CNcomment:SPDIF ģʽ:LPCM,RAW*/
typedef enum hiHI_UNF_SND_SPDIF_MODE_E
{
    HI_UNF_SND_SPDIF_MODE_LPCM,           /**<SPDIF LCPM2.0*/ /**<CNcomment: ������pcm*/
    HI_UNF_SND_SPDIF_MODE_RAW,            /**<SPDIF Pass-through.*/ /**<CNcomment: SPDIF͸��*/
    HI_UNF_SND_SPDIF_MODE_BUTT
} HI_UNF_SND_SPDIF_MODE_E;
/** @} */  /** <!-- ==== Structure Definition end ==== */


/**SPDIF SCMS Mode Setting*/
/**CNcomment:����SPDIF SCMSģʽ*/
typedef enum hiHI_UNF_SND_SPDIF_SCMSMODE_E
{
    HI_UNF_SND_SPDIF_SCMSMODE_COPYALLOW,                /**<Copy Allow*/      /**<CNcomment:������*/
    HI_UNF_SND_SPDIF_SCMSMODE_COPYONCE,                 /**<Copy Once*/       /**<CNcomment:�ɸ���һ��*/
    HI_UNF_SND_SPDIF_SCMSMODE_COPYPROHIBITED,           /**<Copy prohibited*/ /**<CNcomment:��ֹ����*/
    HI_UNF_SND_SPDIF_SCMSMODE_BUTT
} HI_UNF_SND_SPDIF_SCMSMODE_E;



/******************************* API declaration *****************************/
/** \addtogroup      SOUND */
/** @{ */  /** <!--  ��SOUND�� */

/**
\brief Initializes an AO device. CNcomment:��ʼ����Ƶ����豸 CNend
\attention \n
Before calling the SND module, you must call this application programming interface (API). CNcomment:����SNDģ��Ҫ�����ȵ��øýӿ� CNend
\param N/A
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_Init(HI_VOID);

/**
\brief Deinitializes an AO device. CNcomment:ȥ��ʼ����Ƶ����豸 CNend
\attention \n
N/A
\param N/A
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_DeInit(HI_VOID);

/**
\brief Obtains the default configured parameters of an AO device. CNcomment:��ȡ��Ƶ����豸Ĭ�����ò��� CNend
\attention \n
\param[in] enSound     ID of an AO device CNcomment:��Ƶ����豸�� CNend
\param[out] pstAttr     Audio attributes CNcomment:��Ƶ���� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_INVALID_ID      The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_GetDefaultOpenAttr(HI_UNF_SND_E enSound, HI_UNF_SND_ATTR_S *pstAttr);

/**
\brief Starts an AO device. CNcomment:����Ƶ����豸 CNend
\attention \n
One port only can attach to one sound.
CNcomment:ÿ���˿�ֻ�ܰ�һ��sound CNend
\param[in] enSound     ID of an AO device CNcomment:��Ƶ����豸�� CNend
\param[in] pstAttr     Attribute of an AO device CNcomment:��Ƶ����豸���� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_ID      The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\retval ::HI_ERR_AO_NULL_PTR               The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_Open(HI_UNF_SND_E enSound, const HI_UNF_SND_ATTR_S *pstAttr);

/**
\brief Destroys a AO SND instance. CNcomment:������Ƶ���Soundʵ�� CNend
\attention \n
An instance cannot be destroyed repeatedly. CNcomment:��֧���ظ����� CNend
\param[in] enSound     ID of an AO device CNcomment:��Ƶ����豸�� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_INVALID_ID      The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_Close(HI_UNF_SND_E enSound);


/**
\brief Sets the mute status of  AO ports. CNcomment:��Ƶ��������������� CNend
\attention \n
N/A
\param[in] enSound
\param[in] enOutPort CNcomment:sound����˿� CNend
\param[in] bMute
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_ID      The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_SetMute(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_BOOL bMute);

/**
\brief Obtains the mute status of AO ports. CNcomment:��ȡ��Ƶ����ľ�������״̬ CNend
\attention \n
N/A
\param[in] enSound CNcomment:
\param[in] enOutPort CNcomment:sound����˿� CNend
\param[out] pbMute CNcomment:
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_ID      The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_GetMute(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_BOOL *pbMute);

/**
\brief Sets the output mode of the HDMI(Auto/PCM/RAW/HBR2LBR).
\attention \n
\param[in] enSound CNcomment:��Ƶ����豸��  CNend
\param[in] enOutPort  Audio OutputPort   CNcomment:��Ƶ����˿� CNend
\param[in] enHdmiMode HDMI mode CNcomment:HDMIģʽCNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_ID      The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_SetHdmiMode(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_SND_HDMI_MODE_E enHdmiMode);

/**
\brief Gets the output mode of the HDMI.
\attention \n
\param[in] enSound CNcomment:��Ƶ����豸��  CNend
\param[in] enOutPort  Audio OutputPort   CNcomment:��Ƶ����˿� CNend
\param[out] Pointer to the obtained HDMI mode CNcomment:��ȡ����HDMIģʽ��ָ��CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_ID      The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_GetHdmiMode(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_SND_HDMI_MODE_E *penHdmiMode);

/**
\brief Sets the output mode of the SPDIF(PCM/RAW).
\attention \n
\param[in] enSound CNcomment:��Ƶ����豸��  CNend
\param[in] enOutPort  Audio OutputPort   CNcomment:��Ƶ����˿� CNend
\param[in] enHdmiMode SPDIF mode CNcomment:SPDIFģʽCNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_ID    The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_SetSpdifMode(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_SND_SPDIF_MODE_E enSpdifMode);

/**
\brief Gets the output mode of the SPDIF.
\attention \n
\param[in] enSound CNcomment:��Ƶ����豸��  CNend
\param[in] enOutPort  Audio OutputPort   CNcomment:��Ƶ����˿� CNend
\param[out] Pointer to the obtained SPDIF mode CNcomment:��ȡ����SPDIFģʽ��ָ��CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_ID    The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\retval ::HI_ERR_AO_NULL_PTR               The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_GetSpdifMode(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_SND_SPDIF_MODE_E *penSpdifMode);


/**
 \brief Sets the output volume value. CNcomment:����������� CNend
 \attention \n
If s32Gain is set to a value greater than 100 or 0dB, then return failure. CNcomment:���s32Gain���ô���100��0dB������ʧ�� CNend
 \param[in] enSound        ID of an AO device CNcomment:��Ƶ����豸�� CNend
 \param[in] enOutPort  Audio OutputPort     CNcomment:��Ƶ����˿� CNend
 \param[in] pstGain     Volume value CNcomment:���õ�����ֵ CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
 \retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
 \retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
 \retval ::HI_ERR_AO_INVALID_PARA       The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
 \retval ::HI_ERR_SND_INVALID_ID        The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
 \retval ::HI_ERR_AO_NULL_PTR               The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \see \n
N/A
 */
HI_S32   HI_UNF_SND_SetVolume(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, const HI_UNF_SND_GAIN_ATTR_S *pstGain);

/**
\brief Obtains the output volume value. CNcomment:��ȡ������� CNend
\attention \n
The default linear volume value is 100 and abslute volume is 0dB. CNcomment:��ѯ��Ĭ������ֵΪ100(��������) and 0dB(��������) CNend
\param[in] enSound         ID of an AO device CNcomment:��Ƶ����豸�� CNend
 \param[in] enOutPort  Audio OutputPort     CNcomment:��Ƶ����˿� CNend
 \param[out] pstGain    Pointer to the obtained volume value CNcomment:ָ�����ͣ���ȡ��������ֵ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_ID      The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\retval ::HI_ERR_AO_NULL_PTR               The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_GetVolume(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_SND_GAIN_ATTR_S *pstGain);

/**
\brief Sets the SCMS mode of the SPDIF(COPYALLOW/COPYONCE/COPYPROHIBITED).
\attention \n
\param[in] enSound CNcomment:��Ƶ����豸��  CNend
\param[in] enOutPort  Audio OutputPort   CNcomment:��Ƶ����˿� CNend
\param[in] enSpdifSCMSMode  SPDIF SCMS mode CNcomment:SPDIF SCMS ģʽCNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_ID    The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_SetSpdifSCMSMode(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_SND_SPDIF_SCMSMODE_E enSpdifSCMSMode);

/**
\brief Gets the SCMS mode of the SPDIF.
\attention \n
\param[in] enSound CNcomment:��Ƶ����豸��  CNend
\param[in] enOutPort  Audio OutputPort   CNcomment:��Ƶ����˿� CNend
\param[out] Pointer to the obtained SPDIF SCMS mode CNcomment:��ȡ����SPDIF SCMSģʽ��ָ��CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN      Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_ID          The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\retval ::HI_ERR_AO_NULL_PTR            The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_GetSpdifSCMSMode(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_SND_SPDIF_SCMSMODE_E *enSpdifSCMSMode);


/**
\brief Sets the sampling rate during audio output. CNcomment:������Ƶ���ʱ�Ĳ����� CNend
\attention \n
At present, the sampling rate cannot be set, and it is fixed at 48 kHz. The streams that are not sampled at 48 kHz are resampled at 48 kHz.
CNcomment:Ŀǰ���������Ĭ��Ϊ48k(ʵ�����������Ϊ48K~192K)��֧�ִ�8K��192K�������룬�����֧��6���ز�����\n
��˵��趨���������Ϊ192Kʱ(ʵ�����������Ϊ192K)����С��32K�����������(��ʱ��Ӱ�����������ʵ������л�)\n
Ȼ�����趨���������Ϊ8Kʱ(ʵ�����������Ϊ8K~192K)����ʱ����ͨ��HDMI���С��32K������(HDMI��֧��) CNend
\param[in] enSound          ID of an AO device CNcomment:��Ƶ����豸�� CNend
\param[in] enSampleRate    Audio sampling rate. For details, see the description of ::HI_UNF_SAMPLE_RATE_E. CNcomment:��Ƶ�����ʡ���μ�::HI_UNF_SAMPLE_RATE_E CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_SetSampleRate(HI_UNF_SND_E enSound, HI_UNF_SAMPLE_RATE_E enSampleRate);

/**
\brief Obtains the sampling rate during audio output. CNcomment:��ȡ��Ƶ���ʱ�Ĳ����� CNend
\attention \n
The 48 kHz sampling rate is returned by default. CNcomment:�˽ӿ�Ĭ�Ϸ���48kHz������ CNend
\param[in] enSound           ID of an AO device CNcomment:��Ƶ����豸�� CNend
\param[out] penSampleRate   Pointer to the type of the audio sampling rate CNcomment:ָ�����ͣ���Ƶ�����ʵ����� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_GetSampleRate(HI_UNF_SND_E enSound, HI_UNF_SAMPLE_RATE_E *penSampleRate);

/**
\brief Sets the smart volume for audio output. CNcomment:��Ƶ��������������������������� CNend
\attention \n
1. The smart volume is disabled by default.\n
2. The smart volume is valid only for the master audio.\n
3. The smart volume is enabled only when the program is switched.
CNcomment:1. Ĭ�Ϲرո���������\n
2. ������������������Ч\n
3. �������������л���Ŀʱ���� CNend
\param[in] enSound     ID of an AO device CNcomment:��Ƶ����豸�� CNend
\param[in] enOutPort  CNcomment:sound����˿� CNend
\param[in] bSmartVolume     Smart volume enable, HI_TRUE: enabled; HI_FALSE: disabled CNcomment:�Ƿ������������HI_TRUE���򿪣�HI_FALSE���ر� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_SetSmartVolume(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_BOOL bSmartVolume);

/**
\brief Obtains the status of the smart volume for audio output. CNcomment:��ȡ��Ƶ���������������״̬ CNend
\attention \n
\param[in] enSound     ID of an AO device CNcomment:��Ƶ����豸�� CNend
\param[in] enOutPort  CNcomment:sound����˿� CNend
\param[out] pbSmartVolume     Pointer to the enable status of the smart volume CNcomment:ָ�����ͣ��Ƿ���������� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_NULL_PTR               The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_GetSmartVolume(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E eOutPort, HI_BOOL *pbSmartVolume);

/**
\brief Set the AO track mode. CNcomment:������Ƶ�������ģʽ CNend
\attention \n
N/A
\param[in] enSound     ID of an AO device CNcomment:��Ƶ����豸�� CNend
\param[in] enOutPort   CNcomment:sound����˿� CNend
\param[in] enMode     Audio track mode. For details, see the description of ::HI_UNF_TRACK_MODE_E. CNcomment:��Ƶ����ģʽ����μ�::HI_UNF_TRACK_MODE_E CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_SetTrackMode(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_TRACK_MODE_E enMode);

/**
\brief Obtains the AO track mode. CNcomment:��ȡ��Ƶ�������ģʽ CNend
\attention \n
N/A
\param[in] enSound     ID of an AO device CNcomment:��Ƶ����豸�� CNend
\param[in] enOutPort   CNcomment:sound����˿� CNend
\param[out] penMode   Pointer to the AO track mode. For details, see the description of ::HI_UNF_TRACK_MODE_E.
CNcomment:ָ�����ͣ���Ƶ����ģʽ����μ�::HI_UNF_TRACK_MODE_E CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA    The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_GetTrackMode(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_TRACK_MODE_E *penMode);

/**
\brief Attaches the SND module to an audio/video player (AVPLAY). CNcomment:����Ƶ���Sound��AV��Audio Video�������� CNend
\attention \n
Before calling this API, you must create a player and ensure that the player has no output. CNcomment:���ô˽ӿ�ǰ�����ȴ�������������Ӧ��·������û����� CNend
\param[in] hTrack             Instance handle of an AVPLAY CNcomment:Track ʵ����� CNend
\param[in] hSource           Instance handle of an AVPLAY CNcomment:AV����������ʵ����� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA            The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/

HI_S32   HI_UNF_SND_Attach(HI_HANDLE hTrack, HI_HANDLE hSource);

/**
\brief Detaches the SND module from an AVPLAY. CNcomment:���Track��AV�������� CNend
\attention \n
N/A
\param[in] hTrack             Instance handle of an AVPLAY CNcomment:Track ʵ����� CNend
\param[in] hSource    Instance handle of an AVPLAY CNcomment:AV����������ʵ����� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/

HI_S32 HI_UNF_SND_Detach(HI_HANDLE hTrack, HI_HANDLE hSource);

/**
\brief Sets the mixing weight of an audio player. CNcomment:������ƵTrack ����Ȩ�� CNend
\attention \n
The output volumes of two players are calculated as follows: (volume x weight 1 + volume x weight 2)/100. The formula of calculating the output volumes of multiple players is similar.
CNcomment:����Track ��������ļ��㷽��Ϊ�������õ�����%Ȩ��1+���õ�����%Ȩ��2��/100������������ļ��㷽��������� CNend
\param[in] hTrack              ID of an AO device CNcomment:��Ƶ���Track CNend
\param[in] pstMixWeightGain   the MixWeight Gain, ranging from 0 to 100. 0: minimum value; 100: maximum value CNcomment:Ȩ�أ���ΧΪ0��100��0����Сֵ��100�����ֵ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA            The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/

HI_S32  HI_UNF_SND_SetTrackWeight(HI_HANDLE hTrack, const HI_UNF_SND_GAIN_ATTR_S *pstMixWeightGain);

/**
\brief Obtains the mixing weight of an audio player. CNcomment:��ȡ��Ƶ����������Ȩ�� CNend
\attention \n

\param[in] hTrack              ID of an AO device CNcomment:��Ƶ���Track CNend
\param[in] pstMixWeightGain     Pointer to the MixWeight Gain CNcomment:ָ�����ͣ�Ȩ������ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR               The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA            The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_GetTrackWeight(HI_HANDLE hTrack, HI_UNF_SND_GAIN_ATTR_S *pstMixWeightGain);


/**
\brief Sets the L/R channel weight of an audio player. CNcomment:������ƵTrack��������Ȩ�� CNend
\attention \n
\param[in] hTrack              ID of an AO device CNcomment:��Ƶ���Track CNend
\param[in] pstAbsWeightGain   the channel Weight Gain, ranging from 0 to 100. 0: minimum value; 100: maximum value CNcomment:Ȩ�أ���ΧΪ0��100��0����Сֵ��100�����ֵ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA            The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32  HI_UNF_SND_SetTrackAbsWeight(HI_HANDLE hTrack, const HI_UNF_SND_ABSGAIN_ATTR_S *pstAbsWeightGain);
/**
\brief Obtains the L/R channel weight of an audio player. CNcomment:��ȡ��Ƶ��������������Ȩ�� CNend
\attention \n

\param[in] hTrack              ID of an AO device CNcomment:��Ƶ���Track CNend
\param[in] pstAbsWeightGain     Pointer to the ChannelWeight Gain CNcomment:ָ�����ͣ�Ȩ������ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR               The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA            The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32  HI_UNF_SND_GetTrackAbsWeight(HI_HANDLE hTrack, HI_UNF_SND_ABSGAIN_ATTR_S *pstAbsWeightGain);

/**
\brief Sets mute or unmute of All Track. CNcomment:����������ƵTrack �������� CNend
\attention \n
\param[in] enSound              All track of the sound CNcomment:��sound����track CNend
\param[in] bMute               mute or not CNcomment:������� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32  HI_UNF_SND_SetAllTrackMute(HI_UNF_SND_E enSound, HI_BOOL bMute);

/**
\brief Gets mute status of an audio player. CNcomment:��ȡ��ƵTrack ����״̬ CNend
\attention \n
\param[in] enSound              All track of the sound CNcomment:��sound track CNend
\param[in] pbMute               mute status CNcomment:����״̬ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA       The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32  HI_UNF_SND_GetAllTrackMute(HI_UNF_SND_E enSound, HI_BOOL *pbMute);

/**
\brief Set the track channel mode. CNcomment:������ƵTrack  ����ģʽ CNend
\attention \n
N/A
\param[in] hTrack              ID of an AO device CNcomment:��Ƶ���Track CNend
\param[in] enMode             The audio track mode. For details, see the description of ::HI_UNF_TRACK_MODE_E. CNcomment:��Ƶ����ģʽ����μ�::HI_UNF_TRACK_MODE_E CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_SetTrackChannelMode(HI_HANDLE hTrack, HI_UNF_TRACK_MODE_E enMode);

/**
\brief Obtains the track channel mode. CNcomment:��ȡ��ƵTrack ����ģʽ CNend
\attention \n
N/A
\param[in] hTrack              ID of an AO device CNcomment:��Ƶ���Track CNend
\param[out] penMode   Pointer to the audio track mode. For details, see the description of ::HI_UNF_TRACK_MODE_E.
CNcomment:ָ�����ͣ���Ƶ����ģʽ����μ�::HI_UNF_TRACK_MODE_E CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA    The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_GetTrackChannelMode(HI_HANDLE hTrack, HI_UNF_TRACK_MODE_E *penMode);

/**
 \brief Obtains the default configured parameters of an AO Track. CNcomment:��ȡ��Ƶ���TrackĬ�����ò��� CNend
 \attention \n
 \param[in] enTrackType              Track Type CNcomment:Track���� CNend
 \param[out] pstAttr     Audio attributes CNcomment:��Ƶ���� CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
 \retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
 \retval ::HI_ERR_AO_NULL_PTR               The pointer is null. CNcomment:ָ�����Ϊ�� CNend
 \see \n
N/A
 */
HI_S32   HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_E enTrackType, HI_UNF_AUDIOTRACK_ATTR_S *pstAttr);

/**
\brief Create a Track. CNcomment:����һ·Track CNend
\attention \n
Create 8 output tracks(master/slave track) and 6 virtual tracks at the most. only create 1 master track on every sound.
CNcomment:���ɴ���8·���track(master/slave), 6·����track��ÿ��soundֻ�ܴ���һ·master track CNend
\param[in] enSound     ID of an AO device CNcomment:��Ƶ����豸�� CNend
\param[in] pTrackAttr  Track attributes CNcomment:ָ�����ͣ�Track  ���� CNend
\param[out] phTrack   Pointer to the handle of the created Track CNcomment:ָ�����ͣ�������Track ��� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE  Failure  CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_CreateTrack(HI_UNF_SND_E enSound,const HI_UNF_AUDIOTRACK_ATTR_S *pTrackAttr,HI_HANDLE *phTrack);

/**
\brief Destroy a Track. CNcomment:����һ·Track CNend
\attention \n
\param[in] hTrack   the handle of the Track CNcomment:Track ��� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_DestroyTrack(HI_HANDLE hTrack);

/**
\brief set the attribute of  a track, reversed. CNcomment:����ĳһ·track�����ԣ� Ԥ�� CNend
\attention \n
\param[in] hTrack   the handle of the Track CNcomment:Track ��� CNend
\param[in] stTrackAttr   the attribute of the Track CNcomment:Track ���� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_ID The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_PARA The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_SetTrackAttr(HI_HANDLE hTrack, const HI_UNF_AUDIOTRACK_ATTR_S *pstTrackAttr);

/**
\brief get the attribute of  a track, reversed. CNcomment:��ȡĳһ·track�����ԣ� Ԥ�� CNend
\attention \n
1.virtual track Attr not support set.\n
2.pstTrackAttr struct: just enTrackType&u32BufLevelMs can be set ,other members not support.
CNcomment:1.����track��֧����������\n
2.pstTrackAttr�ṹ���н�enTrackType&u32BufLevelMs�������ã�������Ա��֧�� CNend
\param[in] hTrack   the handle of the Track CNcomment:Track ��� CNend
\param[in] pstTrackAttr   the attribute of the Track CNcomment:Track ���� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_ID The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_PARA The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S *pstTrackAttr);

/**
\brief Acquire the audio frame from the track. CNcomment:��ȡĳһ·track����Ƶ֡ CNend
\attention \n
\param[in] hTrack   the handle of the Track CNcomment:Track ��� CNend
\param[in] u32TimeoutMs         acquire timeout.CNcomment:��ȡ��ʱ CNend
\param[out] pstAOFrame the audio frame  CNcomment:Track ��Ƶ֡ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_INVALID_ID The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_PARA   The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_AcquireTrackFrame(HI_HANDLE hTrack, HI_UNF_AO_FRAMEINFO_S *pstAOFrame, HI_U32 u32TimeoutMs);

/**
\brief Release the audio frame . CNcomment:�ͷ�track ��Ƶ֡ CNend
\attention \n
\param[in] hTrack   the handle of the Track CNcomment:Track ��� CNend
\param[in] pstAOFrame the audio frame  CNcomment:Track ��Ƶ֡ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_INVALID_ID  The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_PARA    The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32  HI_UNF_SND_ReleaseTrackFrame(HI_HANDLE hTrack, HI_UNF_AO_FRAMEINFO_S *pstAOFrame);

/**
\brief  Transmits data to a slave track directly. CNcomment:ֱ�ӽ������͵�slave track CNend
\attention \n
1. If HI_ERR_AO_OUT_BUF_FULL is returned, you need to transmit the data that fails to be transmitted last time to ensure the audio continuity.
2. For the PCM data, the restrictions are as follows:
    s32BitPerSample must be set to 16.
    bInterleaved must be set to HI_TRUE. Only interlaced mode is supported.
    u32Channels can be set to 1 or 2.
    u32PtsMs can be ignored.
    ps32PcmBuffer indicates the PCM data pointer.
    ps32BitsBuffer can be ignored.
    u32PcmSamplesPerFrame indicates the number of audio sampling. The data length (in byte) is calculated as follows: u32PcmSamplesPerFrame x u32Channels x sizeof(HI_u16)
    u32BitsBytesPerFrame can be ignored.
    u32FrameIndex can be ignored.
CNcomment:1 �������HI_ERR_AO_OUT_BUF_FULL����Ҫ�����߼������ϴ�ʧ�����ݣ����ܱ�֤����������
2 PCM ���ݸ�ʽ�ڻ���������������
    s32BitPerSample: ����Ϊ16
    bInterleaved: ����ΪHI_TRUE, ��֧�ֽ�֯ģʽ
    u32Channels: 1 ��2
    u32PtsMs: ���Ըò���
    ps32PcmBuffer: PCM ����ָ��
    ps32BitsBuffer: ���Ըò���
    u32PcmSamplesPerFrame: ��Ƶ������, ���ݳ���(unit:Bytes): u32PcmSamplesPerFrame*u32Channels*sizeof(HI_u16)
    u32BitsBytesPerFrame: ���Ըò���
    u32FrameIndex: ���Ըò��� CNend
\param[in] hTrack   Track handle CNcomment:Track ��� CNend
\param[out] pstAOFrame   Information about the audio data CNcomment:��Ƶ������Ϣ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_NULL_PTR    The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_PARA    The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_OUT_BUF_FULL  Data fails to be transmitted because the mixer buffer is full. CNcomment:������������������������ʧ�� CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_SendTrackData(HI_HANDLE hTrack, const HI_UNF_AO_FRAMEINFO_S *pstAOFrame);


/**
\brief create screen share channel. CNcomment: ��ȡ����ͨ������Ĭ������ CNend
\attention \n
none. CNcomment:��
\param[in] enSound      display channel.CNcomment:����ͨ· CNend
\param[out] pstAttr      handle of default attr  .CNcomment:����Ĭ�����Ծ�� CNend
\retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR          Input pointer is NULL.CNcomment:����ָ��Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA   invalid input parameter.CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_AO_INVALID_OPT    invalid operation. CNcomment:�����Ƿ� CNend
\see \n
none.CNcomment:�� CNend
*/
HI_S32   HI_UNF_SND_GetDefaultCastAttr(HI_UNF_SND_E enSound, HI_UNF_SND_CAST_ATTR_S *pstAttr);

/**
\brief create screen share channel. CNcomment: ������������ͨ�� CNend
\attention \n
none. CNcomment:��
\param[in] enSound      display channel.CNcomment:����ͨ· CNend
\param[in] pstAttr      pointer of parameter .CNcomment:ָ��,���Բ��� CNend
\param[out] phCast      handle of screen share .CNcomment:���������� CNend
\retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR          Input pointer is NULL.CNcomment:����ָ��Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA   invalid input parameter.CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_AO_INVALID_OPT    invalid operation. CNcomment:�����Ƿ� CNend
\see \n
none.CNcomment:�� CNend
*/
HI_S32 HI_UNF_SND_CreateCast(HI_UNF_SND_E enSound, HI_UNF_SND_CAST_ATTR_S *pstAttr, HI_HANDLE *phCast);

/**
\brief destroy screen share channel. CNcomment: ������������ͨ�� CNend
\attention \n
none. CNcomment:�� CNend
\param[in] phCast      handle of screen share .CNcomment:���������� CNend
\retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR          Input pointer is NULL.CNcomment:����ָ��Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA   invalid input parameter.CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_AO_INVALID_OPT    invalid operation. CNcomment:�����Ƿ� CNend
\see \n
none.CNcomment:�� CNend
*/
HI_S32 HI_UNF_SND_DestroyCast(HI_HANDLE hCast);

/**
\brief enable screen share. CNcomment: ʹ������������ CNend
\attention \n
none. CNcomment:��
\param[in] phCast      handle of screen share .CNcomment:����������
\param[in] bEnable      enable screen share .CNcomment:ʹ���������� CNend
\retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR          Input pointer is NULL.CNcomment:����ָ��Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA   invalid input parameter.CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_AO_INVALID_OPT    invalid operation. CNcomment:�����Ƿ� CNend
\see \n
none.CNcomment:�� CNend
*/
HI_S32 HI_UNF_SND_SetCastEnable(HI_HANDLE hCast, HI_BOOL bEnable);

/**
\brief get enable flag of screen share. CNcomment: ��ȡ���������Ƿ�ʹ�� CNend
\attention \n
none. CNcomment:�� CNend
\param[in] phCast      handle of screen share .CNcomment:���������� CNend
\param[out] bEnable     flag .CNcomment:��־ CNend
\retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR          Input pointer is NULL.CNcomment:����ָ��Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA   invalid input parameter.CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_AO_INVALID_OPT    invalid operation. CNcomment:�����Ƿ� CNend
\see \n
none.CNcomment:�� CNend
*/
HI_S32 HI_UNF_SND_GetCastEnable(HI_HANDLE hCast, HI_BOOL *pbEnable);

/**
\brief get frame info of snd cast. CNcomment: ��ȡ��������֡��Ϣ CNend
\attention \n
Cast pcm data format  s32BitPerSample(16), u32Channels(2),bInterleaved(HI_TRUE), u32SampleRate(same as SND).
\param[in] hCast      handle of screen share .CNcomment:���������� CNend
\param[out] pstCastFrame        frame info.CNcomment:֡��Ϣ CNend
\param[in] u32TimeoutMs         acquire timeout.CNcomment:��ȡ��ʱ CNend
\retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR          Input pointer is NULL.CNcomment:����ָ��Ϊ�� CNend
\retval ::HI_ERR_V_INVALID_PARA   invalid input parameter.CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_AO_INVALID_OPT    invalid operation. CNcomment:�����Ƿ� CNend
\retval ::HI_ERR_AO_CAST_TIMEOUT   no enough data.CNcomment:���ݲ��� CNend
\see \n
none.CNcomment:�� CNend
*/
HI_S32 HI_UNF_SND_AcquireCastFrame(HI_HANDLE hCast, HI_UNF_AO_FRAMEINFO_S *pstCastFrame, HI_U32 u32TimeoutMs);

/**
\brief release frame info of screen share. CNcomment: �ͷ���������֡��Ϣ CNend
\attention \n
none. CNcomment:�� CNend
\param[in] hCast      handle of screen share .CNcomment:���������� CNend
\param[in] pstCastFrame     frame info.CNcomment:֡��Ϣ CNend
\param[in] u32TimeoutMs    release timeout.CNcomment:�ͷų�ʱ CNend
\retval ::HI_SUCCESS CNcomment: success.�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR          Input pointer is NULL.CNcomment:����ָ��Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA   invalid input parameter.CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_AO_INVALID_OPT    invalid operation. CNcomment:�����Ƿ� CNend
\see \n
none.CNcomment:�� CNend
*/
HI_S32 HI_UNF_SND_ReleaseCastFrame(HI_HANDLE hCast, HI_UNF_AO_FRAMEINFO_S *pstCastFrame);

/**
\brief Sets the L/R channel weight of snd cast. CNcomment:������ƵCast��������Ȩ�� CNend
\attention \n
\param[in] hCast              ID of snd cast CNcomment:��ƵCast ID CNend
\param[in] pstAbsWeightGain   the channel Weight Gain, ranging from 0 to 100. 0: minimum value; 100: maximum value CNcomment:Ȩ�أ���ΧΪ0��100��0����Сֵ��100�����ֵ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA            The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_SND_SetCastAbsWeight(HI_HANDLE hCast, const HI_UNF_SND_ABSGAIN_ATTR_S *pstAbsWeightGain);



/**
\brief Obtains the L/R channel weight of snd cast. CNcomment:��ȡ��ƵCast��������Ȩ�� CNend
\attention \n

\param[in] hCast              ID of snd cast CNcomment:��ƵCast ID CNend
\param[in] pstAbsWeightGain     Pointer to the ChannelWeight Gain CNcomment:ָ�����ͣ�Ȩ������ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR               The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA            The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\see \n
N/A
*/
HI_S32  HI_UNF_SND_GetCastAbsWeight(HI_HANDLE hCast,  HI_UNF_SND_ABSGAIN_ATTR_S *pstAbsWeightGain);




/**
\brief Sets the mute status of  AO ports. CNcomment:��Ƶ��������������� CNend
\attention \n
N/A
\param[in] enSound
\param[in] enOutPort CNcomment:sound����˿� CNend
\param[in] bMute
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_ID      The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_SetCastMute(HI_HANDLE hCast, HI_BOOL bMute);


/**
\brief Obtains the mute status of AO ports. CNcomment:��ȡ��Ƶ����ľ�������״̬ CNend
\attention \n
N/A
\param[in] enSound CNcomment:
\param[in] enOutPort CNcomment:sound����˿� CNend
\param[out] pbMute CNcomment:
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE FAILURE CNcomment:ʧ�� CNend
\retval ::HI_ERR_AO_SOUND_NOT_OPEN    Sound device is not opened. CNcomment:Sound�豸δ�� CNend
\retval ::HI_ERR_AO_NULL_PTR           The pointer is null. CNcomment:ָ�����Ϊ�� CNend
\retval ::HI_ERR_AO_INVALID_PARA        The parameter is invalid. CNcomment:��Ч�Ĳ��� CNend
\retval ::HI_ERR_AO_INVALID_ID      The parameter enSound is invalid. CNcomment:��ЧSound ID CNend
\see \n
N/A
*/
HI_S32   HI_UNF_SND_GetCastMute(HI_HANDLE hCast, HI_BOOL *pbMute);




/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /*__HI_UNF_SND_H__*/

