/**
 * @file     BM_Jump.c
 * @brief    Boot Manager - jump skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/bootloader (commit B-03).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "BM_Jump.h"
#include "Boot_Shared.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
boolean BM_IsVectorTableValid(uint32 VectorTableAddr)
{
    (void)VectorTableAddr;
    /* TODO(BL_SRS_003): check word 0 (MSP) and word 1 (reset vector) ranges */
    return FALSE;
}

void BM_JumpToApp(uint32 VectorTableAddr)
{
    (void)VectorTableAddr;
    /* TODO(BL_SRS_003): disable IRQ, deinit SysTick/NVIC/FLEXCAN_0/Gpt, SCB->VTOR,
     *   __set_MSP(vector[0]), branch to vector[1] */
}
