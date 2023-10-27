/* generated common source file - do not edit */
#include "common_data.h"
const uint8_t DRW_INT_IPL = (2);
            d2_device *   d2_handle0;
ioport_instance_ctrl_t g_ioport_ctrl;
const ioport_instance_t g_ioport =
        {
            .p_api = &g_ioport_on_ioport,
            .p_ctrl = &g_ioport_ctrl,
            .p_cfg = &g_bsp_pin_cfg,
        };
void g_common_init(void) {
}
