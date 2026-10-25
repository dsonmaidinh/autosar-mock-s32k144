/**
 * @file     PduR_Dcm.h
 * @brief    PDU Router (PduR) - interface for the upper layer module Dcm.
 * @details  PduR_<User:Up>Transmit with <User:Up> = Dcm, per AUTOSAR CP R24-11
 *           SWS PDURouter ("available via PduR_<module>.h").
 */

#ifndef PDUR_DCM_H
#define PDUR_DCM_H

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
 * @brief      Requests transmission of a diagnostic response PDU.
 * @details    SWS: SWS_PduR_00406 | Service ID: 0x49 | classic-platform: kept
 *             Behaviour: SWS_PduR_00634 (forwarded to CanTp_Transmit). Project: PDUR_SRS_004
 * @param[in]  TxPduId     Identifier of the PDU to be transmitted.
 * @param[in]  PduInfoPtr  Length of and pointer to the PDU data and pointer to MetaData.
 * @return     E_OK transmit request accepted, E_NOT_OK not accepted.
 */
Std_ReturnType PduR_DcmTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);

#ifdef __cplusplus
}
#endif

#endif /* PDUR_DCM_H */
