/**
 * @file     Dem.h
 * @brief    Diagnostic Event Manager (Dem) - public interface.
 * @details  API skeleton per AUTOSAR CP R24-11 SWS DiagnosticEventManager.
 *           The Dcm <-> Dem interface follows R24-11 (ClientId based), i.e. the
 *           4.0.3 deviation OP-DEM-01 of docs/Mock.docx is NOT applied.
 *           Scope v1.0: no NvM (SWS_Dem_00388 N/A), no OBD/J1939, no freeze
 *           frame / extended data. Dem_MainFunction is declared in SchM_Dem.h.
 *           AR release macros are kept at 4.7.0 to pass the inter-module
 *           version checks of NXP RTD 2.0.0 (Mcu); API signatures follow R24-11.
 *           Project requirements: DEM_SRS_001..DEM_SRS_007.
 */

#ifndef DEM_H
#define DEM_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "Dem_Types.h"
#include "Dem_Cfg.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define DEM_VENDOR_ID                       (0xFFFFU)   /* project-local, not a registered vendor */
#define DEM_MODULE_ID                       (54U)
#define DEM_INSTANCE_ID                     (0U)
#define DEM_AR_RELEASE_MAJOR_VERSION        (4U)
#define DEM_AR_RELEASE_MINOR_VERSION        (7U)
#define DEM_AR_RELEASE_REVISION_VERSION     (0U)
#define DEM_SW_MAJOR_VERSION                (0U)
#define DEM_SW_MINOR_VERSION                (1U)
#define DEM_SW_PATCH_VERSION                (0U)

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Service IDs (SWS chapter 8.3 / 8.5) */
#define DEM_SID_GET_VERSION_INFO                    (0x00U)
#define DEM_SID_PRE_INIT                            (0x01U)
#define DEM_SID_INIT                                (0x02U)
#define DEM_SID_SHUTDOWN                            (0x03U)
#define DEM_SID_SET_EVENT_STATUS                    (0x04U)
#define DEM_SID_RESET_EVENT_STATUS                  (0x05U)
#define DEM_SID_RESTART_OPERATION_CYCLE             (0x08U)
#define DEM_SID_GET_DTC_OF_EVENT                    (0x0DU)
#define DEM_SID_SET_DTC_FILTER                      (0x13U)
#define DEM_SID_GET_DTC_STATUS_AVAILABILITY_MASK    (0x16U)
#define DEM_SID_GET_NUMBER_OF_FILTERED_DTC          (0x17U)
#define DEM_SID_GET_NEXT_FILTERED_DTC               (0x18U)
#define DEM_SID_CLEAR_DTC                           (0x23U)
#define DEM_SID_DISABLE_DTC_SETTING                 (0x24U)
#define DEM_SID_ENABLE_DTC_SETTING                  (0x25U)
#define DEM_SID_GET_TRANSLATION_TYPE                (0x3CU)
#define DEM_SID_MAIN_FUNCTION                       (0x55U)
#define DEM_SID_GET_EVENT_UDS_STATUS                (0xB6U)
#define DEM_SID_SELECT_DTC                          (0xB7U)

/* Development errors (SWS_Dem_00173) */
#define DEM_E_WRONG_CONFIGURATION           (0x10U)
#define DEM_E_PARAM_POINTER                 (0x11U)
#define DEM_E_PARAM_DATA                    (0x12U)
#define DEM_E_PARAM_LENGTH                  (0x13U)
#define DEM_E_INIT_FAILED                   (0x14U)
#define DEM_E_UNINIT                        (0x20U)
#define DEM_E_WRONG_CONDITION               (0x40U)

/* Runtime errors (SWS_Dem_91035) */
#define DEM_E_UDS_STATUS_PROCESSING_FAILED  (0x21U)
#define DEM_E_NODATAAVAILABLE               (0x30U)

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Returns the version information of this module.
 * @details    SWS: SWS_Dem_00177 | Service ID: 0x00 | classic-platform: macro -> function
 * @param[out] versioninfo  Pointer to where to store the version information.
 */
void Dem_GetVersionInfo(Std_VersionInfoType* versioninfo);

/**
 * @brief      Initializes the internal states necessary to process events reported by BSW modules.
 * @details    SWS: SWS_Dem_00179 | Service ID: 0x01
 *             classic-platform: removed ConfigPtr (R24-11). Behaviour: SWS_Dem_00180.
 *             Project: DEM_SRS_001
 */
void Dem_PreInit(void);

/**
 * @brief      Initializes or reinitializes this module.
 * @details    SWS: SWS_Dem_00181 | Service ID: 0x02
 *             classic-platform: added ConfigPtr (R24-11).
 * @param[in]  ConfigPtr  Pointer to the configuration set in VARIANT-POST-BUILD.
 */
void Dem_Init(const Dem_ConfigType* ConfigPtr);

/**
 * @brief      Shuts down this module.
 * @details    SWS: SWS_Dem_00182 | Service ID: 0x03 | classic-platform: kept
 */
void Dem_Shutdown(void);

/**
 * @brief      Called by SW-Cs or BSW modules to report monitor status information.
 * @details    SWS: SWS_Dem_00183 | Service ID: 0x04 | classic-platform: kept
 *             Behaviour: SWS_Dem_00418, SWS_Dem_00419, SWS_Dem_00386..00395, SWS_Dem_00079.
 *             Project: DEM_SRS_002, DEM_SRS_003, DEM_SRS_004, DEM_SRS_006, CANSM_SRS_004
 * @param[in]  EventId      Identification of an event by assigned EventId.
 * @param[in]  EventStatus  Monitor test result.
 * @return     E_OK set of event status was successful, E_NOT_OK failed or could not be accepted.
 */
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);

/**
 * @brief      Resets the event failed status.
 * @details    SWS: SWS_Dem_00185 | Service ID: 0x05 | classic-platform: kept
 * @param[in]  EventId  Identification of an event by assigned EventId.
 * @return     E_OK reset was successful, E_NOT_OK reset failed or is not allowed.
 */
Std_ReturnType Dem_ResetEventStatus(Dem_EventIdType EventId);

/**
 * @brief      Restarts the given operation cycle.
 * @details    SWS: SWS_Dem_00194 | Service ID: 0x08 | classic-platform: not present
 *             (only Dem_SetOperationCycleState), added. Behaviour: SWS_Dem_00344, SWS_Dem_01224.
 *             Project: DEM_SRS_007, ECUM_SRS_003
 * @param[in]  OperationCycleId  Identification of operation cycle, like power cycle.
 * @return     E_OK restart accepted, E_NOT_OK not accepted.
 */
Std_ReturnType Dem_RestartOperationCycle(uint8 OperationCycleId);

/**
 * @brief      Gets the current UDS status byte assigned to the DTC of the event.
 * @details    SWS: SWS_Dem_91008 | Service ID: 0xb6 | classic-platform: not present, added.
 *             Project: DEM_SRS_004 (verification)
 * @param[in]  EventId        Identification of an event by assigned EventId.
 * @param[out] UDSStatusByte  UDS DTC status byte of the requested event.
 * @return     E_OK status available, E_NOT_OK not available.
 */
Std_ReturnType Dem_GetEventUdsStatus(Dem_EventIdType EventId, Dem_UdsStatusByteType* UDSStatusByte);

/**
 * @brief      Gets the DTC of an event.
 * @details    SWS: SWS_Dem_00198 | Service ID: 0x0d | classic-platform: kept
 * @param[in]  EventId     Identification of an event by assigned EventId.
 * @param[in]  DTCFormat   Defines the output-format of the requested DTC value.
 * @param[out] DTCOfEvent  Diagnostic Trouble Code of the event.
 * @return     E_OK, E_NOT_OK, DEM_E_NO_DTC_AVAILABLE.
 */
Std_ReturnType Dem_GetDTCOfEvent(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent);

/*==================================================================================================
*                              INTERFACE Dcm <-> Dem (ClientId based)
==================================================================================================*/
/**
 * @brief      Selects a DTC or DTC group as target for further operations.
 * @details    SWS: SWS_Dem_91016 | Service ID: 0xb7 | classic-platform: not present, added.
 *             Behaviour: SWS_Dem_01198, SWS_Dem_01254. Project: DEM_SRS_005, DCM_SRS_012
 * @param[in]  ClientId   Unique client id, assigned to the instance of the calling module.
 * @param[in]  DTC        DTC or group of DTCs (DEM_DTC_GROUP_ALL_DTCS).
 * @param[in]  DTCFormat  Format of the DTC value.
 * @param[in]  DTCOrigin  Event memory to be used.
 * @return     E_OK DTC successfully selected, DEM_BUSY another Dem_SelectDTC is ongoing.
 */
Std_ReturnType Dem_SelectDTC(uint8 ClientId, uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);

/**
 * @brief      Clears single DTCs, as well as groups of DTCs (selected by Dem_SelectDTC).
 * @details    SWS: SWS_Dem_00665 | Service ID: 0x23
 *             classic-platform: (dtc, format, origin) -> (ClientId) per R24-11.
 *             Behaviour: SWS_Dem_00385, SWS_Dem_00664. Project: DEM_SRS_005, DCM_SRS_012
 * @param[in]  ClientId  Unique client id, assigned to the instance of the calling module.
 * @return     E_OK, DEM_PENDING, DEM_WRONG_DTC, DEM_WRONG_DTCORIGIN, DEM_CLEAR_FAILED,
 *             DEM_CLEAR_BUSY, DEM_CLEAR_MEMORY_ERROR, DEM_BUSY.
 */
Std_ReturnType Dem_ClearDTC(uint8 ClientId);

/**
 * @brief      Disables the DTC setting for all DTCs assigned to the DemEventMemorySet of the client.
 * @details    SWS: SWS_Dem_00242 | Service ID: 0x24
 *             classic-platform: (group, kind) -> (ClientId) per R24-11.
 *             Behaviour: SWS_Dem_00079. Project: DEM_SRS_006, DCM_SRS_013
 * @param[in]  ClientId  Unique client id, assigned to the instance of the calling module.
 * @return     E_OK, E_NOT_OK.
 */
Std_ReturnType Dem_DisableDTCSetting(uint8 ClientId);

/**
 * @brief      (Re)-Enables the DTC setting for all DTCs assigned to the DemEventMemorySet of the client.
 * @details    SWS: SWS_Dem_00243 | Service ID: 0x25
 *             classic-platform: (group, kind) -> (ClientId) per R24-11. Project: DCM_SRS_013
 * @param[in]  ClientId  Unique client id, assigned to the instance of the calling module.
 * @return     E_OK, E_NOT_OK.
 */
Std_ReturnType Dem_EnableDTCSetting(uint8 ClientId);

/**
 * @brief      Sets the DTC filter (UDS 0x19 sub-functions 0x01, 0x02, 0x0A).
 * @details    SWS: SWS_Dem_00208 | Service ID: 0x13
 *             classic-platform: added ClientId, removed DTCKind, boolean filter flags (R24-11).
 *             Behaviour: SWS_Dem_00057, SWS_Dem_00649. Project: DCM_SRS_012
 * @param[in]  ClientId                        Unique client id.
 * @param[in]  DTCStatusMask                   Status byte mask for DTC status byte filtering.
 * @param[in]  DTCFormat                       Defines the output-format of the requested DTC values.
 * @param[in]  DTCOrigin                       Event memory to be filtered.
 * @param[in]  FilterWithSeverity              TRUE: severity information used for filtering.
 * @param[in]  DTCSeverityMask                 Severity mask used if FilterWithSeverity is TRUE.
 * @param[in]  FilterForFaultDetectionCounter  TRUE: fault detection counter used for filtering.
 * @return     E_OK filter accepted, E_NOT_OK wrong filter selected.
 */
Std_ReturnType Dem_SetDTCFilter(uint8 ClientId, uint8 DTCStatusMask, Dem_DTCFormatType DTCFormat,
                                Dem_DTCOriginType DTCOrigin, boolean FilterWithSeverity,
                                Dem_DTCSeverityType DTCSeverityMask, boolean FilterForFaultDetectionCounter);

/**
 * @brief      Gets the number of DTCs matching the filter set by Dem_SetDTCFilter.
 * @details    SWS: SWS_Dem_00214 | Service ID: 0x17
 *             classic-platform: added ClientId, Std_ReturnType (R24-11). Project: DCM_SRS_012
 * @param[in]  ClientId             Unique client id.
 * @param[out] NumberOfFilteredDTC  Number of DTCs matching the defined status mask.
 * @return     E_OK, E_NOT_OK, DEM_PENDING.
 */
Std_ReturnType Dem_GetNumberOfFilteredDTC(uint8 ClientId, uint16* NumberOfFilteredDTC);

/**
 * @brief      Gets the next filtered DTC matching the filter criteria.
 * @details    SWS: SWS_Dem_00215 | Service ID: 0x18
 *             classic-platform: added ClientId, uint8 status, Std_ReturnType (R24-11).
 *             Project: DCM_SRS_012
 * @param[in]  ClientId   Unique client id.
 * @param[out] DTC        Receives the DTC value in the format set by Dem_SetDTCFilter.
 * @param[out] DTCStatus  Receives the status information of the requested DTC.
 * @return     E_OK, DEM_NO_SUCH_ELEMENT, DEM_PENDING.
 */
Std_ReturnType Dem_GetNextFilteredDTC(uint8 ClientId, uint32* DTC, uint8* DTCStatus);

/**
 * @brief      Gets the DTC status availability mask of the selected fault memory.
 * @details    SWS: SWS_Dem_00213 | Service ID: 0x16
 *             classic-platform: added ClientId and DTCOrigin (R24-11). Project: DCM_SRS_012
 * @param[in]  ClientId       Unique client id.
 * @param[out] DTCStatusMask  Status bits supported by the Dem.
 * @param[in]  DTCOrigin      Event memory to be used.
 * @return     E_OK, E_NOT_OK.
 */
Std_ReturnType Dem_GetDTCStatusAvailabilityMask(uint8 ClientId, Dem_UdsStatusByteType* DTCStatusMask,
                                                Dem_DTCOriginType DTCOrigin);

/**
 * @brief      Gets the supported DTC formats of the ECU.
 * @details    SWS: SWS_Dem_00230 | Service ID: 0x3c
 *             classic-platform: added ClientId (R24-11). Project: DCM_SRS_012
 * @param[in]  ClientId  Unique client id.
 * @return     Configured DTC translation format.
 */
Dem_DTCTranslationFormatType Dem_GetTranslationType(uint8 ClientId);

#ifdef __cplusplus
}
#endif

#endif /* DEM_H */
