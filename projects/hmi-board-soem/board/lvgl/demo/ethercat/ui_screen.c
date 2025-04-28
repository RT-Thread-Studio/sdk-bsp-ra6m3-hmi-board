#include "ui.h"

void ui_Screen_screen_init(void)
{
    ui_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1 = lv_label_create(ui_Screen);
    lv_obj_set_width(ui_Label1, 480);
    lv_obj_set_height(ui_Label1, 20);
    lv_obj_set_x(ui_Label1, 0);
    lv_obj_set_y(ui_Label1, -122);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "EtherCAT Motor Control");
    lv_obj_set_style_text_align(ui_Label1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    chart1 = lv_chart_create(ui_Screen);
    lv_obj_set_size(chart1, 250, 150);
    lv_obj_set_x(chart1, 40);
    lv_obj_set_y(chart1, 100);

    lv_chart_set_update_mode(chart1, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_type(chart1, LV_CHART_TYPE_LINE);
    ser1 = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, -100, 100);
    lv_chart_set_axis_tick(chart1, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 5, true, 50);
    lv_chart_set_axis_tick(chart1, LV_CHART_AXIS_PRIMARY_X, 10, 0, 0, 0, true, 0);
    lv_obj_set_style_line_opa(chart1, LV_OPA_40, LV_PART_ITEMS);
    lv_obj_set_style_line_width(chart1, 1, LV_PART_ITEMS);
    lv_obj_set_style_bg_color(chart1, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    lv_obj_set_style_border_width(chart1, 0, 0);


    chart2 = lv_chart_create(ui_Screen);
    lv_obj_set_size(chart2, 250, 150);
    lv_obj_set_x(chart2, 40);
    lv_obj_set_y(chart2, 100);

    lv_chart_set_update_mode(chart2, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_type(chart2, LV_CHART_TYPE_LINE);
    ser2 = lv_chart_add_series(chart2, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(chart2, LV_CHART_AXIS_PRIMARY_Y, -10, 10);
    lv_chart_set_axis_tick(chart2, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 5, true, 50);
    lv_chart_set_axis_tick(chart2, LV_CHART_AXIS_PRIMARY_X, 10, 0, 0, 0, true, 0);
    lv_obj_set_style_line_opa(chart2, LV_OPA_40, LV_PART_ITEMS);
    lv_obj_set_style_line_width(chart2, 1, LV_PART_ITEMS);
    lv_obj_set_style_bg_color(chart2, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    lv_obj_set_style_border_width(chart2, 0, 0);
    lv_obj_add_flag(chart2, LV_OBJ_FLAG_HIDDEN);

    ui_Dropdown1 = lv_dropdown_create(ui_Screen);
    lv_dropdown_set_options(ui_Dropdown1, "CSP Mode\nCSV Mode");
    lv_obj_set_width(ui_Dropdown1, 119);
    lv_obj_set_height(ui_Dropdown1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Dropdown1, 133);
    lv_obj_set_y(ui_Dropdown1, -81);
    lv_obj_set_align(ui_Dropdown1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Dropdown1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_set_style_text_align(ui_Dropdown1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_align(ui_Dropdown1, LV_TEXT_ALIGN_CENTER, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_text_align(lv_dropdown_get_list(ui_Dropdown1), LV_TEXT_ALIGN_CENTER,
            LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_align(lv_dropdown_get_list(ui_Dropdown1), LV_TEXT_ALIGN_CENTER,
            LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_Container1 = lv_obj_create(ui_Screen);
    lv_obj_remove_style_all(ui_Container1);
    lv_obj_set_width(ui_Container1, 284);
    lv_obj_set_height(ui_Container1, 181);
    lv_obj_set_x(ui_Container1, 136);
    lv_obj_set_y(ui_Container1, 34);
    lv_obj_set_align(ui_Container1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label2 = lv_label_create(ui_Container1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, 0);
    lv_obj_set_y(ui_Label2, -70);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Target Position");
    lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextArea1 = lv_textarea_create(ui_Container1);
    lv_obj_set_width(ui_TextArea1, 126);
    lv_obj_set_height(ui_TextArea1, 32);
    lv_obj_set_x(ui_TextArea1, 0);
    lv_obj_set_y(ui_TextArea1, -35);
    lv_obj_set_align(ui_TextArea1, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_TextArea1, "0");
    lv_obj_set_style_text_align(ui_TextArea1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_TextArea1, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    ui_Label3 = lv_label_create(ui_Container1);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, 0);
    lv_obj_set_y(ui_Label3, 5);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "Actual Position");
    lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextArea3 = lv_textarea_create(ui_Container1);
    lv_obj_set_width(ui_TextArea3, 126);
    lv_obj_set_height(ui_TextArea3, 32);
    lv_obj_set_x(ui_TextArea3, 0);
    lv_obj_set_y(ui_TextArea3, 40);
    lv_obj_set_align(ui_TextArea3, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_TextArea3, "0");
    lv_obj_set_style_text_align(ui_TextArea3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_TextArea3, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    ui_Slider1 = lv_slider_create(ui_Container1);
    lv_slider_set_range(ui_Slider1, -100, 100);
    lv_slider_set_mode(ui_Slider1, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_value(ui_Slider1, 0, LV_ANIM_OFF);
    if (lv_slider_get_mode(ui_Slider1) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(ui_Slider1, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Slider1, 150);
    lv_obj_set_height(ui_Slider1, 10);
    lv_obj_set_x(ui_Slider1, 0);
    lv_obj_set_y(ui_Slider1, 81);
    lv_obj_set_align(ui_Slider1, LV_ALIGN_CENTER);

    ui_Container2 = lv_obj_create(ui_Screen);
    lv_obj_remove_style_all(ui_Container2);
    lv_obj_set_width(ui_Container2, 284);
    lv_obj_set_height(ui_Container2, 181);
    lv_obj_set_x(ui_Container2, 136);
    lv_obj_set_y(ui_Container2, 34);
    lv_obj_set_align(ui_Container2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Container2, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_Container2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label6 = lv_label_create(ui_Container2);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, 0);
    lv_obj_set_y(ui_Label6, -70);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "Target Velocity");
    lv_obj_set_style_text_font(ui_Label6, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextArea5 = lv_textarea_create(ui_Container2);
    lv_obj_set_width(ui_TextArea5, 126);
    lv_obj_set_height(ui_TextArea5, 32);
    lv_obj_set_x(ui_TextArea5, 0);
    lv_obj_set_y(ui_TextArea5, -35);
    lv_obj_set_align(ui_TextArea5, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_TextArea5, "0");
    lv_obj_set_style_text_align(ui_TextArea5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_TextArea5, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    ui_Label4 = lv_label_create(ui_Container2);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, 0);
    lv_obj_set_y(ui_Label4, 5);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "Actual Velocity");
    lv_obj_set_style_text_font(ui_Label4, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TextArea2 = lv_textarea_create(ui_Container2);
    lv_obj_set_width(ui_TextArea2, 126);
    lv_obj_set_height(ui_TextArea2, 32);
    lv_obj_set_x(ui_TextArea2, 0);
    lv_obj_set_y(ui_TextArea2, 40);
    lv_obj_set_align(ui_TextArea2, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_TextArea2, "0");
    lv_obj_set_style_text_align(ui_TextArea2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_TextArea2, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    ui_Slider2 = lv_slider_create(ui_Container2);
    lv_slider_set_range(ui_Slider2, -10, 10);
    lv_slider_set_mode(ui_Slider2, LV_SLIDER_MODE_SYMMETRICAL);
    lv_slider_set_value(ui_Slider2, 0, LV_ANIM_OFF);
    if (lv_slider_get_mode(ui_Slider2) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(ui_Slider2, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Slider2, 150);
    lv_obj_set_height(ui_Slider2, 10);
    lv_obj_set_x(ui_Slider2, 0);
    lv_obj_set_y(ui_Slider2, 81);
    lv_obj_set_align(ui_Slider2, LV_ALIGN_CENTER);

    ui_Button1 = lv_btn_create(ui_Screen);
    lv_obj_set_width(ui_Button1, 35);
    lv_obj_set_height(ui_Button1, 32);
    lv_obj_set_x(ui_Button1, -184);
    lv_obj_set_y(ui_Button1, -72);
    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Button1, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label5 = lv_label_create(ui_Screen);
    lv_obj_set_width(ui_Label5, 64);
    lv_obj_set_height(ui_Label5, 20);
    lv_obj_set_x(ui_Label5, -75);
    lv_obj_set_y(ui_Label5, -72);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "stop");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Label5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label9 = lv_label_create(ui_Screen);
    lv_obj_set_width(ui_Label9, 76);
    lv_obj_set_height(ui_Label9, 20);
    lv_obj_set_x(ui_Label9, -60);
    lv_obj_set_y(ui_Label9, -72);
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label9, "running");
    lv_obj_add_flag(ui_Label9, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_set_style_text_color(ui_Label9, lv_color_hex(0x11FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Label9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label9, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label7 = lv_label_create(ui_Screen);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label7, -130);
    lv_obj_set_y(ui_Label7, -72);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "State:");
    lv_obj_set_style_text_align(ui_Label7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Dropdown1, ui_event_Dropdown1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Slider1, ui_event_Slider1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Slider2, ui_event_Slider2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button1, ui_event_Button1, LV_EVENT_ALL, NULL);

}
