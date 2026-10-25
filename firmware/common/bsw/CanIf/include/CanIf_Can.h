/**
 * @file     CanIf_Can.h
 * @brief    CAN Interface (CanIf) - interface towards the CAN driver.
 * @details  Integration header included by NXP RTD Can_43_FLEXCAN. In R24-11
 *           the CanIf callbacks are "available via CanIf.h", so this file only
 *           re-exports CanIf.h and provides the CANIF_CAN_* version macros that
 *           RTD 2.0.0 checks (Can_43_FLEXCAN.c / Can_43_FLEXCAN_Ipw.c).
 */

#ifndef CANIF_CAN_H
#define CANIF_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "CanIf.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CANIF_CAN_VENDOR_ID                     CANIF_VENDOR_ID
#define CANIF_CAN_AR_RELEASE_MAJOR_VERSION      CANIF_AR_RELEASE_MAJOR_VERSION
#define CANIF_CAN_AR_RELEASE_MINOR_VERSION      CANIF_AR_RELEASE_MINOR_VERSION
#define CANIF_CAN_AR_RELEASE_REVISION_VERSION   CANIF_AR_RELEASE_REVISION_VERSION
#define CANIF_CAN_SW_MAJOR_VERSION              CANIF_SW_MAJOR_VERSION
#define CANIF_CAN_SW_MINOR_VERSION              CANIF_SW_MINOR_VERSION
#define CANIF_CAN_SW_PATCH_VERSION              CANIF_SW_PATCH_VERSION

#ifdef __cplusplus
}
#endif

#endif /* CANIF_CAN_H */
