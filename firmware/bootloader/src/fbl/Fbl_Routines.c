/**
 * @file     Fbl_Routines.c
 * @brief    FBL RoutineControl callouts - implementation skeleton.
 * @details  Function bodies are intentionally empty. Implement them on
 *           branch feature/bootloader (commits B-05, B-07).
 */

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Fbl_Routines.h"
#include "Fbl_Flash.h"
#include "Fbl_Crc32.h"
#include "Fbl_Metadata.h"
#include "Fbl_Download.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
Std_ReturnType Fbl_Routine_EraseMemory_Start(const uint8* dataInVar, Dcm_OpStatusType OpStatus,
                                             uint16* currentDataLength, Dcm_NegativeResponseCodeType* ErrorCode)
{
    (void)dataInVar;
    (void)OpStatus;
    (void)currentDataLength;
    (void)ErrorCode;
    /* TODO(BL_SRS_005): Fbl_Metadata_Invalidate + Fbl_Flash_Erase, DCM_E_PENDING until done */
    return E_NOT_OK;
}

Std_ReturnType Fbl_Routine_CheckMemory_Start(uint32 dataIn_Crc32, Dcm_OpStatusType OpStatus,
                                             uint8* dataOut_Result, Dcm_NegativeResponseCodeType* ErrorCode)
{
    (void)dataIn_Crc32;
    (void)OpStatus;
    (void)dataOut_Result;
    (void)ErrorCode;
    /* TODO(BL_SRS_009): Fbl_Download_GetProgrammedRange + Fbl_Crc32_Calculate */
    return E_NOT_OK;
}

Std_ReturnType Fbl_Routine_CheckDependencies_Start(Dcm_OpStatusType OpStatus, uint8* dataOut_Result,
                                                   Dcm_NegativeResponseCodeType* ErrorCode)
{
    (void)OpStatus;
    (void)dataOut_Result;
    (void)ErrorCode;
    /* TODO(BL_SRS_010): Fbl_Metadata_Commit after CheckMemory passed */
    return E_NOT_OK;
}
