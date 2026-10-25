/**
 * @file     Dcm.c
 * @brief    Diagnostic Communication Manager (Dcm) - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/dcm-cansm-comm (commits X-04..X-11) following the
 *           SWS IDs and SRS IDs referenced in Dcm.h, Dcm_ComM.h and SchM_Dcm.h.
 *           The callouts of Dcm_Externals.h are implemented by App/BL.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Dcm.h"
#include "Dcm_ComM.h"
#include "Dcm_Externals.h"
#include "SchM_Dcm.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void Dcm_Init(const Dcm_ConfigType* ConfigPtr)
{
    (void)ConfigPtr;
    /* TODO: SWS_Dcm_00037, SWS_Dcm_00536 (Dcm_GetProgConditions on init) */
}

void Dcm_GetVersionInfo(Std_VersionInfoType* versionInfo)
{
    (void)versionInfo;
    /* TODO: SWS_Dcm_00065 */
}

Std_ReturnType Dcm_GetSecurityLevel(Dcm_SecLevelType* SecLevel)
{
    (void)SecLevel;
    /* TODO(DCM_SRS_003): SWS_Dcm_00338 */
    return E_NOT_OK;
}

Std_ReturnType Dcm_GetSesCtrlType(Dcm_SesCtrlType* SesCtrlType)
{
    (void)SesCtrlType;
    /* TODO(DCM_SRS_002): SWS_Dcm_00339 */
    return E_NOT_OK;
}

Std_ReturnType Dcm_ResetToDefaultSession(void)
{
    /* TODO(DCM_SRS_008): SWS_Dcm_00520 */
    return E_NOT_OK;
}

void Dcm_MainFunction(void)
{
    /* TODO(DCM_SRS_008/009): SWS_Dcm_00053 - S3 timer (SWS_Dcm_01670), P2/P2* and
     *   NRC 0x78 (SWS_Dcm_00024, SWS_Dcm_01567), security delay (SWS_Dcm_01350),
     *   pending operations (SWS_Dcm_00530), ComM_DCM_ActiveDiagnostic (SWS_Dcm_01376) */
}

BufReq_ReturnType Dcm_StartOfReception(PduIdType id, const PduInfoType* info,
                                       PduLengthType TpSduLength, PduLengthType* bufferSizePtr)
{
    (void)id;
    (void)info;
    (void)TpSduLength;
    (void)bufferSizePtr;
    /* TODO(DCM_SRS_016): SWS_Dcm_00094 */
    return BUFREQ_E_NOT_OK;
}

BufReq_ReturnType Dcm_CopyRxData(PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr)
{
    (void)id;
    (void)info;
    (void)bufferSizePtr;
    /* TODO(DCM_SRS_016): SWS_Dcm_00556 */
    return BUFREQ_E_NOT_OK;
}

void Dcm_TpRxIndication(PduIdType id, Std_ReturnType result)
{
    (void)id;
    (void)result;
    /* TODO(DCM_SRS_001..005/016): SWS_Dcm_00093, DSD checks SWS_Dcm_00197, SWS_Dcm_00211,
     *   SWS_Dcm_00217, SWS_Dcm_00273, SWS_Dcm_00696, SWS_Dcm_00275, SWS_Dcm_00001, SWS_Dcm_00204 */
}

BufReq_ReturnType Dcm_CopyTxData(PduIdType id, const PduInfoType* info,
                                 const RetryInfoType* retry, PduLengthType* availableDataPtr)
{
    (void)id;
    (void)info;
    (void)retry;
    (void)availableDataPtr;
    /* TODO(DCM_SRS_016): SWS_Dcm_00092 */
    return BUFREQ_E_NOT_OK;
}

void Dcm_TpTxConfirmation(PduIdType id, Std_ReturnType result)
{
    (void)id;
    (void)result;
    /* TODO(DCM_SRS_006/016): SWS_Dcm_00351, SWS_Dcm_00311, SWS_Dcm_00139, SWS_Dcm_01423 */
}

void Dcm_ComM_NoComModeEntered(uint8 NetworkId)
{
    (void)NetworkId;
    /* TODO: SWS_Dcm_00356 */
}

void Dcm_ComM_SilentComModeEntered(uint8 NetworkId)
{
    (void)NetworkId;
    /* TODO: SWS_Dcm_00358 */
}

void Dcm_ComM_FullComModeEntered(uint8 NetworkId)
{
    (void)NetworkId;
    /* TODO: SWS_Dcm_00360 */
}
