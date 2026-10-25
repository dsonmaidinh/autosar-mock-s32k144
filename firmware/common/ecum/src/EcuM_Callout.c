/**
 * @file     EcuM_Callout.c
 * @brief    ECU State Manager (EcuM) - callout skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/det-ecum (commit D-03) following the SWS IDs and
 *           SRS IDs referenced in EcuM_Externals.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "EcuM_Externals.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void EcuM_AL_DriverInitZero(void)
{
    /* TODO(ECUM_SRS_001): SWS_EcuM_02905 - Det_Init(), Dem_PreInit() */
}

void EcuM_AL_DriverInitOne(void)
{
    /* TODO(ECUM_SRS_001): SWS_EcuM_02907 - MCAL and BSW init in project order */
}

void EcuM_AL_Reset(EcuM_ResetType reset)
{
    (void)reset;
    /* TODO(ECUM_SRS_004): SWS_EcuM_04065 - ECUM_RESET_MCU -> Mcu_PerformReset() */
}

void EcuM_ErrorHook(uint16 reason)
{
    (void)reason;
    /* TODO: SWS_EcuM_02904 */
}
