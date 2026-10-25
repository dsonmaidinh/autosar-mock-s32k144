/**
 * @file     CanIf_Cfg.h
 * @brief    CanIf pre-compile configuration - BOOTLOADER image.
 * @details  Configuration skeleton: switches and symbolic names only. The
 *           configuration content is completed on the feature branch (C-03).
 */

#ifndef CANIF_CFG_H
#define CANIF_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "CanIf_Types.h"

/*==================================================================================================
*                                    CONFIGURATION PARAMETERS
==================================================================================================*/
/** Development error detection: on in Debug_FLASH (DET_ENABLED), off in Release_FLASH */
#if defined(DET_ENABLED)
#define CANIF_DEV_ERROR_DETECT              (STD_ON)
#else
#define CANIF_DEV_ERROR_DETECT              (STD_OFF)
#endif
/** <Mod>_GetVersionInfo API */
#define CANIF_VERSION_INFO_API              (STD_ON)

/** CanIfPrivateDataLengthCheck (SWS_CANIF_00168, CANIF_SRS_006) */
#define CANIF_PRIVATE_DATA_LENGTH_CHECK     (STD_ON)

/** Configuration set passed to CanIf_Init (defined in CanIf_PBcfg.c) */
extern const CanIf_ConfigType CanIf_Config;

#ifdef __cplusplus
}
#endif

#endif /* CANIF_CFG_H */
