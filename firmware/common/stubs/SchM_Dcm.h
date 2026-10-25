/**
 * @file     SchM_Dcm.h
 * @brief    BSW Scheduler stub for module Dcm.
 * @details  Bare-metal project without RTE/OS: this header replaces the
 *           generated SchM_Dcm.h. It provides the exclusive area hooks
 *           and the scheduled (main) function prototypes of Dcm
 *           (AUTOSAR CP R24-11: scheduled functions are "available via"
 *           SchM_<Mod>.h). Main functions are called by Os_Sched (EcuM).
 */

#ifndef SCHM_DCM_H
#define SCHM_DCM_H

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
#define SchM_Enter_Dcm_DCM_EXCLUSIVE_AREA_00()    do { } while (0)
#define SchM_Exit_Dcm_DCM_EXCLUSIVE_AREA_00()     do { } while (0)

/*==================================================================================================
*                                 SCHEDULED FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief    Processing of the Dcm main loop tasks (10 ms task).
 * @details  SWS: SWS_Dcm_00053 | Service ID: 0x25
 *           Project: DCM_SRS_008, DCM_SRS_009, ECUM_SRS_002
 */
void Dcm_MainFunction(void);

#ifdef __cplusplus
}
#endif

#endif /* SCHM_DCM_H */
