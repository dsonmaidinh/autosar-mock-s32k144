/**
 * @file     BM_Request.h
 * @brief    Boot Manager - boot request record in .boot_noinit (0x2000_6FF0).
 * @details  Project module (docs/Mock.docx 1.10). The record is written by the
 *           application callout Dcm_SetProgConditions before a SW reset (BL_SRS_004).
 *           Note: the RTD RamInit only ECC-initializes SRAM below 0x2000_6FF0
 *           (bl.ld). After a power-on reset the record area is not initialized,
 *           so the reset cause (RCM->SRS) must be checked before reading it.
 */

#ifndef BM_REQUEST_H
#define BM_REQUEST_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "Boot_Shared.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Checks for a boot request from the application.
 * @details    TRUE only after a non power-on reset and when Magic == BOOT_REQUEST_MAGIC
 *             and MagicInv == ~Magic. On power-on reset the record is initialized
 *             (cleared) first. Project: BL_SRS_001
 * @return     TRUE stay in the bootloader, FALSE no request.
 */
boolean BM_CheckBootRequest(void);

/**
 * @brief      Returns a copy of the boot request record (reason, tester address).
 * @details    Used by Dcm_GetProgConditions to answer 0x50 02 after the jump (SWS_Dcm_00536).
 * @param[out] RequestPtr  Destination of the record.
 * @return     E_OK record valid, E_NOT_OK no valid record.
 */
Std_ReturnType BM_GetBootRequest(Boot_RequestType* RequestPtr);

/**
 * @brief      Clears the boot request record.
 * @details    Called once the request has been consumed by the bootloader.
 */
void BM_ClearBootRequest(void);

#ifdef __cplusplus
}
#endif

#endif /* BM_REQUEST_H */
