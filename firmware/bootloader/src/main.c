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
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
/**
 * @brief    TEST ONLY: board bring-up, blinks the red LED (PTD15) of the S32K144EVB forever.
 * @details  Checks RTD startup, clock (FIRC 48 MHz), Port and Dio without BSW/scheduler.
 *           Busy-wait delay, about 2-3 toggles per second in Debug_FLASH (-O0).
 */
static void Test_LedBlink(void)
{
    volatile uint32 delay;

    Mcu_Init(&Mcu_Config);
    (void)Mcu_InitClock(McuClockSettingConfig_0);
    Mcu_SetMode(McuModeSettingConf_0);
    Port_Init(&Port_Config);

    for (;;)
    {
        (void)Dio_FlipChannel(DioConf_DioChannel_LED_RED);
        for (delay = 0U; delay < 1500000U; delay++)
        {
        }
    }
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
int main(void)
{
    Test_LedBlink();    /* TEST ONLY: remove after the board bring-up */

    BM_Main();          /* BL_SRS_001..003: jumps to the application, or returns to stay in BL */

    EcuM_Init();        /* ECUM_SRS_001: MCAL + BSW init (BL configuration) */
    Os_Sched_Run();     /* ECUM_SRS_002: 1 ms / 10 ms tasks, never returns */

    return 0;
}
