/**
 * @file     Dem_Cfg.h
 * @brief    Dem pre-compile configuration - APPLICATION image.
 * @details  Configuration skeleton: switches and symbolic names only. The
 *           configuration content is completed on the feature branch (M-02).
 */

#ifndef DEM_CFG_H
#define DEM_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "Dem_Types.h"

/*==================================================================================================
*                                    CONFIGURATION PARAMETERS
==================================================================================================*/
/** Development error detection: on in Debug_FLASH (DET_ENABLED), off in Release_FLASH */
#if defined(DET_ENABLED)
#define DEM_DEV_ERROR_DETECT              (STD_ON)
#else
#define DEM_DEV_ERROR_DETECT              (STD_OFF)
#endif
/** <Mod>_GetVersionInfo API */
#define DEM_VERSION_INFO_API              (STD_ON)

/** Symbolic names of the events (docs/Mock.docx 1.5) */
#define DemConf_DemEventParameter_CANSM_E_BUS_OFF   ((Dem_EventIdType)1U)  /* DTC 0xC07300 */
#define DemConf_DemEventParameter_DUMMY_TEST        ((Dem_EventIdType)2U)  /* DTC 0x9A0113 */
/** Operation cycle and Dcm client (ECUM_SRS_003, DCM_SRS_012) */
#define DemConf_DemOperationCycle_POWER             (0U)
#define DemConf_DemClient_Dcm                       (0U)
/** DemTaskTime [ms] */
#define DEM_TASK_TIME_MS                            (10U)

/** Configuration set passed to Dem_Init (defined in Dem_LCfg.c) */
extern const Dem_ConfigType Dem_Config;

#ifdef __cplusplus
}
#endif

#endif /* DEM_CFG_H */
