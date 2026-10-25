/**
 * @file     Dcm_ComM.h
 * @brief    Diagnostic Communication Manager (Dcm) - callbacks for the ComM.
 * @details  Callbacks per AUTOSAR CP R24-11 SWS DiagnosticCommunicationManager
 *           ("available via Dcm_ComM.h"; classic-platform used Dcm_Cbk.h).
 */

#ifndef DCM_COMM_H
#define DCM_COMM_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Dcm.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      ComM notifies that the network NetworkId entered No Communication mode.
 * @details    SWS: SWS_Dcm_00356 | Service ID: 0x21 | classic-platform: kept
 * @param[in]  NetworkId  Identifier of the network concerned by the mode change.
 */
void Dcm_ComM_NoComModeEntered(uint8 NetworkId);

/**
 * @brief      ComM notifies that the network NetworkId entered Silent Communication mode.
 * @details    SWS: SWS_Dcm_00358 | Service ID: 0x22 | classic-platform: kept
 * @param[in]  NetworkId  Identifier of the network concerned by the mode change.
 */
void Dcm_ComM_SilentComModeEntered(uint8 NetworkId);

/**
 * @brief      ComM notifies that the network NetworkId entered Full Communication mode.
 * @details    SWS: SWS_Dcm_00360 | Service ID: 0x23 | classic-platform: kept
 * @param[in]  NetworkId  Identifier of the network concerned by the mode change.
 */
void Dcm_ComM_FullComModeEntered(uint8 NetworkId);

#ifdef __cplusplus
}
#endif

#endif /* DCM_COMM_H */
