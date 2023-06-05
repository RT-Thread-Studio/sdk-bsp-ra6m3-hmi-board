#include "DisplayPrivate.h"

/**
  * @brief  通用显示初始化
  * @param  无
  * @retval 无
  */
static void Display_CommonInit()
{
    /*APP窗口初始化*/
    AppWindow_Create(lv_scr_act());

    /*页面初始化*/
    DisplayPage_Init();
}

void Display_Init()
{
    Display_CommonInit();
}
