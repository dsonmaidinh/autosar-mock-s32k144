/**
 * @file     BM_Jump.h
 * @brief    Boot Manager - application vector table check and jump.
 * @details  Project module (docs/Mock.docx 3.12, BL_SRS_003). Algorithm learnt
 *           from mianlongxu-cell/S32K144-Automotive-ECU boot_jump.c, rewritten.
 */

#ifndef BM_JUMP_H
#define BM_JUMP_H

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
 * @brief      Checks the initial MSP and the reset vector of a vector table.
 * @details    MSP inside [BOOT_SRAM_START_ADDR, BOOT_SRAM_END_ADDR] and reset vector
 *             inside [BOOT_APP_CODE_START_ADDR, BOOT_APP_END_ADDR]. Project: BL_SRS_003
 * @param[in]  VectorTableAddr  Address of the vector table (BOOT_APP_VECTOR_ADDR).
 * @return     TRUE vector table plausible, FALSE otherwise.
 */
boolean BM_IsVectorTableValid(uint32 VectorTableAddr);

/**
 * @brief      Starts the application, does not return.
 * @details    Disables interrupts, de-initializes SysTick, NVIC, FLEXCAN_0
 *             (Can_43_FLEXCAN_DeInit) and Gpt (Gpt_DeInit) if initialized, sets VTOR,
 *             loads MSP and branches to the reset vector. Project: BL_SRS_003
 * @param[in]  VectorTableAddr  Address of the application vector table.
 */
void BM_JumpToApp(uint32 VectorTableAddr);

#ifdef __cplusplus
}
#endif

#endif /* BM_JUMP_H */
