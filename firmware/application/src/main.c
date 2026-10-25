/**
 * @file     main.c
 * @brief    Mock ECU - application entry point.
 * @details  Called by the RTD startup (startup_cm4.s) after RAM init and
 *           SystemInit. Initialization and scheduling are owned by EcuM.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "EcuM.h"
#include "Os_Sched.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
int main(void)
{
    EcuM_Init();        /* ECUM_SRS_001: MCAL + BSW init in project order */
    Os_Sched_Run();     /* ECUM_SRS_002: 1 ms / 10 ms tasks, never returns */

    return 0;
}
