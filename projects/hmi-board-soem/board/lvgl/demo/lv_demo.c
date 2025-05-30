/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-17     Meco Man      First version
 * 2022-05-10     Meco Man      improve rt-thread initialization process
 */
#include "rtconfig.h"

void lv_user_gui_init(void)
{
    /* display demo; you may replace with your LVGL application at here */
#ifdef BSP_USING_LVGL_VIDEO_DEMO
    extern void lv_video_gui_init(void);
    lv_video_gui_init();
#endif
#ifdef BSP_USING_LVGL_MUSIC_DEMO
    extern void lv_demo_music(void);
    lv_demo_music();
#endif
#ifdef BSP_USING_LVGL_ETHERCAT_DEMO
    extern void lv_ethercat_gui_init(void);
    lv_ethercat_gui_init();
#endif
}
