/**
 * @file     BM_Request.c
 * @brief    Boot Manager - boot request record skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/bootloader (commit B-03).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "BM_Request.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
boolean BM_CheckBootRequest(void)
{
    /* TODO(BL_SRS_001): RCM->SRS POR -> clear record, return FALSE;
     *   else check Magic / MagicInv of the record at BOOT_REQUEST_ADDR (.boot_noinit) */
    return FALSE;
}

Std_ReturnType BM_GetBootRequest(Boot_RequestType* RequestPtr)
{
    (void)RequestPtr;
    /* TODO(B-04): copy the record for Dcm_GetProgConditions */
    return E_NOT_OK;
}

void BM_ClearBootRequest(void)
{
    /* TODO(BL_SRS_001): write 0 to Magic and MagicInv */
}
