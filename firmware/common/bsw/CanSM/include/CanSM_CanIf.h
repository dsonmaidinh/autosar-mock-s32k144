/**
 * @file     CanSM_CanIf.h
 * @brief    CAN State Manager (CanSM) - callbacks for the CanIf.
 * @details  Callbacks per AUTOSAR CP R24-11 SWS CANStateManager
 *           ("available via CanSM_CanIf.h"; classic-platform used CanSM_Cbk.h).
 */

#ifndef CANSM_CANIF_H
#define CANSM_CANIF_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "CanSM.h"
#include "Can_GeneralTypes.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Notifies the CanSM about a bus-off event on a certain CAN controller.
 * @details    SWS: SWS_CanSM_00064 | Service ID: 0x04 | classic-platform: kept
 *             Behaviour: SWS_CanSM_00500, SWS_CanSM_00606, SWS_CanSM_00522
 *             (Dem_SetEventStatus(CANSM_E_BUS_OFF, PREFAILED)).
 *             Project: CANSM_SRS_003, CANSM_SRS_004
 * @param[in]  ControllerId  CAN controller which detected a bus-off event.
 */
void CanSM_ControllerBusOff(uint8 ControllerId);

/**
 * @brief      Notifies the CanSM about a CAN controller mode change.
 * @details    SWS: SWS_CanSM_00396 | Service ID: 0x07
 *             classic-platform: CanIf_ControllerModeType -> Can_ControllerStateType (R24-11).
 *             Project: CANSM_SRS_002, CANSM_SRS_005
 * @param[in]  ControllerId    CAN controller whose mode has changed.
 * @param[in]  ControllerMode  Notified CAN controller mode.
 */
void CanSM_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode);

#ifdef __cplusplus
}
#endif

#endif /* CANSM_CANIF_H */
