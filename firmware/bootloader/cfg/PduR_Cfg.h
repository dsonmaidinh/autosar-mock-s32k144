/**
 * @file     PduR_Cfg.h
 * @brief    PduR pre-compile configuration - BOOTLOADER image.
 * @details  Configuration skeleton: switches and symbolic names only. The
 *           configuration content is completed on the feature branch (T-05).
 */

#ifndef PDUR_CFG_H
#define PDUR_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "PduR_Types.h"

/*==================================================================================================
*                                    CONFIGURATION PARAMETERS
==================================================================================================*/
/** Development error detection: on in Debug_FLASH (DET_ENABLED), off in Release_FLASH */
#if defined(DET_ENABLED)
#define PDUR_DEV_ERROR_DETECT              (STD_ON)
#else
#define PDUR_DEV_ERROR_DETECT              (STD_OFF)
#endif
/** <Mod>_GetVersionInfo API */
#define PDUR_VERSION_INFO_API              (STD_ON)

/* Routing paths (docs/Mock.docx 1.6): 0x7E0 -> Dcm, 0x7DF -> Dcm, Dcm -> 0x7E8 */

/** Configuration set passed to PduR_Init (defined in PduR_PBcfg.c) */
extern const PduR_PBConfigType PduR_Config;

#ifdef __cplusplus
}
#endif

#endif /* PDUR_CFG_H */
