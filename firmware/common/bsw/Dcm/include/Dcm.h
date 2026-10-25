/**
 * @file     Dcm.h
 * @brief    Diagnostic Communication Manager (Dcm) - public interface.
 * @details  API skeleton per AUTOSAR CP R24-11 SWS DiagnosticCommunicationManager.
 *           Scope v1.0: UDS on CAN, services of docs/Mock.docx 1.4; no ROE, no
 *           OBD, no ReadMemory/Upload. ComM callbacks in Dcm_ComM.h, callouts in
 *           Dcm_Externals.h, Dcm_MainFunction in SchM_Dcm.h.
 *           AR release macros are kept at 4.7.0 (RTD 2.0.0 baseline);
 *           API signatures follow R24-11.
 *           Project requirements: DCM_SRS_001..DCM_SRS_016.
 */

#ifndef DCM_H
#define DCM_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Dcm_Types.h"
#include "Dcm_Cfg.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define DCM_VENDOR_ID                       (0xFFFFU)   /* project-local, not a registered vendor */
#define DCM_MODULE_ID                       (53U)
#define DCM_INSTANCE_ID                     (0U)
#define DCM_AR_RELEASE_MAJOR_VERSION        (4U)
#define DCM_AR_RELEASE_MINOR_VERSION        (7U)
#define DCM_AR_RELEASE_REVISION_VERSION     (0U)
#define DCM_SW_MAJOR_VERSION                (0U)
#define DCM_SW_MINOR_VERSION                (1U)
#define DCM_SW_PATCH_VERSION                (0U)

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Service IDs (SWS chapter 8.3 / 8.4 / 8.5 / 8.6) */
#define DCM_SID_INIT                            (0x01U)
#define DCM_SID_GET_SES_CTRL_TYPE               (0x06U)
#define DCM_SID_GET_SECURITY_LEVEL              (0x0DU)
#define DCM_SID_COMM_NO_COM_MODE_ENTERED        (0x21U)
#define DCM_SID_COMM_SILENT_COM_MODE_ENTERED    (0x22U)
#define DCM_SID_COMM_FULL_COM_MODE_ENTERED      (0x23U)
#define DCM_SID_GET_VERSION_INFO                (0x24U)
#define DCM_SID_MAIN_FUNCTION                   (0x25U)
#define DCM_SID_WRITE_MEMORY                    (0x27U)
#define DCM_SID_RESET_TO_DEFAULT_SESSION        (0x2AU)
#define DCM_SID_PROCESS_REQUEST_DOWNLOAD        (0x30U)
#define DCM_SID_PROCESS_REQUEST_TRANSFER_EXIT   (0x32U)
#define DCM_SID_COPY_TX_DATA                    (0x43U)
#define DCM_SID_COPY_RX_DATA                    (0x44U)
#define DCM_SID_TP_RX_INDICATION                (0x45U)
#define DCM_SID_START_OF_RECEPTION              (0x46U)
#define DCM_SID_TP_TX_CONFIRMATION              (0x48U)
#define DCM_SID_SET_PROG_CONDITIONS             (0x61U)
#define DCM_SID_GET_PROG_CONDITIONS             (0x62U)

/* Development errors (SWS_Dcm_00040). Note: R24-11 assigns 0x02 to both
 * DCM_E_INVALID_VALUE and DCM_E_INTERFACE_RETURN_VALUE. */
#define DCM_E_INVALID_VALUE                 (0x02U)
#define DCM_E_INTERFACE_RETURN_VALUE        (0x02U)
#define DCM_E_UNINIT                        (0x05U)
#define DCM_E_PARAM                         (0x06U)
#define DCM_E_PARAM_POINTER                 (0x07U)
#define DCM_E_INIT_FAILED                   (0x08U)
#define DCM_E_SET_PROG_CONDITIONS_FAIL      (0x09U)

/* Runtime errors (SWS_Dcm_01416) */
#define DCM_E_INTERFACE_TIMEOUT             (0x01U)
#define DCM_E_INTERFACE_BUFFER_OVERFLOW     (0x03U)

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Initializes the Dcm module.
 * @details    SWS: SWS_Dcm_00037 | Service ID: 0x01 | classic-platform: kept
 *             Calls Dcm_GetProgConditions at init (SWS_Dcm_00536, SWS_Dcm_00544).
 * @param[in]  ConfigPtr  Pointer to configuration set in Variant PostBuild.
 */
void Dcm_Init(const Dcm_ConfigType* ConfigPtr);

/**
 * @brief      Returns the version information of this module.
 * @details    SWS: SWS_Dcm_00065 | Service ID: 0x24 | classic-platform: macro -> function
 * @param[out] versionInfo  Pointer to where to store the version information.
 */
void Dcm_GetVersionInfo(Std_VersionInfoType* versionInfo);

/**
 * @brief      Provides the active security level value.
 * @details    SWS: SWS_Dcm_00338 | Service ID: 0x0d | classic-platform: kept
 *             Project: DCM_SRS_003, DCM_SRS_007
 * @param[out] SecLevel  Active security level value.
 * @return     E_OK always.
 */
Std_ReturnType Dcm_GetSecurityLevel(Dcm_SecLevelType* SecLevel);

/**
 * @brief      Provides the active session control type value.
 * @details    SWS: SWS_Dcm_00339 | Service ID: 0x06 | classic-platform: kept
 *             Project: DCM_SRS_002, DCM_SRS_006
 * @param[out] SesCtrlType  Active session control type value.
 * @return     E_OK always.
 */
Std_ReturnType Dcm_GetSesCtrlType(Dcm_SesCtrlType* SesCtrlType);

/**
 * @brief      Resets the session to the default session.
 * @details    SWS: SWS_Dcm_00520 | Service ID: 0x2a | classic-platform: kept
 *             Behaviour: SWS_Dcm_01670, SWS_Dcm_00139. Project: DCM_SRS_008
 * @return     E_OK always.
 */
Std_ReturnType Dcm_ResetToDefaultSession(void);

/*==================================================================================================
*                           TP CALLBACK PROTOTYPES (called by PduR)
==================================================================================================*/
/**
 * @brief      Called at the start of receiving an N-SDU.
 * @details    SWS: SWS_Dcm_00094 | Service ID: 0x46
 *             classic-platform: added parameter info (R24-11). Project: DCM_SRS_016
 * @param[in]  id             Identification of the I-PDU.
 * @param[in]  info           Data of the first frame or single frame (may be NULL_PTR).
 * @param[in]  TpSduLength    Total length of the N-SDU to be received.
 * @param[out] bufferSizePtr  Available receive buffer in the receiving module.
 * @return     BUFREQ_OK, BUFREQ_E_NOT_OK, BUFREQ_E_OVFL.
 */
BufReq_ReturnType Dcm_StartOfReception(PduIdType id, const PduInfoType* info,
                                       PduLengthType TpSduLength, PduLengthType* bufferSizePtr);

/**
 * @brief      Called to provide the received data of an I-PDU segment (N-PDU) to the Dcm.
 * @details    SWS: SWS_Dcm_00556 | Service ID: 0x44
 *             classic-platform: info made const (R24-11). Project: DCM_SRS_016
 * @param[in]  id             Identification of the received I-PDU.
 * @param[in]  info           Source buffer and number of bytes to be copied.
 * @param[out] bufferSizePtr  Available receive buffer after data has been copied.
 * @return     BUFREQ_OK, BUFREQ_E_NOT_OK.
 */
BufReq_ReturnType Dcm_CopyRxData(PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr);

/**
 * @brief      Called after an I-PDU has been received via the TP API.
 * @details    SWS: SWS_Dcm_00093 | Service ID: 0x45
 *             classic-platform: NotifResultType -> Std_ReturnType (R24-11).
 *             Project: DCM_SRS_001..DCM_SRS_005, DCM_SRS_016
 * @param[in]  id      Identification of the received I-PDU.
 * @param[in]  result  E_OK reception successful, E_NOT_OK reception failed.
 */
void Dcm_TpRxIndication(PduIdType id, Std_ReturnType result);

/**
 * @brief      Called to acquire the transmit data of an I-PDU segment (N-PDU).
 * @details    SWS: SWS_Dcm_00092 | Service ID: 0x43
 *             classic-platform: info and retry made const (R24-11). Project: DCM_SRS_016
 * @param[in]  id                Identification of the transmitted I-PDU.
 * @param[in]  info              Destination buffer and number of bytes to be copied.
 * @param[in]  retry             Retry information, NULL_PTR if retry is not supported.
 * @param[out] availableDataPtr  Remaining number of bytes available in the TX buffer.
 * @return     BUFREQ_OK, BUFREQ_E_BUSY, BUFREQ_E_NOT_OK.
 */
BufReq_ReturnType Dcm_CopyTxData(PduIdType id, const PduInfoType* info,
                                 const RetryInfoType* retry, PduLengthType* availableDataPtr);

/**
 * @brief      Called after the I-PDU has been transmitted on its network.
 * @details    SWS: SWS_Dcm_00351 | Service ID: 0x48
 *             classic-platform: NotifResultType -> Std_ReturnType (R24-11).
 *             Behaviour: SWS_Dcm_00311 (session change in confirmation), SWS_Dcm_01423.
 *             Project: DCM_SRS_006, DCM_SRS_016, ECUM_SRS_004
 * @param[in]  id      Identification of the transmitted I-PDU.
 * @param[in]  result  E_OK transmission successful, E_NOT_OK transmission failed.
 */
void Dcm_TpTxConfirmation(PduIdType id, Std_ReturnType result);

#ifdef __cplusplus
}
#endif

#endif /* DCM_H */
