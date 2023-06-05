#ifndef __DISPLAYPRIVATE_H
#define __DISPLAYPRIVATE_H
#ifdef __cplusplus

extern "C"
{

#endif

    void Display_Init();
    void Display_Update();

#ifdef __cplusplus
}
#endif

#include "CommonMacro.h"
/*Page*/
#include "PageManager.h"
/*LVGL*/
#include "lvgl.h"
// #include "lv_obj_ext_func.h"
// #include "lv_theme_conf.h"

#include <rtthread.h>
#include "rtdevice.h"
#include "hal_data.h"
#include <rthw.h>

#include <string.h>
#include <stdio.h>

#include "wlan_dev.h"
#include "wlan_cfg.h"
#include "wlan_mgnt.h"
#include "wlan_prot.h"

#include <netdev_ipaddr.h>
#include <netdev.h>

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 272
#define TITLE_HEIGHT 20
#define TITLE_WIDTH 480
#define TITLE_FONT (lv_font_montserrat_20)
extern PageManager_t page;
typedef enum
{
    /*保留*/
    PAGE_NONE,
    /*用户页面*/
    PAGE_DemoLogo,
    PAGE_MainMenu,
    PAGE_LEDAndBtn,
    PAGE_SDCard,
    PAGE_WiFi,
    PAGE_ETH,
    PAGE_Game2048,
    PAGE_VideoPlayer,
    PAGE_Info,
    /*保留*/
    PAGE_MAX
} Page_Type;

void PageDelay(uint32_t ms);
void DisplayPage_Init();

#define PAGE_EXPORT(name)                                                         \
    static PageManager_t *Page;                                                   \
    static lv_obj_t *appWindow;                                                   \
    static void Setup();                                                          \
    static void Exit();                                                           \
    static void Event(lv_event_t *e);                                             \
    static void Page_EventHandler(void *obj, uint8_t event)                       \
    {                                                                             \
        if (obj == Page)                                                          \
        {                                                                         \
            switch (event)                                                        \
            {                                                                     \
            case PM_MSG_Setup:                                                    \
                Setup();                                                          \
                break;                                                            \
            case PM_MSG_Exit:                                                     \
                Exit();                                                           \
                break;                                                            \
            case PM_MSG_Loop: /*Loop();*/                                         \
                break;                                                            \
            default:                                                              \
                break;                                                            \
            }                                                                     \
        }                                                                         \
    }                                                                             \
    void PageRegister_##name(PageManager_t *page, uint8_t pageID)                 \
    {                                                                             \
        appWindow = AppWindow_GetObj(pageID);                                     \
        lv_obj_add_event_cb(appWindow, (lv_event_cb_t)Event, LV_EVENT_ALL, NULL); \
        PM_Register(page, pageID, Page_EventHandler, #name);                      \
        Page = page;                                                              \
    }

#define LV_COLOR_WHITE lv_color_make(0xFF, 0xFF, 0xFF)
#define LV_COLOR_SILVER lv_color_make(0xC0, 0xC0, 0xC0)
#define LV_COLOR_GRAY lv_color_make(0x80, 0x80, 0x80)
#define LV_COLOR_BLACK lv_color_make(0x00, 0x00, 0x00)
#define LV_COLOR_RED lv_color_make(0xFF, 0x00, 0x00)
#define LV_COLOR_MAROON lv_color_make(0x80, 0x00, 0x00)
#define LV_COLOR_YELLOW lv_color_make(0xFF, 0xFF, 0x00)
#define LV_COLOR_OLIVE lv_color_make(0x80, 0x80, 0x00)
#define LV_COLOR_LIME lv_color_make(0x00, 0xFF, 0x00)
#define LV_COLOR_GREEN lv_color_make(0x00, 0x80, 0x00)
#define LV_COLOR_CYAN lv_color_make(0x00, 0xFF, 0xFF)
#define LV_COLOR_AQUA LV_COLOR_CYAN
#define LV_COLOR_TEAL lv_color_make(0x00, 0x80, 0x80)
#define LV_COLOR_BLUE lv_color_make(0x00, 0x00, 0xFF)
#define LV_COLOR_NAVY lv_color_make(0x00, 0x00, 0x80)
#define LV_COLOR_MAGENTA lv_color_make(0xFF, 0x00, 0xFF)
#define LV_COLOR_PURPLE lv_color_make(0x80, 0x00, 0x80)
#define LV_COLOR_ORANGE lv_color_make(0xFF, 0xA5, 0x00)

/*AppWindow*/
void AppWindow_Create(lv_obj_t *par);
lv_obj_t *AppWindow_GetObj(uint8_t pageID);
#define APP_WIN_HEIGHT lv_obj_get_height(appWindow)
#define APP_WIN_WIDTH lv_obj_get_width(appWindow)

int WiFi_Scan(void);
void WIFI_List_Clear(void);
void WIFI_Add_List(char *ssid);
int WiFi_Join(const char *ssid, const char *password);
void wifi_join_event(int ret);
#endif
