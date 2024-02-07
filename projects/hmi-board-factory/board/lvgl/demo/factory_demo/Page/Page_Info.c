
#include "../DisplayPrivate.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define DBG_TAG "page info"
#define DBG_LVL DBG_LOG

#include <rtdbg.h>

PAGE_EXPORT(Info);


/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t* Cont;
static lv_anim_timeline_t*  PageAnimTimeLine = NULL;

LV_IMG_DECLARE(IMG_QRCode);
LV_IMG_DECLARE(IMG_Logo);


static void return_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    // lv_obj_t *obj = lv_event_get_target(e);

    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Clicked: return\n");
        PM_Pop(Page);
    }
}


static void Info_Create(lv_obj_t* par)
{
	static lv_style_t style;
    lv_style_init(&style);
	lv_style_set_text_align(&style, LV_TEXT_ALIGN_LEFT);
    lv_style_set_text_color(&style, LV_COLOR_BLACK);

	
	lv_obj_t* obj = lv_obj_create(par);
	lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_size(obj, 170, 170);
	lv_obj_align(obj, LV_ALIGN_LEFT_MID, 30, 0);
    lv_obj_set_style_bg_color(obj, LV_COLOR_WHITE, LV_PART_MAIN);
	lv_obj_clear_flag(obj,LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);

	lv_obj_t* img = lv_img_create(obj);
	lv_img_set_src(img, &IMG_QRCode);
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
	
	lv_obj_t* label1 = lv_label_create(par);
    //lv_obj_set_width(label1, 150);
    lv_label_set_text(label1, "HMI-Board");
    lv_obj_align_to(label1, obj, LV_ALIGN_OUT_RIGHT_TOP, 10, 10);
	lv_obj_add_style(label1, &style, LV_PART_MAIN);
	lv_obj_add_flag(label1, LV_OBJ_FLAG_EVENT_BUBBLE);
	
	lv_obj_t* label2 = lv_label_create(par);
    //lv_obj_set_width(label2, 150);
    lv_label_set_text(label2, "RT-Thread 5.0.0");
    lv_obj_align_to(label2, label1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
	lv_obj_add_style(label2, &style, LV_PART_MAIN);
	lv_obj_add_flag(label2, LV_OBJ_FLAG_EVENT_BUBBLE);
	
	lv_obj_t* label3 = lv_label_create(par);
    //lv_obj_set_width(label3, 150);
    lv_label_set_text(label3, "LVGL 8.3");
    lv_obj_align_to(label3, label2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
	lv_obj_add_style(label3, &style, LV_PART_MAIN);
	lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
	lv_obj_t* label4 = lv_label_create(par);
    //lv_obj_set_width(label3, 150);
    lv_label_set_text(label4, "QQ Group ID: 546631962");
    lv_obj_align_to(label4, label3, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
	lv_obj_add_style(label4, &style, LV_PART_MAIN);
	lv_obj_add_flag(label4, LV_OBJ_FLAG_EVENT_BUBBLE);
	
	lv_obj_t* label5 = lv_label_create(par);
	lv_label_set_text(label5, "Welcome to join it");
	lv_obj_align_to(label5, label4, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
	lv_obj_add_style(label5, &style, LV_PART_MAIN);
	lv_obj_add_flag(label5, LV_OBJ_FLAG_EVENT_BUBBLE);
	
	lv_obj_t* label6 = lv_label_create(par);
	lv_label_set_text(label6, "Qr code on the right");
	lv_obj_align_to(label6, label5, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
	lv_obj_add_style(label6, &style, LV_PART_MAIN);
	lv_obj_add_flag(label6, LV_OBJ_FLAG_EVENT_BUBBLE);
	
	lv_obj_t* label7 = lv_label_create(par);
	lv_label_set_text(label7, "https://github.com/RT-Thread-Studio/sdk-bsp-ra6m3-hmi-board");
	lv_obj_align_to(label7, label6, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
	lv_obj_set_width(label7, 250);
	lv_label_set_long_mode(label7, LV_LABEL_LONG_WRAP);
	lv_obj_add_style(label7, &style, LV_PART_MAIN);
	lv_obj_add_flag(label7, LV_OBJ_FLAG_EVENT_BUBBLE);

	lv_obj_t *rbtn = lv_btn_create(par);
    lv_obj_align(rbtn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
    lv_obj_set_style_border_width(rbtn, 0, LV_PART_MAIN);
    lv_obj_set_size(rbtn, 50, 50);
    lv_obj_set_style_bg_color(rbtn, lv_color_make(0x99, 0xcc, 0xff), LV_PART_MAIN);
    lv_obj_add_event_cb(rbtn, return_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *rlabel = lv_label_create(rbtn);
    lv_label_set_text(rlabel, LV_SYMBOL_LEFT);
    lv_obj_center(rlabel);
}


static void Cont_Create(lv_obj_t* par)
{
    lv_obj_t* obj = lv_obj_create(par);
    //lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_size(obj, WINDOW_WIDTH, WINDOW_HEIGHT);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(obj, LV_COLOR_WHITE, LV_PART_MAIN);
	lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);//Propagate the events to the parent too
    //lv_obj_add_event_cb(obj, (lv_event_cb_t)ContApps_EventHandler, LV_EVENT_GESTURE, NULL);
    Cont = obj;
}

static void PageAnim_Create()
{
    int32_t cont_rey = lv_obj_get_y(Cont);

    lv_obj_set_y(Cont, WINDOW_HEIGHT);

    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, Cont);
    lv_anim_set_values(&a1, WINDOW_HEIGHT, cont_rey);
    lv_anim_set_early_apply(&a1, false);
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a1, lv_anim_path_ease_in_out);
    lv_anim_set_time(&a1, 300);

    PageAnimTimeLine = lv_anim_timeline_create();
    lv_anim_timeline_add(PageAnimTimeLine, 0, &a1);
}

static void PageAnim_Play(bool playback)
{
    lv_anim_timeline_set_reverse(PageAnimTimeLine, playback);
    lv_anim_timeline_start(PageAnimTimeLine);
    PageDelay(lv_anim_timeline_get_playtime(PageAnimTimeLine));
}

static void Setup()
{

    lv_obj_move_foreground(appWindow);
	Cont_Create(appWindow);
	Info_Create(Cont);
	PageAnim_Create();
	PageAnim_Play(false);
}

static void Exit()
{
	PageAnim_Play(true);
    lv_anim_timeline_del(PageAnimTimeLine);
    lv_obj_clean(appWindow);
}

static void Event(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_PRESSING)
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if (dir == LV_DIR_RIGHT)
        {
            LV_LOG("Page->Pop()\n");
            PM_Pop(Page);
        }
    }
}
