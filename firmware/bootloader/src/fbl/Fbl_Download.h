/**
 * @file     Fbl_Download.h
 * @brief    FBL download state (UDS 0x34 / 0x36 / 0x37).
 * @details  Fbl_Download.c implements the Dcm callouts of Dcm_Externals.h:
 *           Dcm_ProcessRequestDownload (SWS_Dcm_00754), Dcm_WriteMemory
 *           (SWS_Dcm_00540) and Dcm_ProcessRequestTransferExit (SWS_Dcm_00755).
 *           This header exposes the download state to the routines (CheckMemory).
 *           Project: BL_SRS_006, BL_SRS_007, BL_SRS_008
 */

#ifndef FBL_DOWNLOAD_H
#define FBL_DOWNLOAD_H

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
#define FBL_DOWNLOAD_DATA_FORMAT_ID         (0x00U)     /**< no compression / encryption */
#define FBL_DOWNLOAD_MAX_BLOCK_LENGTH       (0x0402UL)  /**< maxNumberOfBlockLength [P] */

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Resets the download state machine (session change, init).
 */
void Fbl_Download_Init(void);

/**
 * @brief      Returns the range programmed by the last completed download.
 * @param[out] AddressPtr  Start address of the download.
 * @param[out] SizePtr     Size given in RequestDownload.
 * @return     E_OK a download was completed (0x37 accepted), E_NOT_OK otherwise.
 */
Std_ReturnType Fbl_Download_GetProgrammedRange(uint32* AddressPtr, uint32* SizePtr);

#ifdef __cplusplus
}
#endif

#endif /* FBL_DOWNLOAD_H */
