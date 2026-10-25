/**
 * @file     SchM_Dem.h
 * @brief    BSW Scheduler stub for module Dem.
 * @details  Bare-metal project without RTE/OS: this header replaces the
 *           generated SchM_Dem.h. It provides the exclusive area hooks
 *           and the scheduled (main) function prototypes of Dem
 *           (AUTOSAR CP R24-11: scheduled functions are "available via"
 *           SchM_<Mod>.h). Main functions are called by Os_Sched (EcuM).
 */

#ifndef SCHM_DEM_H
#define SCHM_DEM_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                    EXCLUSIVE AREA HOOKS
==================================================================================================*/
/* TODO: map to OsIf_SuspendAllInterrupts()/OsIf_ResumeAllInterrupts() when the module needs it. */
#define SchM_Enter_Dem_DEM_EXCLUSIVE_AREA_00()    do { } while (0)
#define SchM_Exit_Dem_DEM_EXCLUSIVE_AREA_00()     do { } while (0)

/*==================================================================================================
*                                 SCHEDULED FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief    Processes all not event based Dem internal functions (10 ms task).
 * @details  SWS: SWS_Dem_00266 | Service ID: 0x55
 *           Project: ECUM_SRS_002
 */
void Dem_MainFunction(void);

#ifdef __cplusplus
}
#endif

#endif /* SCHM_DEM_H */
