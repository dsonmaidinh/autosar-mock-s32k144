/**
 * @file     Fbl_Metadata.h
 * @brief    FBL application metadata record at 0x0007_F000.
 * @details  Project module (docs/Mock.docx 1.10, BL_SRS_002, BL_SRS_010).
 *           Record layout: Boot_MetadataType (Boot_Shared.h).
 */

#ifndef FBL_METADATA_H
#define FBL_METADATA_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
#include "Boot_Shared.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Reads the metadata record from flash.
 * @param[out] MetadataPtr  Destination of the record.
 * @return     E_OK read, E_NOT_OK NULL pointer.
 */
Std_ReturnType Fbl_Metadata_Read(Boot_MetadataType* MetadataPtr);

/**
 * @brief      Checks Magic and ValidFlag of a record (CRC is checked by the caller).
 * @details    Project: BL_SRS_002
 * @param[in]  MetadataPtr  Record to be checked.
 * @return     TRUE record marked valid, FALSE otherwise.
 */
boolean Fbl_Metadata_IsValid(const Boot_MetadataType* MetadataPtr);

/**
 * @brief      Invalidates the application by erasing the metadata sector.
 * @details    Done before the application area is erased (commit B-05).
 * @return     E_OK job accepted, E_NOT_OK otherwise.
 */
Std_ReturnType Fbl_Metadata_Invalidate(void);

/**
 * @brief      Programs a new metadata record with ValidFlag = BOOT_METADATA_VALID.
 * @details    Only after CheckMemory passed in the same programming session. Project: BL_SRS_010
 * @param[in]  MetadataPtr  Record to be programmed.
 * @return     E_OK job accepted, E_NOT_OK otherwise.
 */
Std_ReturnType Fbl_Metadata_Commit(const Boot_MetadataType* MetadataPtr);

#ifdef __cplusplus
}
#endif

#endif /* FBL_METADATA_H */
