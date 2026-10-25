/**
 * @file     Os_Sched.c
 * @brief    Bare-metal cooperative scheduler - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/det-ecum (commit D-04, ECUM_SRS_002).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Os_Sched.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void Os_Sched_Init(void)
{
    /* TODO(ECUM_SRS_002): Gpt_EnableNotification + Gpt_StartTimer(GptChannel_Tick1ms) */
}

void Os_Sched_Run(void)
{
    /* TODO(ECUM_SRS_002): endless loop dispatching Os_Task_1ms / Os_Task_10ms, overrun check */
}

void Os_Sched_TickNotification(void)
{
    /* TODO(ECUM_SRS_002): increment tick counter only (ISR context) */
}

void Os_Task_1ms(void)
{
    /* TODO(ECUM_SRS_002): CanTp_MainFunction() */
}

void Os_Task_10ms(void)
{
    /* TODO(ECUM_SRS_002): Can_43_FLEXCAN_MainFunction_Mode(), CanSM_MainFunction(),
     *                     ComM_MainFunction_CAN0(), Dcm_MainFunction(), Dem_MainFunction() */
}
