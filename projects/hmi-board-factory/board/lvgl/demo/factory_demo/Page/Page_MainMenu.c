
#include "../DisplayPrivate.h"

PAGE_EXPORT(MainMenu);

static lv_obj_t *contApps;
static lv_anim_timeline_t *anim_timeline = NULL;

LV_IMG_DECLARE(IMG_FileExplorer);
LV_IMG_DECLARE(IMG_LEDAndBtn);
LV_IMG_DECLARE(IMG_Recorder);
LV_IMG_DECLARE(IMG_SDCard);
LV_IMG_DECLARE(IMG_WiFi);
LV_IMG_DECLARE(IMG_ETH);
LV_IMG_DECLARE(IMG_Game2048);
LV_IMG_DECLARE(IMG_Info);
typedef struct
{
    const void *src_img;
    const char *name;
    const uint8_t pageID;
    int bg_color;
    lv_obj_t *obj;
} AppICON_TypeDef;

#define APP_DEF(name, color)                         \
    {                                                \
        &IMG_##name, #name, PAGE_##name, color, NULL \
    }
#define APP_ICON_SIZE 90
#define APP_ICON_ANIM_TIME 100
#define MENU_ROW 2
#define MENU_COL 4

static AppICON_TypeDef AppICON_Grp[] =
    {
        APP_DEF(LEDAndBtn, 0xffb84e),
        APP_DEF(SDCard, 0xffb84e),
        APP_DEF(WiFi, 0xffb84e),
        APP_DEF(ETH, 0xffb84e),
        APP_DEF(Game2048, 0xffb84e),
        APP_DEF(Info, 0xffb84e),
};

static void AppClickAnim(lv_obj_t *img, bool ispress)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, img);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_zoom);
    lv_anim_set_values(&a, lv_img_get_zoom(img), ispress ? 190 : LV_IMG_ZOOM_NONE);
    lv_anim_set_time(&a, APP_ICON_ANIM_TIME);

    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);

    lv_anim_start(&a);
}

static void AppICON_EventHandler(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_current_target(e);
    lv_obj_t *img = lv_obj_get_child(obj, NULL);

    lv_event_code_t code = lv_event_get_code(e);
    AppICON_TypeDef *appIcon = (AppICON_TypeDef *)lv_obj_get_user_data(obj);

    if (code == LV_EVENT_PRESSED)
    {
        AppClickAnim(img, true);
    }
    else if (code == LV_EVENT_RELEASED || code == LV_EVENT_PRESS_LOST)
    {
        AppClickAnim(img, false);
    }
    else if (code == LV_EVENT_SHORT_CLICKED)
    {
        uint8_t pageID = appIcon->pageID;

        if (pageID == PAGE_NONE)
            return;

        if (pageID == PAGE_LEDAndBtn)
        {
            PM_Push(Page, PAGE_LEDAndBtn);
        }
        else if (pageID == PAGE_ETH)
        {
            PM_Push(Page, PAGE_ETH);
        }
        else if (pageID == PAGE_SDCard)
        {
            PM_Push(Page, PAGE_SDCard);
        }
        else if (pageID == PAGE_Game2048)
        {
            PM_Push(Page, PAGE_Game2048);
        }
        else if (pageID == PAGE_WiFi)
        {
            PM_Push(Page, PAGE_WiFi);
        }
        else if (pageID == PAGE_Info)
        {
            PM_Push(Page, PAGE_Info);
        }
    }
}

static void AppICON_Create(lv_obj_t *par)
{

    int label_h = 16;

    for (int i = 0; i < __Sizeof(AppICON_Grp); i++)
    {
        lv_obj_t *obj_vir = lv_obj_create(par);
        lv_obj_set_style_border_width(obj_vir, 0, LV_PART_MAIN);
        lv_obj_set_size(obj_vir, APP_ICON_SIZE, APP_ICON_SIZE);
        // lv_obj_set_drag_parent(obj_vir, true);
        // lv_obj_add_event_cb(obj_vir, (lv_event_cb_t)AppICON_EventHandler, LV_EVENT_ALL, NULL);
        lv_obj_set_user_data(obj_vir, &(AppICON_Grp[i]));
        lv_obj_clear_flag(obj_vir, LV_OBJ_FLAG_SCROLLABLE);
        int col = 4;
        lv_coord_t interval_pixel_0 = (APP_WIN_WIDTH - APP_ICON_SIZE * col) / (col + 1);
        lv_coord_t interval_pixel_1 = interval_pixel_0 + APP_ICON_SIZE;
        lv_obj_align(
            obj_vir,
            LV_ALIGN_CENTER,
            -100,
            i * interval_pixel_1);

        lv_obj_set_style_bg_color(obj_vir, lv_color_hex(AppICON_Grp[i].bg_color), LV_PART_MAIN);
        lv_obj_add_event_cb(obj_vir, (lv_event_cb_t)AppICON_EventHandler, LV_EVENT_ALL, NULL);

        lv_obj_t *img = lv_img_create(obj_vir);
        lv_img_set_src(img, AppICON_Grp[i].src_img);
        lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

        lv_obj_t *label = lv_label_create(par);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
        lv_obj_set_width(label, 150);
        lv_label_set_text(label, AppICON_Grp[i].name);
        lv_obj_align_to(label, obj_vir, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
        lv_obj_set_style_text_color(label, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);

        AppICON_Grp[i].obj = obj_vir;
    }
}

static void ContApps_EventHandler(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_current_target(e);
    lv_event_code_t code = lv_event_get_code(e);
    LV_LOG("lv_indev_get_gesture_ code %d\n", code);
    lv_indev_t *indev = lv_indev_get_act();
    if (indev == NULL)
        return;
    lv_point_t vect;
    lv_indev_get_vect(indev, &vect);

    lv_coord_t x = lv_obj_get_x(obj) + vect.x;
    lv_coord_t y = lv_obj_get_y(obj) + vect.y;
    lv_obj_set_pos(obj, x, y);
}

static void ContApps_Create(lv_obj_t *par)
{
    lv_obj_t *obj = lv_obj_create(par);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(obj, 480, 272);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, LV_COLOR_WHITE, LV_PART_MAIN);
    lv_obj_set_scroll_dir(obj, LV_DIR_VER);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE); // Propagate the events to the parent too

    contApps = obj;
}

static void PageAnim_Create()
{
    int32_t cont_rey = lv_obj_get_y(contApps);

    lv_obj_set_y(contApps, WINDOW_HEIGHT);

    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, contApps);
    lv_anim_set_values(&a1, WINDOW_HEIGHT, cont_rey);
    lv_anim_set_early_apply(&a1, false);
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a1, lv_anim_path_ease_out);
    lv_anim_set_time(&a1, 300);

    anim_timeline = lv_anim_timeline_create();
    lv_anim_timeline_add(anim_timeline, 0, &a1);
}

static void PageAnim_Play(bool playback)
{
    lv_anim_timeline_set_reverse(anim_timeline, playback);
    lv_anim_timeline_start(anim_timeline);
    PageDelay(lv_anim_timeline_get_playtime(anim_timeline));
}

/**
 * @brief  页面初始化事件
 * @param  无
 * @retval 无
 */
static void Setup()
{
    /*将此页面移到前台*/
    lv_obj_move_foreground(appWindow);

    ContApps_Create(appWindow);
    // ImgAppShadow_Create(appWindow);
    AppICON_Create(contApps);
    PageAnim_Create();
    PageAnim_Play(false);
}

/**
 * @brief  页面退出事件
 * @param  无
 * @retval 无
 */
static void Exit()
{
    PageAnim_Play(true);
    lv_anim_timeline_del(anim_timeline);
    lv_obj_clean(appWindow);
}

/**
 * @brief  页面事件
 * @param  obj:发生事件的对象
 * @param  event:事件编号
 * @retval 无
 */
static void Event(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_PRESSING)
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir == LV_DIR_RIGHT)
        {
            LV_LOG("Page->Pop()\n");
            PM_Pop(Page);
        }
    }
}
