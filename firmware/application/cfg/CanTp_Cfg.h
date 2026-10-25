/**
 * @file     CanTp_Cfg.h
 * @brief    CanTp pre-compile configuration - APPLICATION image.
 * @details  Configuration skeleton: switches and symbolic names only. The
 *           configuration content is completed on the feature branch (T-04).
 */

#ifndef CANTP_CFG_H
#define CANTP_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "CanTp_Types.h"

/*==================================================================================================
*                                    CONFIGURATION PARAMETERS
==================================================================================================*/
/** Development error detection: on in Debug_FLASH (DET_ENABLED), off in Release_FLASH */
#if defined(DET_ENABLED)
#define CANTP_DEV_ERROR_DETECT              (STD_ON)
#else
#define CANTP_DEV_ERROR_DETECT              (STD_OFF)
#endif
/** <Mod>_GetVersionInfo API */
#define CANTP_VERSION_INFO_API              (STD_ON)

/** CanTpMainFunctionPeriod [ms] (docs/Mock.docx 1.8) */
#define CANTP_MAIN_FUNCTION_PERIOD_MS       (1U)
/** CanTpPaddingByte (SWS_CanTp_00059, CANTP_SRS_009) */
#define CANTP_PADDING_BYTE                  (0xAAU)

/** Configuration set passed to CanTp_Init (defined in CanTp_Cfg.c) */
extern const CanTp_ConfigType CanTp_Config;

#ifdef __cplusplus
}
#endif

#endif /* CANTP_CFG_H */
