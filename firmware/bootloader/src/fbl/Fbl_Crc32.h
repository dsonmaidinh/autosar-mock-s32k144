/**
 * @file     Fbl_Crc32.h
 * @brief    FBL CRC-32 (reflected polynomial 0xEDB88320).
 * @details  Project module (docs/Mock.docx 1.8, BL_SRS_002, BL_SRS_009). The
 *           interface mirrors AUTOSAR Crc_CalculateCRC32 (SWS Crc Library) so the
 *           calculation can be split over several calls; the Crc module itself
 *           is not part of v1.0.
 */

#ifndef FBL_CRC32_H
#define FBL_CRC32_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Calculates the CRC-32 over a data block.
 * @details    Parameters (BOOT_CRC32_POLY_REFLECTED, init / xor-out 0xFFFFFFFF in Boot_Shared.h).
 * @param[in]  DataPtr       Pointer to the start of the data block.
 * @param[in]  Length        Length of the data block in bytes.
 * @param[in]  StartValue32  Start value, ignored when IsFirstCall is TRUE.
 * @param[in]  IsFirstCall   TRUE first call of a sequence, FALSE subsequent call.
 * @return     CRC-32 value.
 */
uint32 Fbl_Crc32_Calculate(const uint8* DataPtr, uint32 Length, uint32 StartValue32, boolean IsFirstCall);

#ifdef __cplusplus
}
#endif

#endif /* FBL_CRC32_H */
