/**
 * @file     Dcm_Callout_Bl.c
 * @brief    Dcm callouts of the bootloader image (programming conditions).
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/bootloader (commit B-04). Security level 0x11
 *           seed/key and DID 0xF15A callouts are added with B-04.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Dcm_Externals.h"
#include "BM_Request.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
Std_ReturnType Dcm_SetProgConditions(Dcm_OpStatusType OpStatus, const Dcm_ProgConditionsType* ProgConditions)
{
    (void)OpStatus;
    (void)ProgConditions;
    /* TODO: SWS_Dcm_00543 - BL ECUReset: nothing to store (reset starts the BL again) */
    return E_OK;
}

Dcm_EcuStartModeType Dcm_GetProgConditions(Dcm_ProgConditionsType* ProgConditions)
{
    (void)ProgConditions;
    /* TODO(SWS_Dcm_00536, SWS_Dcm_00544): after a jump from the App (BM_GetBootRequest),
     *   fill ProgConditions (Sid 0x10, SubFncId 0x02, ResponseRequired) and return DCM_WARM_START
     *   so that the BL answers 0x50 02 in programming session */
    return DCM_COLD_START;
}
