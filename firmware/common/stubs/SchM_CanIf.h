/**
 * @file     SchM_CanIf.h
 * @brief    BSW Scheduler stub for module CanIf.
 * @details  Bare-metal project without RTE/OS: this header replaces the
 *           generated SchM_CanIf.h. It provides the exclusive area hooks
 *           and the scheduled (main) function prototypes of CanIf
 *           (AUTOSAR CP R24-11: scheduled functions are "available via"
 *           SchM_<Mod>.h). Main functions are called by Os_Sched (EcuM).
 */

#ifndef SCHM_CANIF_H
#define SCHM_CANIF_H

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
#define SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_00()    do { } while (0)
#define SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_00()     do { } while (0)

#ifdef __cplusplus
}
#endif

#endif /* SCHM_CANIF_H */
