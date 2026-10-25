/**
 * @file     CanTp_Types.h
 * @brief    CAN Transport Layer (CanTp) - type definitions.
 * @details  Types per AUTOSAR CP R24-11 SWS CANTransportLayer chapter 8.2
 *           ("available via CanTp.h", which includes this file).
 */

#ifndef CANTP_TYPES_H
#define CANTP_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "ComStack_Types.h"

/*==================================================================================================
*                                    STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
 * @brief    Internal module state (SWS_CanTp_00027, SWS_CanTp_00168).
 * @details  Project: CANTP_SRS_001
 */
typedef enum
{
    CANTP_OFF = 0U,     /**< Not initialized (state after power up) */
    CANTP_ON            /**< Initialized, all connections idle after CanTp_Init */
} CanTp_StateType;

/**
 * @brief    Post-build configuration of the CanTp (SWS_CanTp_00340).
 * @details  Implementation specific: physical (0x7E0/0x7E8) and functional
 *           (0x7DF, SF only) N-SDUs, padding 0xAA, BS 0, STmin 0, N_As/N_Ar/
 *           N_Bs/N_Cr 1000 ms in 1 ms ticks (docs/Mock.docx 1.8, T-04).
 */
typedef struct
{
    uint8 CanTp_Dummy;  /* TODO(CANTP_SRS_001): add Rx/Tx N-SDU configuration (T-04) */
} CanTp_ConfigType;

#ifdef __cplusplus
}
#endif

#endif /* CANTP_TYPES_H */
