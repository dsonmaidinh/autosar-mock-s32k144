/**
 * @file     Det.c
 * @brief    Default Error Tracer (Det) - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/det-ecum (commits D-01, D-02) following the SWS
 *           IDs and SRS IDs referenced in Det.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Det.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void Det_Init(const Det_ConfigType* ConfigPtr)
{
    (void)ConfigPtr;
    /* TODO(DET_SRS_002): SWS_Det_00008 - store config, clear error log, set init flag */
}

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    (void)ModuleId;
    (void)InstanceId;
    (void)ApiId;
    (void)ErrorId;
    /* TODO(DET_SRS_001/002): SWS_Det_00009, SWS_Det_00026, SWS_Det_00035, SWS_Det_00208 */
    return E_OK;
}

void Det_Start(void)
{
    /* TODO: SWS_Det_00010 */
}

void Det_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    (void)versioninfo;
    /* TODO: SWS_Det_00011, SWS_Det_00052 - DET_E_PARAM_POINTER on NULL */
}

Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    (void)ModuleId;
    (void)InstanceId;
    (void)ApiId;
    (void)ErrorId;
    /* TODO(DET_SRS_003/004): SWS_Det_01001, SWS_Det_00024 */
    return E_OK;
}

Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId)
{
    (void)ModuleId;
    (void)InstanceId;
    (void)ApiId;
    (void)FaultId;
    /* TODO: SWS_Det_01003 */
    return E_OK;
}
