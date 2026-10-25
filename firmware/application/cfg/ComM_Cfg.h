/**
 * @file     ComM_Cfg.h
 * @brief    ComM pre-compile configuration - APPLICATION image.
 * @details  Configuration skeleton: switches and symbolic names only. The
 *           configuration content is completed on the feature branch (X-02).
 */

#ifndef COMM_CFG_H
#define COMM_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "ComM_Types.h"

/*==================================================================================================
*                                    CONFIGURATION PARAMETERS
==================================================================================================*/
/** Development error detection: on in Debug_FLASH (DET_ENABLED), off in Release_FLASH */
#if defined(DET_ENABLED)
#define COMM_DEV_ERROR_DETECT              (STD_ON)
#else
#define COMM_DEV_ERROR_DETECT              (STD_OFF)
#endif
/** <Mod>_GetVersionInfo API */
#define COMM_VERSION_INFO_API              (STD_ON)

/** ComMMainFunctionPeriod [ms] */
#define COMM_MAIN_FUNCTION_PERIOD_MS        (10U)
/** Symbolic names of the channel and the user (SWS_ComM_00429) */
#define ComMConf_ComMChannel_CAN0           ((NetworkHandleType)0U)
#define ComMConf_ComMUser_Diag              ((ComM_UserHandleType)0U)

/** Configuration set passed to ComM_Init (defined in ComM_Cfg.c) */
extern const ComM_ConfigType ComM_Config;

#ifdef __cplusplus
}
#endif

#endif /* COMM_CFG_H */
