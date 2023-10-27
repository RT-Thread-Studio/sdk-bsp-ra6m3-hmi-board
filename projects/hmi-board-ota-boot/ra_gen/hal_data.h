/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_flash_hp.h"
#include "r_flash_api.h"
#include "r_icu.h"
#include "r_external_irq_api.h"
#include "r_sci_uart.h"
            #include "r_uart_api.h"
FSP_HEADER
/* Flash on Flash HP Instance */
extern const flash_instance_t g_flash;

/** Access the Flash HP instance using these structures when calling API functions directly (::p_api is not used). */
extern flash_hp_instance_ctrl_t g_flash_ctrl;
extern const flash_cfg_t g_flash_cfg;

#ifndef NULL
void NULL(flash_callback_args_t * p_args);
#endif
/** External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq9;

/** Access the ICU instance using these structures when calling API functions directly (::p_api is not used). */
extern icu_instance_ctrl_t g_external_irq9_ctrl;
extern const external_irq_cfg_t g_external_irq9_cfg;

#ifndef irq_callback
void irq_callback(external_irq_callback_args_t * p_args);
#endif
/** External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq13;

/** Access the ICU instance using these structures when calling API functions directly (::p_api is not used). */
extern icu_instance_ctrl_t g_external_irq13_ctrl;
extern const external_irq_cfg_t g_external_irq13_cfg;

#ifndef irq_callback
void irq_callback(external_irq_callback_args_t * p_args);
#endif
/** External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq11;

/** Access the ICU instance using these structures when calling API functions directly (::p_api is not used). */
extern icu_instance_ctrl_t g_external_irq11_ctrl;
extern const external_irq_cfg_t g_external_irq11_cfg;

#ifndef irq_callback
void irq_callback(external_irq_callback_args_t * p_args);
#endif
/** External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq10;

/** Access the ICU instance using these structures when calling API functions directly (::p_api is not used). */
extern icu_instance_ctrl_t g_external_irq10_ctrl;
extern const external_irq_cfg_t g_external_irq10_cfg;

#ifndef irq_callback
void irq_callback(external_irq_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart9;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     g_uart9_ctrl;
            extern const uart_cfg_t g_uart9_cfg;
            extern const sci_uart_extended_cfg_t g_uart9_cfg_extend;

            #ifndef user_uart9_callback
            void user_uart9_callback(uart_callback_args_t * p_args);
            #endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
