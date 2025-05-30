// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.1
// LVGL version: 8.3.11
// Project name: soem

#ifndef _SOEM_UI_H
#define _SOEM_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void ui_Screen_screen_init(void);
extern lv_obj_t * ui_Screen;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Arc1;
void ui_event_Dropdown1(lv_event_t * e);
extern lv_obj_t * ui_Dropdown1;
extern lv_obj_t * ui_Container1;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_TextArea1;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_TextArea3;
void ui_event_Slider1(lv_event_t * e);
extern lv_obj_t * ui_Slider1;
extern lv_obj_t * ui_Container2;
extern lv_obj_t * ui_Label6;
extern lv_obj_t * ui_TextArea5;
extern lv_obj_t * ui_Label4;
extern lv_obj_t * ui_TextArea2;
void ui_event_Slider2(lv_event_t * e);
extern lv_obj_t * ui_Slider2;
void ui_event_Button1(lv_event_t * e);
extern lv_obj_t * ui_Button1;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui_Label9;
extern lv_obj_t * ui_Label7;
extern lv_obj_t * chart1;
extern lv_obj_t * chart2;
extern lv_chart_series_t * ser1;
extern lv_chart_series_t * ser2;
// CUSTOM VARIABLES

// EVENTS

extern lv_obj_t * ui____initial_actions0;

void lv_ethercat_gui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
