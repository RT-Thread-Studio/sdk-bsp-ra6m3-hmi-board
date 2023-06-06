/* generated HAL source file - do not edit */
#include "hal_data.h"


gpt_instance_ctrl_t g_timer5_ctrl;
#if 0
const gpt_extended_pwm_cfg_t g_timer5_pwm_extend =
{
    .trough_ipl          = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT5_COUNTER_UNDERFLOW)
    .trough_irq          = VECTOR_NUMBER_GPT5_COUNTER_UNDERFLOW,
#else
    .trough_irq          = FSP_INVALID_VECTOR,
#endif
    .poeg_link           = GPT_POEG_LINK_POEG0,
    .output_disable      =  GPT_OUTPUT_DISABLE_NONE,
    .adc_trigger         =  GPT_ADC_TRIGGER_NONE,
    .dead_time_count_up  = 0,
    .dead_time_count_down = 0,
    .adc_a_compare_match = 0,
    .adc_b_compare_match = 0,
    .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE,
    .interrupt_skip_count  = GPT_INTERRUPT_SKIP_COUNT_0,
    .interrupt_skip_adc    = GPT_INTERRUPT_SKIP_ADC_NONE,
    .gtioca_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
    .gtiocb_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
};
#endif
const gpt_extended_cfg_t g_timer5_extend =
{
    .gtioca = { .output_enabled = true,
                .stop_level     = GPT_PIN_LEVEL_LOW
              },
    .gtiocb = { .output_enabled = true,
                .stop_level     = GPT_PIN_LEVEL_LOW
              },
    .start_source        = (gpt_source_t) ( GPT_SOURCE_NONE),
    .stop_source         = (gpt_source_t) ( GPT_SOURCE_NONE),
    .clear_source        = (gpt_source_t) ( GPT_SOURCE_NONE),
    .count_up_source     = (gpt_source_t) ( GPT_SOURCE_NONE),
    .count_down_source   = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_a_source    = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_b_source    = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT5_CAPTURE_COMPARE_A)
    .capture_a_irq       = VECTOR_NUMBER_GPT5_CAPTURE_COMPARE_A,
#else
    .capture_a_irq       = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_GPT5_CAPTURE_COMPARE_B)
    .capture_b_irq       = VECTOR_NUMBER_GPT5_CAPTURE_COMPARE_B,
#else
    .capture_b_irq       = FSP_INVALID_VECTOR,
#endif
    .capture_filter_gtioca       = GPT_CAPTURE_FILTER_NONE,
    .capture_filter_gtiocb       = GPT_CAPTURE_FILTER_NONE,
#if 0
    .p_pwm_cfg                   = &g_timer5_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if 0
    .gtior_setting.gtior_b.gtioa  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.oadflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.oahld  = 0U,
    .gtior_setting.gtior_b.oae    = (uint32_t) true,
    .gtior_setting.gtior_b.oadf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfaen  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsa  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
    .gtior_setting.gtior_b.gtiob  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.obdflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.obhld  = 0U,
    .gtior_setting.gtior_b.obe    = (uint32_t) true,
    .gtior_setting.gtior_b.obdf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfben  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsb  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
#else
    .gtior_setting.gtior = 0U,
#endif
};
const timer_cfg_t g_timer5_cfg =
{
    .mode                = TIMER_MODE_PWM,
    /* Actual period: 0.00008333333333333333 seconds. Actual duty: 50%. */ .period_counts = (uint32_t) 0x2710, .duty_cycle_counts = 0x1388, .source_div = (timer_source_div_t)0,
    .channel             = 5,
    .p_callback          = NULL,
    /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
    .p_context           = &NULL,
#endif
    .p_extend            = &g_timer5_extend,
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT5_COUNTER_OVERFLOW)
    .cycle_end_irq       = VECTOR_NUMBER_GPT5_COUNTER_OVERFLOW,
#else
    .cycle_end_irq       = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const timer_instance_t g_timer5 =
{
    .p_ctrl        = &g_timer5_ctrl,
    .p_cfg         = &g_timer5_cfg,
    .p_api         = &g_timer_on_gpt
};
gpt_instance_ctrl_t g_timer_ctrl;
#if 0
const gpt_extended_pwm_cfg_t g_timer_pwm_extend =
{
    .trough_ipl          = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT1_COUNTER_UNDERFLOW)
    .trough_irq          = VECTOR_NUMBER_GPT1_COUNTER_UNDERFLOW,
#else
    .trough_irq          = FSP_INVALID_VECTOR,
#endif
    .poeg_link           = GPT_POEG_LINK_POEG0,
    .output_disable      =  GPT_OUTPUT_DISABLE_NONE,
    .adc_trigger         =  GPT_ADC_TRIGGER_NONE,
    .dead_time_count_up  = 0,
    .dead_time_count_down = 0,
    .adc_a_compare_match = 0,
    .adc_b_compare_match = 0,
    .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE,
    .interrupt_skip_count  = GPT_INTERRUPT_SKIP_COUNT_0,
    .interrupt_skip_adc    = GPT_INTERRUPT_SKIP_ADC_NONE,
    .gtioca_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
    .gtiocb_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
};
#endif
const gpt_extended_cfg_t g_timer_extend =
{
    .gtioca = { .output_enabled = true,
                .stop_level     = GPT_PIN_LEVEL_LOW
              },
    .gtiocb = { .output_enabled = false,
                .stop_level     = GPT_PIN_LEVEL_LOW
              },
    .start_source        = (gpt_source_t) ( GPT_SOURCE_NONE),
    .stop_source         = (gpt_source_t) ( GPT_SOURCE_NONE),
    .clear_source        = (gpt_source_t) ( GPT_SOURCE_NONE),
    .count_up_source     = (gpt_source_t) ( GPT_SOURCE_NONE),
    .count_down_source   = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_a_source    = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_b_source    = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT1_CAPTURE_COMPARE_A)
    .capture_a_irq       = VECTOR_NUMBER_GPT1_CAPTURE_COMPARE_A,
#else
    .capture_a_irq       = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_GPT1_CAPTURE_COMPARE_B)
    .capture_b_irq       = VECTOR_NUMBER_GPT1_CAPTURE_COMPARE_B,
#else
    .capture_b_irq       = FSP_INVALID_VECTOR,
#endif
    .capture_filter_gtioca       = GPT_CAPTURE_FILTER_NONE,
    .capture_filter_gtiocb       = GPT_CAPTURE_FILTER_NONE,
#if 0
    .p_pwm_cfg                   = &g_timer_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if 0
    .gtior_setting.gtior_b.gtioa  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.oadflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.oahld  = 0U,
    .gtior_setting.gtior_b.oae    = (uint32_t) true,
    .gtior_setting.gtior_b.oadf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfaen  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsa  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
    .gtior_setting.gtior_b.gtiob  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.obdflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.obhld  = 0U,
    .gtior_setting.gtior_b.obe    = (uint32_t) false,
    .gtior_setting.gtior_b.obdf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfben  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsb  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
#else
    .gtior_setting.gtior = 0U,
#endif
};
const timer_cfg_t g_timer_cfg =
{
    .mode                = TIMER_MODE_PERIODIC,
    /* Actual period: 3.25e-7 seconds. Actual duty: 48.717948717948715%. */ .period_counts = (uint32_t) 0x27, .duty_cycle_counts = 0x13, .source_div = (timer_source_div_t)0,
    .channel             = 1,
    .p_callback          = NULL,
    /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
    .p_context           = &NULL,
#endif
    .p_extend            = &g_timer_extend,
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT1_COUNTER_OVERFLOW)
    .cycle_end_irq       = VECTOR_NUMBER_GPT1_COUNTER_OVERFLOW,
#else
    .cycle_end_irq       = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const timer_instance_t g_timer =
{
    .p_ctrl        = &g_timer_ctrl,
    .p_cfg         = &g_timer_cfg,
    .p_api         = &g_timer_on_gpt
};
dtc_instance_ctrl_t g_transfer10_ctrl;

transfer_info_t g_transfer10_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_INCREMENTED,
    .repeat_area         = TRANSFER_REPEAT_AREA_DESTINATION,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_FIXED,
    .size                = TRANSFER_SIZE_4_BYTE,
    .mode                = TRANSFER_MODE_BLOCK,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer10_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SSI0_RXI,
};
const transfer_cfg_t g_transfer10_cfg =
{
    .p_info              = &g_transfer10_info,
    .p_extend            = &g_transfer10_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer10 =
{
    .p_ctrl        = &g_transfer10_ctrl,
    .p_cfg         = &g_transfer10_cfg,
    .p_api         = &g_transfer_on_dtc
};
ssi_instance_ctrl_t     g_i2s0_ctrl;

            /** SSI instance configuration */
            const ssi_extended_cfg_t g_i2s0_cfg_extend =
            {
                .audio_clock         = SSI_AUDIO_CLOCK_INTERNAL,
                .bit_clock_div       = SSI_CLOCK_DIV_1,
            };

            /** I2S interface configuration */
            const i2s_cfg_t g_i2s0_cfg =
            {
                .channel             = 0,
                .pcm_width           = I2S_PCM_WIDTH_24_BITS,
                .operating_mode      = I2S_MODE_MASTER,
                .word_length         = I2S_WORD_LENGTH_32_BITS,
                .ws_continue         = I2S_WS_CONTINUE_OFF,
                .p_callback          = i2s_callback,
                .p_context           = NULL,
                .p_extend            = &g_i2s0_cfg_extend,
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
  #if 0 == 0
                .txi_irq                 = VECTOR_NUMBER_SSI0_TXI,
  #else
                .txi_irq                 = VECTOR_NUMBER_SSI0_TXI_RXI,
  #endif
#else
                .txi_irq                 = FSP_INVALID_VECTOR,
#endif
#if (2) != BSP_IRQ_DISABLED
  #if 0 == 0
                .rxi_irq                 = VECTOR_NUMBER_SSI0_RXI,
  #else
                .rxi_irq                 = VECTOR_NUMBER_SSI0_TXI_RXI,
  #endif
#else
                .rxi_irq                 = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SSI0_INT)
                .int_irq                 = VECTOR_NUMBER_SSI0_INT,
#else
                .int_irq                 = FSP_INVALID_VECTOR,
#endif
                .txi_ipl             = (BSP_IRQ_DISABLED),
                .rxi_ipl             = (2),
                .idle_err_ipl        = (2),
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
                .p_transfer_tx       = NULL,
#else
                .p_transfer_tx       = &RA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == g_transfer10)
                .p_transfer_rx       = NULL,
#else
                .p_transfer_rx       = &g_transfer10,
#endif
#undef RA_NOT_DEFINED
            };

/* Instance structure to use this module. */
const i2s_instance_t g_i2s0 =
{
    .p_ctrl        = &g_i2s0_ctrl,
    .p_cfg         = &g_i2s0_cfg,
    .p_api         = &g_i2s_on_ssi
};
ether_phy_instance_ctrl_t g_ether_phy0_ctrl;

const ether_phy_cfg_t g_ether_phy0_cfg =
{

    .channel                   = 0,
    .phy_lsi_address           = 0,
    .phy_reset_wait_time       = 0x00020000,
    .mii_bit_access_wait_time  = 8,
    .flow_control              = ETHER_PHY_FLOW_CONTROL_DISABLE,
    .mii_type                  = ETHER_PHY_MII_TYPE_RMII,
    .p_context                 = NULL,
    .p_extend                  = NULL,

};
/* Instance structure to use this module. */
const ether_phy_instance_t g_ether_phy0 =
{
    .p_ctrl        = &g_ether_phy0_ctrl,
    .p_cfg         = &g_ether_phy0_cfg,
    .p_api         = &g_ether_phy_on_ether_phy
};
ether_instance_ctrl_t g_ether0_ctrl;

            uint8_t g_ether0_mac_address[6] = { 0x00,0x11,0x22,0x33,0x44,0x55 };

            __attribute__((__aligned__(16))) ether_instance_descriptor_t g_ether0_tx_descriptors[1] ETHER_BUFFER_PLACE_IN_SECTION;
            __attribute__((__aligned__(16))) ether_instance_descriptor_t g_ether0_rx_descriptors[1] ETHER_BUFFER_PLACE_IN_SECTION;

            __attribute__((__aligned__(32)))uint8_t g_ether0_ether_buffer0[1536]ETHER_BUFFER_PLACE_IN_SECTION;
__attribute__((__aligned__(32)))uint8_t g_ether0_ether_buffer1[1536]ETHER_BUFFER_PLACE_IN_SECTION;


            uint8_t *pp_g_ether0_ether_buffers[2] = {
(uint8_t *) &g_ether0_ether_buffer0[0],
(uint8_t *) &g_ether0_ether_buffer1[0],
};

            const ether_cfg_t g_ether0_cfg =
            {
                .channel            = 0,
                .zerocopy           = ETHER_ZEROCOPY_DISABLE,
                .multicast          = ETHER_MULTICAST_ENABLE,
                .promiscuous        = ETHER_PROMISCUOUS_DISABLE,
                .flow_control       = ETHER_FLOW_CONTROL_DISABLE,
                .padding            = ETHER_PADDING_DISABLE,
                .padding_offset     = 0,
                .broadcast_filter   = 0,
                .p_mac_address      = g_ether0_mac_address,

                .p_rx_descriptors   = g_ether0_rx_descriptors,
                .p_tx_descriptors   = g_ether0_tx_descriptors,

                .num_tx_descriptors = 1,
                .num_rx_descriptors = 1,

                .pp_ether_buffers   = pp_g_ether0_ether_buffers,

                .ether_buffer_size  = 1536,

#if defined(VECTOR_NUMBER_EDMAC0_EINT)
                .irq                = VECTOR_NUMBER_EDMAC0_EINT,
#else
                .irq                = FSP_INVALID_VECTOR,
#endif

                .interrupt_priority = (12),

                .p_callback         = user_ether0_callback,
                .p_ether_phy_instance = &g_ether_phy0,
                .p_context          = NULL,
                .p_extend           = NULL,
            };

/* Instance structure to use this module. */
const ether_instance_t g_ether0 =
{
    .p_ctrl        = &g_ether0_ctrl,
    .p_cfg         = &g_ether0_cfg,
    .p_api         = &g_ether_on_ether
};
dtc_instance_ctrl_t g_transfer8_ctrl;

transfer_info_t g_transfer8_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_INCREMENTED,
    .repeat_area         = TRANSFER_REPEAT_AREA_DESTINATION,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_FIXED,
    .size                = TRANSFER_SIZE_1_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer8_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SCI4_RXI,
};
const transfer_cfg_t g_transfer8_cfg =
{
    .p_info              = &g_transfer8_info,
    .p_extend            = &g_transfer8_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer8 =
{
    .p_ctrl        = &g_transfer8_ctrl,
    .p_cfg         = &g_transfer8_cfg,
    .p_api         = &g_transfer_on_dtc
};
dtc_instance_ctrl_t g_transfer7_ctrl;

transfer_info_t g_transfer7_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_FIXED,
    .repeat_area         = TRANSFER_REPEAT_AREA_SOURCE,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_INCREMENTED,
    .size                = TRANSFER_SIZE_1_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer7_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SCI4_TXI,
};
const transfer_cfg_t g_transfer7_cfg =
{
    .p_info              = &g_transfer7_info,
    .p_extend            = &g_transfer7_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer7 =
{
    .p_ctrl        = &g_transfer7_ctrl,
    .p_cfg         = &g_transfer7_cfg,
    .p_api         = &g_transfer_on_dtc
};
sci_spi_instance_ctrl_t g_sci_spi4_ctrl;

/** SPI extended configuration */
const sci_spi_extended_cfg_t g_sci_spi4_cfg_extend =
{
    .clk_div = {
        /* Actual calculated bitrate: 7968750. */ .cks = 0, .brr = 2, .mddr = 204,
    }
};

const spi_cfg_t g_sci_spi4_cfg =
{
    .channel         = 4,
    .operating_mode  = SPI_MODE_MASTER,
    .clk_phase       = SPI_CLK_PHASE_EDGE_ODD,
    .clk_polarity    = SPI_CLK_POLARITY_LOW,
    .mode_fault      = SPI_MODE_FAULT_ERROR_DISABLE,
    .bit_order       = SPI_BIT_ORDER_MSB_FIRST,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == g_transfer7)
    .p_transfer_tx   = NULL,
#else
    .p_transfer_tx   = &g_transfer7,
#endif
#if (RA_NOT_DEFINED == g_transfer8)
    .p_transfer_rx   = NULL,
#else
    .p_transfer_rx   = &g_transfer8,
#endif
#undef RA_NOT_DEFINED
    .p_callback      = sci_spi4_callback,
    .p_context       = NULL,
    .rxi_irq         = VECTOR_NUMBER_SCI4_RXI,
    .txi_irq         = VECTOR_NUMBER_SCI4_TXI,
    .tei_irq         = VECTOR_NUMBER_SCI4_TEI,
    .eri_irq         = VECTOR_NUMBER_SCI4_ERI,
    .rxi_ipl         = (12),
    .txi_ipl         = (12),
    .tei_ipl         = (12),
    .eri_ipl         = (12),
    .p_extend        = &g_sci_spi4_cfg_extend,
};
/* Instance structure to use this module. */
const spi_instance_t g_sci_spi4 =
{
    .p_ctrl          = &g_sci_spi4_ctrl,
    .p_cfg           = &g_sci_spi4_cfg,
    .p_api           = &g_spi_on_sci
};
icu_instance_ctrl_t g_external_irq9_ctrl;
const external_irq_cfg_t g_external_irq9_cfg =
{
    .channel             = 9,
    .trigger             = EXTERNAL_IRQ_TRIG_RISING,
    .filter_enable       = false,
    .pclk_div            = EXTERNAL_IRQ_PCLK_DIV_BY_64,
    .p_callback          = irq_callback,
    /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
    .p_context           = &NULL,
#endif
    .p_extend            = NULL,
    .ipl                 = (6),
#if defined(VECTOR_NUMBER_ICU_IRQ9)
    .irq                 = VECTOR_NUMBER_ICU_IRQ9,
#else
    .irq                 = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irq9 =
{
    .p_ctrl        = &g_external_irq9_ctrl,
    .p_cfg         = &g_external_irq9_cfg,
    .p_api         = &g_external_irq_on_icu
};
icu_instance_ctrl_t g_external_irq13_ctrl;
const external_irq_cfg_t g_external_irq13_cfg =
{
    .channel             = 13,
    .trigger             = EXTERNAL_IRQ_TRIG_RISING,
    .filter_enable       = false,
    .pclk_div            = EXTERNAL_IRQ_PCLK_DIV_BY_64,
    .p_callback          = irq_callback,
    /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
    .p_context           = &NULL,
#endif
    .p_extend            = NULL,
    .ipl                 = (12),
#if defined(VECTOR_NUMBER_ICU_IRQ13)
    .irq                 = VECTOR_NUMBER_ICU_IRQ13,
#else
    .irq                 = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irq13 =
{
    .p_ctrl        = &g_external_irq13_ctrl,
    .p_cfg         = &g_external_irq13_cfg,
    .p_api         = &g_external_irq_on_icu
};
icu_instance_ctrl_t g_external_irq11_ctrl;
const external_irq_cfg_t g_external_irq11_cfg =
{
    .channel             = 11,
    .trigger             = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
    .filter_enable       = false,
    .pclk_div            = EXTERNAL_IRQ_PCLK_DIV_BY_64,
    .p_callback          = irq_callback,
    /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
    .p_context           = &NULL,
#endif
    .p_extend            = NULL,
    .ipl                 = (12),
#if defined(VECTOR_NUMBER_ICU_IRQ11)
    .irq                 = VECTOR_NUMBER_ICU_IRQ11,
#else
    .irq                 = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irq11 =
{
    .p_ctrl        = &g_external_irq11_ctrl,
    .p_cfg         = &g_external_irq11_cfg,
    .p_api         = &g_external_irq_on_icu
};
icu_instance_ctrl_t g_external_irq10_ctrl;
const external_irq_cfg_t g_external_irq10_cfg =
{
    .channel             = 10,
    .trigger             = EXTERNAL_IRQ_TRIG_BOTH_EDGE,
    .filter_enable       = false,
    .pclk_div            = EXTERNAL_IRQ_PCLK_DIV_BY_64,
    .p_callback          = irq_callback,
    /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
    .p_context           = &NULL,
#endif
    .p_extend            = NULL,
    .ipl                 = (12),
#if defined(VECTOR_NUMBER_ICU_IRQ10)
    .irq                 = VECTOR_NUMBER_ICU_IRQ10,
#else
    .irq                 = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irq10 =
{
    .p_ctrl        = &g_external_irq10_ctrl,
    .p_cfg         = &g_external_irq10_cfg,
    .p_api         = &g_external_irq_on_icu
};
dtc_instance_ctrl_t g_transfer6_ctrl;

transfer_info_t g_transfer6_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_INCREMENTED,
    .repeat_area         = TRANSFER_REPEAT_AREA_DESTINATION,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_FIXED,
    .size                = TRANSFER_SIZE_1_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer6_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SCI7_RXI,
};
const transfer_cfg_t g_transfer6_cfg =
{
    .p_info              = &g_transfer6_info,
    .p_extend            = &g_transfer6_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer6 =
{
    .p_ctrl        = &g_transfer6_ctrl,
    .p_cfg         = &g_transfer6_cfg,
    .p_api         = &g_transfer_on_dtc
};
dtc_instance_ctrl_t g_transfer5_ctrl;

transfer_info_t g_transfer5_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_FIXED,
    .repeat_area         = TRANSFER_REPEAT_AREA_SOURCE,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_INCREMENTED,
    .size                = TRANSFER_SIZE_1_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer5_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SCI7_TXI,
};
const transfer_cfg_t g_transfer5_cfg =
{
    .p_info              = &g_transfer5_info,
    .p_extend            = &g_transfer5_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer5 =
{
    .p_ctrl        = &g_transfer5_ctrl,
    .p_cfg         = &g_transfer5_cfg,
    .p_api         = &g_transfer_on_dtc
};
sci_spi_instance_ctrl_t g_sci_spi7_ctrl;

/** SPI extended configuration */
const sci_spi_extended_cfg_t g_sci_spi7_cfg_extend =
{
    .clk_div = {
        /* Actual calculated bitrate: 7500000. */ .cks = 0, .brr = 3, .mddr = 0,
    }
};

const spi_cfg_t g_sci_spi7_cfg =
{
    .channel         = 7,
    .operating_mode  = SPI_MODE_MASTER,
    .clk_phase       = SPI_CLK_PHASE_EDGE_ODD,
    .clk_polarity    = SPI_CLK_POLARITY_LOW,
    .mode_fault      = SPI_MODE_FAULT_ERROR_DISABLE,
    .bit_order       = SPI_BIT_ORDER_MSB_FIRST,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == g_transfer5)
    .p_transfer_tx   = NULL,
#else
    .p_transfer_tx   = &g_transfer5,
#endif
#if (RA_NOT_DEFINED == g_transfer6)
    .p_transfer_rx   = NULL,
#else
    .p_transfer_rx   = &g_transfer6,
#endif
#undef RA_NOT_DEFINED
    .p_callback      = sci_spi7_callback,
    .p_context       = NULL,
    .rxi_irq         = VECTOR_NUMBER_SCI7_RXI,
    .txi_irq         = VECTOR_NUMBER_SCI7_TXI,
    .tei_irq         = VECTOR_NUMBER_SCI7_TEI,
    .eri_irq         = VECTOR_NUMBER_SCI7_ERI,
    .rxi_ipl         = (12),
    .txi_ipl         = (12),
    .tei_ipl         = (12),
    .eri_ipl         = (12),
    .p_extend        = &g_sci_spi7_cfg_extend,
};
/* Instance structure to use this module. */
const spi_instance_t g_sci_spi7 =
{
    .p_ctrl          = &g_sci_spi7_ctrl,
    .p_cfg           = &g_sci_spi7_cfg,
    .p_api           = &g_spi_on_sci
};
#ifndef CAN0_BAUD_SETTINGS_OVERRIDE
#define CAN0_BAUD_SETTINGS_OVERRIDE  (0)
#endif
#if CAN0_BAUD_SETTINGS_OVERRIDE
can_bit_timing_cfg_t g_can0_bit_timing_cfg =
{
    .baud_rate_prescaler = 1,
    .time_segment_1 = 4,
    .time_segment_2 = 2,
    .synchronization_jump_width = 1
};
#else
can_bit_timing_cfg_t g_can0_bit_timing_cfg =
{
    /* Actual bitrate: 1000000 Hz. Actual Bit Time Ratio: 83 %. */  .baud_rate_prescaler = 1 +1 /* Division value of baud rate prescaler */, .time_segment_1 = 9, .time_segment_2 = 2, .synchronization_jump_width = 2,
};
#endif

uint32_t g_can0_mailbox_mask[CAN_NO_OF_MAILBOXES_g_can0/4] =
{
0,
#if CAN_NO_OF_MAILBOXES_g_can0 > 4
0x1FFFFFFF,
#endif
#if CAN_NO_OF_MAILBOXES_g_can0 > 8
0x1FFFFFFF,
0x1FFFFFFF,
#endif
#if CAN_NO_OF_MAILBOXES_g_can0 > 16
0x1FFFFFFF,
0x1FFFFFFF,
#endif
#if CAN_NO_OF_MAILBOXES_g_can0 > 24
0x1FFFFFFF,
0x1FFFFFFF,
#endif
};

can_mailbox_t g_can0_mailbox[CAN_NO_OF_MAILBOXES_g_can0] =
{
    {
        .mailbox_id              =  0x100,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
},
    {
        .mailbox_id              =  1,
        .id_mode                 =  CAN_ID_MODE_EXTENDED,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  2,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_TRANSMIT,
        .frame_type              =  CAN_FRAME_TYPE_DATA,
    },
    {
        .mailbox_id              =  3,
        .id_mode                 =  CAN_ID_MODE_EXTENDED,
        .mailbox_type            =  CAN_MAILBOX_TRANSMIT,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
#if CAN_NO_OF_MAILBOXES_g_can0 > 4
    {
        .mailbox_id              =  4,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  5,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  6,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  7,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
#endif
#if CAN_NO_OF_MAILBOXES_g_can0 > 8
    {
        .mailbox_id              =  8,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  9,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  10,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  11,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  12,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA,
    },
    {
        .mailbox_id              =  13,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  14,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  15,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
#endif
#if CAN_NO_OF_MAILBOXES_g_can0 > 16
    {
        .mailbox_id              =  16,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },

    {
        .mailbox_id              =  17,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  18,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  19,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  20,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  21,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  22,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA,
    },
    {
        .mailbox_id              =  23,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
#endif
#if CAN_NO_OF_MAILBOXES_g_can0 > 24
    {
        .mailbox_id              =  24,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  25,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  26,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  27,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  28,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  29,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  30,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    },
    {
        .mailbox_id              =  31,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_DATA
    }
#endif
};

#if CAN_CFG_FIFO_SUPPORT
const can_fifo_interrupt_cfg_t g_can0_fifo_int_cfg =
{
    .fifo_int_mode          = CAN_FIFO_INTERRUPT_MODE_RX_EVERY_FRAME | CAN_FIFO_INTERRUPT_MODE_TX_EVERY_FRAME,
    .rx_fifo_irq             = VECTOR_NUMBER_CAN0_FIFO_RX,
    .tx_fifo_irq             = VECTOR_NUMBER_CAN0_FIFO_TX,
};

can_rx_fifo_cfg_t g_can0_rx_fifo_cfg =
{
    .rx_fifo_mask1 = 0x1FFFFFFF,
    .rx_fifo_mask2 = 0x1FFFFFFF,

    .rx_fifo_id1 =
    {
        .mailbox_id              =  0,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_REMOTE
    },

    .rx_fifo_id2 =
    {
        .mailbox_id              =  0,
        .id_mode                 =  CAN_ID_MODE_STANDARD,
        .mailbox_type            =  CAN_MAILBOX_RECEIVE,
        .frame_type              =  CAN_FRAME_TYPE_REMOTE
    },
};
#endif

const can_extended_cfg_t g_can0_extended_cfg =
{
    .clock_source           = CAN_CLOCK_SOURCE_CANMCLK,
    .p_mailbox_mask         = g_can0_mailbox_mask,
    .p_mailbox              = g_can0_mailbox,
    .global_id_mode         = CAN_GLOBAL_ID_MODE_STANDARD,
    .mailbox_count          = CAN_NO_OF_MAILBOXES_g_can0,
    .message_mode           = CAN_MESSAGE_MODE_OVERWRITE,
#if CAN_CFG_FIFO_SUPPORT
    .p_fifo_int_cfg         = &g_can0_fifo_int_cfg,
    .p_rx_fifo_cfg          = &g_can0_rx_fifo_cfg,
#else
    .p_fifo_int_cfg         = NULL,
    .p_rx_fifo_cfg          = NULL,
#endif
};

can_instance_ctrl_t g_can0_ctrl;
const can_cfg_t g_can0_cfg =
{
    .channel            = 0,
    .p_bit_timing       = &g_can0_bit_timing_cfg,
    .p_callback         = can0_callback,
    .p_extend           = &g_can0_extended_cfg,
    .p_context          = NULL,
    .ipl                = (12),
#if defined(VECTOR_NUMBER_CAN0_MAILBOX_TX)
    .tx_irq             = VECTOR_NUMBER_CAN0_MAILBOX_TX,
#else
    .tx_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_CAN0_MAILBOX_RX)
    .rx_irq             = VECTOR_NUMBER_CAN0_MAILBOX_RX,
#else
    .rx_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_CAN0_ERROR)
    .error_irq             = VECTOR_NUMBER_CAN0_ERROR,
#else
    .error_irq             = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const can_instance_t g_can0 =
{
    .p_ctrl        = &g_can0_ctrl,
    .p_cfg         = &g_can0_cfg,
    .p_api         = &g_can_on_can
};
dtc_instance_ctrl_t g_transfer4_ctrl;

transfer_info_t g_transfer4_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_INCREMENTED,
    .repeat_area         = TRANSFER_REPEAT_AREA_DESTINATION,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_FIXED,
    .size                = TRANSFER_SIZE_1_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer4_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SCI3_RXI,
};
const transfer_cfg_t g_transfer4_cfg =
{
    .p_info              = &g_transfer4_info,
    .p_extend            = &g_transfer4_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer4 =
{
    .p_ctrl        = &g_transfer4_ctrl,
    .p_cfg         = &g_transfer4_cfg,
    .p_api         = &g_transfer_on_dtc
};
dtc_instance_ctrl_t g_transfer3_ctrl;

transfer_info_t g_transfer3_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_FIXED,
    .repeat_area         = TRANSFER_REPEAT_AREA_SOURCE,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_INCREMENTED,
    .size                = TRANSFER_SIZE_1_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer3_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SCI3_TXI,
};
const transfer_cfg_t g_transfer3_cfg =
{
    .p_info              = &g_transfer3_info,
    .p_extend            = &g_transfer3_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer3 =
{
    .p_ctrl        = &g_transfer3_ctrl,
    .p_cfg         = &g_transfer3_cfg,
    .p_api         = &g_transfer_on_dtc
};
sci_spi_instance_ctrl_t g_sci_spi3_ctrl;

/** SPI extended configuration */
const sci_spi_extended_cfg_t g_sci_spi3_cfg_extend =
{
    .clk_div = {
        /* Actual calculated bitrate: 7968750. */ .cks = 0, .brr = 2, .mddr = 204,
    }
};

const spi_cfg_t g_sci_spi3_cfg =
{
    .channel         = 3,
    .operating_mode  = SPI_MODE_MASTER,
    .clk_phase       = SPI_CLK_PHASE_EDGE_ODD,
    .clk_polarity    = SPI_CLK_POLARITY_LOW,
    .mode_fault      = SPI_MODE_FAULT_ERROR_DISABLE,
    .bit_order       = SPI_BIT_ORDER_MSB_FIRST,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == g_transfer3)
    .p_transfer_tx   = NULL,
#else
    .p_transfer_tx   = &g_transfer3,
#endif
#if (RA_NOT_DEFINED == g_transfer4)
    .p_transfer_rx   = NULL,
#else
    .p_transfer_rx   = &g_transfer4,
#endif
#undef RA_NOT_DEFINED
    .p_callback      = sci_spi3_callback,
    .p_context       = NULL,
    .rxi_irq         = VECTOR_NUMBER_SCI3_RXI,
    .txi_irq         = VECTOR_NUMBER_SCI3_TXI,
    .tei_irq         = VECTOR_NUMBER_SCI3_TEI,
    .eri_irq         = VECTOR_NUMBER_SCI3_ERI,
    .rxi_ipl         = (12),
    .txi_ipl         = (12),
    .tei_ipl         = (12),
    .eri_ipl         = (12),
    .p_extend        = &g_sci_spi3_cfg_extend,
};
/* Instance structure to use this module. */
const spi_instance_t g_sci_spi3 =
{
    .p_ctrl          = &g_sci_spi3_ctrl,
    .p_cfg           = &g_sci_spi3_cfg,
    .p_api           = &g_spi_on_sci
};
dtc_instance_ctrl_t g_transfer2_ctrl;

transfer_info_t g_transfer2_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_INCREMENTED,
    .repeat_area         = TRANSFER_REPEAT_AREA_DESTINATION,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_FIXED,
    .size                = TRANSFER_SIZE_1_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer2_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SCI6_RXI,
};
const transfer_cfg_t g_transfer2_cfg =
{
    .p_info              = &g_transfer2_info,
    .p_extend            = &g_transfer2_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer2 =
{
    .p_ctrl        = &g_transfer2_ctrl,
    .p_cfg         = &g_transfer2_cfg,
    .p_api         = &g_transfer_on_dtc
};
dtc_instance_ctrl_t g_transfer1_ctrl;

transfer_info_t g_transfer1_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_FIXED,
    .repeat_area         = TRANSFER_REPEAT_AREA_SOURCE,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_INCREMENTED,
    .size                = TRANSFER_SIZE_1_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 0,
};
const dtc_extended_cfg_t g_transfer1_cfg_extend =
{
    .activation_source   = VECTOR_NUMBER_SCI6_TXI,
};
const transfer_cfg_t g_transfer1_cfg =
{
    .p_info              = &g_transfer1_info,
    .p_extend            = &g_transfer1_cfg_extend,
};

/* Instance structure to use this module. */
const transfer_instance_t g_transfer1 =
{
    .p_ctrl        = &g_transfer1_ctrl,
    .p_cfg         = &g_transfer1_cfg,
    .p_api         = &g_transfer_on_dtc
};
sci_spi_instance_ctrl_t g_sci_spi6_ctrl;

/** SPI extended configuration */
const sci_spi_extended_cfg_t g_sci_spi6_cfg_extend =
{
    .clk_div = {
        /* Actual calculated bitrate: 7968750. */ .cks = 0, .brr = 2, .mddr = 204,
    }
};

const spi_cfg_t g_sci_spi6_cfg =
{
    .channel         = 6,
    .operating_mode  = SPI_MODE_MASTER,
    .clk_phase       = SPI_CLK_PHASE_EDGE_ODD,
    .clk_polarity    = SPI_CLK_POLARITY_LOW,
    .mode_fault      = SPI_MODE_FAULT_ERROR_DISABLE,
    .bit_order       = SPI_BIT_ORDER_MSB_FIRST,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == g_transfer1)
    .p_transfer_tx   = NULL,
#else
    .p_transfer_tx   = &g_transfer1,
#endif
#if (RA_NOT_DEFINED == g_transfer2)
    .p_transfer_rx   = NULL,
#else
    .p_transfer_rx   = &g_transfer2,
#endif
#undef RA_NOT_DEFINED
    .p_callback      = sci_spi6_callback,
    .p_context       = NULL,
    .rxi_irq         = VECTOR_NUMBER_SCI6_RXI,
    .txi_irq         = VECTOR_NUMBER_SCI6_TXI,
    .tei_irq         = VECTOR_NUMBER_SCI6_TEI,
    .eri_irq         = VECTOR_NUMBER_SCI6_ERI,
    .rxi_ipl         = (12),
    .txi_ipl         = (12),
    .tei_ipl         = (12),
    .eri_ipl         = (12),
    .p_extend        = &g_sci_spi6_cfg_extend,
};
/* Instance structure to use this module. */
const spi_instance_t g_sci_spi6 =
{
    .p_ctrl          = &g_sci_spi6_ctrl,
    .p_cfg           = &g_sci_spi6_cfg,
    .p_api           = &g_spi_on_sci
};
gpt_instance_ctrl_t g_timer2_ctrl;
#if 0
const gpt_extended_pwm_cfg_t g_timer2_pwm_extend =
{
    .trough_ipl          = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT2_COUNTER_UNDERFLOW)
    .trough_irq          = VECTOR_NUMBER_GPT2_COUNTER_UNDERFLOW,
#else
    .trough_irq          = FSP_INVALID_VECTOR,
#endif
    .poeg_link           = GPT_POEG_LINK_POEG0,
    .output_disable      =  GPT_OUTPUT_DISABLE_NONE,
    .adc_trigger         =  GPT_ADC_TRIGGER_NONE,
    .dead_time_count_up  = 0,
    .dead_time_count_down = 0,
    .adc_a_compare_match = 0,
    .adc_b_compare_match = 0,
    .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE,
    .interrupt_skip_count  = GPT_INTERRUPT_SKIP_COUNT_0,
    .interrupt_skip_adc    = GPT_INTERRUPT_SKIP_ADC_NONE,
    .gtioca_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
    .gtiocb_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
};
#endif
const gpt_extended_cfg_t g_timer2_extend =
{
    .gtioca = { .output_enabled = false,
                .stop_level     = GPT_PIN_LEVEL_LOW
              },
    .gtiocb = { .output_enabled = false,
                .stop_level     = GPT_PIN_LEVEL_LOW
              },
    .start_source        = (gpt_source_t) ( GPT_SOURCE_NONE),
    .stop_source         = (gpt_source_t) ( GPT_SOURCE_NONE),
    .clear_source        = (gpt_source_t) ( GPT_SOURCE_NONE),
    .count_up_source     = (gpt_source_t) ( GPT_SOURCE_NONE),
    .count_down_source   = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_a_source    = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_b_source    = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT2_CAPTURE_COMPARE_A)
    .capture_a_irq       = VECTOR_NUMBER_GPT2_CAPTURE_COMPARE_A,
#else
    .capture_a_irq       = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_GPT2_CAPTURE_COMPARE_B)
    .capture_b_irq       = VECTOR_NUMBER_GPT2_CAPTURE_COMPARE_B,
#else
    .capture_b_irq       = FSP_INVALID_VECTOR,
#endif
    .capture_filter_gtioca       = GPT_CAPTURE_FILTER_NONE,
    .capture_filter_gtiocb       = GPT_CAPTURE_FILTER_NONE,
#if 0
    .p_pwm_cfg                   = &g_timer2_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if 0
    .gtior_setting.gtior_b.gtioa  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.oadflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.oahld  = 0U,
    .gtior_setting.gtior_b.oae    = (uint32_t) false,
    .gtior_setting.gtior_b.oadf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfaen  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsa  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
    .gtior_setting.gtior_b.gtiob  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.obdflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.obhld  = 0U,
    .gtior_setting.gtior_b.obe    = (uint32_t) false,
    .gtior_setting.gtior_b.obdf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfben  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsb  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
#else
    .gtior_setting.gtior = 0U,
#endif
};
const timer_cfg_t g_timer2_cfg =
{
    .mode                = TIMER_MODE_PERIODIC,
    /* Actual period: 0.000020833333333333333 seconds. Actual duty: 50%. */ .period_counts = (uint32_t) 0x9c4, .duty_cycle_counts = 0x4e2, .source_div = (timer_source_div_t)0,
    .channel             = 2,
    .p_callback          = cb_timer2,
    /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
    .p_context           = &NULL,
#endif
    .p_extend            = &g_timer2_extend,
    .cycle_end_ipl       = (8),
#if defined(VECTOR_NUMBER_GPT2_COUNTER_OVERFLOW)
    .cycle_end_irq       = VECTOR_NUMBER_GPT2_COUNTER_OVERFLOW,
#else
    .cycle_end_irq       = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const timer_instance_t g_timer2 =
{
    .p_ctrl        = &g_timer2_ctrl,
    .p_cfg         = &g_timer2_cfg,
    .p_api         = &g_timer_on_gpt
};
gpt_instance_ctrl_t g_timer6_ctrl;
#if 0
const gpt_extended_pwm_cfg_t g_timer6_pwm_extend =
{
    .trough_ipl          = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT6_COUNTER_UNDERFLOW)
    .trough_irq          = VECTOR_NUMBER_GPT6_COUNTER_UNDERFLOW,
#else
    .trough_irq          = FSP_INVALID_VECTOR,
#endif
    .poeg_link           = GPT_POEG_LINK_POEG0,
    .output_disable      =  GPT_OUTPUT_DISABLE_NONE,
    .adc_trigger         =  GPT_ADC_TRIGGER_NONE,
    .dead_time_count_up  = 0,
    .dead_time_count_down = 0,
    .adc_a_compare_match = 0,
    .adc_b_compare_match = 0,
    .interrupt_skip_source = GPT_INTERRUPT_SKIP_SOURCE_NONE,
    .interrupt_skip_count  = GPT_INTERRUPT_SKIP_COUNT_0,
    .interrupt_skip_adc    = GPT_INTERRUPT_SKIP_ADC_NONE,
    .gtioca_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
    .gtiocb_disable_setting = GPT_GTIOC_DISABLE_PROHIBITED,
};
#endif
const gpt_extended_cfg_t g_timer6_extend =
{
    .gtioca = { .output_enabled = true,
                .stop_level     = GPT_PIN_LEVEL_LOW
              },
    .gtiocb = { .output_enabled = true,
                .stop_level     = GPT_PIN_LEVEL_LOW
              },
    .start_source        = (gpt_source_t) ( GPT_SOURCE_NONE),
    .stop_source         = (gpt_source_t) ( GPT_SOURCE_NONE),
    .clear_source        = (gpt_source_t) ( GPT_SOURCE_NONE),
    .count_up_source     = (gpt_source_t) ( GPT_SOURCE_NONE),
    .count_down_source   = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_a_source    = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_b_source    = (gpt_source_t) ( GPT_SOURCE_NONE),
    .capture_a_ipl       = (BSP_IRQ_DISABLED),
    .capture_b_ipl       = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT6_CAPTURE_COMPARE_A)
    .capture_a_irq       = VECTOR_NUMBER_GPT6_CAPTURE_COMPARE_A,
#else
    .capture_a_irq       = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_GPT6_CAPTURE_COMPARE_B)
    .capture_b_irq       = VECTOR_NUMBER_GPT6_CAPTURE_COMPARE_B,
#else
    .capture_b_irq       = FSP_INVALID_VECTOR,
#endif
    .capture_filter_gtioca       = GPT_CAPTURE_FILTER_NONE,
    .capture_filter_gtiocb       = GPT_CAPTURE_FILTER_NONE,
#if 0
    .p_pwm_cfg                   = &g_timer6_pwm_extend,
#else
    .p_pwm_cfg                   = NULL,
#endif
#if 0
    .gtior_setting.gtior_b.gtioa  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.oadflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.oahld  = 0U,
    .gtior_setting.gtior_b.oae    = (uint32_t) true,
    .gtior_setting.gtior_b.oadf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfaen  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsa  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
    .gtior_setting.gtior_b.gtiob  = (0U << 4U) | (0U << 2U) | (0U << 0U),
    .gtior_setting.gtior_b.obdflt = (uint32_t) GPT_PIN_LEVEL_LOW,
    .gtior_setting.gtior_b.obhld  = 0U,
    .gtior_setting.gtior_b.obe    = (uint32_t) true,
    .gtior_setting.gtior_b.obdf   = (uint32_t) GPT_GTIOC_DISABLE_PROHIBITED,
    .gtior_setting.gtior_b.nfben  = ((uint32_t) GPT_CAPTURE_FILTER_NONE & 1U),
    .gtior_setting.gtior_b.nfcsb  = ((uint32_t) GPT_CAPTURE_FILTER_NONE >> 1U),
#else
    .gtior_setting.gtior = 0U,
#endif
};
const timer_cfg_t g_timer6_cfg =
{
    .mode                = TIMER_MODE_PERIODIC,
    /* Actual period: 0.000012816666666666667 seconds. Actual duty: 50%. */ .period_counts = (uint32_t) 0x602, .duty_cycle_counts = 0x301, .source_div = (timer_source_div_t)0,
    .channel             = 6,
    .p_callback          = NULL,
    /** If NULL then do not add & */
#if defined(NULL)
    .p_context           = NULL,
#else
    .p_context           = &NULL,
#endif
    .p_extend            = &g_timer6_extend,
    .cycle_end_ipl       = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_GPT6_COUNTER_OVERFLOW)
    .cycle_end_irq       = VECTOR_NUMBER_GPT6_COUNTER_OVERFLOW,
#else
    .cycle_end_irq       = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const timer_instance_t g_timer6 =
{
    .p_ctrl        = &g_timer6_ctrl,
    .p_cfg         = &g_timer6_cfg,
    .p_api         = &g_timer_on_gpt
};
#if JPEG_CFG_ENCODE_ENABLE

            /* Luminance quantization table */static const uint8_t quant_table_0[] ={16, 11, 10, 16, 24, 40, 51, 61, 12, 12, 14, 19, 26, 58, 60, 55, 14, 13, 16, 24, 40, 57, 69, 56, 14, 17, 22, 29, 51, 87, 80, 62, 18, 22, 37, 56, 68, 109, 103, 77, 24, 35, 55, 64, 81, 104, 113, 92, 49, 64, 78, 87, 103, 121, 120, 101, 72, 92, 95, 98, 112, 100, 103, 99, };/* Chrominance quantization table */static const uint8_t quant_table_1[] ={17, 18, 24, 47, 99, 99, 99, 99, 18, 21, 26, 66, 99, 99, 99, 99, 24, 26, 56, 99, 99, 99, 99, 99, 47, 66, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, };

            /* Luminance DC coefficients */
            static const uint8_t huffm_dc_table_0[] =
            {
                /* Table K.3 ITU-T81 specification */
                0x00, 0x01, 0x05, 0x01,
                0x01, 0x01, 0x01, 0x01,
                0x01, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x01, 0x02, 0x03,
                0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0A, 0x0B,
            };

            /* Chrominance DC coefficients */
            static const uint8_t huffm_dc_table_1[] =
            {
                /* Table K.4 ITU-T81 specification */
                0x00, 0x03, 0x01, 0x01,
                0x01, 0x01, 0x01, 0x01,
                0x01, 0x01, 0x01, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x01, 0x02, 0x03,
                0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0A, 0x0B,
            };

            /* Luminance AC coefficients */
            static const uint8_t huffm_ac_table_0[] =
            {
                /* Table K.5 ITU-T81 specification */
                0x00, 0x02, 0x01, 0x03,
                0x03, 0x02, 0x04, 0x03,
                0x05, 0x05, 0x04, 0x04,
                0x00, 0x00, 0x01, 0x7D,
                0x01, 0x02, 0x03, 0x00,
                0x04, 0x11, 0x05, 0x12,
                0x21, 0x31, 0x41, 0x06,
                0x13, 0x51, 0x61, 0x07,
                0x22, 0x71, 0x14, 0x32,
                0x81, 0x91, 0xA1, 0x08,
                0x23, 0x42, 0xB1, 0xC1,
                0x15, 0x52, 0xD1, 0xF0,
                0x24, 0x33, 0x62, 0x72,
                0x82, 0x09, 0x0A, 0x16,
                0x17, 0x18, 0x19, 0x1A,
                0x25, 0x26, 0x27, 0x28,
                0x29, 0x2A, 0x34, 0x35,
                0x36, 0x37, 0x38, 0x39,
                0x3A, 0x43, 0x44, 0x45,
                0x46, 0x47, 0x48, 0x49,
                0x4A, 0x53, 0x54, 0x55,
                0x56, 0x57, 0x58, 0x59,
                0x5A, 0x63, 0x64, 0x65,
                0x66, 0x67, 0x68, 0x69,
                0x6A, 0x73, 0x74, 0x75,
                0x76, 0x77, 0x78, 0x79,
                0x7A, 0x83, 0x84, 0x85,
                0x86, 0x87, 0x88, 0x89,
                0x8A, 0x92, 0x93, 0x94,
                0x95, 0x96, 0x97, 0x98,
                0x99, 0x9A, 0xA2, 0xA3,
                0xA4, 0xA5, 0xA6, 0xA7,
                0xA8, 0xA9, 0xAA, 0xB2,
                0xB3, 0xB4, 0xB5, 0xB6,
                0xB7, 0xB8, 0xB9, 0xBA,
                0xC2, 0xC3, 0xC4, 0xC5,
                0xC6, 0xC7, 0xC8, 0xC9,
                0xCA, 0xD2, 0xD3, 0xD4,
                0xD5, 0xD6, 0xD7, 0xD8,
                0xD9, 0xDA, 0xE1, 0xE2,
                0xE3, 0xE4, 0xE5, 0xE6,
                0xE7, 0xE8, 0xE9, 0xEA,
                0xF1, 0xF2, 0xF3, 0xF4,
                0xF5, 0xF6, 0xF7, 0xF8,
                0xF9, 0xFA,
            };

            /* Chrominance AC coefficients */
            static const uint8_t huffm_ac_table_1[] =
            {
                /* Table K.6 ITU-T81 specification */
                0x00, 0x02, 0x01, 0x02,
                0x04, 0x04, 0x03, 0x04,
                0x07, 0x05, 0x04, 0x04,
                0x00, 0x01, 0x02, 0x77,
                0x00, 0x01, 0x02, 0x03,
                0x11, 0x04, 0x05, 0x21,
                0x31, 0x06, 0x12, 0x41,
                0x51, 0x07, 0x61, 0x71,
                0x13, 0x22, 0x32, 0x81,
                0x08, 0x14, 0x42, 0x91,
                0xA1, 0xB1, 0xC1, 0x09,
                0x23, 0x33, 0x52, 0xF0,
                0x15, 0x62, 0x72, 0xD1,
                0x0A, 0x16, 0x24, 0x34,
                0xE1, 0x25, 0xF1, 0x17,
                0x18, 0x19, 0x1A, 0x26,
                0x27, 0x28, 0x29, 0x2A,
                0x35, 0x36, 0x37, 0x38,
                0x39, 0x3A, 0x43, 0x44,
                0x45, 0x46, 0x47, 0x48,
                0x49, 0x4A, 0x53, 0x54,
                0x55, 0x56, 0x57, 0x58,
                0x59, 0x5A, 0x63, 0x64,
                0x65, 0x66, 0x67, 0x68,
                0x69, 0x6A, 0x73, 0x74,
                0x75, 0x76, 0x77, 0x78,
                0x79, 0x7A, 0x82, 0x83,
                0x84, 0x85, 0x86, 0x87,
                0x88, 0x89, 0x8A, 0x92,
                0x93, 0x94, 0x95, 0x96,
                0x97, 0x98, 0x99, 0x9A,
                0xA2, 0xA3, 0xA4, 0xA5,
                0xA6, 0xA7, 0xA8, 0xA9,
                0xAA, 0xB2, 0xB3, 0xB4,
                0xB5, 0xB6, 0xB7, 0xB8,
                0xB9, 0xBA, 0xC2, 0xC3,
                0xC4, 0xC5, 0xC6, 0xC7,
                0xC8, 0xC9, 0xCA, 0xD2,
                0xD3, 0xD4, 0xD5, 0xD6,
                0xD7, 0xD8, 0xD9, 0xDA,
                0xE2, 0xE3, 0xE4, 0xE5,
                0xE6, 0xE7, 0xE8, 0xE9,
                0xEA, 0xF2, 0xF3, 0xF4,
                0xF5, 0xF6, 0xF7, 0xF8,
                0xF9, 0xFA,
            };
            #endif

            jpeg_instance_ctrl_t g_jpeg0_ctrl;
            const jpeg_cfg_t  g_jpeg0_cfg =
            {
                .jedi_ipl           = (8),
                .jdti_ipl           = (8),
            #if defined(VECTOR_NUMBER_JPEG_JEDI)
                .jedi_irq           = VECTOR_NUMBER_JPEG_JEDI,
            #else
                .jedi_irq           = FSP_INVALID_VECTOR,
            #endif
                .jdti_irq           = VECTOR_NUMBER_JPEG_JDTI,

            #if JPEG_CFG_DECODE_ENABLE && JPEG_CFG_ENCODE_ENABLE
                .default_mode              = (JPEG_MODE_DECODE),
            #endif

            #if JPEG_CFG_DECODE_ENABLE
                .decode_input_data_order   = JPEG_DATA_ORDER_NORMAL,
                .decode_output_data_order  = JPEG_DATA_ORDER_NORMAL,
                .pixel_format              = JPEG_DECODE_PIXEL_FORMAT_RGB565,
                .alpha_value               = 255,
                .p_decode_callback         = decode_callback,
                .p_decode_context          = NULL,
            #endif

            #if JPEG_CFG_ENCODE_ENABLE
                .encode_input_data_order   = JPEG_DATA_ORDER_NORMAL,
                .encode_output_data_order  = JPEG_DATA_ORDER_NORMAL,
                .dri_marker                = 512,
                .horizontal_resolution     = 480,
                .vertical_resolution       = 272,
                .horizontal_stride_pixels  = 480,
                .p_quant_luma_table        = quant_table_0,
                .p_quant_chroma_table      = quant_table_1,
                .p_huffman_luma_ac_table   = huffm_ac_table_0,
                .p_huffman_luma_dc_table   = huffm_dc_table_0,
                .p_huffman_chroma_ac_table = huffm_ac_table_1,
                .p_huffman_chroma_dc_table = huffm_dc_table_1,
                .p_encode_callback         = NULL,
                .p_encode_context          = NULL,
            #endif
            };

            const jpeg_instance_t g_jpeg0 =
            {
                .p_api  = (jpeg_api_t const *)&g_jpeg_on_jpeg,
                .p_ctrl = &g_jpeg0_ctrl,
                .p_cfg  = &g_jpeg0_cfg
            };
/** Display framebuffer */
        #if GLCDC_CFG_LAYER_1_ENABLE
        uint8_t fb_background[1][DISPLAY_BUFFER_STRIDE_BYTES_INPUT0 * DISPLAY_VSIZE_INPUT0] BSP_ALIGN_VARIABLE(64) BSP_PLACE_IN_SECTION(".bss");
        #else
        /** Graphics Layer 1 is specified not to be used when starting */
        #endif
        #if GLCDC_CFG_LAYER_2_ENABLE
        uint8_t fb_foreground[2][DISPLAY_BUFFER_STRIDE_BYTES_INPUT1 * DISPLAY_VSIZE_INPUT1] BSP_ALIGN_VARIABLE(64) BSP_PLACE_IN_SECTION(".bss");
        #else
        /** Graphics Layer 2 is specified not to be used when starting */
        #endif

        #if GLCDC_CFG_CLUT_ENABLE
        /** Display CLUT buffer to be used for updating CLUT */
        static uint32_t CLUT_buffer[256];

        /** Display CLUT configuration(only used if using CLUT format) */
        display_clut_cfg_t g_display0_clut_cfg_glcdc =
        {
            .p_base              = (uint32_t *)CLUT_buffer,
            .start               = 0,   /* User have to update this setting when using */
            .size                = 256  /* User have to update this setting when using */
        };
        #else
        /** CLUT is specified not to be used */
        #endif

        #if (false)
         #define GLCDC_CFG_CORRECTION_GAMMA_TABLE_CONST   const
         #define GLCDC_CFG_CORRECTION_GAMMA_TABLE_CAST    (uint16_t *)
         #define GLCDC_CFG_CORRECTION_GAMMA_CFG_CAST      (display_gamma_correction_t *)
        #else
         #define GLCDC_CFG_CORRECTION_GAMMA_TABLE_CONST
         #define GLCDC_CFG_CORRECTION_GAMMA_TABLE_CAST
         #define GLCDC_CFG_CORRECTION_GAMMA_CFG_CAST
        #endif

        #if ((GLCDC_CFG_CORRECTION_GAMMA_ENABLE_R | GLCDC_CFG_CORRECTION_GAMMA_ENABLE_G | GLCDC_CFG_CORRECTION_GAMMA_ENABLE_B) && GLCDC_CFG_COLOR_CORRECTION_ENABLE)
        /** Gamma correction tables */
        #if GLCDC_CFG_CORRECTION_GAMMA_ENABLE_R
        static GLCDC_CFG_CORRECTION_GAMMA_TABLE_CONST uint16_t glcdc_gamma_r_gain[DISPLAY_GAMMA_CURVE_ELEMENT_NUM] = {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024};
        static GLCDC_CFG_CORRECTION_GAMMA_TABLE_CONST uint16_t glcdc_gamma_r_threshold[DISPLAY_GAMMA_CURVE_ELEMENT_NUM] = {0, 64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960};
        #endif
        #if GLCDC_CFG_CORRECTION_GAMMA_ENABLE_G
        static GLCDC_CFG_CORRECTION_GAMMA_TABLE_CONST uint16_t glcdc_gamma_g_gain[DISPLAY_GAMMA_CURVE_ELEMENT_NUM] = {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024};
        static GLCDC_CFG_CORRECTION_GAMMA_TABLE_CONST uint16_t glcdc_gamma_g_threshold[DISPLAY_GAMMA_CURVE_ELEMENT_NUM] = {0, 64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960};
        #endif
        #if GLCDC_CFG_CORRECTION_GAMMA_ENABLE_B
        static GLCDC_CFG_CORRECTION_GAMMA_TABLE_CONST uint16_t glcdc_gamma_b_gain[DISPLAY_GAMMA_CURVE_ELEMENT_NUM] = {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024};
        static GLCDC_CFG_CORRECTION_GAMMA_TABLE_CONST uint16_t glcdc_gamma_b_threshold[DISPLAY_GAMMA_CURVE_ELEMENT_NUM] = {0, 64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960};
        #endif
        GLCDC_CFG_CORRECTION_GAMMA_TABLE_CONST display_gamma_correction_t g_display0_gamma_cfg =
        {
            .r =
            {
                .enable      = GLCDC_CFG_CORRECTION_GAMMA_ENABLE_R,
        #if GLCDC_CFG_CORRECTION_GAMMA_ENABLE_R
                .gain        = GLCDC_CFG_CORRECTION_GAMMA_TABLE_CAST glcdc_gamma_r_gain,
                .threshold   = GLCDC_CFG_CORRECTION_GAMMA_TABLE_CAST glcdc_gamma_r_threshold
        #else
                .gain        = NULL,
                .threshold   = NULL
        #endif
            },
            .g =
            {
                .enable      = GLCDC_CFG_CORRECTION_GAMMA_ENABLE_G,
        #if GLCDC_CFG_CORRECTION_GAMMA_ENABLE_G
                .gain        = GLCDC_CFG_CORRECTION_GAMMA_TABLE_CAST glcdc_gamma_g_gain,
                .threshold   = GLCDC_CFG_CORRECTION_GAMMA_TABLE_CAST glcdc_gamma_g_threshold
        #else
                .gain        = NULL,
                .threshold   = NULL
        #endif
            },
            .b =
            {
                .enable      = GLCDC_CFG_CORRECTION_GAMMA_ENABLE_B,
        #if GLCDC_CFG_CORRECTION_GAMMA_ENABLE_B
                .gain        = GLCDC_CFG_CORRECTION_GAMMA_TABLE_CAST glcdc_gamma_b_gain,
                .threshold   = GLCDC_CFG_CORRECTION_GAMMA_TABLE_CAST glcdc_gamma_b_threshold
        #else
                .gain        = NULL,
                .threshold   = NULL
        #endif
            }
        };
        #endif

        /** Display device extended configuration */
        const glcdc_extended_cfg_t g_display0_extend_cfg =
        {
            .tcon_hsync          = GLCDC_TCON_PIN_0,
            .tcon_vsync          = GLCDC_TCON_PIN_1,
            .tcon_de             = GLCDC_TCON_PIN_2,
            .correction_proc_order = GLCDC_CORRECTION_PROC_ORDER_BRIGHTNESS_CONTRAST2GAMMA,
            .clksrc              = GLCDC_CLK_SRC_INTERNAL,
            .clock_div_ratio     = GLCDC_PANEL_CLK_DIVISOR_24,
            .dithering_mode      = GLCDC_DITHERING_MODE_TRUNCATE,
            .dithering_pattern_A = GLCDC_DITHERING_PATTERN_11,
            .dithering_pattern_B = GLCDC_DITHERING_PATTERN_11,
            .dithering_pattern_C = GLCDC_DITHERING_PATTERN_11,
            .dithering_pattern_D = GLCDC_DITHERING_PATTERN_11
        };

        /** Display control block instance */
        glcdc_instance_ctrl_t g_display0_ctrl;

        /** Display interface configuration */
        const display_cfg_t g_display0_cfg =
        {
            /** Input1(Graphics1 layer) configuration */
            .input[0] =
            {
                #if GLCDC_CFG_LAYER_1_ENABLE
                .p_base              = (uint32_t *)&fb_background[0],
                #else
                .p_base              = NULL,
                #endif
                .hsize               = DISPLAY_HSIZE_INPUT0,
                .vsize               = DISPLAY_VSIZE_INPUT0,
                .hstride             = DISPLAY_BUFFER_STRIDE_PIXELS_INPUT0,
                .format              = DISPLAY_IN_FORMAT_16BITS_RGB565,
                .line_descending_enable = false,
                .lines_repeat_enable = false,
                .lines_repeat_times  = 0
            },

            /** Input2(Graphics2 layer) configuration */
            .input[1] =
            {
                #if GLCDC_CFG_LAYER_2_ENABLE
                .p_base              = (uint32_t *)&fb_foreground[0],
                #else
                .p_base              = NULL,
                #endif
                .hsize               = DISPLAY_HSIZE_INPUT1,
                .vsize               = DISPLAY_VSIZE_INPUT1,
                .hstride             = DISPLAY_BUFFER_STRIDE_PIXELS_INPUT1,
                .format              = DISPLAY_IN_FORMAT_16BITS_RGB565,
                .line_descending_enable = false,
                .lines_repeat_enable = false,
                .lines_repeat_times  = 0
             },

            /** Input1(Graphics1 layer) layer configuration */
            .layer[0] =
            {
                .coordinate = {
                        .x           = 0,
                        .y           = 0
                },
                .bg_color =
                {
                    .byte = {
                        .a           = 255,
                        .r           = 255,
                        .g           = 255,
                        .b           = 255
                    }
                },
                .fade_control        = DISPLAY_FADE_CONTROL_NONE,
                .fade_speed          = 0
            },

            /** Input2(Graphics2 layer) layer configuration */
            .layer[1] =
            {
                .coordinate = {
                        .x           = 0,
                        .y           = 0
                },
                .bg_color =
                {
                    .byte = {
                        .a           = 255,
                        .r           = 255,
                        .g           = 255,
                        .b           = 255
                    }
                },
                .fade_control        = DISPLAY_FADE_CONTROL_NONE,
                .fade_speed          = 0
            },

            /** Output configuration */
            .output =
            {
                .htiming =
                {
                    .total_cyc       = 525,
                    .display_cyc     = 480,
                    .back_porch      = 40,
                    .sync_width       = 1,
                    .sync_polarity   = DISPLAY_SIGNAL_POLARITY_LOACTIVE
                },
                .vtiming =
                {
                    .total_cyc       = 316,
                    .display_cyc     = 272,
                    .back_porch      = 8,
                    .sync_width       = 1,
                    .sync_polarity   = DISPLAY_SIGNAL_POLARITY_LOACTIVE
                },
                .format              = DISPLAY_OUT_FORMAT_16BITS_RGB565,
                .endian              = DISPLAY_ENDIAN_LITTLE,
                .color_order         = DISPLAY_COLOR_ORDER_BGR,
                .data_enable_polarity = DISPLAY_SIGNAL_POLARITY_HIACTIVE,
                .sync_edge           = DISPLAY_SIGNAL_SYNC_EDGE_RISING,
                .bg_color =
                {
                    .byte = {
                        .a           = 255,
                        .r           = 0,
                        .g           = 0,
                        .b           = 0
                    }
                },
#if (GLCDC_CFG_COLOR_CORRECTION_ENABLE)
                .brightness =
                {
                    .enable          = false,
                    .r               = 512,
                    .g               = 512,
                    .b               = 512
                },
                .contrast =
                {
                    .enable          = false,
                    .r               = 128,
                    .g               = 128,
                    .b               = 128
                },
#if (GLCDC_CFG_CORRECTION_GAMMA_ENABLE_R | GLCDC_CFG_CORRECTION_GAMMA_ENABLE_G | GLCDC_CFG_CORRECTION_GAMMA_ENABLE_B)
 #if false
                .p_gamma_correction  = GLCDC_CFG_CORRECTION_GAMMA_CFG_CAST (&g_display0_gamma_cfg),
 #else
                .p_gamma_correction  = &g_display0_gamma_cfg,
 #endif
#else
                .p_gamma_correction  = NULL,
#endif
#endif
                .dithering_on        = false
            },

            /** Display device callback function pointer */
            .p_callback              = _ra_port_display_callback,
            .p_context               = NULL,

            /** Display device extended configuration */
            .p_extend                = (void *)(&g_display0_extend_cfg),

            .line_detect_ipl        = (12),
            .underflow_1_ipl        = (BSP_IRQ_DISABLED),
            .underflow_2_ipl        = (BSP_IRQ_DISABLED),

#if defined(VECTOR_NUMBER_GLCDC_LINE_DETECT)
            .line_detect_irq        = VECTOR_NUMBER_GLCDC_LINE_DETECT,
#else
            .line_detect_irq        = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_GLCDC_UNDERFLOW_1)
            .underflow_1_irq        = VECTOR_NUMBER_GLCDC_UNDERFLOW_1,
#else
            .underflow_1_irq        = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_GLCDC_UNDERFLOW_2)
            .underflow_2_irq        = VECTOR_NUMBER_GLCDC_UNDERFLOW_2,
#else
            .underflow_2_irq        = FSP_INVALID_VECTOR,
#endif
        };

#if GLCDC_CFG_LAYER_1_ENABLE
        /** Display on GLCDC run-time configuration(for the graphics1 layer) */
        display_runtime_cfg_t g_display0_runtime_cfg_bg =
        {
            .input =
            {
                #if (true)
                .p_base              = (uint32_t *)&fb_background[0],
                #else
                .p_base              = NULL,
                #endif
                .hsize               = DISPLAY_HSIZE_INPUT0,
                .vsize               = DISPLAY_VSIZE_INPUT0,
                .hstride             = DISPLAY_BUFFER_STRIDE_PIXELS_INPUT0,
                .format              = DISPLAY_IN_FORMAT_16BITS_RGB565,
                .line_descending_enable = false,
                .lines_repeat_enable = false,
                .lines_repeat_times  = 0
            },
            .layer =
            {
                .coordinate = {
                        .x           = 0,
                        .y           = 0
                },
                .bg_color            =
                {
                    .byte            =
                    {
                        .a           = 255,
                        .r           = 255,
                        .g           = 255,
                        .b           = 255
                    }
                },
                .fade_control        = DISPLAY_FADE_CONTROL_NONE,
                .fade_speed          = 0
            }
        };
#endif
#if GLCDC_CFG_LAYER_2_ENABLE
        /** Display on GLCDC run-time configuration(for the graphics2 layer) */
        display_runtime_cfg_t g_display0_runtime_cfg_fg =
        {
            .input =
            {
                #if (false)
                .p_base              = (uint32_t *)&fb_foreground[0],
                #else
                .p_base              = NULL,
                #endif
                .hsize               = DISPLAY_HSIZE_INPUT1,
                .vsize               = DISPLAY_VSIZE_INPUT1,
                .hstride             = DISPLAY_BUFFER_STRIDE_PIXELS_INPUT1,
                .format              = DISPLAY_IN_FORMAT_16BITS_RGB565,
                .line_descending_enable = false,
                .lines_repeat_enable = false,
                .lines_repeat_times  = 0
             },
            .layer =
            {
                .coordinate = {
                        .x           = 0,
                        .y           = 0
                },
                .bg_color            =
                {
                    .byte            =
                    {
                        .a           = 255,
                        .r           = 255,
                        .g           = 255,
                        .b           = 255
                    }
                },
                .fade_control        = DISPLAY_FADE_CONTROL_NONE,
                .fade_speed          = 0
            }
        };
#endif

/* Instance structure to use this module. */
const display_instance_t g_display0 =
{
    .p_ctrl        = &g_display0_ctrl,
    .p_cfg         = (display_cfg_t *)&g_display0_cfg,
    .p_api         = (display_api_t *)&g_display_on_glcdc
};
dmac_instance_ctrl_t g_transfer0_ctrl;
transfer_info_t g_transfer0_info =
{
    .dest_addr_mode      = TRANSFER_ADDR_MODE_FIXED,
    .repeat_area         = TRANSFER_REPEAT_AREA_SOURCE,
    .irq                 = TRANSFER_IRQ_END,
    .chain_mode          = TRANSFER_CHAIN_MODE_DISABLED,
    .src_addr_mode       = TRANSFER_ADDR_MODE_INCREMENTED,
    .size                = TRANSFER_SIZE_4_BYTE,
    .mode                = TRANSFER_MODE_NORMAL,
    .p_dest              = (void *) NULL,
    .p_src               = (void const *) NULL,
    .num_blocks          = 0,
    .length              = 128,
};
const dmac_extended_cfg_t g_transfer0_extend =
{
    .offset              = 1,
    .src_buffer_size     = 1,
#if defined(VECTOR_NUMBER_DMAC0_INT)
    .irq                 = VECTOR_NUMBER_DMAC0_INT,
#else
    .irq                 = FSP_INVALID_VECTOR,
#endif
    .ipl                 = (12),
    .channel             = 0,
    .p_callback          = g_sdmmc1_dmac_callback,
    .p_context           = NULL,
    .activation_source   = ELC_EVENT_SDHIMMC1_DMA_REQ,
};
const transfer_cfg_t g_transfer0_cfg =
{
    .p_info              = &g_transfer0_info,
    .p_extend            = &g_transfer0_extend,
};
/* Instance structure to use this module. */
const transfer_instance_t g_transfer0 =
{
    .p_ctrl        = &g_transfer0_ctrl,
    .p_cfg         = &g_transfer0_cfg,
    .p_api         = &g_transfer_on_dmac
};
#define RA_NOT_DEFINED (UINT32_MAX)
#if (RA_NOT_DEFINED) != (1)

/* If the transfer module is DMAC, define a DMAC transfer callback. */
#include "r_dmac.h"
extern void r_sdhi_transfer_callback(sdhi_instance_ctrl_t * p_ctrl);

void g_sdmmc1_dmac_callback (dmac_callback_args_t * p_args)
{
    r_sdhi_transfer_callback((sdhi_instance_ctrl_t *) p_args->p_context);
}
#endif
#undef RA_NOT_DEFINED

sdhi_instance_ctrl_t g_sdmmc1_ctrl;
sdmmc_cfg_t g_sdmmc1_cfg =
{
    .bus_width              = SDMMC_BUS_WIDTH_4_BITS,
    .channel                = 1,
    .p_callback             = NULL,
    .p_context              = NULL,
    .block_size             = 512,
    .card_detect            = SDMMC_CARD_DETECT_CD,
    .write_protect          = SDMMC_WRITE_PROTECT_NONE,

    .p_extend               = NULL,
    .p_lower_lvl_transfer   = &g_transfer0,

    .access_ipl             = (12),
    .sdio_ipl               = BSP_IRQ_DISABLED,
    .card_ipl               = (12),
    .dma_req_ipl            = (BSP_IRQ_DISABLED),
#if defined(VECTOR_NUMBER_SDHIMMC1_ACCS)
    .access_irq             = VECTOR_NUMBER_SDHIMMC1_ACCS,
#else
    .access_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SDHIMMC1_CARD)
    .card_irq               = VECTOR_NUMBER_SDHIMMC1_CARD,
#else
    .card_irq               = FSP_INVALID_VECTOR,
#endif
    .sdio_irq               = FSP_INVALID_VECTOR,
#if defined(VECTOR_NUMBER_SDHIMMC1_DMA_REQ)
    .dma_req_irq            = VECTOR_NUMBER_SDHIMMC1_DMA_REQ,
#else
    .dma_req_irq            = FSP_INVALID_VECTOR,
#endif
};
/* Instance structure to use this module. */
const sdmmc_instance_t g_sdmmc1 =
{
    .p_ctrl        = &g_sdmmc1_ctrl,
    .p_cfg         = &g_sdmmc1_cfg,
    .p_api         = &g_sdmmc_on_sdhi
};
sci_uart_instance_ctrl_t     g_uart9_ctrl;

            baud_setting_t               g_uart9_baud_setting =
            {
                /* Baud rate calculated with 0.160% error. */ .abcse = 0, .abcs = 0, .bgdm = 1, .cks = 0, .brr = 64, .mddr = (uint8_t) 256, .brme = false
            };

            /** UART extended configuration for UARTonSCI HAL driver */
            const sci_uart_extended_cfg_t g_uart9_cfg_extend =
            {
                .clock                = SCI_UART_CLOCK_INT,
                .rx_edge_start          = SCI_UART_START_BIT_FALLING_EDGE,
                .noise_cancel         = SCI_UART_NOISE_CANCELLATION_DISABLE,
                .rx_fifo_trigger        = SCI_UART_RX_FIFO_TRIGGER_MAX,
                .p_baud_setting         = &g_uart9_baud_setting,
                .flow_control           = SCI_UART_FLOW_CONTROL_RTS,
                #if 0xFF != 0xFF
                .flow_control_pin       = BSP_IO_PORT_FF_PIN_0xFF,
                #else
                .flow_control_pin       = (bsp_io_port_pin_t) UINT16_MAX,
                #endif
            };

            /** UART interface configuration */
            const uart_cfg_t g_uart9_cfg =
            {
                .channel             = 9,
                .data_bits           = UART_DATA_BITS_8,
                .parity              = UART_PARITY_OFF,
                .stop_bits           = UART_STOP_BITS_1,
                .p_callback          = user_uart9_callback,
                .p_context           = NULL,
                .p_extend            = &g_uart9_cfg_extend,
#define RA_NOT_DEFINED (1)
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
                .p_transfer_tx       = NULL,
#else
                .p_transfer_tx       = &RA_NOT_DEFINED,
#endif
#if (RA_NOT_DEFINED == RA_NOT_DEFINED)
                .p_transfer_rx       = NULL,
#else
                .p_transfer_rx       = &RA_NOT_DEFINED,
#endif
#undef RA_NOT_DEFINED
                .rxi_ipl             = (12),
                .txi_ipl             = (12),
                .tei_ipl             = (12),
                .eri_ipl             = (12),
#if defined(VECTOR_NUMBER_SCI9_RXI)
                .rxi_irq             = VECTOR_NUMBER_SCI9_RXI,
#else
                .rxi_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI9_TXI)
                .txi_irq             = VECTOR_NUMBER_SCI9_TXI,
#else
                .txi_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI9_TEI)
                .tei_irq             = VECTOR_NUMBER_SCI9_TEI,
#else
                .tei_irq             = FSP_INVALID_VECTOR,
#endif
#if defined(VECTOR_NUMBER_SCI9_ERI)
                .eri_irq             = VECTOR_NUMBER_SCI9_ERI,
#else
                .eri_irq             = FSP_INVALID_VECTOR,
#endif
            };

/* Instance structure to use this module. */
const uart_instance_t g_uart9 =
{
    .p_ctrl        = &g_uart9_ctrl,
    .p_cfg         = &g_uart9_cfg,
    .p_api         = &g_uart_on_sci
};
void g_hal_init(void) {
g_common_init();
}
