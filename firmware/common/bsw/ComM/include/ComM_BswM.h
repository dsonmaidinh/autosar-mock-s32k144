/**
 * @file     ComM_BswM.h
 * @brief    Communication Manager (ComM) - interface for the BswM.
 * @details  Callback per AUTOSAR CP R24-11 SWS COMManager ("available via ComM_BswM.h").
 *           No BswM in v1.0: EcuM calls ComM_CommunicationAllowed(CAN0, TRUE) at startup.
 */

#ifndef COMM_BSWM_H
#define COMM_BSWM_H

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
 * @brief      Indicates if communication is allowed on a channel.
 * @details    SWS: SWS_ComM_00871 | Service ID: 0x35 | classic-platform: kept
 * @param[in]  Channel  Channel handle.
 * @param[in]  Allowed  TRUE communication allowed, FALSE communication not allowed.
 */
void ComM_CommunicationAllowed(NetworkHandleType Channel, boolean Allowed);

#ifdef __cplusplus
}
#endif

#endif /* COMM_BSWM_H */
