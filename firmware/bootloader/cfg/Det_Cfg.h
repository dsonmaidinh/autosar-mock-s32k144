/**
 * @file     Det_Cfg.h
 * @brief    Det pre-compile configuration - BOOTLOADER image.
 * @details  Configuration skeleton: switches and symbolic names only. The
 *           configuration content is completed on the feature branch (D-01/D-02).
 */

#ifndef DET_CFG_H
#define DET_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                                    CONFIGURATION PARAMETERS
==================================================================================================*/
/* No pre-compile parameter of the Det is used in v1.0 (error hooks are added with D-02). */

/** Configuration set passed to Det_Init (defined in Det_Cfg.c) */
extern const Det_ConfigType Det_Config;

#ifdef __cplusplus
}
#endif

#endif /* DET_CFG_H */
