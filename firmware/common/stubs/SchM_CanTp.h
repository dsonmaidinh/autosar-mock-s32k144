/**
 * @file     SchM_CanTp.h
 * @brief    BSW Scheduler stub for module CanTp.
 * @details  Bare-metal project without RTE/OS: this header replaces the
 *           generated SchM_CanTp.h. It provides the exclusive area hooks
 *           and the scheduled (main) function prototypes of CanTp
 *           (AUTOSAR CP R24-11: scheduled functions are "available via"
 *           SchM_<Mod>.h). Main functions are called by Os_Sched (EcuM).
 */

#ifndef SCHM_CANTP_H
#define SCHM_CANTP_H

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
#define SchM_Enter_CanTp_CANTP_EXCLUSIVE_AREA_00()    do { } while (0)
#define SchM_Exit_CanTp_CANTP_EXCLUSIVE_AREA_00()     do { } while (0)

/*==================================================================================================
*                                 SCHEDULED FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief    Main function for scheduling the CAN TP (1 ms task).
 * @details  SWS: SWS_CanTp_00213 | Service ID: 0x06
 *           Project: CANTP_SRS_006, CANTP_SRS_007, ECUM_SRS_002
 */
void CanTp_MainFunction(void);

#ifdef __cplusplus
}
#endif

#endif /* SCHM_CANTP_H */
