/**
 * @file     Fbl_Flash.h
 * @brief    FBL flash access - wrapper of Mem_43_INFLS with protected range check.
 * @details  Project module (docs/Mock.docx 3.12). All FTFC commands run from RAM
 *           through the Mem_43_INFLS access code (.acfls_code_ram, BL_SRS_011).
 *           Any request overlapping the bootloader area 0x0000_0000-0x0001_FFFF,
 *           including the Flash Configuration Field, is rejected (BL_SRS_012).
 */

#ifndef FBL_FLASH_H
#define FBL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                    STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief Result of the last flash job (mapped from Mem_43_INFLS_GetJobResult). */
typedef enum
{
    FBL_FLASH_IDLE = 0U,    /**< no job started */
    FBL_FLASH_PENDING,      /**< job in progress, call Fbl_Flash_MainFunction */
    FBL_FLASH_OK,           /**< last job finished successfully */
    FBL_FLASH_FAILED        /**< last job failed */
} Fbl_Flash_StatusType;

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief      Initializes the flash wrapper (Mem_43_INFLS_Init).
 * @details    Called by EcuM_AL_DriverInitOne in the bootloader image.
 */
void Fbl_Flash_Init(void);

/**
 * @brief      Checks that a range is inside the erasable/programmable application area.
 * @details    Allowed: [BOOT_APP_ERASE_START_ADDR, BOOT_APP_ERASE_END_ADDR]. Project: BL_SRS_012
 * @param[in]  Address  Start address.
 * @param[in]  Length   Length in bytes.
 * @return     TRUE allowed, FALSE rejected.
 */
boolean Fbl_Flash_IsRangeAllowed(uint32 Address, uint32 Length);

/**
 * @brief      Starts erasing whole 4 KB sectors.
 * @details    Asynchronous (Mem_43_INFLS_Erase). Project: BL_SRS_005, BL_SRS_011, BL_SRS_012
 * @param[in]  Address  Sector aligned start address.
 * @param[in]  Length   Multiple of BOOT_FLASH_SECTOR_SIZE.
 * @return     E_OK job accepted, E_NOT_OK range rejected or driver busy.
 */
Std_ReturnType Fbl_Flash_Erase(uint32 Address, uint32 Length);

/**
 * @brief      Starts programming data in 8-byte phrases.
 * @details    Asynchronous (Mem_43_INFLS_Write). Project: BL_SRS_007, BL_SRS_011, BL_SRS_012
 * @param[in]  Address  Phrase aligned start address.
 * @param[in]  DataPtr  Data to be programmed.
 * @param[in]  Length   Multiple of BOOT_FLASH_PHRASE_SIZE.
 * @return     E_OK job accepted, E_NOT_OK range rejected or driver busy.
 */
Std_ReturnType Fbl_Flash_Write(uint32 Address, const uint8* DataPtr, uint32 Length);

/**
 * @brief      Returns the status of the last job.
 * @return     Fbl_Flash_StatusType.
 */
Fbl_Flash_StatusType Fbl_Flash_GetStatus(void);

/**
 * @brief      Processes the pending flash job (Mem_43_INFLS_MainFunction).
 * @details    Called from Os_Task_1ms in the bootloader image.
 */
void Fbl_Flash_MainFunction(void);

#ifdef __cplusplus
}
#endif

#endif /* FBL_FLASH_H */
