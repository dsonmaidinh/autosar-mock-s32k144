/**
 * @file     SchM_CanSM.h
 * @brief    BSW Scheduler stub for module CanSM.
 * @details  Bare-metal project without RTE/OS: this header replaces the
 *           generated SchM_CanSM.h. It provides the exclusive area hooks
 *           and the scheduled (main) function prototypes of CanSM
 *           (AUTOSAR CP R24-11: scheduled functions are "available via"
 *           SchM_<Mod>.h). Main functions are called by Os_Sched (EcuM).
 */

#ifndef SCHM_CANSM_H
#define SCHM_CANSM_H

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
#define SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_00()    do { } while (0)
#define SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_00()     do { } while (0)

/*==================================================================================================
*                                 SCHEDULED FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief    Scheduled function of the CanSM (10 ms task).
 * @details  SWS: SWS_CanSM_00065 | Service ID: 0x05
 *           Project: CANSM_SRS_005, ECUM_SRS_002
 */
void CanSM_MainFunction(void);

#ifdef __cplusplus
}
#endif

#endif /* SCHM_CANSM_H */
