/**
 * @file     DummySwc.h
 * @brief    Dummy software component reporting the test event to the Dem.
 * @details  Project component, no AUTOSAR SWS (no RTE in v1.0). Reports
 *           DemConf_DemEventParameter_DUMMY_TEST (DTC 0x9A0113, docs/Mock.docx 1.5)
 *           through Dem_SetEventStatus.
 */

#ifndef DUMMYSWC_H
#define DUMMYSWC_H

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
 * @brief      Initializes the dummy component.
 * @details    Called by EcuM after Dem_Init.
 */
void DummySwc_Init(void);

/**
 * @brief      Cyclic function (10 ms task): reports the monitor result of the test event.
 * @details    Uses Dem_SetEventStatus (SWS_Dem_00183) with PREFAILED / PREPASSED
 *             so that the counter based debounce can be tested (DEM_SRS_002, DEM_SRS_003).
 */
void DummySwc_MainFunction(void);

/**
 * @brief      Test hook: selects the reported monitor result.
 * @param[in]  Failed  TRUE report PREFAILED, FALSE report PREPASSED.
 */
void DummySwc_SetTestFailed(boolean Failed);

#ifdef __cplusplus
}
#endif

#endif /* DUMMYSWC_H */
