/**
 * @file     Dcm_Cfg.h
 * @brief    Dcm pre-compile configuration - APPLICATION image.
 * @details  Configuration skeleton: switches and symbolic names only. The
 *           configuration content is completed on the feature branch (X-07..X-10).
 */

#ifndef DCM_CFG_H
#define DCM_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "Dcm_Types.h"

/*==================================================================================================
*                                    CONFIGURATION PARAMETERS
==================================================================================================*/
/** Development error detection: on in Debug_FLASH (DET_ENABLED), off in Release_FLASH */
#if defined(DET_ENABLED)
#define DCM_DEV_ERROR_DETECT              (STD_ON)
#else
#define DCM_DEV_ERROR_DETECT              (STD_OFF)
#endif
/** <Mod>_GetVersionInfo API */
#define DCM_VERSION_INFO_API              (STD_ON)

/** DcmTaskTime [ms] */
#define DCM_TASK_TIME_MS                    (10U)
/** Diagnostic buffer size [byte] (docs/Mock.docx 1.8): App 256, BL 1026 */
#define DCM_DSL_BUFFER_SIZE                 (256U)
/** Timing [ms]: P2, P2*, S3 (docs/Mock.docx 1.8) */
#define DCM_P2_SERVER_MAX_MS                (50U)
#define DCM_P2STAR_SERVER_MAX_MS            (5000U)
#define DCM_S3_SERVER_MS                    (5000U)
/** Security level of this image: App 0x01 (27 01/02), BL 0x11 (27 11/12) */
#define DCM_SEC_LEVEL_IMAGE                 ((Dcm_SecLevelType)0x01U)

/** Configuration set passed to Dcm_Init (defined in Dcm_LCfg.c) */
extern const Dcm_ConfigType Dcm_Config;

#ifdef __cplusplus
}
#endif

#endif /* DCM_CFG_H */
