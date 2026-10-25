/**
 * @file     CDD_CanTest_Cfg.h
 * @brief    CDD_CanTest configuration (docs/Mock.docx 1.6).
 */

#ifndef CDD_CANTEST_CFG_H
#define CDD_CANTEST_CFG_H

#define CDD_CANTEST_TX_PERIOD_MS            (100U)      /**< 0x3A0 period */
#define CDD_CANTEST_MAIN_FUNCTION_PERIOD_MS (10U)       /**< called from Os_Task_10ms */
#define CDD_CANTEST_TX_DLC                  (8U)
#define CDD_CANTEST_TX_CANID                (0x3A0U)    /**< informative, mapped in CanIf config */
#define CDD_CANTEST_RX_CANID                (0x2B0U)    /**< informative, mapped in CanIf config */

#endif /* CDD_CANTEST_CFG_H */
