/**
 * @file     PduR.h
 * @brief    PDU Router (PduR) - public interface.
 * @details  API skeleton per AUTOSAR CP R24-11 SWS PDURouter.
 *           Scope v1.0: TP routing CanTp <-> Dcm only, no communication
 *           interface routing (SWS_PduR_00625/00627/00621 N/A).
 *           Upper/lower layer specific APIs are in PduR_Dcm.h and PduR_CanTp.h.
 *           AR release macros are kept at 4.7.0 (RTD 2.0.0 baseline);
 *           API signatures follow R24-11.
 *           Project requirements: PDUR_SRS_001..PDUR_SRS_005.
 */

#ifndef PDUR_H
#define PDUR_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "PduR_Types.h"
#include "PduR_Cfg.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define PDUR_VENDOR_ID                      (0xFFFFU)   /* project-local, not a registered vendor */
#define PDUR_MODULE_ID                      (51U)
#define PDUR_INSTANCE_ID                    (0U)
#define PDUR_AR_RELEASE_MAJOR_VERSION       (4U)
#define PDUR_AR_RELEASE_MINOR_VERSION       (7U)
#define PDUR_AR_RELEASE_REVISION_VERSION    (0U)
#define PDUR_SW_MAJOR_VERSION               (0U)
#define PDUR_SW_MINOR_VERSION               (1U)
#define PDUR_SW_PATCH_VERSION               (0U)

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Service IDs (SWS chapter 8.3 / 8.4) */
#define PDUR_SID_LOTP_COPY_TX_DATA          (0x43U)
#define PDUR_SID_LOTP_COPY_RX_DATA          (0x44U)
#define PDUR_SID_LOTP_RX_INDICATION         (0x45U)
#define PDUR_SID_LOTP_START_OF_RECEPTION    (0x46U)
#define PDUR_SID_LOTP_TX_CONFIRMATION       (0x48U)
#define PDUR_SID_UP_TRANSMIT                (0x49U)
#define PDUR_SID_INIT                       (0xF0U)
#define PDUR_SID_GET_VERSION_INFO           (0xF1U)
#define PDUR_SID_GET_CONFIGURATION_ID       (0xF2U)

/* Development errors (SWS_PduR_00100) */
#define PDUR_E_INIT_FAILED                  (0x00U)
#define PDUR_E_UNINIT                       (0x01U)
#define PDUR_E_PDU_ID_INVALID               (0x02U)
#define PDUR_E_ROUTING_PATH_GROUP_ID_INVALID (0x08U)
#define PDUR_E_PARAM_POINTER                (0x09U)

/* Runtime errors (SWS_PDUR_00816) */
#define PDUR_E_TP_GW_TX_REQ_REJECTED        (0x03U)
#define PDUR_E_PDU_INSTANCES_LOST           (0x0AU)

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Initializes the PDU Router.
 * @details    SWS: SWS_PduR_00334 | Service ID: 0xf0 | classic-platform: kept
 *             Behaviour: SWS_PduR_00325, SWS_PduR_00326. Project: PDUR_SRS_001
 * @param[in]  ConfigPtr  Pointer to post build configuration.
 */
void PduR_Init(const PduR_PBConfigType* ConfigPtr);

/**
 * @brief      Returns the version information of this module.
 * @details    SWS: SWS_PduR_00338 | Service ID: 0xf1 | classic-platform: kept
 * @param[out] versionInfo  Pointer to where to store the version information.
 */
void PduR_GetVersionInfo(Std_VersionInfoType* versionInfo);

/**
 * @brief      Returns the unique identifier of the post-build time configuration.
 * @details    SWS: SWS_PduR_00341 | Service ID: 0xf2 | classic-platform: kept
 * @return     Identifier of the post-build time configuration.
 */
PduR_PBConfigIdType PduR_GetConfigurationId(void);

#ifdef __cplusplus
}
#endif

#endif /* PDUR_H */
