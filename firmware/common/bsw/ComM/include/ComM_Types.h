/**
 * @file     ComM_Types.h
 * @brief    Communication Manager (ComM) - type definitions.
 * @details  Types per AUTOSAR CP R24-11 SWS COMManager chapters 8.2 and 8.7.
 *           Without RTE, the Rte_ComM_Type.h types are defined here.
 *           Also used by CanSM (ComM_ModeType).
 */

#ifndef COMM_TYPES_H
#define COMM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "ComStack_Types.h"

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Std_ReturnType extension (SWS_ComM_91027) */
#define COMM_E_MODE_LIMITATION              ((Std_ReturnType)2U)

/* ComM_ModeType values (SWS_ComM_00672) */
#define COMM_NO_COMMUNICATION               ((ComM_ModeType)0U)
#define COMM_SILENT_COMMUNICATION           ((ComM_ModeType)1U)
#define COMM_FULL_COMMUNICATION             ((ComM_ModeType)2U)

/* Reserved user ID (SWS_ComM_00670) */
#define COMM_NOT_USED_USER_ID               ((ComM_UserHandleType)65535U)

/*==================================================================================================
*                                    STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief Communication mode (SWS_ComM_00672). */
typedef uint8 ComM_ModeType;

/**
 * @brief    Handle to identify a ComM user (SWS_ComM_00670).
 * @details  classic-platform uses uint8, R24-11 defines uint16.
 */
typedef uint16 ComM_UserHandleType;

/**
 * @brief    Initialization status of ComM (SWS_ComM_00668).
 * @details  Project: COMM_SRS_001
 */
typedef enum
{
    COMM_UNINIT = 0x00U,    /**< Not initialized or not usable (default after reset) */
    COMM_INIT   = 0x01U     /**< Initialized and usable */
} ComM_InitStatusType;

/**
 * @brief    Post-build configuration of ComM (SWS_ComM_00162).
 * @details  Implementation specific: one channel CAN0 (bus type CAN, NmVariant NONE),
 *           user Diag mapped to CAN0 (docs/Mock.docx X-02).
 */
typedef struct
{
    uint8 ComM_Dummy;   /* TODO(COMM_SRS_002): add channel and user configuration (X-02) */
} ComM_ConfigType;

#ifdef __cplusplus
}
#endif

#endif /* COMM_TYPES_H */
