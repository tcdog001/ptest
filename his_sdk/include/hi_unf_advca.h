/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_advca.h
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : Hisilicon CA API declaration
Function List :
History       :
******************************************************************************/
#ifndef __HI_UNF_ADVCA_H__
#define __HI_UNF_ADVCA_H__

#include "hi_type.h"
#include "hi_unf_cipher.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      ADVCA */
/** @{ */  /** <!-- [ADVCA] */
#define MAX_URI_NUM         (256)
#define MAX_FP_ID_LENGTH    (0x100)

/** Key ladder selecting parameters */
/** CNcomment:ʹ���ĸ�key ladder��־ */
typedef enum hiUNF_ADVCA_CA_TYPE_E
{
    HI_UNF_ADVCA_CA_TYPE_R2R       = 0x0,    /**< Using R2R key ladder */                                                 /**< CNcomment:ʹ��R2R key ladder */
    HI_UNF_ADVCA_CA_TYPE_SP        = 0x1,    /**< Using SP key ladder */                                                  /**< CNcomment:ʹ��SP key ladder */
    HI_UNF_ADVCA_CA_TYPE_CSA2      = 0x1,    /**< Using CSA2 key ladder */                                                /**< CNcomment:ʹ��CSA2 key ladder */
    HI_UNF_ADVCA_CA_TYPE_CSA3      = 0x1,    /**< Using CSA3 key ladder */                                                /**< CNcomment:ʹ��CSA3 key ladder */
    HI_UNF_ADVCA_CA_TYPE_MISC      = 0x2,    /**< Using MISC ladder */                                                    /**< CNcomment:ʹ��SP key ladder */
    HI_UNF_ADVCA_CA_TYPE_GDRM      = 0x3,    /**< Using GDRM ladder */                                                    /**< CNcomment:ʹ��GDRM key ladder */
}HI_UNF_ADVCA_CA_TYPE_E;

/** advanced CA session serect key class*/
typedef enum hiUNF_ADVCA_KEYLADDER_LEV_E
{
	HI_UNF_ADVCA_KEYLADDER_LEV1     = 0,    /**<session serect key level 1*/
	HI_UNF_ADVCA_KEYLADDER_LEV2 ,	        /**<session serect key level 2*/
	HI_UNF_ADVCA_KEYLADDER_LEV3 ,	        /**<session serect key level 3*/
	HI_UNF_ADVCA_KEYLADDER_LEV4,			/**<session serect key level 4*/
	HI_UNF_ADVCA_KEYLADDER_BUTT
}HI_UNF_ADVCA_KEYLADDER_LEV_E;

/** advanced CA session keyladder target */
typedef enum hiUNF_ADVCA_CA_TARGET_E
{
	HI_UNF_ADVCA_CA_TARGET_DEMUX         = 0, /**<demux*/
	HI_UNF_ADVCA_CA_TARGET_MULTICIPHER,	      /**<multicipher*/
}HI_UNF_ADVCA_CA_TARGET_E;

/** advanced CA Encrypt arith*/
typedef enum hiUNF_ADVCA_ALG_TYPE_E
{
    HI_UNF_ADVCA_ALG_TYPE_TDES      = 0,    /**<Encrypt arith :3 DES*/
    HI_UNF_ADVCA_ALG_TYPE_AES,              /**<Encrypt arith : AES*/
    HI_UNF_ADVCA_ALG_TYPE_BUTT
}HI_UNF_ADVCA_ALG_TYPE_E;

/** FLASH device types*/
typedef enum hiUNF_ADVCA_FLASH_TYPE_E
{
    HI_UNF_ADVCA_FLASH_TYPE_SPI     = 0,    /**<SPI flash*/
    HI_UNF_ADVCA_FLASH_TYPE_NAND ,          /**<nand flash*/
    HI_UNF_ADVCA_FLASH_TYPE_NOR ,           /**<nor flash*/
    HI_UNF_ADVCA_FLASH_TYPE_EMMC ,          /**<eMMC*/
    HI_UNF_ADVCA_FLASH_TYPE_BUTT
}HI_UNF_ADVCA_FLASH_TYPE_E;

/** JTAG protect mode*/
typedef enum hiUNF_ADVCA_JTAG_MODE_E
{
    HI_UNF_ADVCA_JTAG_MODE_OPEN     = 0,
    HI_UNF_ADVCA_JTAG_MODE_PROTECT,
    HI_UNF_ADVCA_JTAG_MODE_CLOSED,
    HI_UNF_ADVCA_JTAG_MODE_BUTT
}HI_UNF_ADVCA_JTAG_MODE_E;

/** =======================The following definition is for ADVCA PVR==========================================*/
/** Function pointer for setting CA private data when running PVR*/
typedef HI_S32 (*fpSetCAData)(const HI_CHAR *pFileName, HI_U8 *pInfo, HI_U32 u32CADataLen);
/** Function pointer for getting CA private data when running PVR*/
typedef HI_S32 (*fpGetCAData)(const HI_CHAR *pFileName, HI_U8 *pInfo, HI_U32 u32BufLen, HI_U32* u32CADataLen);
/** Parameter structure of API HI_UNF_ADVCA_PVR_WriteCallBack and HI_UNF_ADVCA_PVR_ReadCallBack*/
typedef struct hiUNF_PVR_CA_CALLBACK_ARGS_S
{
    HI_U32 u32ChnID;                /*channel ID of PVR*/
    HI_CHAR *pFileName;      /* index file name of recorded stream*/
    HI_U64 u64GlobalOffset;         /*Global Offset of the recording stream*/
    HI_U32 u32PhyAddr;		        /*physical address of the recording stream*/
    HI_U32 u32DataSize;             /*size of the the recording stream */ 
}HI_UNF_PVR_CA_CALLBACK_ARGS_S;


/*pay attention: centi_time is a 24bit value 
according to <basic specification 7.1> 
hour(bit 23-19),
minute(bit 18-13),
second(bit 12-7),
centi-second(bit 6-0),
and if fptime in fingerprint = 0xffffff,, which means
( u8Hour = 31,u8Minute = 63,u8Second = 63,u8Centisecond = 127) should show the fingerpring immediately*/
typedef struct HiCENTI_TIME_S
{
	HI_U8 u8Hour;			
	HI_U8 u8Minute;		
	HI_U8 u8Second;		
	HI_U8 u8Centisecond;	
}HI_CENTI_TIME_S;

typedef struct HiFP_ID_S
{
    HI_U16 u16DataLength;
    HI_U8 u8ID[MAX_FP_ID_LENGTH];	
}HI_FP_ID_S;

typedef struct HiFP_S
{
	HI_CENTI_TIME_S stCentiTime;
	HI_U16 u16Duration;            //in 0.01 second steps,for example: u16Duration = 2 means  20ms
	HI_U16 u16Position_X;
	HI_U16 u16Position_Y;
	HI_U8 u8Height;
}HI_FP_S;

typedef struct HiUNF_PVR_FP_INFO_S
{
    HI_U32 u32DisplayOffsetTime;
    HI_BOOL bisFromLPData;
    HI_FP_ID_S stFPID;  
    HI_FP_S stFP;
    HI_U8 MacKey[16]; 
}HI_UNF_PVR_FP_INFO_S;
typedef struct HiUNF_PVR_MAC_FP_INFO_S
{
    HI_UNF_PVR_FP_INFO_S stPVRFPInfo;
    HI_U8 Mac[16];    
}HI_UNF_PVR_MAC_FP_INFO_S;

/** Maturity of program*/
typedef enum hiMATURITY_RATING_S
{
	EN_RAT_G = 0x01,                               /**for the family*/
	EN_RAT_PG = 0x02,                              /**with parental guidance*/
	EN_RAT_A = 0x04,                               /**over 18*/
	EN_RAT_X = 0x08,                               /**erotic*/
    EN_RAT_RESERVE,              
}HI_MATURITY_RATING_E;

/** Recorded stream information */
typedef struct hiUNF_PVR_CA_StreamInfo_S
{
    HI_U32 u32OffsetTime;
    HI_MATURITY_RATING_E Maturity;        /* Maturity of this recorded stream*/
    HI_U8 Reserved[16];                   /* Record reserved private data */
}HI_UNF_PVR_URI_S;

typedef struct
{
    HI_S32 s32Year; /**<The number of years since A.D. 0.,eg.2009*/
    HI_S32 s32Mon;  /**<The number of months since January, in the range 1 to 12.*/
    HI_S32 s32Mday; /**<The day of the month, in the range 1 to 31.*/
    HI_S32 s32Hour; /**<The number of hours past midnight, in the range 0 to 23.*/
    HI_S32 s32Min;  /**<The number of minutes after the hour, in the range 0 to 59.*/
    HI_S32 s32Sec;  /**<The  number of seconds after the minute, normally in the range 0 to 59, but can be up to 60 to allow for leap seconds.*/  
} HI_UNF_ADVCA_Time_S;

typedef struct HiUNF_PVR_CA_PrivateFileHead_S
{
    HI_U8 MagicNum[32];
    HI_UNF_ADVCA_Time_S Starttime;
    HI_U32 URINum;
    HI_U32 FPNum;
    HI_UNF_PVR_URI_S URI[MAX_URI_NUM];        /* Maturity of this recorded stream*/
    HI_U8 MacKey[16]; 
}HI_UNF_PVR_CA_PrivateFileHead_S;

typedef struct HiUNF_PVR_CA_MacPrivateFileHead_S
{
    HI_UNF_PVR_CA_PrivateFileHead_S stCAPrivateFileHead;   
    HI_U8 Mac[16];    
}HI_UNF_PVR_CA_MacPrivateFileHead_S;

typedef struct HiUNF_ADVCA_LOCK_TZ_OTP_PARAM
{
	HI_U32 u32Addr;
	HI_U32 u32Len;
}HI_UNF_ADVCA_LOCK_TZ_OTP_PARAM_S;

typedef enum hiUNF_ADVCA_SP_DSC_MODE_E
{
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_IDSA 		= 0x0020,
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_ECB          	= 0x0021,
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_CI     	= 0x0022,
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_AES_CBC               = 0x4020,
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_AES_ECB               = 0x4021,
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_AES_CBC_PIFF        	= 0x4022,
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_AES_CBC_APPLE    		= 0x4023,
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_AES_CTR               = 0x4024,
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_TDES_CBC              = 0x4040,
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_TDES_ECB              = 0x4041,
     HI_UNF_ADVCA_SP_DSC_MODE_BUTT
}HI_UNF_ADVCA_SP_DSC_MODE_E;

/** Advca CA VendorID */
typedef enum hiUNF_ADVCA_VENDORID_E
{
    HI_UNF_ADVCA_NULL       = 0x00,        /**<No-Advcance CA chipset, Marked with 0*/
    HI_UNF_ADVCA_NAGRA      = 0x01,        /**<NAGRA  Chipse, Marked with R*/
    HI_UNF_ADVCA_IRDETO     = 0x02,        /**<IRDETO Chipset, Marked with I*/
    HI_UNF_ADVCA_CONAX      = 0x03,        /**<CONAX Chipset, Marked with C*/
    HI_UNF_ADVCA_SUMA       = 0x05,        /**<SUMA Chipset, Marked with S*/
    HI_UNF_ADVCA_NOVEL      = 0x06,        /**<NOVEL Chipset, Marked with Y*/
    HI_UNF_ADVCA_VERIMATRIX = 0x07,        /**<VERIMATRIX Chipset, Marked with M*/
    HI_UNF_ADVCA_CTI        = 0x08,        /**<CTI Chipset, Marked with T*/
    HI_UNF_ADVCA_COMMONDCA  = 0x0b,        /**<COMMONCA Chipset, Marked with H*/
    HI_UNF_ADVCA_VENDORIDE_BUTT
}HI_UNF_ADVCA_VENDORID_E;

typedef struct hiUNF_ADVCA_GDRM_ATTS_S
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel;
	HI_BOOL bIsDecrypt;
	HI_HANDLE *phCipherHandle;
}HI_UNF_ADVCA_GDRM_ATTS_S;

/** Advca CA lock type */
typedef enum hiUNF_ADVCA_LOCK_TYPE
{
	HI_UNF_ADVCA_LOCK_RSA_KEY = 0,
	HI_UNF_ADVCA_LOCK_TZ_OTP,
	HI_UNF_ADVCA_LOCK_MISC_KL_DISABLE,
	HI_UNF_ADVCA_LOCK_GG_KL_DISABLE,
	HI_UNF_ADVCA_LOCK_TSKL_CSA3_DISABLE,
	HI_UNF_ADVCA_LOCK_BUTT,
}HI_UNF_ADVCA_LOCK_TYPE_E;


/** DCAS KeyLadder use mode */
typedef enum hiUNF_ADVCA_DCAS_KEYLADDER_LEV_E
{
	HI_UNF_ADVCA_DCAS_KEYLADDER_EK2 		= 0,   	/**<session EK2*/
	HI_UNF_ADVCA_DCAS_KEYLADDER_EK1 		= 1,	/**<session EK1*/
	HI_UNF_ADVCA_DCAS_KEYLADDER_VENDORSYSID = 8,	/**<session Vendor_SysID*/
	HI_UNF_ADVCA_DCAS_KEYLADDER_NONCE 		= 9,	/**<session nonce*/
	HI_UNF_ADVCA_DCAS_KEYLADDER_BUTT
}HI_UNF_ADVCA_DCAS_KEYLADDER_LEV_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      ADVCA */
/** @{ */  /** <!-- [ADVCA] */

/**
\brief Initializes the advanced CA module CNcomment:��ʼ��advance CAģ�� CNend
\attention \n
Call this application programming interface (API) before using the advanced CA module.
The code HI_SUCCESS is returned if this API is called repeatedly.
CNcomment:�ڽ���advance CA��ز���ǰӦ�����ȵ��ñ��ӿ�\n
�ظ����ñ��ӿڣ��᷵�سɹ� CNend
\param N/A CNcomment:�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_OPEN_ERR The CA device fails to start CNcomment:HI_ERR_CA_OPEN_ERR ��CA�豸ʧ�� CNend
\see \n
::HI_UNF_ADVCA_DeInit
*/
HI_S32 HI_UNF_ADVCA_Init(HI_VOID);

/**
\brief Deinitializes the advanced CA module CNcomment:ȥ��ʼ��advance CAģ�� CNend
\attention \n
None CNcomment:�� CNend
\param N/A CNcomment:�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_DeInit(HI_VOID);

/**
\brief Set the ChipId CNcomment:����ChipId  CNend
\attention \n
This application programming interface (API) is allowed to invoked only once. 
It's not allowed to call this API repeatedly.
CHIP_ID should have been setting before chipset is delivered to STB Manufacture.
Please contact Hisilicon before Customer try to use this interface.
CNcomment:\n  CNend
CNcomment:�ýӿ�ֻ�������һ�Σ������ظ����ã������ʹ��\n
CHIP_ID�����Ѱ���CA��˾Ҫ�����ã��ýӿ�����ͻ���Ҫʹ�øýӿ���Ҫ��֪ͨ��˼\n  CNend
\param[in] Id chip id CNcomment:Id chip id\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\see \n
::HI_UNF_ADVCA_SetChipId
*/
HI_S32 HI_UNF_ADVCA_SetChipId(HI_U32 Id);

/**
\brief Obtains the chip ID CNcomment:��ȡоƬID  CNend
\attention \n
The chip ID is read-only.
CNcomment:оƬIDֻ�ܶ�����д CNend
\param[out] pu32ChipId Chip ID CNcomment:pu32ChipId   оƬID  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetChipId(HI_U32 *pu32ChipId);


/**
\brief Obtains the market ID CNcomment:��ȡMarket ID  CNend
\attention \n
None CNcomment:�� CNend
\param[out] u8MarketId market ID CNcomment:u8MarketId   ����г��ı�ʶ��� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetMarketId
*/
HI_S32 HI_UNF_ADVCA_GetMarketId(HI_U8 u8MarketId[4]);

/**
\brief Sets the Market ID CNcomment:����Market ID  CNend
\attention \n
The market ID of the set-top box (STB) is set before delivery. The market ID can be set once only and takes effects after the STB restarts.
CNcomment:�ڻ����г���ʱ���ã���֧������һ�� ���ú�������Ч CNend
\param[in] u8MarketId market ID CNcomment:u8MarketId   ����г��ı�ʶ��� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetMarketId(HI_U8 u8MarketId[4]);


/**
\brief Obtains the serial number of the STB CNcomment:��ȡ���������к� CNend
\attention \n
None CNcomment:�� CNend
\param[out] u8StbSn serial number of the STB CNcomment:u8StbSn   ���������к� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetStbSn
*/
HI_S32 HI_UNF_ADVCA_GetStbSn(HI_U8 u8StbSn[4]);

/**
\brief Sets the serial number of the STB CNcomment:���û��������к� CNend
\attention \n
The serial number of the STB is set before delivery. The market ID can be set once only and takes effects after the STB restarts.
CNcomment:�ڻ����г���ʱ���ã���֧������һ�� ���ú�������Ч CNend
\param[in] u8StbSn serial number of the STB CNcomment:u8StbSn   ���������к� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetStbSn(HI_U8 u8StbSn[4]);

/**
\brief Set the R2R RootKey CNcomment:����R2R RootKey  CNend
\attention \n
This application programming interface (API) is allowed to invoked only once. 
It's not allowed to call this API repeatedly.
R2R RootKey should have been setting before chipset is delivered to STB Manufacture.
Please contact Hisilicon before Customer try to use this interface.
CNcomment:�ýӿ�ֻ�������һ�Σ������ظ�����,�����ʹ�øýӿ�\n
R2RRootKey�����Ѱ���CA��˾Ҫ�����ã��ýӿ�����ͻ���Ҫʹ�øýӿ���Ҫ��֪ͨ��˼\n  CNend
\param[in] pkey R2R Root Key CNcomment:pkey  R2R����Կ\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_GetR2RRootKey
*/
HI_S32 HI_UNF_ADVCA_SetR2RRootKey(HI_U8 *pkey);

/**
\brief Get the R2R RootKey CNcomment:��ȡR2R RootKey  CNend
\attention \n
None CNcomment:�� CNend
\param[out] pkey R2R Root Key CNcomment:pkey  R2R����Կ\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetR2RRootKey
*/
HI_S32 HI_UNF_ADVCA_GetR2RRootKey(HI_U8 *pkey);

/**
\brief Lock the burned keys CNcomment:������д��key  CNend
\attention \n
This application programming interface (API) is used to lock the root keys after burning the root keys
CNcomment:�ýӿڹ���д��Root key֮�������������root key\n  CNend
\param N/A CNcomment:�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\see \n
::HI_UNF_ADVCA_HideLockKeys
*/
HI_S32 HI_UNF_ADVCA_HideLockKeys(HI_VOID);

/**
\brief Obtains the security startup enable status CNcomment:��ȡ��ȫ����ʹ��״̬ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbEnable: Security startup enable. CNcomment:pbEnable   ��ȫ�����Ƿ�ʹ�ܣ� CNend
HI_TRUE enabled CNcomment:HI_TRUE ʹ�ܣ�  CNend
HI_FALSE disabled CNcomment:HI_FALSE ��ʹ�� CNend
\param[out] penFlashType the startup flash type, only valid when SCS is enable
CNcomment:penFlashType ���ڰ�ȫ����ʹ��ʱ��Ч����ʾ��ȫ������Flash���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetSecBootStat(HI_BOOL *pbEnable,HI_UNF_ADVCA_FLASH_TYPE_E *penFlashType);

/**
\brief Obtains the mode of the JTAG interface CNcomment:��ȡJTAG���Կ�ģʽ CNend
\attention \n
None CNcomment:�� CNend
\param[out] penJtagMode Mode of the JTAG interface CNcomment:penJtagMode   JTAG���Կ�ģʽ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_ADVCA_GetJtagMode(HI_UNF_ADVCA_JTAG_MODE_E *penJtagMode);

/**
\brief Sets the mode of the JTAG interface CNcomment:����JTAG���Կ�ģʽ   CNend
\attention \n
If the mode of the JTAG interface is set to closed or password-protected, it cannot be opened.
If the JTAG interface is open, it can be closed or password-protected.
If the JATG interface is password-protected, it can be closed.
After being closed, the JATG interface cannot be set to open or password-protected mode.
CNcomment:��֧������Ϊ��״̬��\n
�򿪵�ʱ����Թرջ�����Ϊ��Կ����״̬��\n
������Կ����״̬ʱ���Թرա�\n
�ر�֮���ܴ򿪺�����Ϊ��Կ����״̬ CNend
\param[in] enJtagMode Mode of the JTAG interface CNcomment:enJtagMode   JTAG���Կ�ģʽ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN �ظ����� CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_ADVCA_SetJtagMode(HI_UNF_ADVCA_JTAG_MODE_E enJtagMode);


/**
\brief Obtains the R2R key ladder stage CNcomment:��ȡR2R key ladder���� CNend
\attention \n
None CNcomment:�� CNend
\param[out] penStage Key ladder stage CNcomment:penStage   key ladder���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetR2RKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);

/**
\brief Sets the R2R key ladder stage CNcomment:����R2R key ladder�ļ���    CNend
\attention \n
The key ladder stage can be set only once before delivery and cannot be changed. Please use default value.
CNcomment:�����г���ʱ���� ��������һ�� ���ɸ���,������ʹ�øýӿڸı�stage  CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3
CNcomment:enStage   key ladder����\n ȡֵֻ��ΪHI_UNF_ADVCA_KEYLADDER_LEV2 ���� HI_UNF_ADVCA_KEYLADDER_LEV3  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief Obtains the digital video broadcasting (DVB) key ladder stage CNcomment:��ȡDVB key ladder�ļ��� CNend
\attention \n
None CNcomment:�� CNend
\param[out] penStage Key ladder stage CNcomment:penStage   key ladder���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetDVBKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);

/**
\brief Sets the DVB key ladder stage CNcomment:����DVB key ladder�ļ���    CNend
\attention \n
The key ladder stage can be set only once before delivery and cannot be changed. Please use default value.
CNcomment:�����г���ʱ���� ��������һ�� ���ɸ���,������ʹ�øýӿڸı�stage  CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage  key ladder����\n ȡֵֻ��ΪHI_UNF_ADVCA_KEYLADDER_lev2 ���� HI_UNF_ADVCA_KEYLADDER_lev3  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetDVBKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief Sets session keys for an R2R key ladder CNcomment:ΪR2R key ladder���ûỰ��Կ    CNend
\attention \n

The stage of the session key cannot be greater than the configured stage of the key ladder. The last stage of the session key is configured by calling the API of the CIPHER module rather than this API.
That is, only session key 1 and session key 2 need to be configured for a 3-stage key ladder.
Only session key 1 needs to be configured for a 2-stage key ladder.
You need to set the key ladder stage by calling HI_UNF_ADVCA_SetR2RKeyLadderStage first.
Session keys can be set during initialization or changed at any time.
CNcomment:ע�����õļ������ܳ������õļ���ֵ�����һ����CIPHERģ���ڲ����ã�����ͨ���˽ӿ����á�\n
Ҳ����˵������3��key ladder��ֻ�����ûỰ��Կ1�ͻỰ��Կ2��\n
����2����key ladder��ֻ�����ûỰ��Կ1��\n
���ȵ���HI_UNF_ADVCA_SetR2RKeyLadderStage����key ladder������\n
�Ự��Կ���Գ�ʼʱ����һ�Σ�Ҳ������ʱ�޸ġ� CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage    ��Կ������[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]  CNend
\param[in] pu8Key Protection key pointer, 128 bits (16 bytes) in total CNcomment:pu8Key     ������Կָ�룬��128bit(16byte)  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT CA�ȴ��ӽ��ܳ�ʱ CNend
\retval ::HI_ERR_CA_R2R_DECRYPT The R2R decryption fails CNcomment:HI_ERR_CA_R2R_DECRYPT  R2R����ʧ�� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);

/**
\brief Sets session keys for a DVB key ladder CNcomment:ΪDVB key ladder���ûỰ��Կ    CNend
\attention \n
The stage of the session key cannot be greater than the configured stage of the key ladder. The last stage of the session key is configured by calling the API of the CIPHER module rather than this API.
That is, only session key 1 and session key 2 need to be configured for a 3-stage key ladder.
Only session key 1 needs to be configured for a 2-stage key ladder.
You need to set the key ladder stage by calling HI_UNF_ADVCA_SetDVBKeyLadderStage first.
 Session keys can be set during initialization or changed at any time.
CNcomment:ע�����õļ������ܳ������õļ���ֵ�����һ����Descramblerģ���ڲ����ã�����ͨ���˽ӿ����á�\n
Ҳ����˵������3��key ladder��ֻ�����ûỰ��Կ1�ͻỰ��Կ2��\n
����2����key ladder��ֻ�����ûỰ��Կ1��\n
���ȵ���HI_UNF_ADVCA_SetDVBKeyLadderStage����key ladder������\n
�Ự��Կ���Գ�ʼʱ����һ�Σ�Ҳ������ʱ�޸ġ� CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage    ��Կ������[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]  CNend
\param[in] pu8Key Protection key pointer, 128 bits (16 bytes) in total CNcomment:pu8Key     ������Կָ�룬��128bit(16byte)  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT CA�ȴ��ӽ��ܳ�ʱ CNend
\retval ::HI_ERR_CA_R2R_DECRYPT The CW decryption fails CNcomment:HI_ERR_CA_CW_DECRYPT   CW����ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetDVBSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);


/** 
\brief Set widevine keyladder session key CNcomment:����widevine keyladder�ĸ���������Կ CNend
\param[in]  enLevel keyladder level for input CNcomment:enLevel ������Կ�ļ��� CNend
\param[in]  hCipherHandle cipher handle input when level 3 CNcomment:hCipherHandle ���������������ʱ����Ҫ����Ԥ�ȴ����õ�Cipher�ľ�� CNend
\param[in]  pu8Input input data for keyladder CNcomment:pu8Input  keyladder���������� CNend
\param[in]  u32InputLen input data length CNcomment:u32InputLen ���ݵĳ��� CNend
\param[out] pu32GdrmFlag the flag value when level 3 CNcomment:pu32GdrmFlag  ���������������Կʱ�������GDRM��־  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS               �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT       CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA   ��������Ƿ� CNend
\retval ::HI_ERR_CA_NOT_SUPPORT The function is not supported CNcomment:HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧�� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ CNend
\return ::HI_ERR_CA_SWPK_ENCRYPT SWPK encryption fails CNcomment:HI_ERR_CA_SWPK_ENCRYPT   SWPK����ʧ�� CNend
\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_SetGDRMSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,
									HI_HANDLE hCipherHandle,
									HI_U8 *pu8Input,
									HI_U32 u32InputLen,
									HI_U32 *pu32GdrmFlag);


/** 
\brief Encrypts software protect keys (SWPKs) CNcomment:�������������Կ CNend
\attention
Before the delivery of the STB, you need to read the SWPKs in plain text format from the flash memory, encrypt SWPKs by calling this API, and store the encrypted SWPKs in the flash memory for security startup.
CNcomment:�����г���ʱ ��Flash�϶�ȡ���ĵ�SWPK(Software Protect Key),���øýӿڼ���,�����ܵ�SWPK�洢��Flash�У����ڰ�ȫ���� CNend
The fist 8 bytes of the SWPK can't be equal to the last 8 bytes.
CNcomment:SWPK��ǰ8���ֽ����8���ֽڲ������ CNend
This API is only for special CA, please contact Hislicon before usage.
CNcomment:ע��:�˽ӿ�Ϊ�ض�CAר�ã�����ʹ�ã�����ϵ��˼ CNend
\param[in]  pPlainSwpk SWPKs in plain text format CNcomment:pPlainSwpk    ����SWPK  CNend
\param[out] pEncryptedSwpk Encrypted SWPKs CNcomment:pEncryptedSwpk  ���ܺ��SWPK  CNend

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS               �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT       CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA   ��������Ƿ� CNend
\retval ::HI_ERR_CA_NOT_SUPPORT The function is not supported CNcomment:HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧�� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ CNend
\return ::HI_ERR_CA_SWPK_ENCRYPT SWPK encryption fails CNcomment:HI_ERR_CA_SWPK_ENCRYPT   SWPK����ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_EncryptSWPK(HI_U8 *pPlainSwpk,HI_U8 *pEncryptedSwpk);

/**
\brief Sets the algorithm of the DVB key ladder CNcomment:����DVB key ladder���㷨    CNend
\attention \n
You must set an algorithm before using a key ladder in a session. The default algorithm is TDES.
It is recommended that you retain the algorithm in a session.
CNcomment:ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_ALG_TYPE_TDES��\n
���λỰ�����У����鱣���㷨���ȶ����䡣 CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief Sets the algorithm of the R2R key ladder CNcomment:����R2R key ladder���㷨    CNend
\attention \n
You must set an algorithm before using a key ladder in a session. The default algorithm is TDES.
It is recommended that you retain the algorithm in a session.
CNcomment:ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_ALG_TYPE_TDES��\n
���λỰ�����У����鱣���㷨���ȶ����䡣 CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief Obtains the algorithm of the DVB key ladder CNcomment: ��ȡ DVB key ladder���㷨    CNend
\attention \n
None CNcomment:�� CNend
\param[in] pEnType Key ladder algorithm CNcomment:pEnType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType);

/**
\brief Obtains the algorithm of the R2R key ladder CNcomment:��ȡ R2R key ladder���㷨    CNend
\attention \n
None CNcomment:�� CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType);

/**
  \brief set RSA key CNcomment:����ǩ��У���RSA���� CNend
  \attention \n
  RSA key should have been setting before chipset is delivered to STB Manufacture.
  The length of RSA key must be 512 Bytes.
     Please contact Hisilicon before Customer try to use this interface.
  CNcomment:�ýӿڽ����ڲ���оƬ����ʽоƬ��������RSAKey\n
     �ýӿ�ֻ�������һ�Σ������ظ�����,�����ʹ�øýӿ�, RSA key�ĳ��ȱ���Ϊ512 Bytes\n
     RSA key�����Ѱ���CA��˾Ҫ�����ã��ýӿ�����ͻ���Ҫʹ�øýӿ���Ҫ��֪ͨ��˼\n  CNend
  \param[in] pkey RSA key CNcomment:pkey  RSA����\n  CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetRSAKey(HI_U8 *pkey);

/**
  \brief set RSA key CNcomment:��ȡǩ��У���RSA���� CNend
  \attention \n
     RSA key can only be read out, only RSAKey is not locked.
     RSA key should have been setting and lock before chipset is delivered to STB Manufacture.
     The length of RSA key must be 512 Bytes.
     Please contact Hisilicon before Customer try to use this interface.
  CNcomment:�ýӿڽ���RSAkeyû�б�����������£���ȡ����, RSA key�ĳ��ȱ���Ϊ512 Bytes\n
     RSA key�����Ѱ���CA��˾Ҫ�����ò��������ýӿ�����ͻ���Ҫʹ�øýӿ���Ҫ��֪ͨ��˼\n  CNend
  \param[in] pkey RSA key CNcomment:pkey  RSA����\n  CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetRSAKey(HI_U8 *pkey);


/**
  \brief This function is used to check if the MarketID is already set
  \attention \n
  None
  \param[in] pbIsMarketIdSet: the pointer point to the buffer to store the return value
  \param[out] pbIsMarketIdSet: save the return value
  \retval ::HI_SUCCESS Success
  \retval ::HI_FAILURE This API fails to be called
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_IsMarketIdSet(HI_BOOL *pbIsMarketIdSet);

/**
  \brief This function is used to get the vendor type of the chipset
  \attention \n
  None
  \param[out] pu32VendorID: The number indicates the vendor id
  \retval ::HI_SUCCESS Success
  \retval ::HI_FAILURE This API fails to be called
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetVendorID(HI_U32 *pu32VendorID);

/**
\brief Enables the security startup function and sets the type of flash memory for security startup
CNcomment:���ð�ȫ����ʹ��,ͬʱָ����ȫ������Flash���� CNend
\attention \n
This function can be enabled only and cannot be disabled after being enabled.
CNcomment:ֻ��ʹ�ܣ�ʹ��֮�󲻿��޸ġ� CNend
\param[in]  enFlashType Type of the flash memory for security startup CNcomment:enFlashType  ������Flash���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_EnableSecBoot(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType);

/**
\brief Enables the security startup function. This API should be used with the API HI_UNF_ADVCA_SetFlashTypeEx.
CNcomment:���ð�ȫ����ʹ�ܣ��ýӿڱ����HI_UNF_ADVCA_SetFlashTypeEx����ʹ�á� CNend
\attention \n
\param[in]  None
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_EnableSecBootEx(HI_VOID);

/**
\brief Sets the type of flash memory for security startup and disable the self boot, which mean that you cannot use the serial port to update the boot. This API should be used with the API HI_UNF_ADVCA_EnableSecBootEx
CNcomment:ָ����ȫ������Flash���ͣ�ͬʱ�ر��Ծٹ��ܣ�������ͨ����������fastboot���ýӿڸ�HI_UNF_ADVCA_EnableSecBootEx����ʹ�� CNend
\attention \n
The setting is performed before delivery and can be performed once only.
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ�� CNend
\param[in]  enFlashType Type of the flash memory for security startup CNcomment:enFlashType  ������Flash���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetFlashTypeEx(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType);

/** 
\brief  Sets whether to use hardware CWs only CNcomment:���ù̶�ʹ��Ӳ��CW�� CNend
\attention
The setting is performed before delivery and can be performed once only.
By default, the CW type (hardware CWs or software CWs) depends on the configuration of the DEMUX.
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϸ���Demux������ѡ��ʹ��Ӳ��CW�ֻ������CW�� CNend
\param  none
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\return ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò��� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_LockHardCwSel(HI_VOID);

/** 
\brief Disables the self-boot function CNcomment:�ر�SelfBoot����,Ҳ����boot�²���ʹ�ô���/�������� CNend
\attention
The setting is performed before delivery and can be performed once only.
The self-boot function is enabled by default.
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ��ʹ��SelfBoot���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized.  CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\return ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò��� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_DisableSelfBoot(HI_VOID);

/**
\brief Obtains the self-boot status CNcomment:��ȡSelfBoot״̬ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbDisable: self-boot status. CNcomment:pbEnable   SelfBoot�Ƿ���� CNend
HI_TRUE enabled CNcomment:HI_TRUE ���ã�  CNend
HI_FALSE disabled CNcomment:HI_FALSE δ���� CNend

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetSelfBootStat(HI_BOOL *pbDisable);

/** 
\brief  Get whether to use hardware CWs only CNcomment:��ȡ�̶�ʹ��Ӳ��CW�ֱ�־ CNend
\attention
None CNcomment:�� CNend
\param[out] pbLock indicates the state of hardware CWs  CNcomment:pbLock Ӳ��CW�ֵı�־λ CNend

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetHardCwSelStat(HI_BOOL *pbLock);

/** 
\brief  Open the SWPK key ladder CNcomment:��boot key ladder  CNend
\attention
\param  none

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SWPKKeyLadderOpen(HI_VOID);

/** 
\brief  Close the SWPK key ladder CNcomment:�ر�boot key ladder  CNend
\attention
\param  none

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SWPKKeyLadderClose(HI_VOID);

/**
\brief Obtains the Version ID CNcomment:��ȡVersion ID  CNend
\attention \n
None CNcomment:�� CNend
\param[out] u8VersionId version ID CNcomment:u8VersionId   �汾�ű�־ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetVersionId
*/
HI_S32 HI_UNF_ADVCA_GetVersionId(HI_U8 u8VersionId[4]);

/**
\brief Sets the Version ID CNcomment:����Version ID  CNend
\attention \n
The version ID of the set-top box (STB) is set before delivery. The version ID can be set once only and takes effects after the STB restarts.
CNcomment:�ڻ����г���ʱ���ã���֧������һ�� ���ú�������Ч CNend
\param[in] u8VersionId version ID CNcomment:u8VersionId   �汾�ű�־ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetVersionId(HI_U8 u8VersionId[4]);

/** 
\brief  Sets whether to check the boot version CNcomment:�����Ƿ���Version  CNend
\attention
The setting is performed before delivery and can be performed once only.
By default, the version check function is disabled
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϲ�ʹ��version check  CNend
\param  none
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\return ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò��� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_EnableVersionCheck(HI_VOID);

/** 
\brief  Get the boot version check flag CNcomment:��ȡ�Ƿ���version�ı�־λ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu32Stat boot version check flag CNcomment:pu32Stat    version���ı�־λ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetVersionCheckStat(HI_U32 *pu32Stat);

/** 
\brief  Sets whether to check the MSID in boot area CNcomment:�����Ƿ���boot area��MSID  CNend
\attention
The setting is performed before delivery and can be performed once only.
By default, the boot MSID check function is disabled
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϲ�ʹ��boot MSID check  CNend
\param none
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\return ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò��� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_EnableBootMSIDCheck(HI_VOID);

/** 
\brief  Get the boot MSID check flag CNcomment:��ȡ�Ƿ���MSID�ı�־λ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu32Stat boot MSID check flag CNcomment:pu32Stat    MSID���ı�־λ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetBootMSIDCheckStat(HI_U32 *pu32Stat);

/** 
\brief  Get the software revision
CNcomment:��ȡ�����revision�汾�� CNend
\attention \n
None CNcomment:�� CNend
\param[out] revision string of Revision CNcomment:revision    Revision�汾�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetRevision(HI_U8 revision[25]);

/** 
\brief  Set the DDR Scramble flag. Normally, this flag has been set as required by CA vendor
CNcomment:����DDR���ű�־λ��һ��߰�оƬ����ʱ�Ѱ���CA��˾Ҫ������ CNend
\attention \n
None CNcomment:�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetDDRScramble(HI_VOID);

/** 
\brief  Get the DDR Scramble flag
CNcomment:��ȡDDR���ű�־λ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu32Stat DDR Scramble flag CNcomment:pu32Stat    DDR���ű�־ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetDDRScrambleStat(HI_U32 *pu32Stat);

/** 
\brief Sets whether to decrypt the BootLoader CNcomment:���ñ����BootLoader���н��� CNend
\attention
The setting is performed before delivery and can be performed once only.
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϸ���Flash�е����ݱ�ʶ������BootLoader�Ƿ���Ҫ���� CNend

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\return ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò��� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_LockBootDecEn(HI_VOID);

/** 
\brief Get the BootLoader Decryption flag CNcomment:��ȡBootLoader���ܵı�־λ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu32Stat BootLoader Decryption flag CNcomment:pu32Stat    Bootloader���ܱ�־λ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetBootDecEnStat(HI_U32 *pu32Stat);





/*============the following is for PVR ===========*/


/** 
\brief  Open ADVCA PVR Record CNcomment:��ADVCA PVR ¼�� CNend
\attention
\param[in] u32RecChnID Channel ID of record CNcomment:u32RecChnID   ¼��ͨ���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_FAILURE Faliure CNcomment:HI_FAILURE                  ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_RecOpen(HI_U32 u32RecChnID);

/** 
\brief  Close ADVCA PVR Record CNcomment:�ر�ADVCA PVR ¼�� CNend
\attention
\param[in] u32RecChnID Channel ID of record CNcomment:u32RecChnID   ¼��ͨ���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_FAILURE Faliure CNcomment:HI_FAILURE                  ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_RecClose(HI_U32 u32RecChnID);

/** 
\brief  Open ADVCA PVR Play CNcomment:��ADVCA PVR ���� CNend
\attention
\param[in] u32PlayChnID Channel ID of record CNcomment:u32PlayChnID   ����ͨ���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_FAILURE Faliure CNcomment:HI_FAILURE                  ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_PlayOpen(HI_U32 u32PlayChnID);

/** 
\brief  Open ADVCA PVR Play CNcomment:�ر�ADVCA PVR ���� CNend
\attention
\param[in] u32PlayChnID Channel ID of record CNcomment:u32PlayChnID   ����ͨ���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_FAILURE Faliure CNcomment:HI_FAILURE                  ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_PlayClose(HI_U32 u32PlayChnID);



/** 
\brief  Register functions of operating CA data CNcomment:ע�����CA˽�����ݵĺ��� CNend
\attention \n
None CNcomment:�� CNend
\param[in] funcGetData Function of getting CA private data when running PVR CNcomment:funcGetData   ������PVRʱ����ȡCA˽�����ݵĺ��� CNend
\param[in] funcSetData Function of setting CA private data when running PVR CNcomment:funcSetData   ������PVRʱ������CA˽�����ݵĺ��� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_FAILURE Faliure CNcomment:HI_FAILURE                  ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_RegisterCADataOps(fpGetCAData funcGetData,fpSetCAData funcSetData);

/** 
\brief  Write callback function which should be registered by PVR,it achieve operating keyladder and M2M encryption 
CNcomment:Ӧ�ñ�PVRע���¼�ƻص�����������Ҫ���ʹ��keyladder��multicipher��¼�����ݽ��м��� CNend
\attention \n
None CNcomment:�� CNend
\param[in] pstCAPVRArgs Structure of parameters used by this function CNcomment:pstCAPVRArgs    ������ʹ�õĲ����ṹ�壬
��ϸ�����HI_UNF_PVR_CA_CALLBACK_ARGS_S�ṹ��Ķ��� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_FAILURE Faliure CNcomment:HI_FAILURE                  ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_WriteCallBack(HI_UNF_PVR_CA_CALLBACK_ARGS_S* pstCAPVRArgs);

/** 
\brief  Read callback function which should be registered by PVR,it achieve operating keyladder and M2M decryption 
CNcomment:Ӧ�ñ�PVRע��Ĳ��Żص�����������Ҫ���ʹ��keyladder��multicipher��¼�����ݽ��н��� CNend
\attention \n
None CNcomment:�� CNend
\param[in] pstCAPVRArgs Structure of parameters used by this function CNcomment:pstCAPVRArgs    ������ʹ�õĲ����ṹ�壬
��ϸ�����HI_UNF_PVR_CA_CALLBACK_ARGS_S�ṹ��Ķ��� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_FAILURE Faliure CNcomment:HI_FAILURE                  ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_ReadCallBack(HI_UNF_PVR_CA_CALLBACK_ARGS_S* pstCAPVRArgs);



/**
\brief  Get the name of CA private data file by index file name
CNcomment:ͨ�������ļ����ֻ�ȡCA˽�������ļ� CNend
\attention \n
None CNcomment:�� CNend

\param[in] pIndexFileName  The name of index file        CNcomment:�����ļ����� CNend
\param[out] CAPrivateFileName  The name  CA private data file  CNcomment:˽�������ļ����� CNend


\retval ::HI_SUCCESS Success     CNcomment: �ɹ� CNend
\retval ::HI_FAILURE Faliure       CNcomment:  ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_GetCAPrivateFileName(HI_CHAR * pIndexFileName,HI_CHAR CAPrivateFileName[128]);

/**
\brief  Create CA private data file
CNcomment: ����CA˽�������ļ� CNend
\attention \n
None CNcomment:�� CNend

\param[in] u32RecChnID  Record channel ID        CNcomment:¼��ͨ��ID  CNend
\param[in] pCAPrivateFileName  The name  CA private data file  CNcomment:˽�������ļ����� CNend
\param[in] pCurTime     The CurrentTime to record stream  CNcomment:��ǰ����ʱ�� CNend

\retval ::HI_SUCCESS Success       CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Faliure          CNcomment: ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_CreateCAPrivateFile( HI_U32 u32RecChnID,HI_CHAR * pCAPrivateFileName, HI_UNF_ADVCA_Time_S *pCurTime);

/**
\brief  Check  if the file of CA private data is correct
CNcomment: �˶�CA ˽�������ļ��Ƿ���ȷ CNend
\attention \n
None CNcomment:�� CNend

\param[in]  pCAPrivateFileName  The name of CA private data file .     CNcomment:CA ˽�������ļ����� CNend
\param[out] pOutRecordStartTime Get the Time to record stream  CNcomment:��ȡ¼�ƿ�ʼʱ�� CNend

\retval ::HI_SUCCESS Check successfully                   CNcomment:�˶Գɹ� CNend
\retval ::HI_FAILURE  Fail to check.                      CNcomment:�˶�ʧ�� CNend
\retval ::0x101  Record storage time expire.              CNcomment:�˶Գɹ�,���Ѿ�ʧЧ CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_CheckCAPrivateFileMAC( HI_CHAR * pCAPrivateFileName, HI_UNF_ADVCA_Time_S *pOutRecordStartTime);

/**
\brief  Save the information of maturity rate into the file of CA private data
CNcomment: �����˼���Ϣ���浽CA ˽�������ļ��� CNend
\attention \n
None CNcomment:�� CNend

\param[in]  u32RecChnID  The record channel ID .                             CNcomment:¼��ͨ��ID  CNend
\param[in]  pCAPrivateFileName  The name of CA private data file .     CNcomment:CA ˽�������ļ����� CNend
\param[in]  pstPVRURI  The information of maturity rate                   CNcomment:���˼���Ϣ CNend


\retval ::HI_SUCCESS Check successfully                   CNcomment:����ɹ� CNend
\retval ::HI_FAILURE  Fail to check.                          CNcomment:����ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_SaveURI( HI_U32 u32RecChnID,HI_CHAR * pCAPrivateFileName ,HI_UNF_PVR_URI_S* pstPVRURI);

/**
\brief  Save the information of fingerprint into the file of CA private data
CNcomment: ��ָ����Ϣ���浽CA ˽�������ļ��� CNend

\attention \n
None CNcomment:�� CNend

\param[in]  u32RecChnID  The record channel ID .                             CNcomment:¼��ͨ��ID  CNend
\param[in]  pCAPrivateFileName  The name of CA private data file .     CNcomment:CA ˽�������ļ����� CNend
\param[in]  pstFPInfo  The information of fingerprint                   CNcomment:ָ����Ϣ CNend


\retval ::HI_SUCCESS Check successfully                   CNcomment:����ɹ� CNend
\retval ::HI_FAILURE  Fail to check.                          CNcomment:����ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_SaveFP( HI_U32 u32RecChnID,HI_CHAR * pCAPrivateFileName,HI_UNF_PVR_FP_INFO_S* pstFPInfo);

/**
\brief  Get the corresponding information of maturity rate based on the number from the file of CA private data
CNcomment: ����number ��CA ˽�������ļ��л�ȡ��Ӧ�ĳ��˼���Ϣ CNend
\attention \n
None CNcomment:�� CNend

\param[in]  pCAPrivateFileName  The name of CA private data file .      CNcomment:CA ˽�������ļ����� CNend
\param[in]  u32URINum  The number of information of maturity level .  CNcomment:���˼���Ϣnumber  CNend
\param[in]  pstPVRURI   The information of maturity rate                   CNcomment:���˼���Ϣ CNend

\retval ::HI_SUCCESS  Get successfully                  CNcomment:��ȡ�ɹ� CNend
\retval ::HI_FAILURE  Fail to get.                          CNcomment:��ȡʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_GetURI( HI_CHAR * pCAPrivateFileName ,HI_U32 u32URINum, HI_UNF_PVR_URI_S* pstURI);

/**
\brief  Get the corresponding information of fingerprint based on the number from the file of CA private data
CNcomment: ����number ��CA ˽�������ļ��л�ȡ��Ӧ��ָ����Ϣ CNend
\attention \n
None CNcomment:�� CNend

\param[in]  pCAPrivateFileName  The name of CA private data file .      CNcomment:CA ˽�������ļ����� CNend
\param[in]  u32FPNum  The number of information of fingerprint .  CNcomment:ָ����Ϣnumber  CNend
\param[in]  pstPVRURI   The information of fingerprint                   CNcomment:ָ����Ϣ CNend

\retval ::HI_SUCCESS  Get successfully                  CNcomment:��ȡ�ɹ� CNend
\retval ::HI_FAILURE  Fail to get.                          CNcomment:��ȡʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_GetFP( HI_CHAR * pCAPrivateFileName,HI_U32 u32FPNum,HI_UNF_PVR_FP_INFO_S* pstFPInfo);

/**
\brief  Get the numbers of maturity rate and fingerprint from the file of CA private data
CNcomment: ��CA ˽�������ļ��л�ȡ���˼���ָ����Ϣ������ CNend
\attention \n
None CNcomment:�� CNend

\param[in]  pCAPrivateFileName  The name of CA private data file .        CNcomment:CA ˽�������ļ����� CNend
\param[in]  u32URINum  The numbers of information of maturity rate .   CNcomment:���˼���Ϣ������ CNend
\param[in]  u32FPNum   The numbers of information of fingerprint           CNcomment:ָ����Ϣ������ CNend

\retval ::HI_SUCCESS  Get successfully                  CNcomment:��ȡ�ɹ� CNend
\retval ::HI_FAILURE  Fail to get.                          CNcomment:��ȡʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_GetURIAndFPNum( HI_CHAR * pCAPrivateFileName,HI_U32* u32URINum,HI_U32* u32FPNum);

/**
\brief  Calculte the AES_CMAC value of data  
CNcomment: �������ݵ�AES_CMAC ֵ CNend
\attention \n
None CNcomment:�� CNend

\param[in]  buffer  pointer of data buffer .        CNcomment:����buffer ָ�� CNend
\param[in]  Length  The length  of data .   CNcomment:���ݳ��� CNend
\param[in]  Key   The key used in Calculte the AES_CMAC of data           CNcomment: AES_CMAC ������ʹ�õ�key  CNend
\param[out]  MAC   The AES_CMAC value          CNcomment:AES_CMAC ֵ CNend

\retval ::HI_SUCCESS  Success                 CNcomment:�ɹ� CNend
\retval ::HI_FAILURE    Failure                     CNcomment:ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_CalculteAES_CMAC(HI_U8 *buffer, HI_U32 Length, HI_U8 Key[16], HI_U8 MAC[16]);

/**
\brief  Get the status of PVR recording  
CNcomment: ��ȡ PVR ¼����Ϣ CNend
\attention \n
None CNcomment:�� CNend

\param[in]  u32RecChnID  The channel ID of record.        CNcomment:¼��ͨ��ID  CNend
\param[out]  SessionKey1  The Session key1 of  PVR recording .   CNcomment:   PVR ¼�Ƽ���session key 1.  CNend
\param[out]  CurrentSessionKey2  The Session key2 of  PVR recording .   CNcomment:  ��ǰ ���� ʹ�õ� PVR ¼�� session key 2.  CNend


\retval ::HI_SUCCESS  Success                 CNcomment:�ɹ� CNend
\retval ::HI_FAILURE    Failure                     CNcomment:ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_PVR_GetRecStatus(HI_U32 u32RecChnID, HI_U8 SessionKey1[16], HI_U8 CurrentSessionKey2[16]);

/**
\brief Sets the algorithm of the SP key ladder CNcomment:����SP key ladder���㷨    CNend
\attention \n
You must set an algorithm before using a key ladder in a session. The default algorithm is TDES.
It is recommended that you retain the algorithm in a session.
CNcomment:ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_ALG_TYPE_TDES��\n
���λỰ�����У����鱣���㷨���ȶ����䡣 CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetSPAlg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief Obtains the algorithm of the SP key ladder CNcomment: ��ȡ SP key ladder���㷨    CNend
\attention \n
None CNcomment:�� CNend
\param[in] pEnType Key ladder algorithm CNcomment:pEnType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetSPAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType);

/**
\brief Sets the SP key ladder stage CNcomment:����SP key ladder�ļ���    CNend
\attention \n
The key ladder stage can be set only once before delivery and cannot be changed. Please use default value.
CNcomment:�����г���ʱ���� ��������һ�� ���ɸ���,������ʹ�øýӿڸı�stage  CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage  key ladder����\n ȡֵֻ��ΪHI_UNF_ADVCA_KEYLADDER_lev2 ���� HI_UNF_ADVCA_KEYLADDER_lev3  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetSPKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief Obtains the SP key ladder stage CNcomment:��ȡSP key ladder�ļ��� CNend
\attention \n
None CNcomment:�� CNend
\param[out] penStage Key ladder stage CNcomment:penStage   key ladder���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetSPKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);


/**
\brief Sets session keys for a SP key ladder CNcomment:ΪSP key ladder���ûỰ��Կ    CNend
\attention \n
The stage of the session key cannot be greater than the configured stage of the key ladder. The last stage of the session key is configured by calling the API of the CIPHER module rather than this API.
That is, only session key 1 and session key 2 need to be configured for a 3-stage key ladder.
Only session key 1 needs to be configured for a 2-stage key ladder.
You need to set the key ladder stage by calling HI_UNF_ADVCA_SetSPKeyLadderStage first.
 Session keys can be set during initialization or changed at any time.
CNcomment:ע�����õļ������ܳ������õļ���ֵ�����һ����Descramblerģ���ڲ����ã�����ͨ���˽ӿ����á�\n
Ҳ����˵������3��key ladder��ֻ�����ûỰ��Կ1�ͻỰ��Կ2��\n
����2����key ladder��ֻ�����ûỰ��Կ1��\n
���ȵ���HI_UNF_ADVCA_SetSPKeyLadderStage����key ladder������\n
�Ự��Կ���Գ�ʼʱ����һ�Σ�Ҳ������ʱ�޸ġ� CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage    ��Կ������[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]  CNend
\param[in] pu8Key Protection key pointer, 128 bits (16 bytes) in total CNcomment:pu8Key     ������Կָ�룬��128bit(16byte)  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT CA�ȴ��ӽ��ܳ�ʱ CNend
\retval ::HI_ERR_CA_R2R_DECRYPT The CW decryption fails CNcomment:HI_ERR_CA_CW_DECRYPT   CW����ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetSPSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);

/**
\brief Sets the descramble mode of the SP key ladder CNcomment:����SP key ladder�Ľ����㷨    CNend
\attention \n
You must set a descramble mode before using a key ladder in a session. The default algorithm is HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_CI.
It is recommended that you retain the descramble mode in a session.
CNcomment:ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_CI��\n
���λỰ�����У����鱣���㷨���ȶ����䡣 CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetSPDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E enType);

/**
\brief Obtains the descramble mode of the SP key ladder CNcomment: ��ȡ SP key ladder���㷨    CNend
\attention \n
None CNcomment:�� CNend
\param[in] pEnType Key ladder algorithm CNcomment:pEnType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetSPDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E *pEnType);

/** 
\brief Decrypts a block of LPK-encrypted data
CNcomment:�������ܿ����͸�CPU�ľ�����·�����ķ������� (Link Protection)  CNend
\attention
\param[in] pEncryptedBlock Block data encrypted by the LPK CNcomment:pEncryptedBlock   ��LPK���ܵķ������� CNend
\param[out] pPlainBlock Plain block data. The data memory is allocated by the caller CNcomment:pPlainBlock      ���ķ������� �ռ��ɵ����߷���  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS               �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT       CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA   ��������Ƿ� CNend
\retval ::HI_ERR_CA_NOT_SUPPORT The function is not supported CNcomment:HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧�� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ CNend
\retval ::HI_ERR_CA_LPK_DECRYPT The API fails to decrypt the LPK block CNcomment:HI_ERR_CA_LPK_DECRYPT    LPK����ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_DecryptLptBlock(HI_U8 *pEncryptedBlock,HI_U8 *pPlainBlock);

/** 
\brief  Loads link protection keys (LPKs) CNcomment: ����LPK  CNend
\attention
\param[in] pEbcryptedLpk LPK encrypted by R2RROOTKEY CNcomment:pEncryptedLpk  ��R2RROOTKEY���ܵ�LPK  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS               �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT       CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA   ��������Ƿ� CNend
\retval ::HI_ERR_CA_NOT_SUPPORT The function is not supported CNcomment:HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧�� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ CNend
\retval ::HI_ERR_CA_LPK_DECRYPT The API fails to load the LPK CNcomment:HI_ERR_CA_LPK_DECRYPT    LPK����ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/

HI_S32 HI_UNF_ADVCA_LoadLpk(HI_U8 *pEncryptedLpk);

/** 
\brief Decrypts a block of link protection key (LPK)-encrypted data
CNcomment:�������ܿ����͸�CPU�ľ�����·���������� (Link Protection)  CNend
\attention
\param[in] pCipherText buffer of the cipher text to be decrypted  CNcomment:pCipherText   ���� CNend
\param[in] s32TextLen the length of the cipher text should be larger than 8 byte CNcomment:s32TextLen    ���ĳ��� Ҫ�����һ��Block���� 8byte  CNend
\param[out] pPlainText the buffer to store the clear text CNcomment:pPlainText   ���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS               �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT       CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA   ��������Ƿ� CNend
\retval ::HI_ERR_CA_NOT_SUPPORT The function is not supported CNcomment:HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧�� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ CNend
\retval ::HI_ERR_CA_LPK_DECRYPT The API fails to decrypt the LPK Param CNcomment:HI_ERR_CA_LPK_DECRYPT    LPK����ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_DecryptLptParam(HI_U8 *pCipherText,HI_S32 s32TextLen,HI_U8 *pPlainText);


/**
  \brief this function is used by the Novel CA for the encryption and decryption setting
   CNcomment:Novel�ڴ�ӽ����㷨��key���� CNend
  \attention \n
  This function is used for the Novel encryption and decrption
  CNcomment:  ���������ṩ�� Novel �ڴ�ӽ��ܷ���ʹ�ã��������üӽ��ܹ���keyladder�㷨��key CNend
  \retval ::HI_SUCCESS Success  CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called  CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_NovelCryptologyConfig(HI_VOID);

/**
  \brief Used for Novel CA to encrypt the data  CNcomment:Novel�ڴ����ݼ��� CNend
  \attention \n
  None  CNcomment: �� CNend
  \param[in]  pPlainText: the buffer to store the data to be encrypted CNcomment:pPlainText ����������ָ�� CNend
  \param[in]  TextLen: the length of the data to be encrypted CNcomment:TextLen    ���������ݳ��� CNend
  \param[in]  pCipherText: the buffer to store the encrypted data CNcomment:pCipherText ���ܺ�����ָ�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_NovelDataEncrypt(HI_U8 *pPlainText, HI_U32 TextLen, HI_U8 *pCipherText);

/**
  \brief This function is used for Novel to decrypt the data CNcomment:TextNovel�ڴ����ݽ��� CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  pPlainText: point to the data to be decrypted CNcomment:pPlainText ������������ָ�� CNend
  \param[in]  TextLen: the length of the data to be decrypted CNcomment:TextLen    ���������ݳ��� CNend
  \param[in]  pCipherText: the buffer store the decrypted data CNcomment:pCipherText ���ܺ�����ָ�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_NovelDataDecrypt(HI_U8 *pCipherText, HI_U32 TextLen, HI_U8 *pPlainText);

/**
\brief Sets oem root key�� it's mainly used for widevine keyladder CNcomment:OEM_root_key ��Ҫ����Widevine keyladder    CNend
\attention \n
This root key could only be written only once be careful, thanks 	CNcomment: �����Կֻ����дһ��,��������� CNend
\param[in] pu8OEMRootKey buffer of the input key	CNcomment:pu8OEMRootKey    ������Կ��buffer  CNend
\param[in] u32KeyLen key length of the input CNcomment:u32KeyLen     ������Կ�ĳ��ȣ��޶�Ϊ16�ֽ�  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_R2R_DECRYPT The CW decryption fails CNcomment:HI_ERR_CA_CW_DECRYPT   CW����ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetOEMRootKey(HI_U8 *pu8OEMRootKey, HI_U32 u32KeyLen);

/**
  \brief This function is used to open the DCAS CNcomment:���ڴ�DCAS CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enAlg: DCAS keyladder algorithm CNcomment:enAlg DCAS keyladder�㷨 CNend  
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_DCASOpen(HI_UNF_CIPHER_ALG_E enAlg);

/**
  \brief This function is used to set the session key CNcomment:��������DCAS session��Կ CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enDCASLevel: the DCAS keyladder level CNcomment:enAlg DCAS keyladder���� CNend  
  \param[in]  pu8Key: the DCAS keyladder session key CNcomment:enAlg DCAS keyladder��Կ CNend  
  \param[in]  pu8Output: the output of the DCAS keyladder CNcomment:pu8Output DCAS keyladder��� CNend  
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetDCASSessionKey(HI_UNF_ADVCA_DCAS_KEYLADDER_LEV_E enDCASLevel, HI_U8 au8Key[16], HI_U8 au8Output[16]);

/**
  \brief This function is used to close the DCAS keyladder CNcomment:���ڹر�DCAS CNend
  \attention \n
  None  CNcomment:�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_DCASClose(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_ADVCA_H__ */



