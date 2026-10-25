/**
 * @file     Os_Sched.h
 * @brief    Bare-metal cooperative scheduler (1 ms / 10 ms tasks).
 * @details  Project module, no AUTOSAR SWS (no OS in v1.0, docs/Mock.docx 1.2).
 *           The 1 ms tick comes from Gpt channel GptChannel_Tick1ms (LPIT0),
 *           whose notification is configured as Os_Sched_TickNotification.
 *           Project requirement: ECUM_SRS_002.
 */

#ifndef OS_SCHED_H
#define OS_SCHED_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define OS_SCHED_TICK_MS                    (1U)    /**< Gpt tick period [ms] */
#define OS_SCHED_TASK_10MS_DIVIDER          (10U)   /**< 10 ms task = 10 ticks */

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Initializes the scheduler and starts the 1 ms Gpt channel.
 * @details    Called at the end of EcuM_Init(). Project: ECUM_SRS_002
 */
void Os_Sched_Init(void);

/**
 * @brief      Scheduler main loop, never returns.
 * @details    Dispatches Os_Task_1ms() and Os_Task_10ms() on pending ticks.
 *             Project: ECUM_SRS_002
 */
void Os_Sched_Run(void);

/**
 * @brief      Gpt channel notification of the 1 ms tick (ISR context).
 * @details    Referenced by Gpt_PBcfg.c (GptChannel_Tick1ms). Only sets the tick flag.
 */
void Os_Sched_TickNotification(void);

/**
 * @brief      1 ms task: CanTp_MainFunction().
 * @details    Project: ECUM_SRS_002
 */
void Os_Task_1ms(void);

/**
 * @brief      10 ms task: Can_43_FLEXCAN_MainFunction_Mode(), CanSM_MainFunction(),
 *             ComM_MainFunction_CAN0(), Dcm_MainFunction(), Dem_MainFunction().
 * @details    Project: ECUM_SRS_002
 */
void Os_Task_10ms(void);

#ifdef __cplusplus
}
#endif

#endif /* OS_SCHED_H */
