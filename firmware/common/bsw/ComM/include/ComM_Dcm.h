/**
 * @file     ComM_Dcm.h
 * @brief    Communication Manager (ComM) - interface for the Dcm.
 * @details  Callbacks per AUTOSAR CP R24-11 SWS COMManager ("available via ComM_Dcm.h").
 */

#ifndef COMM_DCM_H
#define COMM_DCM_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "ComM.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Indication of active diagnostic by the Dcm.
 * @details    SWS: SWS_ComM_00873 | Service ID: 0x1f | classic-platform: kept
 *             Behaviour: SWS_ComM_00866 (treated as FULL_COM request).
 *             Project: COMM_SRS_003, DCM_SRS_015
 * @param[in]  Channel  Channel needed for diagnostic communication.
 */
void ComM_DCM_ActiveDiagnostic(NetworkHandleType Channel);

/**
 * @brief      Indication of inactive diagnostic by the Dcm.
 * @details    SWS: SWS_ComM_00874 | Service ID: 0x20 | classic-platform: kept
 *             Project: COMM_SRS_003
 * @param[in]  Channel  Channel no longer needed for diagnostic communication.
 */
void ComM_DCM_InactiveDiagnostic(NetworkHandleType Channel);

#ifdef __cplusplus
}
#endif

#endif /* COMM_DCM_H */
