/**
 * @file     Dem_Types.h
 * @brief    Diagnostic Event Manager (Dem) - type definitions.
 * @details  Types per AUTOSAR CP R24-11 SWS DiagnosticEventManager chapters
 *           8.2 and 8.6.1. Without RTE, the Rte_Dem_Type.h types are defined here.
 */

#ifndef DEM_TYPES_H
#define DEM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Std_ReturnType extensions (return values of the Dem API tables, e.g. SWS_Dem_00665) */
#define DEM_PENDING                         ((Std_ReturnType)4U)
#define DEM_CLEAR_BUSY                      ((Std_ReturnType)5U)
#define DEM_CLEAR_MEMORY_ERROR              ((Std_ReturnType)6U)
#define DEM_CLEAR_FAILED                    ((Std_ReturnType)7U)
#define DEM_WRONG_DTC                       ((Std_ReturnType)8U)
#define DEM_WRONG_DTCORIGIN                 ((Std_ReturnType)9U)
#define DEM_E_NO_DTC_AVAILABLE              ((Std_ReturnType)10U)
#define DEM_E_NO_FDC_AVAILABLE              ((Std_ReturnType)14U)
#define DEM_BUFFER_TOO_SMALL                ((Std_ReturnType)21U)
#define DEM_BUSY                            ((Std_ReturnType)22U)
#define DEM_NO_SUCH_ELEMENT                 ((Std_ReturnType)48U)

/* Dem_EventStatusType values (SWS_Dem_00926) */
#define DEM_EVENT_STATUS_PASSED                 ((Dem_EventStatusType)0x00U)
#define DEM_EVENT_STATUS_FAILED                 ((Dem_EventStatusType)0x01U)
#define DEM_EVENT_STATUS_PREPASSED              ((Dem_EventStatusType)0x02U)
#define DEM_EVENT_STATUS_PREFAILED              ((Dem_EventStatusType)0x03U)
#define DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED  ((Dem_EventStatusType)0x04U)

/* Dem_UdsStatusByteType bit masks (SWS_Dem_00928) */
#define DEM_UDS_STATUS_TF                   ((Dem_UdsStatusByteType)0x01U)
#define DEM_UDS_STATUS_TFTOC                ((Dem_UdsStatusByteType)0x02U)
#define DEM_UDS_STATUS_PDTC                 ((Dem_UdsStatusByteType)0x04U)
#define DEM_UDS_STATUS_CDTC                 ((Dem_UdsStatusByteType)0x08U)
#define DEM_UDS_STATUS_TNCSLC               ((Dem_UdsStatusByteType)0x10U)
#define DEM_UDS_STATUS_TFSLC                ((Dem_UdsStatusByteType)0x20U)
#define DEM_UDS_STATUS_TNCTOC               ((Dem_UdsStatusByteType)0x40U)
#define DEM_UDS_STATUS_WIR                  ((Dem_UdsStatusByteType)0x80U)

/* Dem_DTCFormatType values (SWS_Dem_00933) */
#define DEM_DTC_FORMAT_OBD                  ((Dem_DTCFormatType)0U)
#define DEM_DTC_FORMAT_UDS                  ((Dem_DTCFormatType)1U)
#define DEM_DTC_FORMAT_J1939                ((Dem_DTCFormatType)2U)
#define DEM_DTC_FORMAT_OBD_3BYTE            ((Dem_DTCFormatType)3U)

/* Dem_DTCOriginType values (SWS_Dem_00934) */
#define DEM_DTC_ORIGIN_PRIMARY_MEMORY       ((Dem_DTCOriginType)0x0001U)
#define DEM_DTC_ORIGIN_PERMANENT_MEMORY     ((Dem_DTCOriginType)0x0003U)
#define DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY  ((Dem_DTCOriginType)0x0004U)

/* Dem_DTCSeverityType bits (SWS_Dem_00937) */
#define DEM_SEVERITY_NO_SEVERITY            ((Dem_DTCSeverityType)0x00U)
#define DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS  ((Dem_DTCSeverityType)0x01U)
#define DEM_SEVERITY_WWHOBD_CLASS_A         ((Dem_DTCSeverityType)0x02U)
#define DEM_SEVERITY_WWHOBD_CLASS_B1        ((Dem_DTCSeverityType)0x04U)
#define DEM_SEVERITY_WWHOBD_CLASS_B2        ((Dem_DTCSeverityType)0x08U)
#define DEM_SEVERITY_WWHOBD_CLASS_C         ((Dem_DTCSeverityType)0x10U)
#define DEM_SEVERITY_MAINTENANCE_ONLY       ((Dem_DTCSeverityType)0x20U)
#define DEM_SEVERITY_CHECK_AT_NEXT_HALT     ((Dem_DTCSeverityType)0x40U)
#define DEM_SEVERITY_CHECK_IMMEDIATELY      ((Dem_DTCSeverityType)0x80U)

/* Dem_DTCTranslationFormatType values (SWS_Dem_00936) */
#define DEM_DTC_TRANSLATION_ISO15031_6          ((Dem_DTCTranslationFormatType)0x00U)
#define DEM_DTC_TRANSLATION_ISO14229_1          ((Dem_DTCTranslationFormatType)0x01U)
#define DEM_DTC_TRANSLATION_SAEJ1939_73         ((Dem_DTCTranslationFormatType)0x02U)
#define DEM_DTC_TRANSLATION_ISO11992_4          ((Dem_DTCTranslationFormatType)0x03U)
#define DEM_DTC_TRANSLATION_J2012DA_FORMAT_04   ((Dem_DTCTranslationFormatType)0x04U)

/* Group of all DTCs (SWS_Dem_01198) */
#define DEM_DTC_GROUP_ALL_DTCS              (0xFFFFFFUL)

/*==================================================================================================
*                                    STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief Identification of an event, 0 is not a valid value (SWS_Dem_00925). */
typedef uint16 Dem_EventIdType;

/** @brief Monitor test result (SWS_Dem_00926). */
typedef uint8 Dem_EventStatusType;

/** @brief UDS DTC status byte, ISO 14229-1 (SWS_Dem_00928). */
typedef uint8 Dem_UdsStatusByteType;

/** @brief Format of the DTC value (SWS_Dem_00933). */
typedef uint8 Dem_DTCFormatType;

/** @brief Event memory location (SWS_Dem_00934). */
typedef uint16 Dem_DTCOriginType;

/** @brief DTC severity bit field (SWS_Dem_00937). */
typedef uint8 Dem_DTCSeverityType;

/** @brief DTC translation format as defined in ISO 14229-1 (SWS_Dem_00936). */
typedef uint8 Dem_DTCTranslationFormatType;

/**
 * @brief    Post-build configuration of the Dem (SWS_Dem_00924).
 * @details  Implementation specific: events CAN bus-off (DTC 0xC07300) and
 *           dummy test event (DTC 0x9A0113), counter-based debounce,
 *           power operation cycle (docs/Mock.docx 1.5, M-02).
 */
typedef struct
{
    uint8 Dem_Dummy;    /* TODO(DEM_SRS_002/003): add event, DTC and debounce tables (M-02) */
} Dem_ConfigType;

#ifdef __cplusplus
}
#endif

#endif /* DEM_TYPES_H */
