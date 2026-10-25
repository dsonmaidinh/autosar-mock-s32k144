/**
 * @file     CanTp.c
 * @brief    CAN Transport Layer (CanTp) - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/tp-path (commits T-02..T-04) following the SWS IDs
 *           and SRS IDs referenced in CanTp.h and SchM_CanTp.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "CanTp.h"
#include "SchM_CanTp.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void CanTp_Init(const CanTp_ConfigType* CfgPtr)
{
    (void)CfgPtr;
    /* TODO(CANTP_SRS_001): SWS_CanTp_00208, SWS_CanTp_00027, SWS_CanTp_00168, SWS_CanTp_00030 */
}

void CanTp_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    (void)versioninfo;
    /* TODO: SWS_CanTp_00210 */
}

void CanTp_Shutdown(void)
{
    /* TODO: SWS_CanTp_00211 */
}

Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
    (void)TxPduId;
    (void)PduInfoPtr;
    /* TODO(CANTP_SRS_002/003): SWS_CanTp_00212, SWS_CanTp_00231, SWS_CanTp_00232, SWS_CanTp_00086 */
    return E_NOT_OK;
}

void CanTp_MainFunction(void)
{
    /* TODO(CANTP_SRS_006/007): SWS_CanTp_00213, N_As/N_Ar/N_Bs/N_Cr timers
     *   (SWS_CanTp_00312, 00313, 00316, 00310, 00311, 00075), STmin, FC(WAIT) */
}

void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
    (void)RxPduId;
    (void)PduInfoPtr;
    /* TODO(CANTP_SRS_004/005/008/009): SWS_CanTp_00214, SWS_CanTp_00079, SWS_CanTp_00329,
     *   SWS_CanTp_00081, SWS_CanTp_00318, SWS_CanTp_00353, SWS_CanTp_00064, SWS_CanTp_00269,
     *   SWS_CanTp_00314, SWS_CanTp_00309, SWS_CanTp_00317, SWS_CanTp_00093, SWS_CanTp_00116 */
}

void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    (void)TxPduId;
    (void)result;
    /* TODO(CANTP_SRS_003/007): SWS_CanTp_00215, SWS_CanTp_00090 */
}
