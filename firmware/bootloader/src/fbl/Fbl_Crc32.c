/**
 * @file     Fbl_Crc32.c
 * @brief    FBL CRC-32 - implementation skeleton.
 * @details  Function body intentionally empty. Implement on branch
 *           feature/bootloader (commit B-07).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Fbl_Crc32.h"
#include "Boot_Shared.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
uint32 Fbl_Crc32_Calculate(const uint8* DataPtr, uint32 Length, uint32 StartValue32, boolean IsFirstCall)
{
    (void)DataPtr;
    (void)Length;
    (void)StartValue32;
    (void)IsFirstCall;
    /* TODO(BL_SRS_002/009): bitwise or table driven CRC-32, BOOT_CRC32_POLY_REFLECTED */
    return 0U;
}
