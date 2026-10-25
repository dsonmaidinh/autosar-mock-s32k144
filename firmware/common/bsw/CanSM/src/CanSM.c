/**
 * @file     CanSM.c
 * @brief    CAN State Manager (CanSM) - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/dcm-cansm-comm (commit X-01) following the SWS IDs
 *           and SRS IDs referenced in CanSM.h, CanSM_CanIf.h and SchM_CanSM.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "CanSM.h"
#include "CanSM_CanIf.h"
#include "SchM_CanSM.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void CanSM_Init(const CanSM_ConfigType* ConfigPtr)
{
    (void)ConfigPtr;
    /* TODO(CANSM_SRS_001): SWS_CanSM_00023, SWS_CanSM_00423 */
}

void CanSM_DeInit(void)
{
    /* TODO: SWS_CanSM_91001 */
}

void CanSM_GetVersionInfo(Std_VersionInfoType* VersionInfo)
{
    (void)VersionInfo;
    /* TODO: SWS_CanSM_00024 */
}

Std_ReturnType CanSM_RequestComMode(NetworkHandleType network, ComM_ModeType ComM_Mode)
{
    (void)network;
    (void)ComM_Mode;
    /* TODO(CANSM_SRS_002): SWS_CanSM_00062, SWS_CanSM_00184, SWS_CanSM_00555, SWS_CanSM_00182 */
    return E_NOT_OK;
}

Std_ReturnType CanSM_GetCurrentComMode(NetworkHandleType network, ComM_ModeType* ComM_ModePtr)
{
    (void)network;
    (void)ComM_ModePtr;
    /* TODO: SWS_CanSM_00063, SWS_CanSM_00282 */
    return E_NOT_OK;
}

void CanSM_MainFunction(void)
{
    /* TODO(CANSM_SRS_005): SWS_CanSM_00065, bus-off recovery SWS_CanSM_00514, SWS_CanSM_00515 */
}

void CanSM_ControllerBusOff(uint8 ControllerId)
{
    (void)ControllerId;
    /* TODO(CANSM_SRS_003/004): SWS_CanSM_00064, SWS_CanSM_00500, SWS_CanSM_00606, SWS_CanSM_00522 */
}

void CanSM_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode)
{
    (void)ControllerId;
    (void)ControllerMode;
    /* TODO: SWS_CanSM_00396 */
}
