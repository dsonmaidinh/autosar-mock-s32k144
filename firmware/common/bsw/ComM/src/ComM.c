/**
 * @file     ComM.c
 * @brief    Communication Manager (ComM) - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/dcm-cansm-comm (commit X-02) following the SWS IDs
 *           and SRS IDs referenced in ComM.h, ComM_Dcm.h, ComM_BswM.h and
 *           SchM_ComM.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "ComM.h"
#include "ComM_Dcm.h"
#include "ComM_BswM.h"
#include "SchM_ComM.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void ComM_Init(const ComM_ConfigType* ConfigPtr)
{
    (void)ConfigPtr;
    /* TODO(COMM_SRS_001): SWS_ComM_00146 */
}

void ComM_DeInit(void)
{
    /* TODO: SWS_ComM_00147, SWS_ComM_00794 */
}

Std_ReturnType ComM_GetStatus(ComM_InitStatusType* Status)
{
    (void)Status;
    /* TODO(COMM_SRS_001): SWS_ComM_00242 */
    return E_NOT_OK;
}

Std_ReturnType ComM_RequestComMode(ComM_UserHandleType User, ComM_ModeType ComMode)
{
    (void)User;
    (void)ComMode;
    /* TODO(COMM_SRS_001/002): SWS_ComM_00110, SWS_ComM_00612, SWS_ComM_00069 */
    return E_NOT_OK;
}

Std_ReturnType ComM_GetRequestedComMode(ComM_UserHandleType User, ComM_ModeType* ComMode)
{
    (void)User;
    (void)ComMode;
    /* TODO: SWS_ComM_00079 */
    return E_NOT_OK;
}

Std_ReturnType ComM_GetCurrentComMode(ComM_UserHandleType User, ComM_ModeType* ComMode)
{
    (void)User;
    (void)ComMode;
    /* TODO: SWS_ComM_00083 */
    return E_NOT_OK;
}

void ComM_GetVersionInfo(Std_VersionInfoType* Versioninfo)
{
    (void)Versioninfo;
    /* TODO: SWS_ComM_00370 */
}

void ComM_BusSM_ModeIndication(NetworkHandleType Channel, ComM_ModeType ComMode)
{
    (void)Channel;
    (void)ComMode;
    /* TODO(COMM_SRS_002): SWS_ComM_00675 */
}

void ComM_DCM_ActiveDiagnostic(NetworkHandleType Channel)
{
    (void)Channel;
    /* TODO(COMM_SRS_003): SWS_ComM_00873, SWS_ComM_00866 */
}

void ComM_DCM_InactiveDiagnostic(NetworkHandleType Channel)
{
    (void)Channel;
    /* TODO(COMM_SRS_003): SWS_ComM_00874 */
}

void ComM_CommunicationAllowed(NetworkHandleType Channel, boolean Allowed)
{
    (void)Channel;
    (void)Allowed;
    /* TODO: SWS_ComM_00871 */
}

void ComM_MainFunction_CAN0(void)
{
    /* TODO(COMM_SRS_004): SWS_ComM_00429 - channel state machine of CAN0,
     *   FULL_COM -> CanSM_RequestComMode (SWS_ComM_00069) */
}
