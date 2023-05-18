/* generated vector header file - do not edit */
        #ifndef VECTOR_DATA_H
        #define VECTOR_DATA_H
                /* Number of interrupts allocated */
        #ifndef VECTOR_DATA_IRQ_COUNT
        #define VECTOR_DATA_IRQ_COUNT    (40)
        #endif
        /* ISR prototypes */
        void sci_uart_rxi_isr(void);
        void sci_uart_txi_isr(void);
        void sci_uart_tei_isr(void);
        void sci_uart_eri_isr(void);
        void sdhimmc_accs_isr(void);
        void sdhimmc_card_isr(void);
        void dmac_int_isr(void);
        void glcdc_line_detect_isr(void);
        void drw_int_isr(void);
        void jpeg_jedi_isr(void);
        void jpeg_jdti_isr(void);
        void gpt_counter_overflow_isr(void);
        void sci_spi_rxi_isr(void);
        void sci_spi_txi_isr(void);
        void sci_spi_tei_isr(void);
        void sci_spi_eri_isr(void);
        void can_error_isr(void);
        void can_rx_isr(void);
        void can_tx_isr(void);
        void r_icu_isr(void);
        void ether_eint_isr(void);
        void ssi_rxi_isr(void);
        void ssi_int_isr(void);

        /* Vector table allocations */
        #define VECTOR_NUMBER_SCI9_RXI ((IRQn_Type) 0) /* SCI9 RXI (Received data full) */
        #define SCI9_RXI_IRQn          ((IRQn_Type) 0) /* SCI9 RXI (Received data full) */
        #define VECTOR_NUMBER_SCI9_TXI ((IRQn_Type) 1) /* SCI9 TXI (Transmit data empty) */
        #define SCI9_TXI_IRQn          ((IRQn_Type) 1) /* SCI9 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_SCI9_TEI ((IRQn_Type) 2) /* SCI9 TEI (Transmit end) */
        #define SCI9_TEI_IRQn          ((IRQn_Type) 2) /* SCI9 TEI (Transmit end) */
        #define VECTOR_NUMBER_SCI9_ERI ((IRQn_Type) 3) /* SCI9 ERI (Receive error) */
        #define SCI9_ERI_IRQn          ((IRQn_Type) 3) /* SCI9 ERI (Receive error) */
        #define VECTOR_NUMBER_SDHIMMC1_ACCS ((IRQn_Type) 4) /* SDHIMMC1 ACCS (Card access) */
        #define SDHIMMC1_ACCS_IRQn          ((IRQn_Type) 4) /* SDHIMMC1 ACCS (Card access) */
        #define VECTOR_NUMBER_SDHIMMC1_CARD ((IRQn_Type) 5) /* SDHIMMC1 CARD (Card detect) */
        #define SDHIMMC1_CARD_IRQn          ((IRQn_Type) 5) /* SDHIMMC1 CARD (Card detect) */
        #define VECTOR_NUMBER_DMAC0_INT ((IRQn_Type) 6) /* DMAC0 INT (DMAC transfer end 0) */
        #define DMAC0_INT_IRQn          ((IRQn_Type) 6) /* DMAC0 INT (DMAC transfer end 0) */
        #define VECTOR_NUMBER_GLCDC_LINE_DETECT ((IRQn_Type) 7) /* GLCDC LINE DETECT (Specified line) */
        #define GLCDC_LINE_DETECT_IRQn          ((IRQn_Type) 7) /* GLCDC LINE DETECT (Specified line) */
        #define VECTOR_NUMBER_DRW_INT ((IRQn_Type) 8) /* DRW INT (Display list interrupt) */
        #define DRW_INT_IRQn          ((IRQn_Type) 8) /* DRW INT (Display list interrupt) */
        #define VECTOR_NUMBER_JPEG_JEDI ((IRQn_Type) 9) /* JPEG JEDI (Compression/decompression process interrupt) */
        #define JPEG_JEDI_IRQn          ((IRQn_Type) 9) /* JPEG JEDI (Compression/decompression process interrupt) */
        #define VECTOR_NUMBER_JPEG_JDTI ((IRQn_Type) 10) /* JPEG JDTI (Data transfer interrupt) */
        #define JPEG_JDTI_IRQn          ((IRQn_Type) 10) /* JPEG JDTI (Data transfer interrupt) */
        #define VECTOR_NUMBER_GPT2_COUNTER_OVERFLOW ((IRQn_Type) 11) /* GPT2 COUNTER OVERFLOW (Overflow) */
        #define GPT2_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 11) /* GPT2 COUNTER OVERFLOW (Overflow) */
        #define VECTOR_NUMBER_SCI6_RXI ((IRQn_Type) 12) /* SCI6 RXI (Received data full) */
        #define SCI6_RXI_IRQn          ((IRQn_Type) 12) /* SCI6 RXI (Received data full) */
        #define VECTOR_NUMBER_SCI6_TXI ((IRQn_Type) 13) /* SCI6 TXI (Transmit data empty) */
        #define SCI6_TXI_IRQn          ((IRQn_Type) 13) /* SCI6 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_SCI6_TEI ((IRQn_Type) 14) /* SCI6 TEI (Transmit end) */
        #define SCI6_TEI_IRQn          ((IRQn_Type) 14) /* SCI6 TEI (Transmit end) */
        #define VECTOR_NUMBER_SCI6_ERI ((IRQn_Type) 15) /* SCI6 ERI (Receive error) */
        #define SCI6_ERI_IRQn          ((IRQn_Type) 15) /* SCI6 ERI (Receive error) */
        #define VECTOR_NUMBER_SCI3_RXI ((IRQn_Type) 16) /* SCI3 RXI (Received data full) */
        #define SCI3_RXI_IRQn          ((IRQn_Type) 16) /* SCI3 RXI (Received data full) */
        #define VECTOR_NUMBER_SCI3_TXI ((IRQn_Type) 17) /* SCI3 TXI (Transmit data empty) */
        #define SCI3_TXI_IRQn          ((IRQn_Type) 17) /* SCI3 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_SCI3_TEI ((IRQn_Type) 18) /* SCI3 TEI (Transmit end) */
        #define SCI3_TEI_IRQn          ((IRQn_Type) 18) /* SCI3 TEI (Transmit end) */
        #define VECTOR_NUMBER_SCI3_ERI ((IRQn_Type) 19) /* SCI3 ERI (Receive error) */
        #define SCI3_ERI_IRQn          ((IRQn_Type) 19) /* SCI3 ERI (Receive error) */
        #define VECTOR_NUMBER_CAN0_ERROR ((IRQn_Type) 20) /* CAN0 ERROR (Error interrupt) */
        #define CAN0_ERROR_IRQn          ((IRQn_Type) 20) /* CAN0 ERROR (Error interrupt) */
        #define VECTOR_NUMBER_CAN0_MAILBOX_RX ((IRQn_Type) 21) /* CAN0 MAILBOX RX (Reception complete interrupt) */
        #define CAN0_MAILBOX_RX_IRQn          ((IRQn_Type) 21) /* CAN0 MAILBOX RX (Reception complete interrupt) */
        #define VECTOR_NUMBER_CAN0_MAILBOX_TX ((IRQn_Type) 22) /* CAN0 MAILBOX TX (Transmission complete interrupt) */
        #define CAN0_MAILBOX_TX_IRQn          ((IRQn_Type) 22) /* CAN0 MAILBOX TX (Transmission complete interrupt) */
        #define VECTOR_NUMBER_CAN0_FIFO_RX ((IRQn_Type) 23) /* CAN0 FIFO RX (Receive FIFO interrupt) */
        #define CAN0_FIFO_RX_IRQn          ((IRQn_Type) 23) /* CAN0 FIFO RX (Receive FIFO interrupt) */
        #define VECTOR_NUMBER_CAN0_FIFO_TX ((IRQn_Type) 24) /* CAN0 FIFO TX (Transmit FIFO interrupt) */
        #define CAN0_FIFO_TX_IRQn          ((IRQn_Type) 24) /* CAN0 FIFO TX (Transmit FIFO interrupt) */
        #define VECTOR_NUMBER_SCI7_RXI ((IRQn_Type) 25) /* SCI7 RXI (Received data full) */
        #define SCI7_RXI_IRQn          ((IRQn_Type) 25) /* SCI7 RXI (Received data full) */
        #define VECTOR_NUMBER_SCI7_TXI ((IRQn_Type) 26) /* SCI7 TXI (Transmit data empty) */
        #define SCI7_TXI_IRQn          ((IRQn_Type) 26) /* SCI7 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_SCI7_TEI ((IRQn_Type) 27) /* SCI7 TEI (Transmit end) */
        #define SCI7_TEI_IRQn          ((IRQn_Type) 27) /* SCI7 TEI (Transmit end) */
        #define VECTOR_NUMBER_SCI7_ERI ((IRQn_Type) 28) /* SCI7 ERI (Receive error) */
        #define SCI7_ERI_IRQn          ((IRQn_Type) 28) /* SCI7 ERI (Receive error) */
        #define VECTOR_NUMBER_ICU_IRQ10 ((IRQn_Type) 29) /* ICU IRQ10 (External pin interrupt 10) */
        #define ICU_IRQ10_IRQn          ((IRQn_Type) 29) /* ICU IRQ10 (External pin interrupt 10) */
        #define VECTOR_NUMBER_ICU_IRQ11 ((IRQn_Type) 30) /* ICU IRQ11 (External pin interrupt 11) */
        #define ICU_IRQ11_IRQn          ((IRQn_Type) 30) /* ICU IRQ11 (External pin interrupt 11) */
        #define VECTOR_NUMBER_ICU_IRQ13 ((IRQn_Type) 31) /* ICU IRQ13 (External pin interrupt 13) */
        #define ICU_IRQ13_IRQn          ((IRQn_Type) 31) /* ICU IRQ13 (External pin interrupt 13) */
        #define VECTOR_NUMBER_ICU_IRQ9 ((IRQn_Type) 32) /* ICU IRQ9 (External pin interrupt 9) */
        #define ICU_IRQ9_IRQn          ((IRQn_Type) 32) /* ICU IRQ9 (External pin interrupt 9) */
        #define VECTOR_NUMBER_SCI4_RXI ((IRQn_Type) 33) /* SCI4 RXI (Received data full) */
        #define SCI4_RXI_IRQn          ((IRQn_Type) 33) /* SCI4 RXI (Received data full) */
        #define VECTOR_NUMBER_SCI4_TXI ((IRQn_Type) 34) /* SCI4 TXI (Transmit data empty) */
        #define SCI4_TXI_IRQn          ((IRQn_Type) 34) /* SCI4 TXI (Transmit data empty) */
        #define VECTOR_NUMBER_SCI4_TEI ((IRQn_Type) 35) /* SCI4 TEI (Transmit end) */
        #define SCI4_TEI_IRQn          ((IRQn_Type) 35) /* SCI4 TEI (Transmit end) */
        #define VECTOR_NUMBER_SCI4_ERI ((IRQn_Type) 36) /* SCI4 ERI (Receive error) */
        #define SCI4_ERI_IRQn          ((IRQn_Type) 36) /* SCI4 ERI (Receive error) */
        #define VECTOR_NUMBER_EDMAC0_EINT ((IRQn_Type) 37) /* EDMAC0 EINT (EDMAC 0 interrupt) */
        #define EDMAC0_EINT_IRQn          ((IRQn_Type) 37) /* EDMAC0 EINT (EDMAC 0 interrupt) */
        #define VECTOR_NUMBER_SSI0_RXI ((IRQn_Type) 38) /* SSI0 RXI (Receive data full) */
        #define SSI0_RXI_IRQn          ((IRQn_Type) 38) /* SSI0 RXI (Receive data full) */
        #define VECTOR_NUMBER_SSI0_INT ((IRQn_Type) 39) /* SSI0 INT (Error interrupt) */
        #define SSI0_INT_IRQn          ((IRQn_Type) 39) /* SSI0 INT (Error interrupt) */
        #endif /* VECTOR_DATA_H */