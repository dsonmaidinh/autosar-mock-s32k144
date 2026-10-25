/**
 * @file     CanSM.h
 * @brief    CAN State Manager (CanSM) - public interface.
 * @details  API skeleton per AUTOSAR CP R24-11 SWS CANStateManager.
 *           Scope v1.0: one network with one controller (SWS_CanSM_00653 N/A),
 *           no transceiver/PN/wakeup, no baudrate switching. CanIf callbacks
 *           are in CanSM_CanIf.h, CanSM_MainFunction in SchM_CanSM.h.
 *           AR release macros are kept at 4.7.0 (RTD 2.0.0 baseline);
 *           API signatures follow R24-11.
 *           Project requirements: CANSM_SRS_001..CANSM_SRS_005.
 */

#ifndef CANSM_H
#define CANSM_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "ComM_Types.h"
#include "CanSM_Cfg.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CANSM_VENDOR_ID                     (0xFFFFU)   /* project-local, not a registered vendor */
#define CANSM_MODULE_ID                     (140U)
#define CANSM_INSTANCE_ID                   (0U)
#define CANSM_AR_RELEASE_MAJOR_VERSION      (4U)
#define CANSM_AR_RELEASE_MINOR_VERSION      (7U)
#define CANSM_AR_RELEASE_REVISION_VERSION   (0U)
#define CANSM_SW_MAJOR_VERSION              (0U)
#define CANSM_SW_MINOR_VERSION              (1U)
#define CANSM_SW_PATCH_VERSION              (0U)

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Service IDs (SWS chapter 8.3 / 8.4 / 8.5) */
#define CANSM_SID_INIT                          (0x00U)
#define CANSM_SID_GET_VERSION_INFO              (0x01U)
#define CANSM_SID_REQUEST_COM_MODE              (0x02U)
#define CANSM_SID_GET_CURRENT_COM_MODE          (0x03U)
#define CANSM_SID_CONTROLLER_BUS_OFF            (0x04U)
#define CANSM_SID_MAIN_FUNCTION                 (0x05U)
#define CANSM_SID_CONTROLLER_MODE_INDICATION    (0x07U)
#define CANSM_SID_DEINIT                        (0x14U)

/* Development errors (SWS_CanSM_00654) */
#define CANSM_E_UNINIT                      (0x01U)
#define CANSM_E_PARAM_POINTER               (0x02U)
#define CANSM_E_INVALID_NETWORK_HANDLE      (0x03U)
#define CANSM_E_PARAM_CONTROLLER            (0x04U)
#define CANSM_E_PARAM_TRANSCEIVER           (0x05U)
#define CANSM_E_NOT_IN_NO_COM               (0x0BU)

/* Runtime errors (SWS_CanSM_00664) */
#define CANSM_E_MODE_REQUEST_TIMEOUT        (0x0AU)

/*==================================================================================================
*                                    STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
 * @brief    Post-build configuration of the CanSM (SWS_CanSM_00597).
 * @details  Implementation specific: network CAN0 -> controller FLEXCAN_0,
 *           bus-off recovery L1 10 ms x5, L2 1000 ms, Dem event CANSM_E_BUS_OFF
 *           (docs/Mock.docx 1.8, X-01).
 */
typedef struct
{
    uint8 CanSM_Dummy;  /* TODO(CANSM_SRS_001/005): add network and bus-off configuration (X-01) */
} CanSM_ConfigType;

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Initializes the CanSM module.
 * @details    SWS: SWS_CanSM_00023 | Service ID: 0x00 | classic-platform: kept
 *             Behaviour: SWS_CanSM_00423. Project: CANSM_SRS_001
 * @param[in]  ConfigPtr  Pointer to init structure for the post build parameters of the CanSM.
 */
void CanSM_Init(const CanSM_ConfigType* ConfigPtr);

/**
 * @brief      De-initializes the CanSM module.
 * @details    SWS: SWS_CanSM_91001 | Service ID: 0x14 | classic-platform: not present, added.
 */
void CanSM_DeInit(void);

/**
 * @brief      Returns the version information of this module.
 * @details    SWS: SWS_CanSM_00024 | Service ID: 0x01 | classic-platform: macro -> function
 * @param[out] VersionInfo  Pointer to where to store the version information.
 */
void CanSM_GetVersionInfo(Std_VersionInfoType* VersionInfo);

/**
 * @brief      Requests a communication mode for the given CAN network.
 * @details    SWS: SWS_CanSM_00062 | Service ID: 0x02 | classic-platform: kept
 *             Behaviour: SWS_CanSM_00184, SWS_CanSM_00555, SWS_CanSM_00182.
 *             Project: CANSM_SRS_002
 * @param[in]  network    Handle of the addressed CAN network.
 * @param[in]  ComM_Mode  Requested communication mode.
 * @return     E_OK service accepted, E_NOT_OK service denied.
 */
Std_ReturnType CanSM_RequestComMode(NetworkHandleType network, ComM_ModeType ComM_Mode);

/**
 * @brief      Returns the current communication mode of the given CAN network.
 * @details    SWS: SWS_CanSM_00063 | Service ID: 0x03 | classic-platform: kept
 *             Behaviour: SWS_CanSM_00282.
 * @param[in]  network       Network handle whose current communication mode shall be put out.
 * @param[out] ComM_ModePtr  Pointer where the current communication mode shall be put out.
 * @return     E_OK service accepted, E_NOT_OK service denied.
 */
Std_ReturnType CanSM_GetCurrentComMode(NetworkHandleType network, ComM_ModeType* ComM_ModePtr);

#ifdef __cplusplus
}
#endif

#endif /* CANSM_H */
