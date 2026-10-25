/**
 * @file     CanIf.h
 * @brief    CAN Interface (CanIf) - public interface.
 * @details  API skeleton per AUTOSAR CP R24-11 SWS CANInterface.
 *           Prototypes taken from openAUTOSAR/classic-platform where they match
 *           R24-11, otherwise corrected to R24-11 (see docs/Mock.docx 6.2).
 *           AR release macros are kept at 4.7.0 to pass the inter-module
 *           version checks of NXP RTD 2.0.0; API signatures follow R24-11.
 *           Project requirements: CANIF_SRS_001..CANIF_SRS_010.
 */

#ifndef CANIF_H
#define CANIF_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "CanIf_Types.h"
#include "CanIf_Cfg.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CANIF_VENDOR_ID                     (0xFFFFU)   /* project-local, not a registered vendor */
#define CANIF_MODULE_ID                     (60U)
#define CANIF_INSTANCE_ID                   (0U)
#define CANIF_AR_RELEASE_MAJOR_VERSION      (4U)
#define CANIF_AR_RELEASE_MINOR_VERSION      (7U)
#define CANIF_AR_RELEASE_REVISION_VERSION   (0U)
#define CANIF_SW_MAJOR_VERSION              (0U)
#define CANIF_SW_MINOR_VERSION              (1U)
#define CANIF_SW_PATCH_VERSION              (0U)

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Service IDs (SWS chapter 8.3 / 8.4) */
#define CANIF_SID_INIT                          (0x01U)
#define CANIF_SID_SET_CONTROLLER_MODE           (0x03U)
#define CANIF_SID_GET_CONTROLLER_MODE           (0x04U)
#define CANIF_SID_SET_PDU_MODE                  (0x09U)
#define CANIF_SID_GET_PDU_MODE                  (0x0AU)
#define CANIF_SID_GET_VERSION_INFO              (0x0BU)
#define CANIF_SID_TX_CONFIRMATION               (0x13U)
#define CANIF_SID_RX_INDICATION                 (0x14U)
#define CANIF_SID_CONTROLLER_BUS_OFF            (0x16U)
#define CANIF_SID_CONTROLLER_MODE_INDICATION    (0x17U)
#define CANIF_SID_TRANSMIT                      (0x49U)
#define CANIF_SID_CONTROLLER_ERROR_STATE_PASSIVE (0x4FU)
#define CANIF_SID_ERROR_NOTIFICATION            (0x50U)

/* Development errors (SWS_CANIF_91006) */
#define CANIF_E_PARAM_CANID                 (10U)
#define CANIF_E_PARAM_HOH                   (12U)
#define CANIF_E_PARAM_LPDU                  (13U)
#define CANIF_E_PARAM_CONTROLLERID          (15U)
#define CANIF_E_PARAM_WAKEUPSOURCE          (16U)
#define CANIF_E_PARAM_TRCV                  (17U)
#define CANIF_E_PARAM_TRCVMODE              (18U)
#define CANIF_E_PARAM_TRCVWAKEUPMODE        (19U)
#define CANIF_E_PARAM_POINTER               (20U)
#define CANIF_E_PARAM_CTRLMODE              (21U)
#define CANIF_E_PARAM_PDU_MODE              (22U)
#define CANIF_E_PARAM_CAN_ERROR             (23U)
#define CANIF_E_UNINIT                      (30U)
#define CANIF_E_INVALID_TXPDUID             (50U)
#define CANIF_E_INVALID_RXPDUID             (60U)
#define CANIF_E_INIT_FAILED                 (80U)

/* Runtime errors (SWS_CANIF_91007) */
#define CANIF_E_INVALID_DATA_LENGTH         (61U)
#define CANIF_E_DATA_LENGTH_MISMATCH        (62U)
#define CANIF_E_STOPPED                     (70U)
#define CANIF_E_TXPDU_LENGTH_EXCEEDED       (90U)

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Initializes internal and external interfaces of the CanIf.
 * @details    SWS: SWS_CANIF_00001 | Service ID: 0x01 | classic-platform: kept
 *             Behaviour: SWS_CANIF_00085. Project: CANIF_SRS_001
 * @param[in]  ConfigPtr  Pointer to configuration parameter set.
 */
void CanIf_Init(const CanIf_ConfigType* ConfigPtr);

/**
 * @brief      Calls Can_SetControllerMode() for the requested CAN controller.
 * @details    SWS: SWS_CANIF_00003 | Service ID: 0x03
 *             classic-platform: fixed CanIf_ControllerModeType -> Can_ControllerStateType.
 *             Behaviour: SWS_CANIF_00308, SWS_CANIF_00311. Project: CANIF_SRS_008
 * @param[in]  ControllerId    Abstracted CanIf ControllerId.
 * @param[in]  ControllerMode  Requested mode transition.
 * @return     E_OK request accepted, E_NOT_OK request not accepted.
 */
Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode);

/**
 * @brief      Reports about the current status of the requested CAN controller.
 * @details    SWS: SWS_CANIF_00229 | Service ID: 0x04
 *             classic-platform: fixed CanIf_ControllerModeType -> Can_ControllerStateType.
 * @param[in]  ControllerId       Abstracted CanIf ControllerId.
 * @param[out] ControllerModePtr  Pointer to where the current mode is stored.
 * @return     E_OK mode read, E_NOT_OK not read.
 */
Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, Can_ControllerStateType* ControllerModePtr);

/**
 * @brief      Requests transmission of a PDU.
 * @details    SWS: SWS_CANIF_00005 | Service ID: 0x49 | classic-platform: kept
 *             Behaviour: SWS_CANIF_00318, SWS_CANIF_00162, SWS_CANIF_00243, SWS_CANIF_00382.
 *             Project: CANIF_SRS_002, CANIF_SRS_003
 * @param[in]  TxPduId     Identifier of the PDU to be transmitted.
 * @param[in]  PduInfoPtr  Length of and pointer to the PDU data and pointer to MetaData.
 * @return     E_OK transmit request accepted, E_NOT_OK not accepted.
 */
Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);

/**
 * @brief      Changes the PduMode of a channel.
 * @details    SWS: SWS_CANIF_00008 | Service ID: 0x09
 *             classic-platform: fixed CanIf_PduSetModeType -> CanIf_PduModeType.
 *             Behaviour: SWS_CANIF_00874, SWS_CANIF_00341, SWS_CANIF_00860. Project: CANIF_SRS_004
 * @param[in]  ControllerId    All PDUs of the own ECU connected to this controller are affected.
 * @param[in]  PduModeRequest  Requested PDU mode change.
 * @return     E_OK request accepted, E_NOT_OK not accepted.
 */
Std_ReturnType CanIf_SetPduMode(uint8 ControllerId, CanIf_PduModeType PduModeRequest);

/**
 * @brief      Reports the current mode of the requested PDU channel.
 * @details    SWS: SWS_CANIF_00009 | Service ID: 0x0a
 *             classic-platform: fixed CanIf_PduGetModeType -> CanIf_PduModeType.
 * @param[in]  ControllerId  All PDUs of the own ECU connected to this controller are affected.
 * @param[out] PduModePtr    Pointer to where the current PDU mode is stored.
 * @return     E_OK mode read, E_NOT_OK not read.
 */
Std_ReturnType CanIf_GetPduMode(uint8 ControllerId, CanIf_PduModeType* PduModePtr);

/**
 * @brief      Returns the version information of this module.
 * @details    SWS: SWS_CANIF_00158 | Service ID: 0x0b | classic-platform: macro -> function
 * @param[out] VersionInfo  Pointer to where to store the version information.
 */
void CanIf_GetVersionInfo(Std_VersionInfoType* VersionInfo);

/*==================================================================================================
*                        CALLBACK PROTOTYPES (called by Can_43_FLEXCAN)
==================================================================================================*/
/**
 * @brief      Confirms a previously successfully processed transmission of a CAN TxPDU.
 * @details    SWS: SWS_CANIF_00007 | Service ID: 0x13 | classic-platform: kept
 *             Behaviour: SWS_CANIF_00383, SWS_CANIF_00412. Project: CANIF_SRS_007
 * @param[in]  CanTxPduId  L-PDU handle of CAN L-PDU successfully transmitted.
 */
void CanIf_TxConfirmation(PduIdType CanTxPduId);

/**
 * @brief      Indicates a successful reception of a received CAN Rx L-PDU.
 * @details    SWS: SWS_CANIF_00006 | Service ID: 0x14
 *             classic-platform: kept the 4.x variant, removed (Hrh, CanId, Dlc, Sdu) variant.
 *             Behaviour: SWS_CANIF_00389, SWS_CANIF_00030, SWS_CANIF_00168, SWS_CANIF_00416/417/419.
 *             Project: CANIF_SRS_005, CANIF_SRS_006
 * @param[in]  Mailbox     Identifies the HRH and its corresponding CAN Controller.
 * @param[in]  PduInfoPtr  Pointer to the received L-PDU.
 */
void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr);

/**
 * @brief      Indicates a controller BusOff event.
 * @details    SWS: SWS_CANIF_00218 | Service ID: 0x16 | classic-platform: kept
 *             Behaviour: SWS_CANIF_00724, SWS_CANIF_00431, SWS_CANIF_00739. Project: CANIF_SRS_010
 * @param[in]  ControllerId  Abstract CanIf ControllerId assigned to a CAN controller.
 */
void CanIf_ControllerBusOff(uint8 ControllerId);

/**
 * @brief      Indicates a controller state transition.
 * @details    SWS: SWS_CANIF_00699 | Service ID: 0x17
 *             classic-platform: fixed CanIf_ControllerModeType -> Can_ControllerStateType.
 *             Behaviour: SWS_CANIF_00711. Project: CANIF_SRS_009
 * @param[in]  ControllerId    Abstract CanIf ControllerId.
 * @param[in]  ControllerMode  Mode to which the CAN controller transitioned.
 */
void CanIf_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode);

/**
 * @brief      Indicates that the controller entered error passive state.
 * @details    SWS: SWS_CANIF_91008 | Service ID: 0x4f | classic-platform: not present, added.
 *             Called by RTD only when CAN_43_FLEXCAN_ERROR_INTERRUPT_SUPPORT == STD_ON.
 * @param[in]  ControllerId    Abstract CanIf ControllerId.
 * @param[in]  RxErrorCounter  Value of the Rx error counter.
 * @param[in]  TxErrorCounter  Value of the Tx error counter.
 */
void CanIf_ControllerErrorStatePassive(uint8 ControllerId, uint16 RxErrorCounter, uint16 TxErrorCounter);

/**
 * @brief      Indicates a CAN bus error event.
 * @details    SWS: SWS_CANIF_91009 | Service ID: 0x50 | classic-platform: not present, added.
 *             Called by RTD only when CAN_43_FLEXCAN_ERROR_INTERRUPT_SUPPORT == STD_ON.
 * @param[in]  ControllerId   Abstract CanIf ControllerId.
 * @param[in]  Can_ErrorType  Reported CAN error.
 */
void CanIf_ErrorNotification(uint8 ControllerId, Can_ErrorType Can_ErrorType);

#ifdef __cplusplus
}
#endif

#endif /* CANIF_H */
