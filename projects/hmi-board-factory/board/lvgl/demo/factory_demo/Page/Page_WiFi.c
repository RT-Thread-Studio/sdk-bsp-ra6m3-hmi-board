#include "../DisplayPrivate.h"
#define DBG_TAG "page wifi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
/*导出页面*/
PAGE_EXPORT(WiFi);
typedef struct
{
    const char *text;
    const uint8_t pageID;
    lv_obj_t *btn;
    lv_obj_t *line;
} ListBtn_Typedef;

static lv_anim_timeline_t *PageAnimTimeLine = NULL;
static lv_anim_timeline_t *MsgAnimTimeLine = NULL;
static lv_anim_timeline_t *KeyBoardAnimTimeLine = NULL;
static lv_obj_t *list1;
static lv_obj_t *Cont;
static lv_obj_t *Title;

static lv_obj_t *MsgBg;
static lv_obj_t *MsgRect;
static lv_obj_t *MsgText;
static lv_obj_t *MsgKeyBoard;
char Wifi_Ssid[64];
char Wifi_Pwd[64];
static uint8_t isKeyBoardHide = 1;

static void Msg_Create(lv_obj_t *par, const char *name);
static void MsgAnim_Create(void);
static void MsgAnim_Play(bool playback);
static void KeyBoardAnim_Play(bool playback);

void wifi_join_event(int ret)
{
    LOG_I("WiFi_Join ret:[%d]", ret);
    if (ret == -RT_EINVAL)
    {
        LOG_W("WIFI SSID is null or too lang");
        lv_label_set_text_fmt(MsgText, "%s connect failed!", Wifi_Ssid);
    }
    else if (ret == -RT_ERROR)
    {
        LOG_W("wifi connect failed!");
        lv_label_set_text_fmt(MsgText, "%s connect failed!", Wifi_Ssid);
    }
    else if (ret == -RT_ENOMEM)
    {
        LOG_W("wifi connect can not complete");
        lv_label_set_text_fmt(MsgText, "%s connect failed!", Wifi_Ssid);
    }
    else if (ret == RT_EOK)
    {
        LOG_I("wifi connect success ");

        lv_label_set_text_fmt(MsgText, "%s connect success!", Wifi_Ssid);
    }
}

static void event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
        const char *s = lv_list_get_btn_text(list1, obj);
        LV_LOG_USER("Clicked: %s", s);
        lv_label_set_text(MsgText, s);
        MsgAnim_Play(false);
    }
}

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
        WiFi_Scan();
    }
}

static void close_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Clicked: Msg Close\n");
        if (isKeyBoardHide)
            MsgAnim_Play(true);
        else
        {
            KeyBoardAnim_Play(true);
            isKeyBoardHide = 1;
        }
    }
}

static void pwd_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED && isKeyBoardHide)
    {
        LV_LOG_USER("Clicked: Msg LV_EVENT_CLICKED\n");
        KeyBoardAnim_Play(false);
        isKeyBoardHide = 0;
    }
    else if (code == LV_EVENT_VALUE_CHANGED)
    {
        LV_LOG_USER("Clicked: Msg LV_EVENT_VALUE_CHANGED %s\n", lv_textarea_get_text(obj));
    }
    else if (code == LV_EVENT_CANCEL)
    {
        LV_LOG_USER("Clicked: Msg LV_EVENT_KEY\n");
        KeyBoardAnim_Play(true);
        isKeyBoardHide = 1;
    }
    else if (code == LV_EVENT_READY)
    {
        LV_LOG_USER("Clicked: Msg LV_EVENT_KEY %d\n");
        sprintf(Wifi_Ssid, "%s", lv_label_get_text(MsgText));
        sprintf(Wifi_Pwd, "%s", lv_textarea_get_text(obj));
        LOG_I("ssid:[%s]", Wifi_Ssid);
        LOG_I("password:[%s]", Wifi_Pwd);
        lv_label_set_text_fmt(MsgText, "%s connecting..", Wifi_Ssid);
        if (WiFi_Join(Wifi_Ssid, Wifi_Pwd))
        {
            lv_label_set_text_fmt(MsgText, "%s connect failed!", Wifi_Ssid);
        }
        KeyBoardAnim_Play(true);
        isKeyBoardHide = 1;
    }
}

static void List_Create(lv_obj_t *par)
{
    /*Create a list*/
    list1 = lv_list_create(par);
    lv_obj_set_size(list1, WINDOW_WIDTH, WINDOW_HEIGHT - TITLE_HEIGHT);
    lv_obj_center(list1);
    lv_obj_set_style_radius(list1, 0, LV_PART_MAIN);
    lv_obj_add_flag(list1, LV_OBJ_FLAG_EVENT_BUBBLE); // Propagate the events to the parent too

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

void WIFI_Add_List(char *ssid)
{
    lv_obj_t *obj = lv_list_add_btn(list1, LV_SYMBOL_WIFI, ssid);
    lv_obj_t *label = lv_obj_get_child(obj, 1);
    lv_obj_add_event_cb(obj, event_handler, LV_EVENT_CLICKED, NULL);
    lv_label_set_long_mode(label, LV_LABEL_LONG_DOT);
}

void WIFI_List_Clear(void)
{
    lv_obj_clean(list1);
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
    lv_obj_set_size(rect, 250, 120);
    lv_obj_set_style_bg_color(rect, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
    lv_obj_clear_flag(rect, LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_set_style_border_side(rect, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT, LV_PART_MAIN);
    lv_obj_set_style_radius(rect, 10, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(rect);
    lv_label_set_text(label, name);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
    LV_LOG_USER("[%s]", name);
    MsgText = label;
    MsgRect = rect;

    lv_obj_t *pwd_ta = lv_textarea_create(rect);
    lv_textarea_set_text(pwd_ta, "");
    lv_textarea_set_password_mode(pwd_ta, true);
    lv_textarea_set_one_line(pwd_ta, true);
    lv_obj_set_width(pwd_ta, lv_pct(70));
    lv_obj_align(pwd_ta, LV_ALIGN_BOTTOM_LEFT, 0, -10);
    lv_obj_add_event_cb(pwd_ta, pwd_event_handler, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(pwd_ta, pwd_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(pwd_ta, pwd_event_handler, LV_EVENT_CANCEL, NULL);
    lv_obj_add_event_cb(pwd_ta, pwd_event_handler, LV_EVENT_READY, NULL);
    /*Create a label and position it above the text box*/
    lv_obj_t *pwd_label = lv_label_create(rect);
    lv_label_set_text(pwd_label, "Password:");
    lv_obj_align_to(pwd_label, pwd_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

    lv_obj_t *rbtn = lv_btn_create(rect);
    lv_obj_align(rbtn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_set_style_border_width(rbtn, 0, LV_PART_MAIN);
    lv_obj_set_size(rbtn, 50, 30);
    lv_obj_set_style_bg_color(rbtn, lv_color_make(0x99, 0xcc, 0xff), LV_PART_MAIN);
    lv_obj_add_event_cb(rbtn, close_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *rlabel = lv_label_create(rbtn);
    lv_label_set_text(rlabel, LV_SYMBOL_LEFT);
    lv_obj_center(rlabel);

    lv_obj_t *kb = lv_keyboard_create(par);
    lv_keyboard_set_textarea(kb, pwd_ta);
    MsgKeyBoard = kb;
}

static void KsyBoardAnim_Create()
{
    int32_t last_y = lv_obj_get_y(MsgKeyBoard);
    lv_obj_set_y(MsgKeyBoard, WINDOW_HEIGHT);
    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, MsgKeyBoard);
    lv_anim_set_values(&a1, WINDOW_HEIGHT, last_y);
    lv_anim_set_early_apply(&a1, false);
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a1, lv_anim_path_ease_in_out);
    lv_anim_set_time(&a1, 200);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, MsgRect);
    lv_anim_set_values(&a2, 0, -60);
    lv_anim_set_early_apply(&a2, false);
    lv_anim_set_exec_cb(&a2, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a2, lv_anim_path_ease_in_out);
    lv_anim_set_time(&a2, 200);

    KeyBoardAnimTimeLine = lv_anim_timeline_create();
    lv_anim_timeline_add(KeyBoardAnimTimeLine, 0, &a1);
    lv_anim_timeline_add(KeyBoardAnimTimeLine, 0, &a2);
}

static void KeyBoardAnim_Play(bool playback)
{
    lv_anim_timeline_set_reverse(KeyBoardAnimTimeLine, playback);
    lv_anim_timeline_start(KeyBoardAnimTimeLine);
    // PageDelay(lv_anim_timeline_get_playtime(MsgAnimTimeLine));
}

static void MsgAnim_Create()
{
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
}

static void Cont_Create(lv_obj_t *par)
{
    lv_obj_t *obj = lv_obj_create(par);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_size(obj, WINDOW_WIDTH, WINDOW_HEIGHT - TITLE_HEIGHT);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(obj, LV_COLOR_BLACK, LV_PART_MAIN);
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
    lv_label_set_text(label, "WiFi");
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

    PageAnimTimeLine = lv_anim_timeline_create();
    lv_anim_timeline_add(PageAnimTimeLine, 0, &a1);
    lv_anim_timeline_add(PageAnimTimeLine, 0, &a2);
}

static void PageAnim_Play(bool playback)
{
    lv_anim_timeline_set_reverse(PageAnimTimeLine, playback);
    lv_anim_timeline_start(PageAnimTimeLine);
    PageDelay(lv_anim_timeline_get_playtime(PageAnimTimeLine));
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
    KsyBoardAnim_Create();
    PageAnim_Create();
    PageAnim_Play(false);
    WiFi_Scan();
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
    lv_anim_timeline_del(PageAnimTimeLine);
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
