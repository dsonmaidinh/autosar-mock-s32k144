/**
 * @file     EcuM_Externals.h
 * @brief    ECU State Manager (EcuM) - callouts (configurable interfaces).
 * @details  Callouts per AUTOSAR CP R24-11 SWS ECUStateManager chapter 8.5,
 *           "available via EcuM_Externals.h". Implemented in EcuM_Callout.c.
 *           Also included by RTD Gpt (wakeup API), therefore it provides the
 *           ECUM_CBK_* version macros expected by RTD 2.0.0.
 */

#ifndef ECUM_EXTERNALS_H
#define ECUM_EXTERNALS_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "EcuM.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ECUM_CBK_VENDOR_ID                      ECUM_VENDOR_ID
#define ECUM_CBK_AR_RELEASE_MAJOR_VERSION       ECUM_AR_RELEASE_MAJOR_VERSION
#define ECUM_CBK_AR_RELEASE_MINOR_VERSION       ECUM_AR_RELEASE_MINOR_VERSION
#define ECUM_CBK_AR_RELEASE_REVISION_VERSION    ECUM_AR_RELEASE_REVISION_VERSION
#define ECUM_CBK_SW_MAJOR_VERSION               ECUM_SW_MAJOR_VERSION
#define ECUM_CBK_SW_MINOR_VERSION               ECUM_SW_MINOR_VERSION
#define ECUM_CBK_SW_PATCH_VERSION               ECUM_SW_PATCH_VERSION

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Driver initialization before the post-build configuration is loaded.
 * @details    SWS: SWS_EcuM_02905 | Service ID: 0x31
 *             Only pre-compile/link-time configured modules (Det, Dem_PreInit).
 *             Project: ECUM_SRS_001
 */
void EcuM_AL_DriverInitZero(void);

/**
 * @brief      Driver initialization and hardware-related startup activities.
 * @details    SWS: SWS_EcuM_02907 | Service ID: 0x33
 *             Mcu, Port, Gpt, Can_43_FLEXCAN, (Mem_43_INFLS in BL) and BSW in the
 *             order given by ECUM_SRS_001.
 */
void EcuM_AL_DriverInitOne(void);

/**
 * @brief      Performs a reset of the given type.
 * @details    SWS: SWS_EcuM_04065 | Service ID: 0x4C
 *             Project: ECUM_SRS_004 (Mcu_PerformReset after diagnostic response confirmation).
 * @param[in]  reset  Type of reset to be performed.
 */
void EcuM_AL_Reset(EcuM_ResetType reset);

/**
 * @brief      Called in case of an inconsistent configuration or failed startup.
 * @details    SWS: SWS_EcuM_02904 | Service ID: 0x30
 * @param[in]  reason  Reason for calling the error hook.
 */
void EcuM_ErrorHook(uint16 reason);

#ifdef __cplusplus
}
#endif

#endif /* ECUM_EXTERNALS_H */
