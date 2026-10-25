/**
 * @file     CanIf_Types.h
 * @brief    CAN Interface (CanIf) - type definitions.
 * @details  Types per AUTOSAR CP R24-11 SWS CANInterface chapter 8.2.
 *           Imported types (Can_ControllerStateType, Can_HwType, Can_ErrorType,
 *           PduInfoType, ...) come from RTD Can_GeneralTypes.h / ComStack_Types.h
 *           (SWS_CANIF_00142).
 */

#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

/*==================================================================================================
*                                    STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
 * @brief    PDU mode of a CAN channel (SWS_CANIF_00137).
 * @details  Project: CANIF_SRS_003, CANIF_SRS_004
 */
typedef enum
{
    CANIF_OFFLINE            = 0x00U,  /**< Tx and Rx path disabled */
    CANIF_TX_OFFLINE         = 0x01U,  /**< Tx path disabled, Rx path enabled */
    CANIF_TX_OFFLINE_ACTIVE  = 0x02U,  /**< Tx path offline active, Rx path enabled */
    CANIF_ONLINE             = 0x03U   /**< Tx and Rx path enabled */
} CanIf_PduModeType;

/**
 * @brief    Post-build configuration of the CanIf (SWS_CANIF_00144, SWS_CANIF_00523).
 * @details  Implementation specific: Tx/Rx L-PDU tables, HTH/HRH mapping,
 *           software filter for BasicCAN HRH (0x7E0/0x7DF), upper layer callbacks.
 */
typedef struct
{
    uint8 CanIf_Dummy;  /* TODO(CANIF_SRS_001/005): add Tx/Rx PDU and HOH configuration (C-03) */
} CanIf_ConfigType;

#ifdef __cplusplus
}
#endif

#endif /* CANIF_TYPES_H */
