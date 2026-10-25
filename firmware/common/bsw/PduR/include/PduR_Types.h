/**
 * @file     PduR_Types.h
 * @brief    PDU Router (PduR) - type definitions.
 * @details  Types per AUTOSAR CP R24-11 SWS PDURouter chapter 8.2
 *           ("available via PduR.h", which includes this file).
 */

#ifndef PDUR_TYPES_H
#define PDUR_TYPES_H

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
/** @brief Identification of the post-build configuration in use (SWS_PduR_00771). */
typedef uint16 PduR_PBConfigIdType;

/**
 * @brief    States of the PDU Router (SWS_PduR_00742).
 * @details  Behaviour: SWS_PduR_00325, SWS_PduR_00326. Project: PDUR_SRS_001
 */
typedef enum
{
    PDUR_UNINIT = 0U,   /**< PDU Router not initialised */
    PDUR_ONLINE         /**< PDU Router initialized successfully */
} PduR_StateType;

/**
 * @brief    Post-build configuration of the PDU Router (SWS_PduR_00743).
 * @details  Implementation specific: routing paths 0x7E0 -> Dcm, 0x7DF -> Dcm,
 *           Dcm -> 0x7E8 (SWS_PduR_00161, SWS_PduR_00766, SWS_PduR_00673).
 */
typedef struct
{
    PduR_PBConfigIdType PduR_ConfigurationId;
    /* TODO(PDUR_SRS_002..005): add TP routing path tables (T-05) */
} PduR_PBConfigType;

#ifdef __cplusplus
}
#endif

#endif /* PDUR_TYPES_H */
