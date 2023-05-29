/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_dtc.h"
#include "r_transfer_api.h"
#include "r_i2s_api.h"
            #include "r_ssi.h"
#include "r_ether_phy.h"
#include "r_ether_phy_api.h"
#include "r_ether.h"
#include "r_ether_api.h"
#include "r_sci_spi.h"
#include "r_spi_api.h"
#include "r_icu.h"
#include "r_external_irq_api.h"
#include "r_can.h"
#include "r_can_api.h"
#include "r_jpeg.h"
#include "r_glcdc.h"
            #include "r_display_api.h"
#include "r_dmac.h"
#include "r_transfer_api.h"
#include "r_sdhi.h"
#include "r_sdmmc_api.h"
#include "r_sci_uart.h"
            #include "r_uart_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer5;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer5_ctrl;
extern const timer_cfg_t g_timer5_cfg;

#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer_ctrl;
extern const timer_cfg_t g_timer_cfg;

#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer10;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer10_ctrl;
extern const transfer_cfg_t g_transfer10_cfg;
/** SSI Instance. */
            extern const i2s_instance_t      g_i2s0;

            /** Access the SSI instance using these structures when calling API functions directly (::p_api is not used). */
            extern ssi_instance_ctrl_t g_i2s0_ctrl;
            extern const i2s_cfg_t g_i2s0_cfg;

            #ifndef i2s_callback
            void i2s_callback(i2s_callback_args_t * p_args);
            #endif
/** ether_phy on ether_phy Instance. */
extern const ether_phy_instance_t g_ether_phy0;

/** Access the Ethernet PHY instance using these structures when calling API functions directly (::p_api is not used). */
extern ether_phy_instance_ctrl_t g_ether_phy0_ctrl;
extern const ether_phy_cfg_t g_ether_phy0_cfg;
#if (BSP_FEATURE_TZ_HAS_TRUSTZONE == 1) && (BSP_TZ_SECURE_BUILD != 1) && (BSP_TZ_NONSECURE_BUILD != 1)
#define ETHER_BUFFER_PLACE_IN_SECTION BSP_PLACE_IN_SECTION(".ns_buffer.eth")
#else
#define ETHER_BUFFER_PLACE_IN_SECTION
#endif

/** ether on ether Instance. */
extern const ether_instance_t g_ether0;

/** Access the Ethernet instance using these structures when calling API functions directly (::p_api is not used). */
extern ether_instance_ctrl_t g_ether0_ctrl;
extern const ether_cfg_t g_ether0_cfg;

#ifndef user_ether0_callback
void user_ether0_callback(ether_callback_args_t * p_args);
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer8;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer8_ctrl;
extern const transfer_cfg_t g_transfer8_cfg;
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer7;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer7_ctrl;
extern const transfer_cfg_t g_transfer7_cfg;
/** SPI on SCI Instance. */
extern const spi_instance_t g_sci_spi4;

/** Access the SCI_SPI instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_spi_instance_ctrl_t g_sci_spi4_ctrl;
extern const spi_cfg_t g_sci_spi4_cfg;

/** Called by the driver when a transfer has completed or an error has occurred (Must be implemented by the user). */
#ifndef sci_spi4_callback
void sci_spi4_callback(spi_callback_args_t * p_args);
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
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer6;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer6_ctrl;
extern const transfer_cfg_t g_transfer6_cfg;
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer5;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer5_ctrl;
extern const transfer_cfg_t g_transfer5_cfg;
/** SPI on SCI Instance. */
extern const spi_instance_t g_sci_spi7;

/** Access the SCI_SPI instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_spi_instance_ctrl_t g_sci_spi7_ctrl;
extern const spi_cfg_t g_sci_spi7_cfg;

/** Called by the driver when a transfer has completed or an error has occurred (Must be implemented by the user). */
#ifndef sci_spi7_callback
void sci_spi7_callback(spi_callback_args_t * p_args);
#endif
/** CAN on CAN Instance. */
extern const can_instance_t g_can0;
/** Access the CAN instance using these structures when calling API functions directly (::p_api is not used). */
extern can_instance_ctrl_t g_can0_ctrl;
extern const can_cfg_t g_can0_cfg;
extern const can_extended_cfg_t g_can0_cfg_extend;




#ifndef can0_callback
void can0_callback(can_callback_args_t * p_args);
#endif
#define CAN_NO_OF_MAILBOXES_g_can0 (32)
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer4;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer4_ctrl;
extern const transfer_cfg_t g_transfer4_cfg;
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer3;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer3_ctrl;
extern const transfer_cfg_t g_transfer3_cfg;
/** SPI on SCI Instance. */
extern const spi_instance_t g_sci_spi3;

/** Access the SCI_SPI instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_spi_instance_ctrl_t g_sci_spi3_ctrl;
extern const spi_cfg_t g_sci_spi3_cfg;

/** Called by the driver when a transfer has completed or an error has occurred (Must be implemented by the user). */
#ifndef sci_spi3_callback
void sci_spi3_callback(spi_callback_args_t * p_args);
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer2;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer2_ctrl;
extern const transfer_cfg_t g_transfer2_cfg;
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer1;

/** Access the DTC instance using these structures when calling API functions directly (::p_api is not used). */
extern dtc_instance_ctrl_t g_transfer1_ctrl;
extern const transfer_cfg_t g_transfer1_cfg;
/** SPI on SCI Instance. */
extern const spi_instance_t g_sci_spi6;

/** Access the SCI_SPI instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_spi_instance_ctrl_t g_sci_spi6_ctrl;
extern const spi_cfg_t g_sci_spi6_cfg;

/** Called by the driver when a transfer has completed or an error has occurred (Must be implemented by the user). */
#ifndef sci_spi6_callback
void sci_spi6_callback(spi_callback_args_t * p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer2;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer2_ctrl;
extern const timer_cfg_t g_timer2_cfg;

#ifndef cb_timer2
void cb_timer2(timer_callback_args_t * p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer6;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer6_ctrl;
extern const timer_cfg_t g_timer6_cfg;

#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif
extern const jpeg_instance_t g_jpeg0;

            /** Access the JPEG instance using these structures when calling API functions directly (::p_api is not used). */
            extern jpeg_instance_ctrl_t g_jpeg0_ctrl;
            extern const jpeg_cfg_t  g_jpeg0_cfg;

            #if JPEG_CFG_DECODE_ENABLE
             #ifndef decode_callback
            void decode_callback(jpeg_callback_args_t * p_args);
             #endif
            #endif

            #if JPEG_CFG_ENCODE_ENABLE
             #ifndef NULL
            void NULL(jpeg_callback_args_t * p_args);
             #endif
            #endif
#define GLCDC_CFG_LAYER_1_ENABLE (true)
            #define GLCDC_CFG_LAYER_2_ENABLE (false)

            #define GLCDC_CFG_CLUT_ENABLE (false)

            #define GLCDC_CFG_CORRECTION_GAMMA_ENABLE_R       (false)
            #define GLCDC_CFG_CORRECTION_GAMMA_ENABLE_G       (false)
            #define GLCDC_CFG_CORRECTION_GAMMA_ENABLE_B       (false)

            /* Display on GLCDC Instance. */
            extern const display_instance_t g_display0;
            extern display_runtime_cfg_t g_display0_runtime_cfg_fg;
            extern display_runtime_cfg_t g_display0_runtime_cfg_bg;

            /** Access the GLCDC instance using these structures when calling API functions directly (::p_api is not used). */
            extern glcdc_instance_ctrl_t g_display0_ctrl;
            extern const display_cfg_t g_display0_cfg;

            #if ((GLCDC_CFG_CORRECTION_GAMMA_ENABLE_R | GLCDC_CFG_CORRECTION_GAMMA_ENABLE_G | GLCDC_CFG_CORRECTION_GAMMA_ENABLE_B) && GLCDC_CFG_COLOR_CORRECTION_ENABLE && !(false))
            extern display_gamma_correction_t g_display0_gamma_cfg;
            #endif

            #if GLCDC_CFG_CLUT_ENABLE
            extern display_clut_cfg_t g_display0_clut_cfg_glcdc;
            #endif

            #ifndef _ra_port_display_callback
            void _ra_port_display_callback(display_callback_args_t * p_args);
            #endif

            #define DISPLAY_IN_FORMAT_16BITS_RGB565_0
            #if defined (DISPLAY_IN_FORMAT_32BITS_RGB888_0) || defined (DISPLAY_IN_FORMAT_32BITS_ARGB8888_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (32)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_RGB565_0) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB1555_0) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB4444_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (16)
            #elif defined (DISPLAY_IN_FORMAT_CLUT8_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (8)
            #elif defined (DISPLAY_IN_FORMAT_CLUT4_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (4)
            #else
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (1)
            #endif
            #define DISPLAY_HSIZE_INPUT0                 (480)
            #define DISPLAY_VSIZE_INPUT0                 (272)
            #define DISPLAY_BUFFER_STRIDE_BYTES_INPUT0   (((DISPLAY_HSIZE_INPUT0 * DISPLAY_BITS_PER_PIXEL_INPUT0 + 0x1FF) >> 9) << 6)
            #define DISPLAY_BUFFER_STRIDE_PIXELS_INPUT0  ((DISPLAY_BUFFER_STRIDE_BYTES_INPUT0 * 8) / DISPLAY_BITS_PER_PIXEL_INPUT0)
            #if GLCDC_CFG_LAYER_1_ENABLE
            extern uint8_t fb_background[1][DISPLAY_BUFFER_STRIDE_BYTES_INPUT0 * DISPLAY_VSIZE_INPUT0];
            #endif

            #define DISPLAY_IN_FORMAT_16BITS_RGB565_1
            #if defined (DISPLAY_IN_FORMAT_32BITS_RGB888_1) || defined (DISPLAY_IN_FORMAT_32BITS_ARGB8888_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (32)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_RGB565_1) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB1555_1) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB4444_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (16)
            #elif defined (DISPLAY_IN_FORMAT_CLUT8_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (8)
            #elif defined (DISPLAY_IN_FORMAT_CLUT4_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (4)
            #else
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (1)
            #endif
            #define DISPLAY_HSIZE_INPUT1                 (480)
            #define DISPLAY_VSIZE_INPUT1                 (272)
            #define DISPLAY_BUFFER_STRIDE_BYTES_INPUT1   (((DISPLAY_HSIZE_INPUT1 * DISPLAY_BITS_PER_PIXEL_INPUT1 + 0x1FF) >> 9) << 6)
            #define DISPLAY_BUFFER_STRIDE_PIXELS_INPUT1  ((DISPLAY_BUFFER_STRIDE_BYTES_INPUT1 * 8) / DISPLAY_BITS_PER_PIXEL_INPUT1)
            #if GLCDC_CFG_LAYER_2_ENABLE
            extern uint8_t fb_foreground[2][DISPLAY_BUFFER_STRIDE_BYTES_INPUT1 * DISPLAY_VSIZE_INPUT1];
            #endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_transfer0;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g_transfer0_ctrl;
extern const transfer_cfg_t g_transfer0_cfg;

#ifndef g_sdmmc1_dmac_callback
void g_sdmmc1_dmac_callback(dmac_callback_args_t * p_args);
#endif
/** SDMMC on SDMMC Instance. */
extern const sdmmc_instance_t g_sdmmc1;


/** Access the SDMMC instance using these structures when calling API functions directly (::p_api is not used). */
extern sdhi_instance_ctrl_t g_sdmmc1_ctrl;
extern sdmmc_cfg_t g_sdmmc1_cfg;

#ifndef NULL
void NULL(sdmmc_callback_args_t * p_args);
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
