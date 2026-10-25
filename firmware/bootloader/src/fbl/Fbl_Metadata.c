/**
 * @file     Fbl_Metadata.c
 * @brief    FBL application metadata - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/bootloader (commits B-05, B-07).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Fbl_Metadata.h"
#include "Fbl_Flash.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
Std_ReturnType Fbl_Metadata_Read(Boot_MetadataType* MetadataPtr)
{
    (void)MetadataPtr;
    /* TODO(BL_SRS_002): copy from BOOT_METADATA_ADDR */
    return E_NOT_OK;
}

boolean Fbl_Metadata_IsValid(const Boot_MetadataType* MetadataPtr)
{
    (void)MetadataPtr;
    /* TODO(BL_SRS_002): Magic == BOOT_METADATA_MAGIC && ValidFlag == BOOT_METADATA_VALID */
    return FALSE;
}

Std_ReturnType Fbl_Metadata_Invalidate(void)
{
    /* TODO(B-05): Fbl_Flash_Erase(BOOT_METADATA_ADDR, BOOT_METADATA_SIZE) */
    return E_NOT_OK;
}

Std_ReturnType Fbl_Metadata_Commit(const Boot_MetadataType* MetadataPtr)
{
    (void)MetadataPtr;
    /* TODO(BL_SRS_010): Fbl_Flash_Write(BOOT_METADATA_ADDR, record, sizeof(Boot_MetadataType)) */
    return E_NOT_OK;
}
