/**
 * @file     CanIf.c
 * @brief    CAN Interface (CanIf) - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/can-path (commits C-01..C-05) following the SWS IDs
 *           and SRS IDs referenced in CanIf.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "CanIf.h"
#include "SchM_CanIf.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void CanIf_Init(const CanIf_ConfigType* ConfigPtr)
{
    (void)ConfigPtr;
    /* TODO(CANIF_SRS_001): SWS_CANIF_00001, SWS_CANIF_00085 */
}

Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode)
{
    (void)ControllerId;
    (void)ControllerMode;
    /* TODO(CANIF_SRS_008): SWS_CANIF_00003, SWS_CANIF_00308, SWS_CANIF_00311 */
    return E_NOT_OK;
}

Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, Can_ControllerStateType* ControllerModePtr)
{
    (void)ControllerId;
    (void)ControllerModePtr;
    /* TODO: SWS_CANIF_00229 */
    return E_NOT_OK;
}

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
    (void)TxPduId;
    (void)PduInfoPtr;
    /* TODO(CANIF_SRS_002/003): SWS_CANIF_00005, SWS_CANIF_00318, SWS_CANIF_00162,
     *                          SWS_CANIF_00243, SWS_CANIF_00319, SWS_CANIF_00320, SWS_CANIF_00382 */
    return E_NOT_OK;
}

Std_ReturnType CanIf_SetPduMode(uint8 ControllerId, CanIf_PduModeType PduModeRequest)
{
    (void)ControllerId;
    (void)PduModeRequest;
    /* TODO(CANIF_SRS_004): SWS_CANIF_00008, SWS_CANIF_00874, SWS_CANIF_00341, SWS_CANIF_00860 */
    return E_NOT_OK;
}

Std_ReturnType CanIf_GetPduMode(uint8 ControllerId, CanIf_PduModeType* PduModePtr)
{
    (void)ControllerId;
    (void)PduModePtr;
    /* TODO: SWS_CANIF_00009 */
    return E_NOT_OK;
}

void CanIf_GetVersionInfo(Std_VersionInfoType* VersionInfo)
{
    (void)VersionInfo;
    /* TODO: SWS_CANIF_00158 */
}

void CanIf_TxConfirmation(PduIdType CanTxPduId)
{
    (void)CanTxPduId;
    /* TODO(CANIF_SRS_007): SWS_CANIF_00007, SWS_CANIF_00383, SWS_CANIF_00412 */
}

void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr)
{
    (void)Mailbox;
    (void)PduInfoPtr;
    /* TODO(CANIF_SRS_005/006): SWS_CANIF_00006, SWS_CANIF_00389, SWS_CANIF_00030, SWS_CANIF_00663,
     *                          SWS_CANIF_00877, SWS_CANIF_00168, SWS_CANIF_00902,
     *                          SWS_CANIF_00416, SWS_CANIF_00417, SWS_CANIF_00419 */
}

void CanIf_ControllerBusOff(uint8 ControllerId)
{
    (void)ControllerId;
    /* TODO(CANIF_SRS_010): SWS_CANIF_00218, SWS_CANIF_00724, SWS_CANIF_00431, SWS_CANIF_00739 */
}

void CanIf_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode)
{
    (void)ControllerId;
    (void)ControllerMode;
    /* TODO(CANIF_SRS_009): SWS_CANIF_00699, SWS_CANIF_00711 */
}

void CanIf_ControllerErrorStatePassive(uint8 ControllerId, uint16 RxErrorCounter, uint16 TxErrorCounter)
{
    (void)ControllerId;
    (void)RxErrorCounter;
    (void)TxErrorCounter;
    /* TODO: SWS_CANIF_91008 */
}

void CanIf_ErrorNotification(uint8 ControllerId, Can_ErrorType Can_ErrorType)
{
    (void)ControllerId;
    (void)Can_ErrorType;
    /* TODO: SWS_CANIF_91009 */
}
