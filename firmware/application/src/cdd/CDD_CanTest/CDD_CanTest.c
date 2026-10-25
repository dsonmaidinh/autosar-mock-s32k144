/**
 * @file     CDD_CanTest.c
 * @brief    Complex driver for the CAN path test frames - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/can-path (commit C-06) and X-10 (Tx enable).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "CDD_CanTest.h"
#include "CanIf.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void CDD_CanTest_Init(void)
{
    /* TODO(C-06): Tx enabled, echo byte 0, period counter 0 */
}

void CDD_CanTest_MainFunction(void)
{
    /* TODO(C-06): every CDD_CANTEST_TX_PERIOD_MS call CanIf_Transmit(0x3A0 PDU) */
}

void CDD_CanTest_SetTxEnabled(boolean Enabled)
{
    (void)Enabled;
    /* TODO(X-10): UDS 0x28 CommunicationControl */
}

void CDD_CanTest_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
    (void)RxPduId;
    (void)PduInfoPtr;
    /* TODO(C-06): store byte 0 of 0x2B0 for the echo */
}

void CDD_CanTest_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    (void)TxPduId;
    (void)result;
    /* TODO(C-06): optional Tx statistics */
}
