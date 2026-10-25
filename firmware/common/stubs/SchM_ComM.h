/**
 * @file     SchM_ComM.h
 * @brief    BSW Scheduler stub for module ComM.
 * @details  Bare-metal project without RTE/OS: this header replaces the
 *           generated SchM_ComM.h. It provides the exclusive area hooks
 *           and the scheduled (main) function prototypes of ComM
 *           (AUTOSAR CP R24-11: scheduled functions are "available via"
 *           SchM_<Mod>.h). Main functions are called by Os_Sched (EcuM).
 */

#ifndef SCHM_COMM_H
#define SCHM_COMM_H

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
#define SchM_Enter_ComM_COMM_EXCLUSIVE_AREA_00()    do { } while (0)
#define SchM_Exit_ComM_COMM_EXCLUSIVE_AREA_00()     do { } while (0)

/*==================================================================================================
*                                 SCHEDULED FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief    ComM main function of channel CAN0 (10 ms task).
 * @details  SWS: SWS_ComM_00429 | Service ID: 0x60
 *           ComM_MainFunction_<ComMChannel.ShortName> with ShortName = CAN0.
 *           Project: COMM_SRS_004, ECUM_SRS_002
 */
void ComM_MainFunction_CAN0(void);

#ifdef __cplusplus
}
#endif

#endif /* SCHM_COMM_H */
