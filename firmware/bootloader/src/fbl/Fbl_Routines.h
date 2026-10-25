/**
 * @file     Fbl_Routines.h
 * @brief    FBL RoutineControl (UDS 0x31) start callouts of the bootloader.
 * @details  Dcm routine callouts Xxx_Start (SWS_Dcm_01203, Service ID 0x5b) for the
 *           RIDs of docs/Mock.docx 1.5. Signal layout configured in Dcm_LCfg.c (B-04):
 *             - 0xFF00 EraseMemory:               in 0x44 + address(4) + size(4) (dataInVar)
 *             - 0x0202 CheckMemory:               in CRC32 (uint32), out result (uint8)
 *             - 0xFF01 CheckProgrammingDependencies: out result (uint8)
 *           Unsupported RIDs are rejected by the Dcm with NRC 0x31 (fix of SummerFalls).
 */

#ifndef FBL_ROUTINES_H
#define FBL_ROUTINES_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "Dcm_Types.h"

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define FBL_RID_ERASE_MEMORY                (0xFF00U)
#define FBL_RID_CHECK_MEMORY                (0x0202U)
#define FBL_RID_CHECK_DEPENDENCIES          (0xFF01U)

#define FBL_ROUTINE_RESULT_OK               (0x00U)
#define FBL_ROUTINE_RESULT_NOT_OK           (0x01U)

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      RID 0xFF00 EraseMemory start.
 * @details    SWS_Dcm_01203 (Xxx_Start, variable length input). Invalidates the metadata,
 *             then erases whole 4 KB sectors; returns DCM_E_PENDING while erasing (NRC 0x78).
 *             Project: BL_SRS_005
 * @param[in]  dataInVar          addressAndLengthFormatIdentifier (0x44), address, size.
 * @param[in]  OpStatus           DCM_INITIAL, DCM_PENDING or DCM_CANCEL.
 * @param[inout] currentDataLength In: request length, out: response length (0).
 * @param[out] ErrorCode          NRC 0x31 for a range outside the application area.
 * @return     E_OK, E_NOT_OK, DCM_E_PENDING, DCM_E_FORCE_RCRRP.
 */
Std_ReturnType Fbl_Routine_EraseMemory_Start(const uint8* dataInVar, Dcm_OpStatusType OpStatus,
                                             uint16* currentDataLength, Dcm_NegativeResponseCodeType* ErrorCode);

/**
 * @brief      RID 0x0202 CheckMemory start.
 * @details    SWS_Dcm_01203. CRC-32 over the downloaded range compared to the tester value.
 *             Project: BL_SRS_009
 * @param[in]  dataIn_Crc32   CRC-32 supplied by the tester.
 * @param[in]  OpStatus       DCM_INITIAL, DCM_PENDING or DCM_CANCEL.
 * @param[out] dataOut_Result FBL_ROUTINE_RESULT_OK / _NOT_OK.
 * @param[out] ErrorCode      NRC 0x24 when no download has been completed.
 * @return     E_OK, E_NOT_OK, DCM_E_PENDING.
 */
Std_ReturnType Fbl_Routine_CheckMemory_Start(uint32 dataIn_Crc32, Dcm_OpStatusType OpStatus,
                                             uint8* dataOut_Result, Dcm_NegativeResponseCodeType* ErrorCode);

/**
 * @brief      RID 0xFF01 CheckProgrammingDependencies start.
 * @details    SWS_Dcm_01203. Commits the metadata record (VALID) when CheckMemory passed.
 *             Project: BL_SRS_010
 * @param[in]  OpStatus       DCM_INITIAL, DCM_PENDING or DCM_CANCEL.
 * @param[out] dataOut_Result FBL_ROUTINE_RESULT_OK -> application marked valid.
 * @param[out] ErrorCode      NRC 0x24 when CheckMemory has not passed.
 * @return     E_OK, E_NOT_OK, DCM_E_PENDING.
 */
Std_ReturnType Fbl_Routine_CheckDependencies_Start(Dcm_OpStatusType OpStatus, uint8* dataOut_Result,
                                                   Dcm_NegativeResponseCodeType* ErrorCode);

#ifdef __cplusplus
}
#endif

#endif /* FBL_ROUTINES_H */
