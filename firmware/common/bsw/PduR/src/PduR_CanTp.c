/**
 * @file     PduR_CanTp.c
 * @brief    PDU Router (PduR) - CanTp callbacks skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/tp-path (commit T-03) following the SWS IDs and
 *           SRS IDs referenced in PduR_CanTp.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "PduR_CanTp.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType id, const PduInfoType* info,
                                             PduLengthType TpSduLength, PduLengthType* bufferSizePtr)
{
    (void)id;
    (void)info;
    (void)TpSduLength;
    (void)bufferSizePtr;
    /* TODO(PDUR_SRS_002): SWS_PduR_00507, SWS_PduR_00549 -> Dcm_StartOfReception */
    return BUFREQ_E_NOT_OK;
}

BufReq_ReturnType PduR_CanTpCopyRxData(PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr)
{
    (void)id;
    (void)info;
    (void)bufferSizePtr;
    /* TODO(PDUR_SRS_003): SWS_PduR_00512, SWS_PduR_00428 -> Dcm_CopyRxData */
    return BUFREQ_E_NOT_OK;
}

void PduR_CanTpRxIndication(PduIdType id, Std_ReturnType result)
{
    (void)id;
    (void)result;
    /* TODO(PDUR_SRS_003): SWS_PduR_00375, SWS_PduR_00429 -> Dcm_TpRxIndication */
}

BufReq_ReturnType PduR_CanTpCopyTxData(PduIdType id, const PduInfoType* info,
                                       const RetryInfoType* retry, PduLengthType* availableDataPtr)
{
    (void)id;
    (void)info;
    (void)retry;
    (void)availableDataPtr;
    /* TODO(PDUR_SRS_005): SWS_PduR_00518, SWS_PduR_00299 -> Dcm_CopyTxData */
    return BUFREQ_E_NOT_OK;
}

void PduR_CanTpTxConfirmation(PduIdType id, Std_ReturnType result)
{
    (void)id;
    (void)result;
    /* TODO(PDUR_SRS_005): SWS_PduR_00381, SWS_PduR_00301 -> Dcm_TpTxConfirmation */
}
