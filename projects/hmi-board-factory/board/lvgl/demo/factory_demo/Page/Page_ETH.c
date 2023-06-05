
#include "../DisplayPrivate.h"
#include "lv_file_explorer.h"
#define DBG_TAG "page eth"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
/*导出页面*/
PAGE_EXPORT(ETH);
static lv_obj_t *list1;
static lv_obj_t *Cont;
static lv_obj_t *Title;
static lv_obj_t *Text_Area;
static lv_anim_timeline_t *PageAnimTimeLine = NULL;
static void Ifinfo_Print(void);
static void Text_Area_add_text(const char *format, ...);

static void return_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Clicked: return\n");
        PM_Pop(Page);
    }
}

static void refresh_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
        LV_LOG_USER("Clicked: refresh");
        lv_obj_clean(list1);
        Ifinfo_Print();
    }
}

static void close_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
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

void List_Add_Btn(char *str)
{
    lv_obj_t *obj = lv_list_add_btn(list1, LV_SYMBOL_WIFI, str);
    lv_obj_t *label = lv_obj_get_child(obj, 1);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
}

void List_Add_Text(char *str)
{
    lv_obj_t *obj = lv_list_add_text(list1, str);
    lv_obj_t *label = lv_obj_get_child(obj, 1);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
}

static void Text_Area_Create(lv_obj_t *par)
{
    lv_obj_t *textarea = lv_textarea_create(par);
    lv_obj_align(textarea, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(textarea, WINDOW_WIDTH - 10, WINDOW_HEIGHT - TITLE_HEIGHT - 10);
    lv_obj_add_state(textarea, LV_STATE_DEFAULT); /*To be sure the cursor is visible*/
    Text_Area = textarea;
}

static void Text_Area_add_text(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    rt_kprintf("%s", buffer);
    List_Add_Text(buffer);
    va_end(args);
    PageDelay(5);
}

static void Ifinfo_Print(void)
{
#define NETDEV_IFCONFIG_MAC_MAX_LEN 6
#define NETDEV_IFCONFIG_IMEI_MAX_LEN 8
    rt_slist_t *node = RT_NULL;
    rt_ubase_t index;

    struct netdev *netdev = RT_NULL;
    struct netdev *cur_netdev_list = netdev_list;
    for (node = &(cur_netdev_list->list); node; node = rt_slist_next(node))
    {
        netdev = rt_list_entry(node, struct netdev, list);

        Text_Area_add_text("network interface device: %.*s%s\n",
                           RT_NAME_MAX, netdev->name,
                           (netdev == netdev_default) ? " (Default)" : "");
        Text_Area_add_text("MTU: %d\n", netdev->mtu);

        /* 6 - MAC address, 8 - IEMI */
        if (netdev->hwaddr_len == NETDEV_IFCONFIG_MAC_MAX_LEN)
        {
            Text_Area_add_text("MAC: %02x%02x%02x%02x%02x%02x ",
                               netdev->hwaddr[0],
                               netdev->hwaddr[1],
                               netdev->hwaddr[2],
                               netdev->hwaddr[3],
                               netdev->hwaddr[4],
                               netdev->hwaddr[5]);
        }
        else if (netdev->hwaddr_len == NETDEV_IFCONFIG_IMEI_MAX_LEN)
        {
            Text_Area_add_text("IMEI: ");
            for (index = 0; index < netdev->hwaddr_len; index++)
            {
                /* two numbers are displayed at one time*/
                if (netdev->hwaddr[index] < 10 && index != netdev->hwaddr_len - 1)
                {
                    Text_Area_add_text("%02d", netdev->hwaddr[index]);
                }
                else
                {
                    Text_Area_add_text("%d", netdev->hwaddr[index]);
                }
            }
        }
        Text_Area_add_text("\nFLAGS:");
        if (netdev->flags & NETDEV_FLAG_UP)
            Text_Area_add_text(" UP");
        else
            Text_Area_add_text(" DOWN");
        if (netdev->flags & NETDEV_FLAG_LINK_UP)
            Text_Area_add_text(" LINK_UP");
        else
            Text_Area_add_text(" LINK_DOWN");
#ifdef SAL_INTERNET_CHECK
        if (netdev->flags & NETDEV_FLAG_INTERNET_UP)
            Text_Area_add_text(" INTERNET_UP");
        else
            Text_Area_add_text(" INTERNET_DOWN");
#endif
        if (netdev->flags & NETDEV_FLAG_DHCP)
            Text_Area_add_text(" DHCP_ENABLE");
        else
            Text_Area_add_text(" DHCP_DISABLE");
        if (netdev->flags & NETDEV_FLAG_ETHARP)
            Text_Area_add_text(" ETHARP");
        if (netdev->flags & NETDEV_FLAG_BROADCAST)
            Text_Area_add_text(" BROADCAST");
        if (netdev->flags & NETDEV_FLAG_IGMP)
            Text_Area_add_text(" IGMP");
        Text_Area_add_text("\n");
        Text_Area_add_text("ip address: %s\n", inet_ntoa(netdev->ip_addr));
        Text_Area_add_text("gw address: %s\n", inet_ntoa(netdev->gw));
        Text_Area_add_text("net mask  : %s\n", inet_ntoa(netdev->netmask));
        for (index = 0; index < NETDEV_DNS_SERVERS_NUM; index++)
        {
            Text_Area_add_text("dns server #%d: %s\n", index, inet_ntoa(netdev->dns_servers[index]));
        }

        if (rt_slist_next(node))
        {
            Text_Area_add_text("\n");
        }
    }
}

static void Cont_Create(lv_obj_t *par)
{
    lv_obj_t *obj = lv_obj_create(par);
    // lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_size(obj, WINDOW_WIDTH, WINDOW_HEIGHT - TITLE_HEIGHT);
    lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(obj, LV_COLOR_GRAY, LV_PART_MAIN);
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
    lv_label_set_text(label, "eth");
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_color(label, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN);

    Title = obj;
}

static void PageAnim_Create()
{
    int32_t cont_rey = lv_obj_get_y(Cont);
    int32_t tile_rey = lv_obj_get_y(Title);

    lv_obj_set_y(Cont, WINDOW_HEIGHT);
    lv_obj_set_y(Title, -TITLE_HEIGHT);

    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, Cont);
    lv_anim_set_values(&a1, WINDOW_HEIGHT, cont_rey);
    lv_anim_set_early_apply(&a1, false);
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a1, lv_anim_path_ease_in_out);
    lv_anim_set_time(&a1, 300);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, Title);
    lv_anim_set_values(&a2, -TITLE_HEIGHT, tile_rey);
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

static void Setup()
{
    /*将此页面移到前台*/
    lv_obj_move_foreground(appWindow);
    Cont_Create(appWindow);
    Title_Create(appWindow);
    List_Create(Cont);
    // Text_Area_Create(Cont);
    PageAnim_Create();
    PageAnim_Play(false);
    Ifinfo_Print();
}

/**
 * @brief  页面退出事件
 * @param  无
 * @retval 无
 */
static void Exit()
{
    PageAnim_Play(true);
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
