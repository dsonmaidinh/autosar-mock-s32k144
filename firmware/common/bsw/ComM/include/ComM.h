/**
 * @file     ComM.h
 * @brief    Communication Manager (ComM) - public interface.
 * @details  API skeleton per AUTOSAR CP R24-11 SWS COMManager.
 *           Scope v1.0: one channel CAN0, no NM, no PNC, no inhibition
 *           (SWS_ComM_00869 / 00890 N/A). Dcm callbacks in ComM_Dcm.h,
 *           BswM callback in ComM_BswM.h, ComM_MainFunction_CAN0 in SchM_ComM.h.
 *           AR release macros are kept at 4.7.0 (RTD 2.0.0 baseline);
 *           API signatures follow R24-11.
 *           Project requirements: COMM_SRS_001..COMM_SRS_004.
 */

#ifndef COMM_H
#define COMM_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "ComM_Types.h"
#include "ComM_Cfg.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define COMM_VENDOR_ID                      (0xFFFFU)   /* project-local, not a registered vendor */
#define COMM_MODULE_ID                      (12U)
#define COMM_INSTANCE_ID                    (0U)
#define COMM_AR_RELEASE_MAJOR_VERSION       (4U)
#define COMM_AR_RELEASE_MINOR_VERSION       (7U)
#define COMM_AR_RELEASE_REVISION_VERSION    (0U)
#define COMM_SW_MAJOR_VERSION               (0U)
#define COMM_SW_MINOR_VERSION               (1U)
#define COMM_SW_PATCH_VERSION               (0U)

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Service IDs (SWS chapter 8.3 / 8.4 / 8.5) */
#define COMM_SID_INIT                       (0x01U)
#define COMM_SID_DEINIT                     (0x02U)
#define COMM_SID_GET_STATUS                 (0x03U)
#define COMM_SID_REQUEST_COM_MODE           (0x05U)
#define COMM_SID_GET_REQUESTED_COM_MODE     (0x07U)
#define COMM_SID_GET_CURRENT_COM_MODE       (0x08U)
#define COMM_SID_GET_VERSION_INFO           (0x10U)
#define COMM_SID_DCM_ACTIVE_DIAGNOSTIC      (0x1FU)
#define COMM_SID_DCM_INACTIVE_DIAGNOSTIC    (0x20U)
#define COMM_SID_BUSSM_MODE_INDICATION      (0x33U)
#define COMM_SID_COMMUNICATION_ALLOWED      (0x35U)
#define COMM_SID_MAIN_FUNCTION              (0x60U)

/* Development errors (SWS_ComM_00234) */
#define COMM_E_UNINIT                       (0x01U)
#define COMM_E_WRONG_PARAMETERS             (0x02U)
#define COMM_E_PARAM_POINTER                (0x03U)
#define COMM_E_INIT_FAILED                  (0x04U)

/* Runtime errors (SWS_ComM_91110) */
#define COMM_E_READ_NV_FAILED               (0x01U)

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Initializes the AUTOSAR Communication Manager and restarts the internal state machines.
 * @details    SWS: SWS_ComM_00146 | Service ID: 0x01 | classic-platform: kept
 *             Project: COMM_SRS_001
 * @param[in]  ConfigPtr  Pointer to post-build configuration data.
 */
void ComM_Init(const ComM_ConfigType* ConfigPtr);

/**
 * @brief      De-initializes the AUTOSAR Communication Manager.
 * @details    SWS: SWS_ComM_00147 | Service ID: 0x02 | classic-platform: kept
 *             Behaviour: SWS_ComM_00794.
 */
void ComM_DeInit(void);

/**
 * @brief      Returns the initialization status of the AUTOSAR Communication Manager.
 * @details    SWS: SWS_ComM_00242 | Service ID: 0x03 | classic-platform: kept
 *             Project: COMM_SRS_001
 * @param[out] Status  COMM_UNINIT or COMM_INIT.
 * @return     E_OK successfully returned, E_NOT_OK not returned.
 */
Std_ReturnType ComM_GetStatus(ComM_InitStatusType* Status);

/**
 * @brief      Requesting of a communication mode by a user.
 * @details    SWS: SWS_ComM_00110 | Service ID: 0x05
 *             classic-platform: kept (ComM_UserHandleType widened to uint16).
 *             Behaviour: SWS_ComM_00612, SWS_ComM_00069. Project: COMM_SRS_001, COMM_SRS_002
 * @param[in]  User     Handle of the user who requests a mode.
 * @param[in]  ComMode  COMM_FULL_COMMUNICATION or COMM_NO_COMMUNICATION.
 * @return     E_OK, E_NOT_OK, COMM_E_MODE_LIMITATION.
 */
Std_ReturnType ComM_RequestComMode(ComM_UserHandleType User, ComM_ModeType ComMode);

/**
 * @brief      Returns the requested communication mode of a user.
 * @details    SWS: SWS_ComM_00079 | Service ID: 0x07 | classic-platform: kept
 * @param[in]  User     Handle of the user.
 * @param[out] ComMode  Requested communication mode of the user.
 * @return     E_OK successfully returned, E_NOT_OK not returned.
 */
Std_ReturnType ComM_GetRequestedComMode(ComM_UserHandleType User, ComM_ModeType* ComMode);

/**
 * @brief      Returns the current communication mode of the channel the user is assigned to.
 * @details    SWS: SWS_ComM_00083 | Service ID: 0x08 | classic-platform: kept
 * @param[in]  User     Handle of the user.
 * @param[out] ComMode  Current communication mode of the corresponding channel.
 * @return     E_OK successfully returned, E_NOT_OK not returned.
 */
Std_ReturnType ComM_GetCurrentComMode(ComM_UserHandleType User, ComM_ModeType* ComMode);

/**
 * @brief      Returns the version information of this module.
 * @details    SWS: SWS_ComM_00370 | Service ID: 0x10 | classic-platform: macro -> function
 * @param[out] Versioninfo  Pointer to where to store the version information.
 */
void ComM_GetVersionInfo(Std_VersionInfoType* Versioninfo);

/*==================================================================================================
*                         CALLBACK PROTOTYPES (called by the bus state manager)
==================================================================================================*/
/**
 * @brief      Indication of the actual bus mode by the corresponding bus state manager (CanSM).
 * @details    SWS: SWS_ComM_00675 | Service ID: 0x33
 *             classic-platform: ComMode passed by value instead of pointer (R24-11).
 *             Project: COMM_SRS_002
 * @param[in]  Channel  Channel handle.
 * @param[in]  ComMode  Current bus communication mode.
 */
void ComM_BusSM_ModeIndication(NetworkHandleType Channel, ComM_ModeType ComMode);

#ifdef __cplusplus
}
#endif

#endif /* COMM_H */
