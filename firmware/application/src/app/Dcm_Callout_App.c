/**
 * @file     Dcm_Callout_App.c
 * @brief    Dcm callouts of the application image.
 * @details  Implements the callouts of Dcm_Externals.h used by the application
 *           (jump to bootloader). Function bodies are intentionally empty:
 *           implement them on branch feature/dcm-cansm-comm (commit X-11).
 *           Security seed/key, DID and RID callouts are added with X-08 / X-10.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Dcm_Externals.h"
#include "Boot_Shared.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
Std_ReturnType Dcm_SetProgConditions(Dcm_OpStatusType OpStatus, const Dcm_ProgConditionsType* ProgConditions)
{
    (void)OpStatus;
    (void)ProgConditions;
    /* TODO(DCM_SRS_014, BL_SRS_004): SWS_Dcm_00543 - write Boot_RequestType at BOOT_REQUEST_ADDR
     *   (Magic, ~Magic, BOOT_REQUEST_REASON_PROGRAMMING) then return E_OK */
    return E_NOT_OK;
}

Dcm_EcuStartModeType Dcm_GetProgConditions(Dcm_ProgConditionsType* ProgConditions)
{
    (void)ProgConditions;
    /* TODO: SWS_Dcm_00544 - application always starts cold (no response after BL jump) */
    return DCM_COLD_START;
}
