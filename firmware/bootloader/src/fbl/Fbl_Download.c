/**
 * @file     Fbl_Download.c
 * @brief    FBL download callouts of the Dcm - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/bootloader (commit B-06).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Fbl_Download.h"
#include "Fbl_Flash.h"
#include "Dcm_Externals.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void Fbl_Download_Init(void)
{
    /* TODO(B-06): clear expected address / size / programmed byte counter */
}

Std_ReturnType Fbl_Download_GetProgrammedRange(uint32* AddressPtr, uint32* SizePtr)
{
    (void)AddressPtr;
    (void)SizePtr;
    /* TODO(B-06/B-07) */
    return E_NOT_OK;
}

Std_ReturnType Dcm_ProcessRequestDownload(Dcm_OpStatusType OpStatus, uint8 DataFormatIdentifier,
                                          uint8 MemoryIdentifier, uint32 MemoryAddress, uint32 MemorySize,
                                          uint32* BlockLength, Dcm_NegativeResponseCodeType* ErrorCode)
{
    (void)OpStatus;
    (void)DataFormatIdentifier;
    (void)MemoryIdentifier;
    (void)MemoryAddress;
    (void)MemorySize;
    (void)BlockLength;
    (void)ErrorCode;
    /* TODO(BL_SRS_006): SWS_Dcm_00754 - format 0x00, erased range inside the App area,
     *   *BlockLength = FBL_DOWNLOAD_MAX_BLOCK_LENGTH, else NRC 0x31 / 0x70 */
    return E_NOT_OK;
}

Dcm_ReturnWriteMemoryType Dcm_WriteMemory(Dcm_OpStatusType OpStatus, uint8 MemoryIdentifier,
                                          uint32 MemoryAddress, uint32 MemorySize, const uint8* MemoryData,
                                          Dcm_NegativeResponseCodeType* ErrorCode)
{
    (void)OpStatus;
    (void)MemoryIdentifier;
    (void)MemoryAddress;
    (void)MemorySize;
    (void)MemoryData;
    (void)ErrorCode;
    /* TODO(BL_SRS_007): SWS_Dcm_00540 - Fbl_Flash_Write at the next expected address,
     *   DCM_WRITE_PENDING while busy, NRC 0x72 on failure */
    return DCM_WRITE_FAILED;
}

Std_ReturnType Dcm_ProcessRequestTransferExit(Dcm_OpStatusType OpStatus,
                                              const uint8* transferRequestParameterRecord,
                                              uint32 transferRequestParameterRecordSize,
                                              uint8* transferResponseParameterRecord,
                                              uint32* transferResponseParameterRecordSize,
                                              Dcm_NegativeResponseCodeType* ErrorCode)
{
    (void)OpStatus;
    (void)transferRequestParameterRecord;
    (void)transferRequestParameterRecordSize;
    (void)transferResponseParameterRecord;
    (void)transferResponseParameterRecordSize;
    (void)ErrorCode;
    /* TODO(BL_SRS_008): SWS_Dcm_00755 - programmed bytes == size of RequestDownload, else NRC 0x24 */
    return E_NOT_OK;
}
