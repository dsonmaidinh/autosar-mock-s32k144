/**
 * @file     Det.h
 * @brief    Default Error Tracer (Det) - public interface.
 * @details  API skeleton per AUTOSAR CP R24-11 SWS DefaultErrorTracer.
 *           AR release macros are kept at 4.7.0 to pass the inter-module
 *           version checks of NXP RTD 2.0.0; API signatures follow R24-11.
 *           Project requirements: DET_SRS_001..DET_SRS_004 (docs/Mock.docx 3.10).
 */

#ifndef DET_H
#define DET_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define DET_VENDOR_ID                       (0xFFFFU)   /* project-local, not a registered vendor */
#define DET_MODULE_ID                       (15U)
#define DET_INSTANCE_ID                     (0U)
#define DET_AR_RELEASE_MAJOR_VERSION        (4U)
#define DET_AR_RELEASE_MINOR_VERSION        (7U)
#define DET_AR_RELEASE_REVISION_VERSION     (0U)
#define DET_SW_MAJOR_VERSION                (0U)
#define DET_SW_MINOR_VERSION                (1U)
#define DET_SW_PATCH_VERSION                (0U)

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Service IDs (SWS chapter 8.3) */
#define DET_SID_INIT                        (0x00U)
#define DET_SID_REPORT_ERROR                (0x01U)
#define DET_SID_START                       (0x02U)
#define DET_SID_GET_VERSION_INFO            (0x03U)
#define DET_SID_REPORT_RUNTIME_ERROR        (0x04U)
#define DET_SID_REPORT_TRANSIENT_FAULT      (0x05U)

/* Development errors (SWS_Det_00301) */
#define DET_E_PARAM_POINTER                 (0x01U)

/*==================================================================================================
*                                    STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
 * @brief    Configuration data structure of the Det module (SWS_Det_00210).
 * @details  Implementation specific. Holds e.g. the configured error hooks.
 */
typedef struct
{
    uint8 Det_Dummy;    /* TODO: replace by project configuration (error hooks, log size) */
} Det_ConfigType;

/* Included after Det_ConfigType so that Det_Cfg.h can declare the configuration set. */
#include "Det_Cfg.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Initializes the Default Error Tracer.
 * @details    SWS: SWS_Det_00008 | Service ID: 0x00
 *             Project: DET_SRS_002, DET_SRS_004 (init flag)
 * @param[in]  ConfigPtr  Pointer to the selected configuration set.
 */
void Det_Init(const Det_ConfigType* ConfigPtr);

/**
 * @brief      Service to report development errors.
 * @details    SWS: SWS_Det_00009 | Service ID: 0x01
 *             Project: DET_SRS_001, DET_SRS_002
 * @param[in]  ModuleId    Module ID of calling module.
 * @param[in]  InstanceId  Identifier of the index based instance of a module.
 * @param[in]  ApiId       ID of API service in which error is detected.
 * @param[in]  ErrorId     ID of detected development error.
 * @return     Always E_OK (only for compatibility with RTE).
 */
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

/**
 * @brief      Service to start the Default Error Tracer.
 * @details    SWS: SWS_Det_00010 | Service ID: 0x02
 */
void Det_Start(void);

/**
 * @brief      Returns the version information of this module.
 * @details    SWS: SWS_Det_00011 | Service ID: 0x03
 * @param[out] versioninfo  Pointer to where to store the version information.
 */
void Det_GetVersionInfo(Std_VersionInfoType* versioninfo);

/**
 * @brief      Service to report runtime errors.
 * @details    SWS: SWS_Det_01001 | Service ID: 0x04
 *             Project: DET_SRS_003, DET_SRS_004
 * @param[in]  ModuleId    Module ID of calling module.
 * @param[in]  InstanceId  Identifier of the index based instance of a module.
 * @param[in]  ApiId       ID of API service in which error is detected.
 * @param[in]  ErrorId     ID of detected runtime error.
 * @return     Always E_OK.
 */
Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

/**
 * @brief      Service to report transient faults.
 * @details    SWS: SWS_Det_01003 | Service ID: 0x05
 * @param[in]  ModuleId    Module ID of calling module.
 * @param[in]  InstanceId  Identifier of the index based instance of a module.
 * @param[in]  ApiId       ID of API service in which transient fault is detected.
 * @param[in]  FaultId     ID of detected transient fault.
 * @return     Return value of the configured callout, E_OK if none is configured.
 */
Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId);

#ifdef __cplusplus
}
#endif

#endif /* DET_H */
