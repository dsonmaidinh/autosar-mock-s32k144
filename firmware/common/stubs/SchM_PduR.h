/**
 * @file     SchM_PduR.h
 * @brief    BSW Scheduler stub for module PduR.
 * @details  Bare-metal project without RTE/OS: this header replaces the
 *           generated SchM_PduR.h. It provides the exclusive area hooks
 *           and the scheduled (main) function prototypes of PduR
 *           (AUTOSAR CP R24-11: scheduled functions are "available via"
 *           SchM_<Mod>.h). Main functions are called by Os_Sched (EcuM).
 */

#ifndef SCHM_PDUR_H
#define SCHM_PDUR_H

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
#define SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_00()    do { } while (0)
#define SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_00()     do { } while (0)

#ifdef __cplusplus
}
#endif

#endif /* SCHM_PDUR_H */
