/**
 * @file     BM_Main.c
 * @brief    Boot Manager - decision skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/bootloader (commit B-03).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "BM_Main.h"
#include "BM_Request.h"
#include "BM_Jump.h"
#include "Fbl_Metadata.h"
#include "Fbl_Crc32.h"
#include "Boot_Shared.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void BM_Main(void)
{
    /* TODO(BL_SRS_001..003): if (!BM_CheckBootRequest() && BM_IsAppValid() &&
     *   BM_IsVectorTableValid(BOOT_APP_VECTOR_ADDR)) { BM_JumpToApp(BOOT_APP_VECTOR_ADDR); } */
}

boolean BM_IsAppValid(void)
{
    /* TODO(BL_SRS_002): Fbl_Metadata_Read + Fbl_Metadata_IsValid + Fbl_Crc32_Calculate */
    return FALSE;
}
