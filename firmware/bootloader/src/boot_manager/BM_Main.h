/**
 * @file     BM_Main.h
 * @brief    Boot Manager - decision: stay in the bootloader or start the application.
 * @details  Project module, no AUTOSAR SWS (docs/Mock.docx 1.11, 3.12).
 *           The application is started only when all three conditions hold:
 *             1. no boot request record in .boot_noinit       (BM_CheckBootRequest)
 *             2. metadata valid and CRC-32 matches             (BM_IsAppValid)
 *             3. App vector table has valid MSP / reset vector (BM_IsVectorTableValid)
 */

#ifndef BM_MAIN_H
#define BM_MAIN_H

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
 * @brief      Boot decision, called first in main().
 * @details    Jumps to the application (does not return) when conditions 1..3 hold,
 *             otherwise returns and the bootloader stack is started.
 *             Project: BL_SRS_001, BL_SRS_002, BL_SRS_003
 */
void BM_Main(void);

/**
 * @brief      Checks whether a valid application is present.
 * @details    Metadata at BOOT_METADATA_ADDR has Magic and ValidFlag set and the
 *             CRC-32 over AppSize bytes equals the stored Crc32. Project: BL_SRS_002
 * @return     TRUE application valid, FALSE otherwise.
 */
boolean BM_IsAppValid(void);

#ifdef __cplusplus
}
#endif

#endif /* BM_MAIN_H */
