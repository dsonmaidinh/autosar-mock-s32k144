/**
 * @file     DummySwc.c
 * @brief    Dummy software component - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/dem (commit M-02).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "DummySwc.h"
#include "Dem.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void DummySwc_Init(void)
{
    /* TODO(M-02): reset the test state */
}

void DummySwc_MainFunction(void)
{
    /* TODO(DEM_SRS_002/003): Dem_SetEventStatus(DemConf_DemEventParameter_DUMMY_TEST, ...) */
}

void DummySwc_SetTestFailed(boolean Failed)
{
    (void)Failed;
    /* TODO(M-02): store the requested monitor result */
}
