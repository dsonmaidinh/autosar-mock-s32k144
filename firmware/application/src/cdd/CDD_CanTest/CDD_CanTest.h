/**
 * @file     CDD_CanTest.h
 * @brief    Complex driver for the CAN path test frames.
 * @details  Project CDD, no AUTOSAR SWS of its own. Upper layer of CanIf for:
 *             - Tx 0x3A0 every 100 ms (MB8)
 *             - Rx 0x2B0 (MB16), echoed into byte 0 of the next 0x3A0 frame
 *           (docs/Mock.docx 1.6, commit C-06). The CanIf callbacks follow the
 *           R24-11 forms <User_RxIndication> / <User_TxConfirmation> configured
 *           with CanIfRxPduUserRxIndicationName / CanIfTxPduUserTxConfirmationName.
 */

#ifndef CDD_CANTEST_H
#define CDD_CANTEST_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "CDD_CanTest_Cfg.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Initializes the test driver (Tx enabled, echo byte 0).
 * @details    Called by EcuM after CanIf_Init.
 */
void CDD_CanTest_Init(void);

/**
 * @brief      Cyclic function (10 ms task): transmits 0x3A0 every CDD_CANTEST_TX_PERIOD_MS.
 * @details    Uses CanIf_Transmit (SWS_CANIF_00005). Project: CAN-TC-03
 */
void CDD_CanTest_MainFunction(void);

/**
 * @brief      Enables / disables the periodic transmission (UDS 0x28 CommunicationControl).
 * @details    Called by the Dcm communication control handling (commit X-10).
 * @param[in]  Enabled  TRUE transmission enabled, FALSE disabled.
 */
void CDD_CanTest_SetTxEnabled(boolean Enabled);

/**
 * @brief      Indication of a received 0x2B0 frame (<User_RxIndication> of CanIf).
 * @details    Signature per R24-11 <User_RxIndication> (as SWS_CanTp_00214). Project: CAN-TC-04
 * @param[in]  RxPduId     ID of the received PDU.
 * @param[in]  PduInfoPtr  Length of and pointer to the received data.
 */
void CDD_CanTest_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

/**
 * @brief      Confirmation of a transmitted 0x3A0 frame (<User_TxConfirmation> of CanIf).
 * @details    Signature per R24-11 <User_TxConfirmation> (as SWS_CanTp_00215).
 * @param[in]  TxPduId  ID of the PDU that has been transmitted.
 * @param[in]  result   E_OK transmission successful, E_NOT_OK transmission failed.
 */
void CDD_CanTest_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

#ifdef __cplusplus
}
#endif

#endif /* CDD_CANTEST_H */
