
#include "../DisplayPrivate.h"
#include "lv_file_explorer.h"
#define DBG_TAG "page sdcard"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*导出页面*/
PAGE_EXPORT(SDCard);

typedef struct
{
    const char *text;
    const uint8_t pageID;
    lv_obj_t *btn;
    lv_obj_t *line;
} ListBtn_Typedef;

static ListBtn_Typedef btnGrp[] =
    {
        {"Time.txt", PAGE_NONE},
        {"Backlight.wav", PAGE_NONE},
        {"Wuhu.avi", PAGE_NONE},
        {"Lala.mp4", PAGE_NONE},
        {"Yuele.mp3", PAGE_NONE},
        {"Rio.jpg", PAGE_NONE},
        {"Wotule.png", PAGE_NONE}};
static lv_anim_timeline_t *anim_timeline = NULL;
static lv_anim_timeline_t *MsgAnimTimeLine = NULL;
static lv_obj_t *list1;
static lv_obj_t *Cont;
static lv_obj_t *Title;

static lv_obj_t *MsgBg;
static lv_obj_t *MsgRect;
static lv_obj_t *MsgText;

static lv_obj_t *file_explorer_panel;

static void Msg_Create(lv_obj_t *par, const char *name);
static void MsgAnim_Create(void);
static void MsgAnim_Play(bool playback);
static void File_Explorer_Create(lv_obj_t *par);

char file_name[128];

static void return_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Clicked: return\n");
        PM_Pop(Page);
    }
}

static void refresh_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Clicked: refresh");
    }
}

static void close_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Clicked: Msg Close\n");
        MsgAnim_Play(true);
    }
}

int is_avi_file(const char *filename)
{
    char *extension = strrchr(filename, '.');
    if (extension != NULL && strcmp(extension + 1, "avi") == 0)
    {
        LV_LOG_USER("%s is a avi file", filename);
        return 1;
    }
    else
    {
        LV_LOG_USER("%s is not a avi file", filename);
        return 0;
    }
}

static void file_explorer_event_cb(lv_event_t *e)
{
    const char *s = lv_file_explorer_get_selected_file_name(file_explorer_panel);
    const char *dir = lv_file_explorer_get_current_path(file_explorer_panel);
    LOG_I("%s", s);
    LOG_I("%s", dir);
    LV_LOG_USER("Clicked: Msg Close %d %s\n", code, s);
    if (is_avi_file(s))
    {
        sprintf(file_name, "%s%s", dir, s);
        PM_Push(Page, PAGE_VideoPlayer);
    }
}

static void List_Create(lv_obj_t *par)
{
    File_Explorer_Create(par);

    lv_obj_t *rbtn = lv_btn_create(par);
    lv_obj_align(rbtn, LV_ALIGN_BOTTOM_RIGHT, -10, -70);
    lv_obj_set_style_border_width(rbtn, 0, LV_PART_MAIN);
    lv_obj_set_size(rbtn, 50, 50);
    lv_obj_set_style_bg_color(rbtn, lv_color_make(0x99, 0xcc, 0xff), LV_PART_MAIN);
    lv_obj_add_event_cb(rbtn, return_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *rlabel = lv_label_create(rbtn);
    lv_label_set_text(rlabel, LV_SYMBOL_LEFT);
    lv_obj_center(rlabel);

    lv_obj_t *fbtn = lv_btn_create(par);
    lv_obj_align(fbtn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_set_style_border_width(fbtn, 0, LV_PART_MAIN);
    lv_obj_set_size(fbtn, 50, 50);
    lv_obj_set_style_bg_color(fbtn, lv_color_make(0x99, 0xcc, 0xff), LV_PART_MAIN);
    lv_obj_add_event_cb(fbtn, refresh_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *flabel = lv_label_create(fbtn);
    lv_label_set_text(flabel, LV_SYMBOL_REFRESH);
    lv_obj_center(flabel);
}

static void File_Explorer_Create(lv_obj_t *par)
{

    file_explorer_panel = lv_file_explorer_create(par);
    // lv_obj_set_style_border_width(file_explorer_panel, 5, LV_PART_MAIN);
    lv_obj_set_size(file_explorer_panel, WINDOW_WIDTH, WINDOW_HEIGHT - TITLE_HEIGHT);
    lv_obj_align(file_explorer_panel, LV_ALIGN_CENTER, 0, 0);

    lv_file_explorer_set_sort(file_explorer_panel, LV_EXPLORER_SORT_NONE);
    lv_file_explorer_open_dir(file_explorer_panel, "/");

    lv_obj_add_event_cb(file_explorer_panel, file_explorer_event_cb, LV_EVENT_VALUE_CHANGED, par);
}

static void Msg_Create(lv_obj_t *par, const char *name)
{
    lv_obj_t *bg = lv_obj_create(par);
    lv_obj_align(bg, LV_ALIGN_BOTTOM_MID, 0, 0);
    // lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(bg, 0, LV_PART_MAIN);
    lv_obj_set_size(bg, WINDOW_WIDTH, WINDOW_HEIGHT - TITLE_HEIGHT);
    lv_obj_set_style_bg_color(bg, LV_COLOR_GRAY, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bg, 0, LV_PART_MAIN);
    lv_obj_clear_flag(bg, LV_OBJ_FLAG_SCROLLABLE);
    MsgBg = bg;

    lv_obj_t *rect = lv_obj_create(par);
    lv_obj_align(rect, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(rect, 5, LV_PART_MAIN);
    lv_obj_set_size(rect, 200, 150);
    lv_obj_set_style_bg_color(rect, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
    lv_obj_clear_flag(rect, LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_set_style_border_side(rect, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT, LV_PART_MAIN);
    lv_obj_set_style_radius(rect, 10, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(rect);
    lv_label_set_text(label, name);
    lv_obj_center(label);
    MsgText = label;
    MsgRect = rect;

    lv_obj_t *rbtn = lv_btn_create(rect);
    lv_obj_align(rbtn, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_border_width(rbtn, 0, LV_PART_MAIN);
    lv_obj_set_size(rbtn, 50, 30);
    lv_obj_set_style_bg_color(rbtn, lv_color_make(0x99, 0xcc, 0xff), LV_PART_MAIN);
    lv_obj_add_event_cb(rbtn, close_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *rlabel = lv_label_create(rbtn);
    lv_label_set_text(rlabel, LV_SYMBOL_LEFT);
    lv_obj_center(rlabel);
}

static void MsgAnim_Create()
{
    int32_t tile_rey = lv_obj_get_y(MsgRect);

    lv_obj_set_y(MsgRect, WINDOW_HEIGHT);
    lv_obj_set_y(MsgBg, WINDOW_HEIGHT);
    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, MsgBg);
    lv_anim_set_values(&a1, WINDOW_HEIGHT, 0);
    lv_anim_set_early_apply(&a1, false);
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a1, lv_anim_path_ease_in_out);
    lv_anim_set_time(&a1, 300);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, MsgRect);
    lv_anim_set_values(&a2, WINDOW_HEIGHT, 0);
    lv_anim_set_early_apply(&a2, false);
    lv_anim_set_exec_cb(&a2, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a2, lv_anim_path_ease_in_out);
    lv_anim_set_time(&a2, 300);

    MsgAnimTimeLine = lv_anim_timeline_create();
    lv_anim_timeline_add(MsgAnimTimeLine, 0, &a1);
    lv_anim_timeline_add(MsgAnimTimeLine, 0, &a2);
}

static void MsgAnim_Play(bool playback)
{
    if (playback)
        lv_obj_add_flag(MsgBg, LV_OBJ_FLAG_EVENT_BUBBLE);
    else
        lv_obj_clear_flag(MsgBg, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_anim_timeline_set_reverse(MsgAnimTimeLine, playback);
    lv_anim_timeline_start(MsgAnimTimeLine);
    // PageDelay(lv_anim_timeline_get_playtime(MsgAnimTimeLine));
}

static void Cont_Create(lv_obj_t *par)
{
    lv_obj_t *obj = lv_obj_create(par);
    // lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_size(obj, WINDOW_WIDTH, WINDOW_HEIGHT - TITLE_HEIGHT);
    lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(obj, LV_COLOR_BLACK, LV_PART_MAIN);
    lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE); // Propagate the events to the parent too
    // lv_obj_add_event_cb(obj, (lv_event_cb_t)ContApps_EventHandler, LV_EVENT_GESTURE, NULL);
    Cont = obj;
}

static void Title_Create(lv_obj_t *par)
{
    lv_obj_t *obj = lv_obj_create(par);
    lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_size(obj, TITLE_WIDTH, TITLE_HEIGHT);
    lv_obj_set_style_bg_color(obj, lv_color_make(0xcc, 0xcc, 0xcc), LV_PART_MAIN);
    lv_obj_set_scroll_dir(obj, LV_DIR_VER);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE); // Propagate the events to the parent too
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *label = lv_label_create(obj);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_size(label, TITLE_WIDTH, TITLE_HEIGHT);
    // lv_obj_set_style_text_font(label, &TITLE_FONT, 0);
    lv_label_set_text(label, "SDCard");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_color(label, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);

    Title = obj;
}

static void PageAnim_Create()
{
    int32_t cont_rey = lv_obj_get_y(Cont);
    int32_t tile_rey = lv_obj_get_y(Title);

    lv_obj_set_y(Cont, WINDOW_HEIGHT - TITLE_HEIGHT * 2);
    lv_obj_set_y(Title, -TITLE_HEIGHT * 2);

    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, Cont);
    lv_anim_set_values(&a1, WINDOW_HEIGHT - TITLE_HEIGHT * 2, cont_rey);
    lv_anim_set_early_apply(&a1, false);
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a1, lv_anim_path_ease_in_out);
    lv_anim_set_time(&a1, 300);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, Title);
    lv_anim_set_values(&a2, -TITLE_HEIGHT * 2, tile_rey);
    lv_anim_set_early_apply(&a2, false);
    lv_anim_set_exec_cb(&a2, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a2, lv_anim_path_ease_in_out);
    lv_anim_set_time(&a2, 300);

    anim_timeline = lv_anim_timeline_create();
    lv_anim_timeline_add(anim_timeline, 0, &a1);
    lv_anim_timeline_add(anim_timeline, 0, &a2);
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
    Cont_Create(appWindow);
    Title_Create(appWindow);
    List_Create(Cont);
    Msg_Create(appWindow, "");
    MsgAnim_Create();
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
    lv_anim_timeline_del(MsgAnimTimeLine);
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
