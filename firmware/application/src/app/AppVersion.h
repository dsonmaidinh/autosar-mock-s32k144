/**
 * @file     AppVersion.h
 * @brief    Application software version.
 * @details  Stored in the metadata record by the FBL (Boot_MetadataType.AppVersion)
 *           and set to 1.0.0 by commit R-04 (docs/Mock.docx 5.4).
 */

#ifndef APPVERSION_H
#define APPVERSION_H

#include "Std_Types.h"

#define APP_SW_MAJOR_VERSION                (0U)
#define APP_SW_MINOR_VERSION                (1U)
#define APP_SW_PATCH_VERSION                (0U)

/** Packed version 0x00MMmmpp */
#define APP_SW_VERSION                      (((uint32)APP_SW_MAJOR_VERSION << 16U) | \
                                             ((uint32)APP_SW_MINOR_VERSION << 8U)  | \
                                             (uint32)APP_SW_PATCH_VERSION)

#endif /* APPVERSION_H */
