
#include "../DisplayPrivate.h"
#define DBG_TAG "LVGL Page_LEDAndBtn"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#define APP_ICON_ANIM_TIME 100
/*导出页面*/
PAGE_EXPORT(LEDAndBtn);
#define LED_PIN1 BSP_IO_PORT_02_PIN_09 /* Onboard LED pins */
#define LED_PIN2 BSP_IO_PORT_02_PIN_10 /* Onboard LED pins */
#define BTN0_TEST_PIN "p005"
#define BTN1_TEST_PIN "p006"
#define BTN2_TEST_PIN "p007"

typedef struct
{
    int state;
    const char *name;
    lv_obj_t *obj;
} BIGSwitch_TypeDef;

typedef struct
{
    const char *name;
    lv_obj_t *obj;
} Btn_TypeDef;

static lv_obj_t *SwitchCont;
static lv_obj_t *BtnCont;
static lv_anim_timeline_t *anim_timeline = NULL;
static lv_obj_t *Cont;
static lv_obj_t *Title;
static void slider_event_cb(lv_event_t *e);
static lv_obj_t *slider_label;

static BIGSwitch_TypeDef BIGSW_Grp[] =
    {
        {0, "LED0", NULL},
        {0, "LED1", NULL},
};

static Btn_TypeDef Btn_Grp[] =
    {
        {"BTN0", NULL},
        {"BTN1", NULL},
        {"BTN0", NULL},
};
static rt_thread_t scan_thread = RT_NULL;

static void return_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Clicked: return\n");
        PM_Pop(Page);
    }
}

static void irq0_callback_test(void *args)
{
    lv_led_toggle(Btn_Grp[0].obj);
    LOG_I("btn1 passed\n");
}

static void irq1_callback_test(void *args)
{
    lv_led_toggle(Btn_Grp[1].obj);
    LOG_I("btn2 passed\n");
}

static void input_gpio_init(void)
{
    /* init */
    rt_base_t pin0 = rt_pin_get(BTN0_TEST_PIN);
    rt_base_t pin1 = rt_pin_get(BTN1_TEST_PIN);

    LOG_I("\n pin0 number : 0x%04X \n", pin0);
    LOG_I("\n pin1 number : 0x%04X \n", pin1);

    rt_pin_attach_irq(pin0, PIN_IRQ_MODE_RISING, irq0_callback_test, RT_NULL);
    rt_pin_attach_irq(pin1, PIN_IRQ_MODE_RISING, irq1_callback_test, RT_NULL);

    rt_pin_irq_enable(pin0, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(pin1, PIN_IRQ_ENABLE);
}

static void SWClickAnim(lv_obj_t *sw, bool ispress)
{
    lv_anim_t a;
    int y = lv_obj_get_y(sw);
    lv_anim_init(&a);
    lv_anim_set_var(&a, sw);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a, y, ispress ? y + 10 : y - 10);
    lv_anim_set_time(&a, APP_ICON_ANIM_TIME);

    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);

    lv_anim_start(&a);
}

static void BIGSwitch_event_handler(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    BIGSwitch_TypeDef *BIGSwitch = (BIGSwitch_TypeDef *)lv_obj_get_user_data(obj);
    if (BIGSwitch)
    {
        BIGSwitch->state = ~BIGSwitch->state;
        SWClickAnim(BIGSwitch->obj, BIGSwitch->state);
        if (BIGSwitch->obj == BIGSW_Grp[0].obj)
        {
            rt_pin_write(LED_PIN1, BIGSW_Grp[0].state ? PIN_LOW : PIN_HIGH);
            LOG_I("led0 LV_EVENT_CLICKED state = %d", BIGSW_Grp[0].state);
        }
        else if (BIGSwitch->obj == BIGSW_Grp[1].obj)
        {
            rt_pin_write(LED_PIN2, BIGSW_Grp[1].state ? PIN_LOW : PIN_HIGH);
            LOG_I("led1 LV_EVENT_CLICKED state = %d", BIGSW_Grp[1].state);
        }
    }
}

static lv_obj_t *BIGSwitch_Create(lv_obj_t *par, int x, int y, const char *str, BIGSwitch_TypeDef *data, int state)
{

    lv_obj_t *sw_bottom = lv_obj_create(par);
    lv_obj_set_size(sw_bottom, 130, 60);
    lv_obj_align(sw_bottom, LV_ALIGN_CENTER, x, y);
    lv_obj_set_style_bg_color(sw_bottom, lv_color_make(0x67, 0x8A, 0xAD), LV_PART_MAIN);
    lv_obj_set_style_radius(sw_bottom, 23, LV_PART_MAIN);
    lv_obj_set_style_border_width(sw_bottom, 0, LV_PART_MAIN);

    lv_obj_t *sw_body = lv_obj_create(par);
    lv_obj_set_size(sw_body, 120, 50);
    lv_obj_align_to(sw_body, sw_bottom, LV_ALIGN_TOP_MID, 0, -10);
    lv_obj_set_style_bg_color(sw_body, lv_color_make(0x5D, 0x7C, 0x9C), LV_PART_MAIN);
    lv_obj_set_style_radius(sw_body, 20, LV_PART_MAIN);
    lv_obj_set_style_border_width(sw_body, 0, LV_PART_MAIN);

    lv_obj_t *sw_top = lv_obj_create(par);
    lv_obj_set_size(sw_top, 120, 50);
    lv_obj_align_to(sw_top, sw_body, LV_ALIGN_TOP_MID, 0, state ? -10 : -20);
    lv_obj_set_style_bg_color(sw_top, lv_color_make(0x99, 0xCC, 0xFF), LV_PART_MAIN);
    lv_obj_set_style_radius(sw_top, 20, LV_PART_MAIN);
    lv_obj_set_style_border_width(sw_top, 0, LV_PART_MAIN);
    lv_obj_add_event_cb(sw_top, (lv_event_cb_t)BIGSwitch_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_user_data(sw_top, data);
    lv_obj_clear_flag(sw_top, LV_OBJ_FLAG_SCROLLABLE);

    // lv_obj_t* img = lv_img_create(par);
    lv_obj_t *label = lv_label_create(sw_top);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_size(label, 120, 40);
    lv_label_set_text(label, str);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 10);
    lv_obj_set_style_text_color(label, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);

    return sw_top;
}

static void BIGSwitchGrp_Create(lv_obj_t *par)
{
    lv_obj_t *tabel = lv_obj_create(par);
    lv_obj_align(tabel, LV_ALIGN_CENTER, 0, 15);
    lv_obj_set_size(tabel, 300, 80);
    lv_obj_set_style_border_width(tabel, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabel, lv_color_make(0xcc, 0xcc, 0xcc), LV_PART_MAIN);
    lv_obj_add_flag(tabel, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(tabel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(tabel, 30, LV_PART_MAIN);
    for (int i = 0; i < __Sizeof(BIGSW_Grp); i++)
    {
        BIGSW_Grp[i].obj = BIGSwitch_Create(tabel, -70 + i * 140, 0, BIGSW_Grp[i].name, &(BIGSW_Grp[i]), BIGSW_Grp[i].state);
    }
    SwitchCont = tabel;
}

static void BtnGrp_Create(lv_obj_t *par)
{
    lv_obj_t *tabel = lv_obj_create(par);
    lv_obj_align(tabel, LV_ALIGN_TOP_MID, 0, 20);
    lv_obj_set_size(tabel, 300, 70);
    lv_obj_set_style_border_width(tabel, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(tabel, lv_color_make(0xcc, 0xcc, 0xcc), LV_PART_MAIN);
    lv_obj_add_flag(tabel, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(tabel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(tabel, 30, LV_PART_MAIN);
    for (int i = 0; i < __Sizeof(Btn_Grp); i++)
    {
        lv_obj_t *led = lv_led_create(tabel);
        lv_obj_set_size(led, 83, 50);
        lv_obj_align(led, LV_ALIGN_LEFT_MID, i * (85 + 10), 0);
        lv_obj_set_style_bg_color(led, lv_color_make(0x99, 0xCC, 0xFF), LV_PART_MAIN);
        lv_obj_set_style_radius(led, 20, LV_PART_MAIN);
        lv_obj_set_style_border_width(led, 4, LV_PART_MAIN);
        lv_obj_set_style_border_color(led, lv_color_make(0x67, 0x8A, 0xAD), LV_PART_MAIN);
        lv_obj_set_user_data(led, &(Btn_Grp[i]));
        lv_obj_clear_flag(led, LV_OBJ_FLAG_SCROLLABLE);

        // lv_obj_t* img = lv_img_create(par);
        lv_obj_t *label = lv_label_create(led);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
        lv_obj_set_size(label, 80, 40);
        lv_label_set_text(label, Btn_Grp[i].name);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 10);
        lv_obj_set_style_text_color(label, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
        Btn_Grp[i].obj = led;
    }
    BtnCont = tabel;

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

static void Back_light_set(int val)
{
#ifdef BSP_USING_PWM5
#define LCD_PWM_DEV_NAME "pwm5"
#define LCD_PWM_DEV_CHANNEL 0

    struct rt_device_pwm *pwm_dev;

    /* turn on the LCD backlight */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(LCD_PWM_DEV_NAME);
    /* pwm frequency:100K = 10000ns */
    rt_pwm_set(pwm_dev, LCD_PWM_DEV_CHANNEL, 10000, val);
    rt_pwm_enable(pwm_dev, LCD_PWM_DEV_CHANNEL);
#endif
}

static void slider_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    int val = (int)lv_slider_get_value(slider);
    char buf[32];
    lv_snprintf(buf, sizeof(buf), "backlight: %d%%", val);
    lv_label_set_text(slider_label, buf);
    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    Back_light_set(val * 100);
}

void Slider_Create(lv_obj_t *par)
{
    /*Create a slider in the center of the display*/
    lv_obj_t *slider = lv_slider_create(par);
    lv_obj_set_size(slider, 290, 20);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_align(slider, LV_ALIGN_BOTTOM_MID, 0, -30);
    /*Create a label below the slider*/
    slider_label = lv_label_create(par);
    lv_slider_set_value(slider, 100,  LV_ANIM_OFF);
    lv_label_set_text(slider_label, "backlight: 100%");

    lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}

static void Cont_Create(lv_obj_t *par)
{
    lv_obj_t *obj = lv_obj_create(par);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_size(obj, WINDOW_WIDTH, WINDOW_HEIGHT);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, LV_COLOR_WHITE, LV_PART_MAIN);
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
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(obj, lv_color_make(0xcc, 0xcc, 0xcc), LV_PART_MAIN);
    lv_obj_set_scroll_dir(obj, LV_DIR_VER);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE); // Propagate the events to the parent too
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *label = lv_label_create(obj);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
    lv_obj_set_size(label, TITLE_WIDTH, TITLE_HEIGHT);
    // lv_obj_set_style_text_font(label, &TITLE_FONT, 0);
    lv_label_set_text(label, "LED&BTN");
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

static void Btn_Scan_Thread_Entry(void *parameter)
{
    uint8_t last_state = 0;
    rt_base_t pin2 = rt_pin_get(BTN2_TEST_PIN);
    LOG_I("\n pin2 number : 0x%04X \n", pin2);
    while (1)
    {
        if (rt_pin_read(pin2) == 0)
        {
            rt_thread_mdelay(5);
            if (rt_pin_read(pin2) == 0)
            {
                last_state = ~last_state;
                lv_led_toggle(Btn_Grp[2].obj);
            }
        }
        rt_thread_mdelay(10);
    }
}

static void Btn_Scan_Thread_Create(void)
{
    scan_thread = rt_thread_create("btn_scan", Btn_Scan_Thread_Entry, RT_NULL, 512, 25, 10);
    if (scan_thread != RT_NULL)
    {
        rt_thread_startup(scan_thread);
    }
    else
    {
        rt_kprintf("create scan_thread failed!\n");
    }
}

static void Setup()
{
    /*将此页面移到前台*/
    lv_obj_move_foreground(appWindow);

    Cont_Create(appWindow);
    Title_Create(appWindow);
    BtnGrp_Create(Cont);
    BIGSwitchGrp_Create(Cont);
    Slider_Create(Cont);
    input_gpio_init();
    Btn_Scan_Thread_Create();
    PageAnim_Create();
    PageAnim_Play(false);
}

static void Exit()
{
    PageAnim_Play(true);
    rt_thread_delete(scan_thread);
    lv_anim_timeline_del(anim_timeline);
    lv_obj_clean(appWindow);
}

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
