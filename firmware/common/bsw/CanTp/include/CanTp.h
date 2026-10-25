/**
 * @file     CanTp.h
 * @brief    CAN Transport Layer (CanTp) - public interface.
 * @details  API skeleton per AUTOSAR CP R24-11 SWS CANTransportLayer (ISO 15765-2).
 *           Callbacks for CanIf are "available via CanTp.h" in R24-11.
 *           CanTp_MainFunction is declared in SchM_CanTp.h.
 *           AR release macros are kept at 4.7.0 (RTD 2.0.0 baseline);
 *           API signatures follow R24-11.
 *           Project requirements: CANTP_SRS_001..CANTP_SRS_009.
 */

#ifndef CANTP_H
#define CANTP_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "CanTp_Types.h"
#include "CanTp_Cfg.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CANTP_VENDOR_ID                     (0xFFFFU)   /* project-local, not a registered vendor */
#define CANTP_MODULE_ID                     (35U)
#define CANTP_INSTANCE_ID                   (0U)
#define CANTP_AR_RELEASE_MAJOR_VERSION      (4U)
#define CANTP_AR_RELEASE_MINOR_VERSION      (7U)
#define CANTP_AR_RELEASE_REVISION_VERSION   (0U)
#define CANTP_SW_MAJOR_VERSION              (0U)
#define CANTP_SW_MINOR_VERSION              (1U)
#define CANTP_SW_PATCH_VERSION              (0U)

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Service IDs (SWS chapter 8.3 / 8.4 / 8.5) */
#define CANTP_SID_INIT                      (0x01U)
#define CANTP_SID_SHUTDOWN                  (0x02U)
#define CANTP_SID_MAIN_FUNCTION             (0x06U)
#define CANTP_SID_GET_VERSION_INFO          (0x07U)
#define CANTP_SID_TX_CONFIRMATION           (0x40U)
#define CANTP_SID_RX_INDICATION             (0x42U)
#define CANTP_SID_TRANSMIT                  (0x49U)

/* Development errors (SWS_CanTp_00293) */
#define CANTP_E_PARAM_CONFIG                (0x01U)
#define CANTP_E_PARAM_ID                    (0x02U)
#define CANTP_E_PARAM_POINTER               (0x03U)
#define CANTP_E_INIT_FAILED                 (0x04U)
#define CANTP_E_UNINIT                      (0x20U)
#define CANTP_E_INVALID_TX_ID               (0x30U)
#define CANTP_E_INVALID_RX_ID               (0x40U)

/* Runtime errors (SWS_CanTp_00352) */
#define CANTP_E_PADDING                     (0x70U)
#define CANTP_E_INVALID_TATYPE              (0x90U)
#define CANTP_E_OPER_NOT_SUPPORTED          (0xA0U)
#define CANTP_E_COM                         (0xB0U)
#define CANTP_E_RX_COM                      (0xC0U)
#define CANTP_E_TX_COM                      (0xD0U)

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Initializes the CanTp module.
 * @details    SWS: SWS_CanTp_00208 | Service ID: 0x01 | classic-platform: kept
 *             Behaviour: SWS_CanTp_00030. Project: CANTP_SRS_001
 * @param[in]  CfgPtr  Pointer to the CanTp post-build configuration data.
 */
void CanTp_Init(const CanTp_ConfigType* CfgPtr);

/**
 * @brief      Returns the version information of this module.
 * @details    SWS: SWS_CanTp_00210 | Service ID: 0x07 | classic-platform: macro -> function
 * @param[out] versioninfo  Pointer to where to store the version information.
 */
void CanTp_GetVersionInfo(Std_VersionInfoType* versioninfo);

/**
 * @brief      Shuts down the CanTp module.
 * @details    SWS: SWS_CanTp_00211 | Service ID: 0x02 | classic-platform: kept
 */
void CanTp_Shutdown(void);

/**
 * @brief      Requests transmission of a PDU (SF or segmented FF/CF).
 * @details    SWS: SWS_CanTp_00212 | Service ID: 0x49 | classic-platform: kept
 *             Behaviour: SWS_CanTp_00231, SWS_CanTp_00232, SWS_CanTp_00086, SWS_CanTp_00092.
 *             Project: CANTP_SRS_002, CANTP_SRS_003
 * @param[in]  TxPduId     Identifier of the PDU to be transmitted.
 * @param[in]  PduInfoPtr  Length of and pointer to the PDU data and pointer to MetaData.
 * @return     E_OK transmit request accepted, E_NOT_OK not accepted.
 */
Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);

/*==================================================================================================
*                           CALLBACK PROTOTYPES (called by CanIf)
==================================================================================================*/
/**
 * @brief      Indication of a received PDU from a lower layer communication interface module.
 * @details    SWS: SWS_CanTp_00214 | Service ID: 0x42
 *             classic-platform: PduInfoPtr made const (R24-11).
 *             Behaviour: SWS_CanTp_00079, SWS_CanTp_00329, SWS_CanTp_00064, SWS_CanTp_00269,
 *             SWS_CanTp_00314, SWS_CanTp_00093, SWS_CanTp_00116.
 *             Project: CANTP_SRS_004, CANTP_SRS_005, CANTP_SRS_008, CANTP_SRS_009
 * @param[in]  RxPduId     ID of the received PDU.
 * @param[in]  PduInfoPtr  Length of and pointer to the received data and pointer to MetaData.
 */
void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

/**
 * @brief      Confirmation of a transmitted PDU by the lower layer communication interface module.
 * @details    SWS: SWS_CanTp_00215 | Service ID: 0x40
 *             classic-platform: added parameter result (R24-11).
 *             Behaviour: SWS_CanTp_00090, SWS_CanTp_00310. Project: CANTP_SRS_003, CANTP_SRS_007
 * @param[in]  TxPduId  ID of the PDU that has been transmitted.
 * @param[in]  result   E_OK transmission successful, E_NOT_OK transmission failed.
 */
void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

#ifdef __cplusplus
}
#endif

#endif /* CANTP_H */
