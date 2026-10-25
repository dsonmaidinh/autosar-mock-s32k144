/**
 * @file     Dcm_Externals.h
 * @brief    Diagnostic Communication Manager (Dcm) - callouts (configurable interfaces).
 * @details  Callouts per AUTOSAR CP R24-11 SWS DiagnosticCommunicationManager
 *           chapter 8.6 ("available via Dcm_Externals.h"). They are NOT
 *           implemented in firmware/common:
 *             - Application: Dcm_SetProgConditions / Dcm_GetProgConditions
 *               (application/src/app/Dcm_Callout_App.c, X-11)
 *             - Bootloader:  all callouts below (bootloader/src/fbl, B-04..B-06)
 *           Security seed/key and DID/RID callouts (Xxx_GetSeed, Xxx_ReadData,
 *           ...) are configuration specific and declared with the Dcm configuration.
 */

#ifndef DCM_EXTERNALS_H
#define DCM_EXTERNALS_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Dcm_Types.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Stores the programming conditions before a jump to the bootloader / ECU reset.
 * @details    SWS: SWS_Dcm_00543 | Service ID: 0x61
 *             classic-platform: added OpStatus, ProgConditions made const (R24-11).
 *             Behaviour: SWS_Dcm_00532, SWS_Dcm_00535, SWS_Dcm_00715.
 *             Project: DCM_SRS_014, BL_SRS_004 (App writes boot request record at 0x2000_6FF0)
 * @param[in]  OpStatus        DCM_INITIAL, DCM_PENDING or DCM_CANCEL.
 * @param[in]  ProgConditions  Conditions on which the jump to bootloader has been requested.
 * @return     E_OK, E_NOT_OK, DCM_E_PENDING.
 */
Std_ReturnType Dcm_SetProgConditions(Dcm_OpStatusType OpStatus, const Dcm_ProgConditionsType* ProgConditions);

/**
 * @brief      Gets the programming conditions at Dcm initialization.
 * @details    SWS: SWS_Dcm_00544 | Service ID: 0x62 | classic-platform: kept
 *             Behaviour: SWS_Dcm_00536 (BL answers 0x50 02 after jump).
 * @param[out] ProgConditions  Conditions on which the jump from the application has been requested.
 * @return     DCM_COLD_START or DCM_WARM_START.
 */
Dcm_EcuStartModeType Dcm_GetProgConditions(Dcm_ProgConditionsType* ProgConditions);

/**
 * @brief      Callout for UDS 0x34 RequestDownload.
 * @details    SWS: SWS_Dcm_00754 | Service ID: 0x30
 *             classic-platform: added MemoryIdentifier (R24-11).
 *             Behaviour: SWS_Dcm_00496, SWS_Dcm_01591, SWS_Dcm_01417, SWS_Dcm_01419.
 *             Project: BL_SRS_006 (dataFormat 0x00, range check, BlockLength 0x0402)
 * @param[in]  OpStatus              DCM_INITIAL, DCM_PENDING or DCM_CANCEL.
 * @param[in]  DataFormatIdentifier  Compression and encryption method.
 * @param[in]  MemoryIdentifier      Memory identifier.
 * @param[in]  MemoryAddress         Start address of the download.
 * @param[in]  MemorySize            Size of the download.
 * @param[inout] BlockLength         Max. number of bytes of one TransferData request.
 * @param[out] ErrorCode             NRC if E_NOT_OK is returned.
 * @return     E_OK, E_NOT_OK, DCM_E_PENDING, DCM_E_FORCE_RCRRP.
 */
Std_ReturnType Dcm_ProcessRequestDownload(Dcm_OpStatusType OpStatus, uint8 DataFormatIdentifier,
                                          uint8 MemoryIdentifier, uint32 MemoryAddress, uint32 MemorySize,
                                          uint32* BlockLength, Dcm_NegativeResponseCodeType* ErrorCode);

/**
 * @brief      Callout for UDS 0x36 TransferData (write the received block into memory).
 * @details    SWS: SWS_Dcm_00540 | Service ID: 0x27
 *             classic-platform: MemoryData made const, added ErrorCode (R24-11).
 *             Behaviour: SWS_Dcm_00502, SWS_Dcm_00503. Project: BL_SRS_007
 * @param[in]  OpStatus          DCM_INITIAL, DCM_PENDING, DCM_CANCEL or DCM_FORCE_RCRRP_OK.
 * @param[in]  MemoryIdentifier  Memory identifier.
 * @param[in]  MemoryAddress     Start address of the block.
 * @param[in]  MemorySize        Number of bytes in MemoryData.
 * @param[in]  MemoryData        Data to be written.
 * @param[out] ErrorCode         NRC if DCM_WRITE_FAILED is returned.
 * @return     DCM_WRITE_OK, DCM_WRITE_PENDING, DCM_WRITE_FAILED, DCM_WRITE_FORCE_RCRRP.
 */
Dcm_ReturnWriteMemoryType Dcm_WriteMemory(Dcm_OpStatusType OpStatus, uint8 MemoryIdentifier,
                                          uint32 MemoryAddress, uint32 MemorySize, const uint8* MemoryData,
                                          Dcm_NegativeResponseCodeType* ErrorCode);

/**
 * @brief      Callout for UDS 0x37 RequestTransferExit.
 * @details    SWS: SWS_Dcm_00755 | Service ID: 0x32
 *             classic-platform: request/response parameter records split (R24-11).
 *             Behaviour: SWS_Dcm_00505, SWS_Dcm_01593. Project: BL_SRS_008
 * @param[in]  OpStatus                             DCM_INITIAL, DCM_PENDING or DCM_CANCEL.
 * @param[in]  transferRequestParameterRecord       Request parameter record.
 * @param[in]  transferRequestParameterRecordSize   Length of the request parameter record.
 * @param[out] transferResponseParameterRecord      Response parameter record.
 * @param[inout] transferResponseParameterRecordSize In: max. size, out: used size.
 * @param[out] ErrorCode                            NRC if E_NOT_OK is returned.
 * @return     E_OK, E_NOT_OK, DCM_E_PENDING, DCM_E_FORCE_RCRRP.
 */
Std_ReturnType Dcm_ProcessRequestTransferExit(Dcm_OpStatusType OpStatus,
                                              const uint8* transferRequestParameterRecord,
                                              uint32 transferRequestParameterRecordSize,
                                              uint8* transferResponseParameterRecord,
                                              uint32* transferResponseParameterRecordSize,
                                              Dcm_NegativeResponseCodeType* ErrorCode);

#ifdef __cplusplus
}
#endif

#endif /* DCM_EXTERNALS_H */
