/**
 * @file     PduR_Dcm.c
 * @brief    PDU Router (PduR) - Dcm interface skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/tp-path (commit T-03) following the SWS IDs and
 *           SRS IDs referenced in PduR_Dcm.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "PduR_Dcm.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
Std_ReturnType PduR_DcmTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
    (void)TxPduId;
    (void)PduInfoPtr;
    /* TODO(PDUR_SRS_004): SWS_PduR_00406, SWS_PduR_00634 -> CanTp_Transmit */
    return E_NOT_OK;
}
