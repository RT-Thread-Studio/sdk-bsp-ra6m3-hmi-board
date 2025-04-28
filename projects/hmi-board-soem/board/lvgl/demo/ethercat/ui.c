#include "ui.h"
#include "stdio.h"

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_Screen
void ui_Screen_screen_init(void);
lv_obj_t * ui_Screen;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Arc1;
void ui_event_Dropdown1(lv_event_t * e);
lv_obj_t * ui_Dropdown1;
lv_obj_t * ui_Container1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_TextArea1;
lv_obj_t * ui_Label3;
lv_obj_t * ui_TextArea3;
void ui_event_Slider1(lv_event_t * e);
lv_obj_t * ui_Slider1;
lv_obj_t * ui_Container2;
lv_obj_t * ui_Label6;
lv_obj_t * ui_TextArea5;
lv_obj_t * ui_Label4;
lv_obj_t * ui_TextArea2;
void ui_event_Slider2(lv_event_t * e);
lv_obj_t * ui_Slider2;
void ui_event_Button1(lv_event_t * e);
lv_obj_t * ui_Button1;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Label9;
lv_obj_t * ui_Label7;
lv_obj_t * chart1;
lv_obj_t * chart2;
lv_chart_series_t * ser1;
lv_chart_series_t * ser2;
// CUSTOM VARIABLES

// EVENTS
lv_obj_t * ui____initial_actions0;

static rt_uint8_t btn_state = 0;
extern rt_uint8_t mode;

extern void turn_on(void);
extern void turn_off(void);
extern void set_data(int32_t data);

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Dropdown1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        mode = lv_dropdown_get_selected(ui_Dropdown1);
        if (mode == 0)
        {
            lv_obj_add_flag(ui_Container2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_Container1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(chart2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(chart1, LV_OBJ_FLAG_HIDDEN);
            lv_textarea_set_text(ui_TextArea1, "0");
            lv_slider_set_value(ui_Slider1, 0, 0);
        }
        else if (mode == 1)
        {
            lv_obj_add_flag(ui_Container1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_Container2, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(chart1, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(chart2, LV_OBJ_FLAG_HIDDEN);
            lv_textarea_set_text(ui_TextArea5, "2");
            lv_slider_set_value(ui_Slider2, 0, 0);
        }
        turn_off();
        rt_thread_mdelay(500);
        turn_on();
    }
}

void ui_event_Slider1(lv_event_t * e)
{
    int32_t val;
    char str[5];
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        val = lv_slider_get_value(ui_Slider1);
        set_data(val);
        snprintf(str, sizeof(str), "%"LV_PRId32, val);
        lv_textarea_set_text(ui_TextArea1, str);
    }
}

void ui_event_Slider2(lv_event_t * e)
{
    int32_t val;
    char str[5];
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        val = lv_slider_get_value(ui_Slider2);
        set_data(val);
        snprintf(str, sizeof(str), "%"LV_PRId32, val);
        lv_textarea_set_text(ui_TextArea5, str);
    }
}

void ui_event_Button1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        if (btn_state == 0)
        {
            btn_state = 1;
            lv_obj_set_style_bg_color(ui_Button1, lv_color_hex(0x00FF00), LV_PART_MAIN);
            lv_obj_add_flag(ui_Label5, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_Label9, LV_OBJ_FLAG_HIDDEN);
            turn_on();
            lv_textarea_set_text(ui_TextArea1, "0");
            lv_slider_set_value(ui_Slider1, 0, 0);
        }
        else if (btn_state == 1)
        {
            btn_state = 0;
            lv_obj_set_style_bg_color(ui_Button1, lv_color_hex(0xFF0000), LV_PART_MAIN);
            lv_obj_add_flag(ui_Label9, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_Label5, LV_OBJ_FLAG_HIDDEN);
            turn_off();
            lv_textarea_set_text(ui_TextArea5, "2");
            lv_slider_set_value(ui_Slider2, 0, 0);
        }
    }
}

///////////////////// SCREENS ////////////////////

void lv_ethercat_gui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen);
}
