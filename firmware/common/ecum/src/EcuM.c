/**
 * @file     EcuM.c
 * @brief    ECU State Manager (EcuM) - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/det-ecum (commit D-03) following the SWS IDs and
 *           SRS IDs referenced in EcuM.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "EcuM.h"
#include "EcuM_Externals.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void EcuM_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    (void)versioninfo;
    /* TODO: SWS_EcuM_02813 */
}

void EcuM_Init(void)
{
    /* TODO(ECUM_SRS_001): SWS_EcuM_02811, SWS_EcuM_02411, SWS_EcuM_04145
     *   EcuM_AL_DriverInitZero() -> Det_Init, Dem_PreInit
     *   EcuM_AL_DriverInitOne()  -> Mcu, Port, Gpt, Can_43_FLEXCAN, CanIf, CanTp, PduR,
     *                               Dem_Init, ComM, CanSM, Dcm
     * TODO(ECUM_SRS_003): Dem_RestartOperationCycle(power cycle) after Dem_Init
     * TODO(ECUM_SRS_002): Os_Sched_Init() */
}

void EcuM_SetWakeupEvent(EcuM_WakeupSourceType sources)
{
    (void)sources;
    /* TODO: SWS_EcuM_02826 - wakeup not used in v1.0 */
}

void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    (void)wakeupSource;
    /* TODO: SWS_EcuM_91007 - wakeup not used in v1.0 */
}
