
#include "../DisplayPrivate.h"

PAGE_EXPORT(DemoLogo);
#define ANIM_TIME 300
#define STANDARDGREY LV_COLOR_MAKE(0x80, 0x80, 0x80)
#define STANDARDWHITE LV_COLOR_MAKE(0xFF, 0xFF, 0xFF)
#define DEEPDGREY LV_COLOR_MAKE(0x33, 0x33, 0x33)
#define ALBUM_SIZE 80
#define ALBUM_ANIM_TIME 100

static const lv_coord_t Btn_Width = 80;
static const lv_coord_t Btn_Height = 30;

static lv_obj_t* Cont;
static lv_obj_t* rect1;
static lv_obj_t* rect2;
static lv_obj_t* label;
static lv_anim_timeline_t* anim_timeline = NULL;

static void Demologo_Create(lv_obj_t* par)
{
    rect1 = lv_obj_create(par);
    lv_obj_set_style_border_width(rect1, 0, LV_PART_MAIN);
    lv_obj_set_size(rect1, 100, 34);
    lv_obj_clear_flag(rect1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(rect1, LV_COLOR_BLACK, LV_PART_MAIN);
    lv_obj_align(rect1, LV_ALIGN_LEFT_MID,-15,0);
    lv_obj_set_style_radius(rect1,0,LV_PART_MAIN);
    lv_obj_add_flag(rect1, LV_OBJ_FLAG_EVENT_BUBBLE);//Propagate the events to the parent too

    rect2 = lv_obj_create(par);
    lv_obj_set_style_border_width(rect2, 0, LV_PART_MAIN);
    lv_obj_set_size(rect2, 380, 34);
    lv_obj_align_to(rect2, rect1, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_obj_clear_flag(rect2, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(rect2, LV_COLOR_GRAY, LV_PART_MAIN);
    lv_obj_set_style_radius(rect2, 0, LV_PART_MAIN);
    lv_obj_add_flag(rect2, LV_OBJ_FLAG_EVENT_BUBBLE);//Propagate the events to the parent too

    label = lv_label_create(par);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_width(label, 150);
    //lv_obj_set_style_text_font(label, &lv_font_montserrat_32, 0);
    lv_label_set_text(label, "Factory Demo");
    lv_obj_align_to(label, rect1, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    lv_obj_set_style_text_color(label, LV_COLOR_BLACK, LV_PART_MAIN);
    lv_obj_add_flag(label, LV_OBJ_FLAG_EVENT_BUBBLE);//Propagate the events to the parent too
}

static void Cont_Create(lv_obj_t* par)
{
    lv_obj_t* obj = lv_obj_create(par);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    //lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_size(obj, WINDOW_WIDTH, WINDOW_HEIGHT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, LV_COLOR_WHITE, LV_PART_MAIN);
    lv_obj_set_scroll_dir(obj, LV_DIR_VER);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);//Propagate the events to the parent too
    //lv_obj_add_event_cb(obj, (lv_event_cb_t)ContApps_EventHandler, LV_EVENT_GESTURE, NULL);
    Cont = obj;
}

static void PageAnim_Create()
{
    int32_t rect1_rex = lv_obj_get_x(rect1);
    int32_t rect2_rex = lv_obj_get_x(rect2);
    int32_t label_rex = lv_obj_get_x(label);

    lv_obj_set_x(rect1, -120);
    lv_obj_set_x(rect2, -420);
    lv_obj_set_x(label, -380);
    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, rect1);
    lv_anim_set_values(&a1, -120, rect1_rex);
    lv_anim_set_early_apply(&a1, false);
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&a1, lv_anim_path_ease_out);
    lv_anim_set_time(&a1, 300);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, rect2);
    lv_anim_set_values(&a2, -420, rect2_rex);
    lv_anim_set_early_apply(&a2, false);
    lv_anim_set_exec_cb(&a2, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&a2, lv_anim_path_ease_out);
    lv_anim_set_time(&a2, 300);

    /* obj2 */
    lv_anim_t a3;
    lv_anim_init(&a3);
    lv_anim_set_var(&a3, label);
    lv_anim_set_values(&a3, -380, rect2_rex+label_rex);
    lv_anim_set_early_apply(&a3, false);
    lv_anim_set_exec_cb(&a3, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_path_cb(&a3, lv_anim_path_ease_in_out);
    lv_anim_set_time(&a3, 300);

    anim_timeline = lv_anim_timeline_create();
    lv_anim_timeline_add(anim_timeline, 0, &a1);
    lv_anim_timeline_add(anim_timeline, 100, &a2);
    lv_anim_timeline_add(anim_timeline, 200, &a3);
}

static void PageAnim_Play(bool playback)
{
    lv_anim_timeline_set_reverse(anim_timeline, playback);
    lv_anim_timeline_start(anim_timeline);
    PageDelay(500);
}

static void Setup()
{
    lv_obj_move_foreground(appWindow);
    Cont_Create(appWindow);
    Demologo_Create(Cont);
    PageAnim_Create();
    PageDelay(100);
    PageAnim_Play(false);
}


static void Exit()
{
    PageAnim_Play(true);
    lv_anim_timeline_del(anim_timeline);
    lv_obj_clean(appWindow);
}


static void Event(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG("Push(PAGE_MainMenu)\n");
        PM_Push(Page, PAGE_MainMenu);
    }
}

