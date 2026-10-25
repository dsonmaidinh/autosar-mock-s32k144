/**
 * @file     PduR_CanTp.h
 * @brief    PDU Router (PduR) - interface for the lower layer TP module CanTp.
 * @details  PduR_<User:LoTp>* callbacks with <User:LoTp> = CanTp, per AUTOSAR CP
 *           R24-11 SWS PDURouter ("available via PduR_<module>.h").
 *           classic-platform signatures (4.0.3) corrected to R24-11:
 *           StartOfReception gets info, const PduInfoType/RetryInfoType,
 *           NotifResultType -> Std_ReturnType (docs/Mock.docx T-03).
 */

#ifndef PDUR_CANTP_H
#define PDUR_CANTP_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "PduR.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Called at the start of receiving an N-SDU.
 * @details    SWS: SWS_PduR_00507 | Service ID: 0x46
 *             classic-platform: added parameter info (R24-11).
 *             Behaviour: SWS_PduR_00549. Project: PDUR_SRS_002
 * @param[in]  id             Identification of the I-PDU.
 * @param[in]  info           Pointer to a PduInfoType containing the data of the first frame
 *                            or single frame (may be NULL_PTR).
 * @param[in]  TpSduLength    Total length of the N-SDU to be received.
 * @param[out] bufferSizePtr  Available receive buffer in the receiving module.
 * @return     BUFREQ_OK, BUFREQ_E_NOT_OK, BUFREQ_E_OVFL.
 */
BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType id, const PduInfoType* info,
                                             PduLengthType TpSduLength, PduLengthType* bufferSizePtr);

/**
 * @brief      Called to provide the received data of an I-PDU segment (N-PDU) to the upper layer.
 * @details    SWS: SWS_PduR_00512 | Service ID: 0x44
 *             classic-platform: info made const (R24-11).
 *             Behaviour: SWS_PduR_00428. Project: PDUR_SRS_003
 * @param[in]  id             Identification of the received I-PDU.
 * @param[in]  info           Provides the source buffer and the number of bytes to be copied.
 * @param[out] bufferSizePtr  Available receive buffer after data has been copied.
 * @return     BUFREQ_OK, BUFREQ_E_NOT_OK.
 */
BufReq_ReturnType PduR_CanTpCopyRxData(PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr);

/**
 * @brief      Called after an I-PDU has been received via the TP API.
 * @details    SWS: SWS_PduR_00375 | Service ID: 0x45
 *             classic-platform: NotifResultType -> Std_ReturnType (R24-11).
 *             Behaviour: SWS_PduR_00429. Project: PDUR_SRS_003
 * @param[in]  id      Identification of the received I-PDU.
 * @param[in]  result  E_OK reception successful, E_NOT_OK reception failed.
 */
void PduR_CanTpRxIndication(PduIdType id, Std_ReturnType result);

/**
 * @brief      Called to acquire the transmit data of an I-PDU segment (N-PDU).
 * @details    SWS: SWS_PduR_00518 | Service ID: 0x43
 *             classic-platform: info and retry made const (R24-11).
 *             Behaviour: SWS_PduR_00299. Project: PDUR_SRS_005
 * @param[in]  id                Identification of the transmitted I-PDU.
 * @param[in]  info              Provides the destination buffer and the number of bytes to be copied.
 * @param[in]  retry             Retry information, NULL_PTR if retry is not supported.
 * @param[out] availableDataPtr  Remaining number of bytes available in the TX buffer.
 * @return     BUFREQ_OK, BUFREQ_E_BUSY, BUFREQ_E_NOT_OK.
 */
BufReq_ReturnType PduR_CanTpCopyTxData(PduIdType id, const PduInfoType* info,
                                       const RetryInfoType* retry, PduLengthType* availableDataPtr);

/**
 * @brief      Called after the I-PDU has been transmitted on its network.
 * @details    SWS: SWS_PduR_00381 | Service ID: 0x48
 *             classic-platform: NotifResultType -> Std_ReturnType (R24-11).
 *             Behaviour: SWS_PduR_00301. Project: PDUR_SRS_005
 * @param[in]  id      Identification of the transmitted I-PDU.
 * @param[in]  result  E_OK transmission successful, E_NOT_OK transmission failed.
 */
void PduR_CanTpTxConfirmation(PduIdType id, Std_ReturnType result);

#ifdef __cplusplus
}
#endif

#endif /* PDUR_CANTP_H */
