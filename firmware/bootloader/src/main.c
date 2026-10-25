/**
 * @file     main.c
 * @brief    Mock ECU - bootloader entry point.
 * @details  Called by the RTD startup (startup_cm4.s) after RAM init and
 *           SystemInit. The Boot Manager decides first whether the
 *           application is started (docs/Mock.docx 1.11); otherwise the
 *           bootloader stack (CanIf/CanTp/PduR/Dcm + FBL) is started by EcuM.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "BM_Main.h"
#include "EcuM.h"
#include "Os_Sched.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
int main(void)
{
    BM_Main();          /* BL_SRS_001..003: jumps to the application, or returns to stay in BL */

    EcuM_Init();        /* ECUM_SRS_001: MCAL + BSW init (BL configuration) */
    Os_Sched_Run();     /* ECUM_SRS_002: 1 ms / 10 ms tasks, never returns */

    return 0;
}
