/**
 * @file     PduR.c
 * @brief    PDU Router (PduR) - core implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/tp-path (commits T-01, T-03, T-05) following the
 *           SWS IDs and SRS IDs referenced in PduR.h.
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "PduR.h"
#include "SchM_PduR.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void PduR_Init(const PduR_PBConfigType* ConfigPtr)
{
    (void)ConfigPtr;
    /* TODO(PDUR_SRS_001): SWS_PduR_00334, SWS_PduR_00325, SWS_PduR_00326 */
}

void PduR_GetVersionInfo(Std_VersionInfoType* versionInfo)
{
    (void)versionInfo;
    /* TODO: SWS_PduR_00338 */
}

PduR_PBConfigIdType PduR_GetConfigurationId(void)
{
    /* TODO: SWS_PduR_00341 */
    return (PduR_PBConfigIdType)0U;
}
