/**
 * @file     Dem.c
 * @brief    Diagnostic Event Manager (Dem) - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/dem (commits M-01..M-04) following the SWS IDs and
 *           SRS IDs referenced in Dem.h and SchM_Dem.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Dem.h"
#include "SchM_Dem.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void Dem_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    (void)versioninfo;
    /* TODO: SWS_Dem_00177 */
}

void Dem_PreInit(void)
{
    /* TODO(DEM_SRS_001): SWS_Dem_00179, SWS_Dem_00180 */
}

void Dem_Init(const Dem_ConfigType* ConfigPtr)
{
    (void)ConfigPtr;
    /* TODO: SWS_Dem_00181 */
}

void Dem_Shutdown(void)
{
    /* TODO: SWS_Dem_00182 */
}

void Dem_MainFunction(void)
{
    /* TODO: SWS_Dem_00266 */
}

Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
    (void)EventId;
    (void)EventStatus;
    /* TODO(DEM_SRS_002/003/004/006): SWS_Dem_00183, SWS_Dem_00418, SWS_Dem_00419,
     *   SWS_Dem_00386, SWS_Dem_00389, SWS_Dem_00390, SWS_Dem_00393, SWS_Dem_00395, SWS_Dem_00079 */
    return E_NOT_OK;
}

Std_ReturnType Dem_ResetEventStatus(Dem_EventIdType EventId)
{
    (void)EventId;
    /* TODO: SWS_Dem_00185 */
    return E_NOT_OK;
}

Std_ReturnType Dem_RestartOperationCycle(uint8 OperationCycleId)
{
    (void)OperationCycleId;
    /* TODO(DEM_SRS_007): SWS_Dem_00194, SWS_Dem_00344, SWS_Dem_01224 */
    return E_NOT_OK;
}

Std_ReturnType Dem_GetEventUdsStatus(Dem_EventIdType EventId, Dem_UdsStatusByteType* UDSStatusByte)
{
    (void)EventId;
    (void)UDSStatusByte;
    /* TODO(DEM_SRS_004): SWS_Dem_91008 */
    return E_NOT_OK;
}

Std_ReturnType Dem_GetDTCOfEvent(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent)
{
    (void)EventId;
    (void)DTCFormat;
    (void)DTCOfEvent;
    /* TODO: SWS_Dem_00198 */
    return E_NOT_OK;
}

Std_ReturnType Dem_SelectDTC(uint8 ClientId, uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    (void)ClientId;
    (void)DTC;
    (void)DTCFormat;
    (void)DTCOrigin;
    /* TODO(DEM_SRS_005): SWS_Dem_91016, SWS_Dem_01198, SWS_Dem_01254 */
    return E_NOT_OK;
}

Std_ReturnType Dem_ClearDTC(uint8 ClientId)
{
    (void)ClientId;
    /* TODO(DEM_SRS_005): SWS_Dem_00665, SWS_Dem_00385, SWS_Dem_00664 */
    return E_NOT_OK;
}

Std_ReturnType Dem_DisableDTCSetting(uint8 ClientId)
{
    (void)ClientId;
    /* TODO(DEM_SRS_006): SWS_Dem_00242, SWS_Dem_00079 */
    return E_NOT_OK;
}

Std_ReturnType Dem_EnableDTCSetting(uint8 ClientId)
{
    (void)ClientId;
    /* TODO: SWS_Dem_00243 */
    return E_NOT_OK;
}

Std_ReturnType Dem_SetDTCFilter(uint8 ClientId, uint8 DTCStatusMask, Dem_DTCFormatType DTCFormat,
                                Dem_DTCOriginType DTCOrigin, boolean FilterWithSeverity,
                                Dem_DTCSeverityType DTCSeverityMask, boolean FilterForFaultDetectionCounter)
{
    (void)ClientId;
    (void)DTCStatusMask;
    (void)DTCFormat;
    (void)DTCOrigin;
    (void)FilterWithSeverity;
    (void)DTCSeverityMask;
    (void)FilterForFaultDetectionCounter;
    /* TODO: SWS_Dem_00208, SWS_Dem_00057, SWS_Dem_00649 */
    return E_NOT_OK;
}

Std_ReturnType Dem_GetNumberOfFilteredDTC(uint8 ClientId, uint16* NumberOfFilteredDTC)
{
    (void)ClientId;
    (void)NumberOfFilteredDTC;
    /* TODO: SWS_Dem_00214 */
    return E_NOT_OK;
}

Std_ReturnType Dem_GetNextFilteredDTC(uint8 ClientId, uint32* DTC, uint8* DTCStatus)
{
    (void)ClientId;
    (void)DTC;
    (void)DTCStatus;
    /* TODO: SWS_Dem_00215 */
    return DEM_NO_SUCH_ELEMENT;
}

Std_ReturnType Dem_GetDTCStatusAvailabilityMask(uint8 ClientId, Dem_UdsStatusByteType* DTCStatusMask,
                                                Dem_DTCOriginType DTCOrigin)
{
    (void)ClientId;
    (void)DTCStatusMask;
    (void)DTCOrigin;
    /* TODO: SWS_Dem_00213 */
    return E_NOT_OK;
}

Dem_DTCTranslationFormatType Dem_GetTranslationType(uint8 ClientId)
{
    (void)ClientId;
    /* TODO: SWS_Dem_00230 */
    return DEM_DTC_TRANSLATION_ISO14229_1;
}
