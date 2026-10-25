/**
 * @file     Fbl_Flash.c
 * @brief    FBL flash access - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/bl-flash (commit F-02).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Fbl_Flash.h"
#include "Boot_Shared.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void Fbl_Flash_Init(void)
{
    /* TODO(F-02): Mem_43_INFLS_Init(NULL_PTR) */
}

boolean Fbl_Flash_IsRangeAllowed(uint32 Address, uint32 Length)
{
    (void)Address;
    (void)Length;
    /* TODO(BL_SRS_012): reject overlap with BOOT_BL_START_ADDR..BOOT_BL_END_ADDR, overflow check */
    return FALSE;
}

Std_ReturnType Fbl_Flash_Erase(uint32 Address, uint32 Length)
{
    (void)Address;
    (void)Length;
    /* TODO(BL_SRS_005/011/012): Mem_43_INFLS_Erase(MEM_43_INFLS_INSTANCE_0_ID, ...) */
    return E_NOT_OK;
}

Std_ReturnType Fbl_Flash_Write(uint32 Address, const uint8* DataPtr, uint32 Length)
{
    (void)Address;
    (void)DataPtr;
    (void)Length;
    /* TODO(BL_SRS_007/011/012): Mem_43_INFLS_Write(MEM_43_INFLS_INSTANCE_0_ID, ...) */
    return E_NOT_OK;
}

Fbl_Flash_StatusType Fbl_Flash_GetStatus(void)
{
    /* TODO(F-02): map Mem_43_INFLS_GetJobResult(MEM_43_INFLS_INSTANCE_0_ID) */
    return FBL_FLASH_IDLE;
}

void Fbl_Flash_MainFunction(void)
{
    /* TODO(F-02): Mem_43_INFLS_MainFunction() */
}
