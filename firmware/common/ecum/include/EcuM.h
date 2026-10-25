/**
 * @file     EcuM.h
 * @brief    ECU State Manager (EcuM) - public interface (tailored, no OS).
 * @details  API skeleton per AUTOSAR CP R24-11 SWS ECUStateManager.
 *           Tailoring: only the STARTUP part of EcuM_Init (StartPreOS) is
 *           used; there is no OS, no sleep and no shutdown target handling
 *           (SWS_EcuM_02932 / 02838 N/A, see docs/Mock.docx 3.11.2).
 *           AR release macros are kept at 4.7.0 to pass the inter-module
 *           version checks of NXP RTD 2.0.0; API signatures follow R24-11.
 *           Project requirements: ECUM_SRS_001..ECUM_SRS_004.
 */

#ifndef ECUM_H
#define ECUM_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "EcuM_Cfg.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ECUM_VENDOR_ID                      (0xFFFFU)   /* project-local, not a registered vendor */
#define ECUM_MODULE_ID                      (10U)
#define ECUM_INSTANCE_ID                    (0U)
#define ECUM_AR_RELEASE_MAJOR_VERSION       (4U)
#define ECUM_AR_RELEASE_MINOR_VERSION       (7U)
#define ECUM_AR_RELEASE_REVISION_VERSION    (0U)
#define ECUM_SW_MAJOR_VERSION               (0U)
#define ECUM_SW_MINOR_VERSION               (1U)
#define ECUM_SW_PATCH_VERSION               (0U)

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Service IDs (SWS chapter 8.3 / 8.4 / 8.5) */
#define ECUM_SID_GET_VERSION_INFO           (0x00U)
#define ECUM_SID_INIT                       (0x01U)
#define ECUM_SID_SET_WAKEUP_EVENT           (0x0CU)
#define ECUM_SID_AL_DRIVER_INIT_ZERO        (0x31U)
#define ECUM_SID_AL_DRIVER_INIT_ONE         (0x33U)
#define ECUM_SID_ERROR_HOOK                 (0x30U)
#define ECUM_SID_CHECK_WAKEUP               (0x49U)
#define ECUM_SID_AL_RESET                   (0x4CU)

/* Development errors (SWS_EcuM_04032) - values are assigned by implementation */
#define ECUM_E_UNINIT                       (0x10U)
#define ECUM_E_SERVICE_DISABLED             (0x11U)
#define ECUM_E_INVALID_PAR                  (0x13U)
#define ECUM_E_MULTIPLE_RUN_REQUESTS        (0x14U)
#define ECUM_E_MISMATCHED_RUN_RELEASE       (0x15U)
#define ECUM_E_STATE_PAR_OUT_OF_RANGE       (0x16U)
#define ECUM_E_UNKNOWN_WAKEUP_SOURCE        (0x17U)
#define ECUM_E_INIT_FAILED                  (0x18U)
#define ECUM_E_PARAM_POINTER                (0x19U)

/* Runtime errors (SWS_EcuM_91003) - value assigned by implementation */
#define ECUM_E_WAKEUP_TIMEOUT               (0x20U)

/* Predefined wakeup sources, EcuM_WakeupSourceType (SWS_EcuM_04040) */
#define ECUM_WKSOURCE_POWER                 ((EcuM_WakeupSourceType)0x01U)
#define ECUM_WKSOURCE_RESET                 ((EcuM_WakeupSourceType)0x02U)
#define ECUM_WKSOURCE_INTERNAL_RESET        ((EcuM_WakeupSourceType)0x04U)
#define ECUM_WKSOURCE_INTERNAL_WDG          ((EcuM_WakeupSourceType)0x08U)
#define ECUM_WKSOURCE_EXTERNAL_WDG          ((EcuM_WakeupSourceType)0x10U)

/* Reset mechanisms, EcuM_ResetType (SWS_EcuM_04044) */
#define ECUM_RESET_MCU                      ((EcuM_ResetType)0U)
#define ECUM_RESET_WDG                      ((EcuM_ResetType)1U)
#define ECUM_RESET_IO                       ((EcuM_ResetType)2U)

/*==================================================================================================
*                                    STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief Bit field of wakeup sources (SWS_EcuM_04040). */
typedef uint32 EcuM_WakeupSourceType;

/** @brief Reset mechanisms supported by EcuM (SWS_EcuM_04044). */
typedef uint8 EcuM_ResetType;

/**
 * @brief    Post-build configuration of EcuM (SWS_EcuM_04038, SWS_EcuM_02801).
 * @details  Holds pointers to the ConfigType of every module initialized by EcuM.
 */
typedef struct
{
    uint8 EcuM_Dummy;   /* TODO: add Mcu/Port/Gpt/Can/CanIf/... config pointers (ECUM_SRS_001) */
} EcuM_ConfigType;

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Returns the version information of this module.
 * @details    SWS: SWS_EcuM_02813 | Service ID: 0x00
 * @param[out] versioninfo  Pointer to where to store the version information.
 */
void EcuM_GetVersionInfo(Std_VersionInfoType* versioninfo);

/**
 * @brief      Initializes the ECU state manager and carries out the startup procedure.
 * @details    SWS: SWS_EcuM_02811 | Service ID: 0x01
 *             Tailored StartPreOS sequence (SWS_EcuM_02411, SWS_EcuM_04145, SWS_EcuM_02603).
 *             Project: ECUM_SRS_001 (init order), ECUM_SRS_003 (operation cycle start).
 */
void EcuM_Init(void);

/**
 * @brief      Sets the wakeup event.
 * @details    SWS: SWS_EcuM_02826 | Service ID: 0x0c
 *             Called by MCAL drivers (e.g. RTD Gpt/Can) when wakeup support is enabled.
 * @param[in]  sources  Value to be set.
 */
void EcuM_SetWakeupEvent(EcuM_WakeupSourceType sources);

/**
 * @brief      Polls the wakeup sources.
 * @details    SWS: SWS_EcuM_91007 | Service ID: 0x49
 * @param[in]  wakeupSource  Wakeup sources to be checked.
 */
void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource);

#ifdef __cplusplus
}
#endif

#endif /* ECUM_H */
