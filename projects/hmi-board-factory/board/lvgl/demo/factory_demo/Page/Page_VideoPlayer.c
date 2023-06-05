
#include "../DisplayPrivate.h"
#include "player.h"
#include "drv_jpeg.h"
#define DBG_TAG "page video"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#define JPEG_WIDTH 400
#define JPEG_HEIGHT 240

/*导出页面*/
PAGE_EXPORT(VideoPlayer);
static lv_obj_t *Cont;
static lv_obj_t *avi_obj;
static struct player v_player;
static decode_drv_t decode;
static uint8_t *jpeg_outbuffer;

static void lv_avi_window_create(lv_obj_t *parent)
{
    avi_obj = lv_img_create(parent);
    lv_obj_set_size(avi_obj, JPEG_WIDTH, JPEG_HEIGHT);
    lv_obj_align(avi_obj, LV_ALIGN_CENTER, 0, 0);
}

static void Cont_Create(lv_obj_t *par)
{
    lv_obj_t *obj = lv_obj_create(par);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_size(obj, WINDOW_WIDTH, WINDOW_HEIGHT);
    lv_obj_set_style_bg_color(obj, LV_COLOR_BLACK, LV_PART_MAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE); // Propagate the events to the parent too
    // lv_obj_add_event_cb(obj, (lv_event_cb_t)ContApps_EventHandler, LV_EVENT_GESTURE, NULL);
    Cont = obj;
}

void palyer_list_clear(player_t p)
{
    LOG_I("palyer_list_clear..");
    p->song_current = 0;
    p->video_num = 0;
    int i;
    for (i = 0; i < __Sizeof(p->video_list); i++)
    {
        if (p->video_list[i] != RT_NULL)
        {
            LOG_I("DEL: %s", p->video_list[i]);
            p->video_list[i] = RT_NULL;
        }
    }
}

static int player_init(void)
{
    extern char file_name[64];
    v_player.decode = &decode;
    v_player.decode->jpeg_out_buf = NULL;
    v_player.decode->decode_read = _DrawBitmap;
    palyer_list_clear(&v_player);
    player_start(&v_player);
    player_control(&v_player, PLAYER_CMD_INIT, (void *)file_name);
    return 0;
}

static void Setup()
{
    /*将此页面移到前台*/
    lv_obj_move_foreground(appWindow);
    Cont_Create(appWindow);
    lv_avi_window_create(Cont);
    PageDelay(100);
    player_init();
}

static void Exit()
{
    player_delete(&v_player);
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
