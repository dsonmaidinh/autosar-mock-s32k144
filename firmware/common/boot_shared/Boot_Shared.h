/**
 * @file     Boot_Shared.h
 * @brief    Definitions shared by the Bootloader and the Application image.
 * @details  Project module, no AUTOSAR SWS (ISO 14229-1 programming sequence).
 *           Memory map: docs/Mock.docx 1.10, boot flow: 1.11.
 *           Values marked [P] are proposals to be confirmed on target (Sprint S5).
 *           Users:
 *             - Application: Dcm_SetProgConditions writes the boot request (BL_SRS_004)
 *             - Bootloader:  BM_CheckBootRequest / BM_IsAppValid / BM_JumpToApp
 *                            (BL_SRS_001..003), FBL metadata commit (BL_SRS_010)
 */

#ifndef BOOT_SHARED_H
#define BOOT_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                    MEMORY MAP (docs/Mock.docx 1.10)
==================================================================================================*/
/* P-Flash, sector size 4 KB [V RM] */
#define BOOT_FLASH_SECTOR_SIZE              (0x00001000UL)
#define BOOT_FLASH_PHRASE_SIZE              (8UL)           /**< FTFC program phrase [V RM] */

/* Bootloader area, never erased or programmed by the FBL (BL_SRS_012) */
#define BOOT_BL_START_ADDR                  (0x00000000UL)
#define BOOT_BL_END_ADDR                    (0x0001FFFFUL)
#define BOOT_FLASH_CONFIG_START_ADDR        (0x00000400UL)  /**< Flash Configuration Field */
#define BOOT_FLASH_CONFIG_END_ADDR          (0x0000040FUL)

/* Application area (BL_SRS_003, BL_SRS_005, BL_SRS_006) */
#define BOOT_APP_VECTOR_ADDR                (0x00020000UL)  /**< App vector table, VTOR value */
#define BOOT_APP_CODE_START_ADDR            (0x00020400UL)
#define BOOT_APP_END_ADDR                   (0x0007EFFFUL)
#define BOOT_APP_ERASE_START_ADDR           (0x00020000UL)  /**< Erasable range for RID 0xFF00 */
#define BOOT_APP_ERASE_END_ADDR             (0x0007FFFFUL)  /**< includes the metadata sector */

/* Application metadata, one sector (BL_SRS_002, BL_SRS_010) */
#define BOOT_METADATA_ADDR                  (0x0007F000UL)
#define BOOT_METADATA_SIZE                  BOOT_FLASH_SECTOR_SIZE

/* SRAM range used for the initial MSP check (BL_SRS_003) */
#define BOOT_SRAM_START_ADDR                (0x1FFF8000UL)
#define BOOT_SRAM_END_ADDR                  (0x20007000UL)  /**< exclusive */

/*==================================================================================================
*                              BOOT REQUEST RECORD (BL_SRS_001, BL_SRS_004)
==================================================================================================*/
#define BOOT_REQUEST_ADDR                   (0x20006FF0UL)  /**< .boot_noinit, 16 bytes [P] */
#define BOOT_REQUEST_SIZE                   (16UL)
#define BOOT_REQUEST_MAGIC                  (0x424F4F54UL)  /**< "BOOT" [P] */
#define BOOT_REQUEST_MAGIC_INV              (~BOOT_REQUEST_MAGIC)

/* Reason of the boot request [P] */
#define BOOT_REQUEST_REASON_NONE            (0x00U)
#define BOOT_REQUEST_REASON_PROGRAMMING     (0x01U)         /**< UDS 0x10 02 received by App */

/** @brief Placement of the boot request record in the no-init RAM area (linker P-07). */
#define BOOT_SHARED_NOINIT                  __attribute__((section(".boot_noinit")))

/**
 * @brief    Boot request record at BOOT_REQUEST_ADDR (16 bytes, survives SW reset).
 * @details  Valid when Magic == BOOT_REQUEST_MAGIC and MagicInv == ~Magic (BL_SRS_001).
 */
typedef struct
{
    uint32 Magic;           /**< BOOT_REQUEST_MAGIC */
    uint32 MagicInv;        /**< bitwise inverse of Magic */
    uint8  Reason;          /**< BOOT_REQUEST_REASON_* */
    uint8  SubFncId;        /**< sub-function of the request (Dcm_ProgConditionsType.SubFncId) */
    uint16 TesterAddress;   /**< Dcm_ProgConditionsType.TesterAddress */
    uint32 Reserved;        /**< pad to 16 bytes */
} Boot_RequestType;

/*==================================================================================================
*                              APPLICATION METADATA (BL_SRS_002, BL_SRS_010)
==================================================================================================*/
#define BOOT_METADATA_MAGIC                 (0x4D455441UL)  /**< "META" [P] */
#define BOOT_METADATA_VALID                 (0xA5A5A5A5UL)  /**< set by RID 0xFF01 only [P] */
#define BOOT_METADATA_INVALID               (0xFFFFFFFFUL)  /**< erased flash */

#define BOOT_FINGERPRINT_SIZE               (9U)            /**< DID 0xF15A: YYMMDD (3) + tester (6) [P] */

/* CRC-32 over the application (BL_SRS_002, BL_SRS_009) [P] */
#define BOOT_CRC32_POLY_REFLECTED           (0xEDB88320UL)
#define BOOT_CRC32_INIT                     (0xFFFFFFFFUL)
#define BOOT_CRC32_XOROUT                   (0xFFFFFFFFUL)

/**
 * @brief    Application metadata record at BOOT_METADATA_ADDR [P].
 * @details  Size is a multiple of BOOT_FLASH_PHRASE_SIZE (40 bytes) so it can be
 *           programmed phrase by phrase. The BL jumps to the App only when
 *           Magic and ValidFlag are set and Crc32 matches (BL_SRS_002).
 */
typedef struct
{
    uint32 Magic;                               /**< BOOT_METADATA_MAGIC */
    uint32 ValidFlag;                           /**< BOOT_METADATA_VALID / _INVALID */
    uint32 AppStartAddr;                        /**< BOOT_APP_VECTOR_ADDR */
    uint32 AppSize;                             /**< bytes covered by Crc32 */
    uint32 Crc32;                               /**< CRC-32 (0xEDB88320) over the App */
    uint32 AppVersion;                          /**< application SW version */
    uint8  Fingerprint[BOOT_FINGERPRINT_SIZE];  /**< DID 0xF15A */
    uint8  Reserved[7];                         /**< pad to a multiple of 8 bytes */
} Boot_MetadataType;

/*==================================================================================================
*                                    COMPILE TIME CHECKS
==================================================================================================*/
typedef char Boot_RequestSizeCheck[(sizeof(Boot_RequestType) == BOOT_REQUEST_SIZE) ? 1 : -1];
typedef char Boot_MetadataSizeCheck[((sizeof(Boot_MetadataType) % BOOT_FLASH_PHRASE_SIZE) == 0U) ? 1 : -1];

#ifdef __cplusplus
}
#endif

#endif /* BOOT_SHARED_H */
