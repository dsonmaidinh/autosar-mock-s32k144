/**
 * @file     CanSM_Cfg.h
 * @brief    CanSM pre-compile configuration - APPLICATION image.
 * @details  Configuration skeleton: switches and symbolic names only. The
 *           configuration content is completed on the feature branch (X-01).
 */

#ifndef CANSM_CFG_H
#define CANSM_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                    CONFIGURATION PARAMETERS
==================================================================================================*/
/** Development error detection: on in Debug_FLASH (DET_ENABLED), off in Release_FLASH */
#if defined(DET_ENABLED)
#define CANSM_DEV_ERROR_DETECT              (STD_ON)
#else
#define CANSM_DEV_ERROR_DETECT              (STD_OFF)
#endif
/** <Mod>_GetVersionInfo API */
#define CANSM_VERSION_INFO_API              (STD_ON)

/** CanSMMainFunctionTimePeriod [ms] */
#define CANSM_MAIN_FUNCTION_PERIOD_MS       (10U)
/** Bus-off recovery: L1 period, L1 -> L2 counter, L2 period (CANSM_SRS_005) [P] */
#define CANSM_BOR_TIME_L1_MS                (10U)
#define CANSM_BOR_COUNTER_L1_TO_L2          (5U)
#define CANSM_BOR_TIME_L2_MS                (1000U)
/** Report CANSM_E_BUS_OFF to the Dem (SWS_CanSM_00522). Off in the bootloader (no Dem). */
#define CANSM_DEM_EVENT_BUS_OFF_ENABLED     (STD_ON)

/** Configuration set passed to CanSM_Init (defined in CanSM_Cfg.c) */
extern const CanSM_ConfigType CanSM_Config;

#ifdef __cplusplus
}
#endif

#endif /* CANSM_CFG_H */
