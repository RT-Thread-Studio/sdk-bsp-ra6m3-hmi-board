#include "DisplayPrivate.h"

/*实例化页面调度器*/
PageManager_t page;

/*页面导入*/
#define PAGE_IMPORT(name)                                                       \
    do                                                                          \
    {                                                                           \
        extern void PageRegister_##name(PageManager_t *page_p, uint8_t pageID); \
        PageRegister_##name(&page, PAGE_##name);                                \
    } while (0)

static void page_gestute_event_cb(lv_obj_t *obj, lv_event_t event)
{
    if (event.code == LV_EVENT_GESTURE)
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        PM_EventTransmit(&page, obj, dir);
    }
}

/**
 * @brief  页面初始化
 * @param  无
 * @retval 无
 */
void DisplayPage_Init()
{
    PM_PageManagerInit(&page, PAGE_MAX, 10);
    PAGE_IMPORT(DemoLogo);
    PAGE_IMPORT(MainMenu); // 主菜单
    PAGE_IMPORT(LEDAndBtn);
    PAGE_IMPORT(ETH);
    PAGE_IMPORT(SDCard);
    PAGE_IMPORT(WiFi);
    PAGE_IMPORT(Game2048);
    PAGE_IMPORT(VideoPlayer);
    PAGE_IMPORT(Info);
    // page.Push(PAGE_LEDAndBtn);
    PM_Push(&page, PAGE_DemoLogo);
    lv_obj_add_event_cb(lv_scr_act(), (lv_event_cb_t)page_gestute_event_cb, LV_EVENT_ALL, NULL);
}

/**
 * @brief  显示更新
 * @param  无
 * @retval 无
 */
void Display_Update()
{
    PM_Running(&page);
    // lv_task_handler();
}

/**
 * @brief  页面阻塞延时，保持lvgl更新
 * @param  无
 * @retval 无
 */
void PageDelay(uint32_t ms)
{
    uint32_t lastTime = lv_tick_get();

    while (lv_tick_elaps(lastTime) <= ms)
    {
        lv_task_handler();
        rt_thread_mdelay(LV_DISP_DEF_REFR_PERIOD);
    }
}
