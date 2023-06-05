/* generated vector source file - do not edit */
        #include "bsp_api.h"
        /* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
        #if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_uart_rxi_isr, /* SCI9 RXI (Received data full) */
            [1] = sci_uart_txi_isr, /* SCI9 TXI (Transmit data empty) */
            [2] = sci_uart_tei_isr, /* SCI9 TEI (Transmit end) */
            [3] = sci_uart_eri_isr, /* SCI9 ERI (Receive error) */
            [4] = sdhimmc_accs_isr, /* SDHIMMC1 ACCS (Card access) */
            [5] = sdhimmc_card_isr, /* SDHIMMC1 CARD (Card detect) */
            [6] = dmac_int_isr, /* DMAC0 INT (DMAC transfer end 0) */
            [7] = glcdc_line_detect_isr, /* GLCDC LINE DETECT (Specified line) */
            [8] = drw_int_isr, /* DRW INT (Display list interrupt) */
            [9] = jpeg_jedi_isr, /* JPEG JEDI (Compression/decompression process interrupt) */
            [10] = jpeg_jdti_isr, /* JPEG JDTI (Data transfer interrupt) */
            [11] = gpt_counter_overflow_isr, /* GPT2 COUNTER OVERFLOW (Overflow) */
            [12] = sci_spi_rxi_isr, /* SCI6 RXI (Received data full) */
            [13] = sci_spi_txi_isr, /* SCI6 TXI (Transmit data empty) */
            [14] = sci_spi_tei_isr, /* SCI6 TEI (Transmit end) */
            [15] = sci_spi_eri_isr, /* SCI6 ERI (Receive error) */
            [16] = sci_spi_rxi_isr, /* SCI3 RXI (Received data full) */
            [17] = sci_spi_txi_isr, /* SCI3 TXI (Transmit data empty) */
            [18] = sci_spi_tei_isr, /* SCI3 TEI (Transmit end) */
            [19] = sci_spi_eri_isr, /* SCI3 ERI (Receive error) */
            [20] = can_error_isr, /* CAN0 ERROR (Error interrupt) */
            [21] = can_rx_isr, /* CAN0 MAILBOX RX (Reception complete interrupt) */
            [22] = can_tx_isr, /* CAN0 MAILBOX TX (Transmission complete interrupt) */
            [23] = can_rx_isr, /* CAN0 FIFO RX (Receive FIFO interrupt) */
            [24] = can_tx_isr, /* CAN0 FIFO TX (Transmit FIFO interrupt) */
            [25] = sci_spi_rxi_isr, /* SCI7 RXI (Received data full) */
            [26] = sci_spi_txi_isr, /* SCI7 TXI (Transmit data empty) */
            [27] = sci_spi_tei_isr, /* SCI7 TEI (Transmit end) */
            [28] = sci_spi_eri_isr, /* SCI7 ERI (Receive error) */
            [29] = r_icu_isr, /* ICU IRQ10 (External pin interrupt 10) */
            [30] = r_icu_isr, /* ICU IRQ11 (External pin interrupt 11) */
            [31] = r_icu_isr, /* ICU IRQ13 (External pin interrupt 13) */
            [32] = r_icu_isr, /* ICU IRQ9 (External pin interrupt 9) */
            [33] = sci_spi_rxi_isr, /* SCI4 RXI (Received data full) */
            [34] = sci_spi_txi_isr, /* SCI4 TXI (Transmit data empty) */
            [35] = sci_spi_tei_isr, /* SCI4 TEI (Transmit end) */
            [36] = sci_spi_eri_isr, /* SCI4 ERI (Receive error) */
            [37] = ether_eint_isr, /* EDMAC0 EINT (EDMAC 0 interrupt) */
            [38] = ssi_rxi_isr, /* SSI0 RXI (Receive data full) */
            [39] = ssi_int_isr, /* SSI0 INT (Error interrupt) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_SCI9_RXI), /* SCI9 RXI (Received data full) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_SCI9_TXI), /* SCI9 TXI (Transmit data empty) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_SCI9_TEI), /* SCI9 TEI (Transmit end) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_SCI9_ERI), /* SCI9 ERI (Receive error) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_SDHIMMC1_ACCS), /* SDHIMMC1 ACCS (Card access) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_SDHIMMC1_CARD), /* SDHIMMC1 CARD (Card detect) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_DMAC0_INT), /* DMAC0 INT (DMAC transfer end 0) */
            [7] = BSP_PRV_IELS_ENUM(EVENT_GLCDC_LINE_DETECT), /* GLCDC LINE DETECT (Specified line) */
            [8] = BSP_PRV_IELS_ENUM(EVENT_DRW_INT), /* DRW INT (Display list interrupt) */
            [9] = BSP_PRV_IELS_ENUM(EVENT_JPEG_JEDI), /* JPEG JEDI (Compression/decompression process interrupt) */
            [10] = BSP_PRV_IELS_ENUM(EVENT_JPEG_JDTI), /* JPEG JDTI (Data transfer interrupt) */
            [11] = BSP_PRV_IELS_ENUM(EVENT_GPT2_COUNTER_OVERFLOW), /* GPT2 COUNTER OVERFLOW (Overflow) */
            [12] = BSP_PRV_IELS_ENUM(EVENT_SCI6_RXI), /* SCI6 RXI (Received data full) */
            [13] = BSP_PRV_IELS_ENUM(EVENT_SCI6_TXI), /* SCI6 TXI (Transmit data empty) */
            [14] = BSP_PRV_IELS_ENUM(EVENT_SCI6_TEI), /* SCI6 TEI (Transmit end) */
            [15] = BSP_PRV_IELS_ENUM(EVENT_SCI6_ERI), /* SCI6 ERI (Receive error) */
            [16] = BSP_PRV_IELS_ENUM(EVENT_SCI3_RXI), /* SCI3 RXI (Received data full) */
            [17] = BSP_PRV_IELS_ENUM(EVENT_SCI3_TXI), /* SCI3 TXI (Transmit data empty) */
            [18] = BSP_PRV_IELS_ENUM(EVENT_SCI3_TEI), /* SCI3 TEI (Transmit end) */
            [19] = BSP_PRV_IELS_ENUM(EVENT_SCI3_ERI), /* SCI3 ERI (Receive error) */
            [20] = BSP_PRV_IELS_ENUM(EVENT_CAN0_ERROR), /* CAN0 ERROR (Error interrupt) */
            [21] = BSP_PRV_IELS_ENUM(EVENT_CAN0_MAILBOX_RX), /* CAN0 MAILBOX RX (Reception complete interrupt) */
            [22] = BSP_PRV_IELS_ENUM(EVENT_CAN0_MAILBOX_TX), /* CAN0 MAILBOX TX (Transmission complete interrupt) */
            [23] = BSP_PRV_IELS_ENUM(EVENT_CAN0_FIFO_RX), /* CAN0 FIFO RX (Receive FIFO interrupt) */
            [24] = BSP_PRV_IELS_ENUM(EVENT_CAN0_FIFO_TX), /* CAN0 FIFO TX (Transmit FIFO interrupt) */
            [25] = BSP_PRV_IELS_ENUM(EVENT_SCI7_RXI), /* SCI7 RXI (Received data full) */
            [26] = BSP_PRV_IELS_ENUM(EVENT_SCI7_TXI), /* SCI7 TXI (Transmit data empty) */
            [27] = BSP_PRV_IELS_ENUM(EVENT_SCI7_TEI), /* SCI7 TEI (Transmit end) */
            [28] = BSP_PRV_IELS_ENUM(EVENT_SCI7_ERI), /* SCI7 ERI (Receive error) */
            [29] = BSP_PRV_IELS_ENUM(EVENT_ICU_IRQ10), /* ICU IRQ10 (External pin interrupt 10) */
            [30] = BSP_PRV_IELS_ENUM(EVENT_ICU_IRQ11), /* ICU IRQ11 (External pin interrupt 11) */
            [31] = BSP_PRV_IELS_ENUM(EVENT_ICU_IRQ13), /* ICU IRQ13 (External pin interrupt 13) */
            [32] = BSP_PRV_IELS_ENUM(EVENT_ICU_IRQ9), /* ICU IRQ9 (External pin interrupt 9) */
            [33] = BSP_PRV_IELS_ENUM(EVENT_SCI4_RXI), /* SCI4 RXI (Received data full) */
            [34] = BSP_PRV_IELS_ENUM(EVENT_SCI4_TXI), /* SCI4 TXI (Transmit data empty) */
            [35] = BSP_PRV_IELS_ENUM(EVENT_SCI4_TEI), /* SCI4 TEI (Transmit end) */
            [36] = BSP_PRV_IELS_ENUM(EVENT_SCI4_ERI), /* SCI4 ERI (Receive error) */
            [37] = BSP_PRV_IELS_ENUM(EVENT_EDMAC0_EINT), /* EDMAC0 EINT (EDMAC 0 interrupt) */
            [38] = BSP_PRV_IELS_ENUM(EVENT_SSI0_RXI), /* SSI0 RXI (Receive data full) */
            [39] = BSP_PRV_IELS_ENUM(EVENT_SSI0_INT), /* SSI0 INT (Error interrupt) */
        };
        #endif