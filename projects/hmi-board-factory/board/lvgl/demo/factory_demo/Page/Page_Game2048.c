
#include "../DisplayPrivate.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define DBG_TAG "2048"
#define DBG_LVL DBG_LOG

#include <rtdbg.h>

/*********************
 *      DEFINES
 *********************/
#ifdef LV_100ASK_2048_MATRIX_SIZE
#define MATRIX_SIZE LV_100ASK_2048_MATRIX_SIZE
#else
#define MATRIX_SIZE 4
#endif
#define MY_CLASS &lv_100ask_2048_class

#define LV_100ASK_2048_BG_COLOR lv_color_hex(0xb3a397)
#define LV_100ASK_2048_TEXT_BLACK_COLOR lv_color_hex(0x6c635b)
#define LV_100ASK_2048_TEXT_WHITE_COLOR lv_color_hex(0xf8f5f0)

#define LV_100ASK_2048_NUMBER_EMPTY_COLOR lv_color_hex(0xc7b9ac)
#define LV_100ASK_2048_NUMBER_2_COLOR lv_color_hex(0xeee4da)
#define LV_100ASK_2048_NUMBER_4_COLOR lv_color_hex(0xede0c8)
#define LV_100ASK_2048_NUMBER_8_COLOR lv_color_hex(0xf2b179)
#define LV_100ASK_2048_NUMBER_16_COLOR lv_color_hex(0xf59563)
#define LV_100ASK_2048_NUMBER_32_COLOR lv_color_hex(0xf67c5f)
#define LV_100ASK_2048_NUMBER_64_COLOR lv_color_hex(0xf75f3b)
#define LV_100ASK_2048_NUMBER_128_COLOR lv_color_hex(0xedcf72)
#define LV_100ASK_2048_NUMBER_256_COLOR lv_color_hex(0xedcc61)
#define LV_100ASK_2048_NUMBER_512_COLOR lv_color_hex(0xedc850)
#define LV_100ASK_2048_NUMBER_1024_COLOR lv_color_hex(0xedc53f)
#define LV_100ASK_2048_NUMBER_2048_COLOR lv_color_hex(0xedc22e)

/**********************
 *      TYPEDEFS
 **********************/
/*Data of canvas*/
typedef struct
{
    lv_obj_t obj;
    lv_obj_t *btnm;
    uint16_t score;
    uint16_t map_count;
    uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE];
    char *btnm_map[MATRIX_SIZE * MATRIX_SIZE + MATRIX_SIZE];
    bool game_over;
} lv_100ask_2048_t;

/***********************
 * GLOBAL VARIABLES
 ***********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t *lv_100ask_2048_create(lv_obj_t *parent);

/*=====================
 * Setter functions
 *====================*/
void lv_100ask_2048_set_new_game(lv_obj_t *obj);

/*=====================
 * Getter functions
 *====================*/
uint16_t lv_100ask_2048_get_best_tile(lv_obj_t *obj);

uint16_t lv_100ask_2048_get_score(lv_obj_t *obj);

bool lv_100ask_2048_get_status(lv_obj_t *obj);

/*导出页面*/
PAGE_EXPORT(Game2048);

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void cont_event(lv_event_t *e);
static void reset_event_handler(lv_event_t *e);
static void lv_100ask_2048_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj);
static void lv_100ask_2048_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj);
static void lv_100ask_2048_event(const lv_obj_class_t *class_p, lv_event_t *e);
static void btnm_event_cb(lv_event_t *e);
static void MsgAnim_Play(bool playback);
static void Msg_Create(lv_obj_t *par);
static void MsgAnim_Create(void);

static void init_matrix_num(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
static void addRandom(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
static void update_btnm_map(char *lv_100ask_2048_btnm_map[], uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
static lv_color_t get_num_color(uint16_t num);
static char *int_to_str(char *str, uint16_t num);

static uint8_t count_empty(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
static uint8_t find_target(uint16_t array[MATRIX_SIZE], uint8_t x, uint8_t stop);
static void rotate_matrix(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
static bool find_pair_down(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
static bool slide_array(uint16_t *score, uint16_t array[MATRIX_SIZE]);
static bool move_up(uint16_t *score, uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
static bool move_down(uint16_t *score, uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
static bool move_left(uint16_t *score, uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
static bool move_right(uint16_t *score, uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);
static bool game_over(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE]);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t *Cont;
static lv_obj_class_t lv_100ask_2048_class;
static lv_obj_t *game_cont;
static lv_obj_t *game_score_label;
static lv_obj_t *game_MsgBg;
static lv_obj_t *game_MsgText;
static lv_obj_t *game_MsgRect;
static lv_anim_timeline_t *PageAnimTimeLine = NULL;
static lv_anim_timeline_t *MsgAnimTimeLine = NULL;
static bool isMsgShow = 0;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static void Msg_Create(lv_obj_t *par)
{
    lv_obj_t *bg = lv_obj_create(par);
    lv_obj_align(bg, LV_ALIGN_BOTTOM_MID, 0, 0);
    // lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(bg, 0, LV_PART_MAIN);
    lv_obj_set_size(bg, WINDOW_WIDTH, WINDOW_HEIGHT);
    lv_obj_set_style_bg_color(bg, LV_COLOR_GRAY, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bg, 0, LV_PART_MAIN);
    lv_obj_clear_flag(bg, LV_OBJ_FLAG_SCROLLABLE);
    game_MsgBg = bg;

    lv_obj_t *rect = lv_obj_create(par);
    lv_obj_align(rect, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(rect, 5, LV_PART_MAIN);
    lv_obj_set_size(rect, 250, 120);
    lv_obj_set_style_bg_color(rect, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
    lv_obj_clear_flag(rect, LV_OBJ_FLAG_SCROLLABLE);
    // lv_obj_set_style_border_side(rect, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT, LV_PART_MAIN);
    lv_obj_set_style_radius(rect, 10, LV_PART_MAIN);
    game_MsgRect = rect;

    lv_obj_t *label = lv_label_create(rect);
    lv_label_set_text(label, "GAME OVER!");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    label = lv_label_create(rect);
    lv_label_set_text_fmt(label, "Score:%d", lv_100ask_2048_get_score(game_cont));
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -10);
    game_MsgText = label;

    lv_obj_t *rbtn = lv_btn_create(rect);
    lv_obj_align(rbtn, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_border_width(rbtn, 0, LV_PART_MAIN);
    lv_obj_set_size(rbtn, 50, 30);
    lv_obj_set_style_bg_color(rbtn, lv_color_make(0x99, 0xcc, 0xff), LV_PART_MAIN);
    lv_obj_add_event_cb(rbtn, reset_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *rlabel = lv_label_create(rbtn);
    lv_label_set_text(rlabel, LV_SYMBOL_REFRESH);
    lv_obj_center(rlabel);
}

static void MsgAnim_Create()
{

    lv_obj_set_y(game_MsgBg, WINDOW_HEIGHT);
    lv_obj_set_y(game_MsgRect, WINDOW_HEIGHT);

    lv_anim_t a1;
    lv_anim_init(&a1);
    lv_anim_set_var(&a1, game_MsgBg);
    lv_anim_set_values(&a1, WINDOW_HEIGHT, 0);
    lv_anim_set_early_apply(&a1, false);
    lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_path_cb(&a1, lv_anim_path_ease_in_out);
    lv_anim_set_time(&a1, 300);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_var(&a2, game_MsgRect);
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
    isMsgShow = playback ? false : true;
    if (playback)
        lv_obj_add_flag(game_MsgBg, LV_OBJ_FLAG_EVENT_BUBBLE);
    else
        lv_obj_clear_flag(game_MsgBg, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_anim_timeline_set_reverse(MsgAnimTimeLine, playback);
    lv_anim_timeline_start(MsgAnimTimeLine);
    // PageDelay(lv_anim_timeline_get_playtime(MsgAnimTimeLine));
}

lv_obj_t *lv_100ask_2048_create(lv_obj_t *parent)
{
    lv_100ask_2048_class.constructor_cb = lv_100ask_2048_constructor;
    lv_100ask_2048_class.destructor_cb = lv_100ask_2048_destructor;
    lv_100ask_2048_class.event_cb = lv_100ask_2048_event;
    lv_100ask_2048_class.width_def = LV_DPI_DEF * 2;
    lv_100ask_2048_class.height_def = LV_DPI_DEF * 2;
    lv_100ask_2048_class.group_def = LV_OBJ_CLASS_GROUP_DEF_TRUE;
    lv_100ask_2048_class.instance_size = sizeof(lv_100ask_2048_t);
    lv_100ask_2048_class.base_class = &lv_obj_class;
    LV_LOG_INFO("begin");
    lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(obj, (lv_event_cb_t)cont_event, LV_EVENT_VALUE_CHANGED, NULL);

    return obj;
}

/*=====================
 * Setter functions
 *====================*/
void lv_100ask_2048_set_new_game(lv_obj_t *obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_100ask_2048_t *game_2048 = (lv_100ask_2048_t *)obj;

    game_2048->score = 0;
    game_2048->game_over = false;
    game_2048->map_count = MATRIX_SIZE * MATRIX_SIZE + MATRIX_SIZE;

    init_matrix_num(game_2048->matrix);
    update_btnm_map(game_2048->btnm_map, game_2048->matrix);
    lv_btnmatrix_set_map(game_2048->btnm, (const char **)(game_2048->btnm_map));

    lv_event_send(obj, LV_EVENT_VALUE_CHANGED, NULL);
}

/*=====================
 * Getter functions
 *====================*/
uint16_t lv_100ask_2048_get_score(lv_obj_t *obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_100ask_2048_t *game_2048 = (lv_100ask_2048_t *)obj;

    return game_2048->score;
}

bool lv_100ask_2048_get_status(lv_obj_t *obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_100ask_2048_t *game_2048 = (lv_100ask_2048_t *)obj;

    return game_2048->game_over;
}

uint16_t lv_100ask_2048_get_best_tile(lv_obj_t *obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_100ask_2048_t *game_2048 = (lv_100ask_2048_t *)obj;

    uint8_t x, y;
    uint16_t best_tile = 0;

    for (x = 0; x < MATRIX_SIZE; x++)
    {
        for (y = 0; y < MATRIX_SIZE; y++)
        {
            if (best_tile < game_2048->matrix[x][y])
                best_tile = game_2048->matrix[x][y];
        }
    }

    return (uint16_t)(1 << best_tile);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void cont_event(lv_event_t *e)
{
    LV_LOG_USER("LV_EVENT_VALUE_CHANGED\n");
    lv_label_set_text_fmt(game_score_label, "%d", lv_100ask_2048_get_score(game_cont));
    lv_obj_t *obj = lv_event_get_current_target(e);

    lv_100ask_2048_t *game_2048 = (lv_100ask_2048_t *)obj;
    if (game_2048->game_over)
    {
        lv_label_set_text_fmt(game_MsgText, "Score:%d", lv_100ask_2048_get_score(game_cont));
        MsgAnim_Play(false);
    }
}

static void return_event_handler(lv_event_t *e)
{
    LV_LOG("Page->Pop()\n");
    PM_Pop(Page);
}

static void reset_event_handler(lv_event_t *e)
{
    LV_LOG_USER("LV_EVENT_VALUE_CHANGED\n");
    LOG_I("isMsgShow %d", isMsgShow);
    if (isMsgShow)
    {
        MsgAnim_Play(true);
    }
    lv_100ask_2048_set_new_game(game_cont);
}

static void lv_2048_funcbtn_create(lv_obj_t *par)
{
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
    lv_obj_add_event_cb(fbtn, reset_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *flabel = lv_label_create(fbtn);
    lv_label_set_text(flabel, LV_SYMBOL_REFRESH);
    lv_obj_center(flabel);
}

static void lv_2048_gameinfo_create(lv_obj_t *par)
{
    lv_obj_t *label1 = lv_label_create(par);
    lv_label_set_text(label1, "score:");
    lv_obj_align(label1, LV_ALIGN_TOP_RIGHT, -20, 10);
    lv_obj_set_style_text_color(label1, LV_COLOR_BLACK, LV_PART_MAIN);

    lv_obj_t *label2 = lv_label_create(par);
    lv_label_set_text(label2, "0");
    lv_obj_align(label2, LV_ALIGN_TOP_RIGHT, -20, 30);
    lv_obj_set_style_text_color(label2, LV_COLOR_BLACK, LV_PART_MAIN);

    game_score_label = label2;
}

static void lv_100ask_2048_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    lv_100ask_2048_t *game_2048 = (lv_100ask_2048_t *)obj;

    game_2048->score = 0;
    game_2048->game_over = false;
    game_2048->map_count = MATRIX_SIZE * MATRIX_SIZE + MATRIX_SIZE;

    uint16_t index;
    for (index = 0; index < game_2048->map_count; index++)
    {

        if (((index + 1) % 5) == 0)
        {
            game_2048->btnm_map[index] = (char *)lv_mem_alloc(2);
            if ((index + 1) == game_2048->map_count)
                strcpy(game_2048->btnm_map[index], "");
            else
                strcpy(game_2048->btnm_map[index], "\n");
        }
        else
        {
            game_2048->btnm_map[index] = (char *)lv_mem_alloc(5);
            strcpy(game_2048->btnm_map[index], " ");
        }
    }

    init_matrix_num(game_2048->matrix);
    update_btnm_map(game_2048->btnm_map, game_2048->matrix);

    /*obj style init*/
    lv_theme_t *theme = lv_theme_get_from_obj(obj);
    lv_obj_set_style_outline_color(obj, theme->color_primary, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(obj, lv_disp_dpx(theme->disp, 2), LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(obj, lv_disp_dpx(theme->disp, 2), LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(obj, LV_OPA_50, LV_STATE_FOCUS_KEY);

    /*game_2048->btnm init*/
    game_2048->btnm = lv_btnmatrix_create(obj);
    lv_obj_set_size(game_2048->btnm, LV_PCT(100), LV_PCT(100));
    lv_obj_center(game_2048->btnm);
    lv_obj_set_style_pad_all(game_2048->btnm, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(game_2048->btnm, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_group_remove_obj(game_2048->btnm);
    lv_obj_add_flag(game_2048->btnm, LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_btnmatrix_set_map(game_2048->btnm, (const char **)(game_2048->btnm_map));
    lv_btnmatrix_set_btn_ctrl_all(game_2048->btnm, LV_BTNMATRIX_CTRL_DISABLED);

    lv_obj_add_event_cb(game_2048->btnm, btnm_event_cb, LV_EVENT_ALL, NULL);

    LV_TRACE_OBJ_CREATE("finished");
}

static void lv_100ask_2048_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
{
    LV_UNUSED(class_p);

    lv_100ask_2048_t *game_2048 = (lv_100ask_2048_t *)obj;
    uint16_t index;
    for (index = 0; index < game_2048->map_count; index++)
    {
        lv_mem_free(game_2048->btnm_map[index]);
    }
}

static void lv_100ask_2048_event(const lv_obj_class_t *class_p, lv_event_t *e)
{
    LV_UNUSED(class_p);

    lv_res_t res;

    /*Call the ancestor's event handler*/
    res = lv_obj_event_base(MY_CLASS, e);
    if (res != LV_RES_OK)
        return;

    bool success = false;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btnm = lv_event_get_target(e);
    lv_obj_t *obj = lv_event_get_current_target(e);

    lv_100ask_2048_t *game_2048 = (lv_100ask_2048_t *)obj;

    if (code == LV_EVENT_CLICKED)
    {
        game_2048->game_over = game_over(game_2048->matrix);
        if (!game_2048->game_over)
        {
            switch (lv_indev_get_gesture_dir(lv_indev_get_act()))
            {
            case LV_DIR_TOP:
                success = move_left(&(game_2048->score), game_2048->matrix);
                break;
            case LV_DIR_BOTTOM:
                success = move_right(&(game_2048->score), game_2048->matrix);
                break;
            case LV_DIR_LEFT:
                success = move_up(&(game_2048->score), game_2048->matrix);
                break;
            case LV_DIR_RIGHT:
                success = move_down(&(game_2048->score), game_2048->matrix);
                break;
            default:
                break;
            }
        }
        else
        {
            LV_LOG_USER("2048 GAME OVER!");
            res = lv_event_send(obj, LV_EVENT_VALUE_CHANGED, NULL);
            if (res != LV_RES_OK)
                return;
        }
    }
    else if (code == LV_EVENT_KEY)
    {
        game_2048->game_over = game_over(game_2048->matrix);
        if (!game_2048->game_over)
        {
            switch (*((uint8_t *)lv_event_get_param(e)))
            {
            case LV_KEY_UP:
                success = move_left(&(game_2048->score), game_2048->matrix);
                break;
            case LV_KEY_DOWN:
                success = move_right(&(game_2048->score), game_2048->matrix);
                break;
            case LV_KEY_LEFT:
                success = move_up(&(game_2048->score), game_2048->matrix);
                break;
            case LV_KEY_RIGHT:
                success = move_down(&(game_2048->score), game_2048->matrix);
                break;
            default:
                break;
            }
        }
        else
        {
            LV_LOG_USER("100ASK 2048 GAME OVER!");
            res = lv_event_send(obj, LV_EVENT_VALUE_CHANGED, NULL);
            if (res != LV_RES_OK)
                return;
        }
    }

    if (success)
    {
        addRandom(game_2048->matrix);
        update_btnm_map(game_2048->btnm_map, game_2048->matrix);
        lv_btnmatrix_set_map(game_2048->btnm, (const char **)(game_2048->btnm_map));

        res = lv_event_send(obj, LV_EVENT_VALUE_CHANGED, NULL);
        if (res != LV_RES_OK)
            return;
    }
}

static void btnm_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btnm = lv_event_get_target(e);
    lv_obj_t *parent = lv_obj_get_parent(btnm);

    lv_100ask_2048_t *game_2048 = (lv_100ask_2048_t *)parent;

    if (code == LV_EVENT_DRAW_PART_BEGIN)
    {
        lv_obj_draw_part_dsc_t *dsc = (lv_obj_draw_part_dsc_t *)lv_event_get_param(e);

        /*Change the draw descriptor the button*/
        if ((dsc->id >= 0) && (dsc->label_dsc))
        {
            uint16_t x, y, num;

            x = (uint16_t)((dsc->id) / 4);
            y = (dsc->id) % 4;
            num = (uint16_t)(1 << (game_2048->matrix[x][y]));

            dsc->rect_dsc->radius = 3;
            dsc->rect_dsc->bg_color = get_num_color(num);

            if (num < 8)
                dsc->label_dsc->color = LV_100ASK_2048_TEXT_BLACK_COLOR;
            else
                dsc->label_dsc->color = LV_100ASK_2048_TEXT_WHITE_COLOR;
        }
        /*Change the draw descriptor the btnm main*/
        else if ((dsc->id == 0) && !(dsc->label_dsc))
        {
            dsc->rect_dsc->radius = 5;
            dsc->rect_dsc->bg_color = LV_100ASK_2048_BG_COLOR;
            dsc->rect_dsc->border_width = 0;
        }
    }
}

static void init_matrix_num(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    uint8_t x, y;

    for (x = 0; x < MATRIX_SIZE; x++)
    {
        for (y = 0; y < MATRIX_SIZE; y++)
        {
            matrix[x][y] = 0;
        }
    }

    /* 初始化两个随机位置的随机数 */
    addRandom(matrix);
    addRandom(matrix);
}

static void addRandom(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    static bool initialized = false;
    uint16_t x, y;
    uint16_t r, len = 0;
    uint16_t n, list[MATRIX_SIZE * MATRIX_SIZE][2];

    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }

    for (x = 0; x < MATRIX_SIZE; x++)
    {
        for (y = 0; y < MATRIX_SIZE; y++)
        {
            if (matrix[x][y] == 0)
            {
                list[len][0] = x;
                list[len][1] = y;
                len++;
            }
        }
    }

    if (len > 0)
    {
        r = rand() % len;
        x = list[r][0];
        y = list[r][1];
        n = ((rand() % 10) / 9) + 1;
        matrix[x][y] = n;
    }
}

static void update_btnm_map(char *btnm_map[], uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    uint8_t x, y, index;

    index = 0;
    for (x = 0; x < MATRIX_SIZE; x++)
    {
        for (y = 0; y < MATRIX_SIZE; y++)
        {

            if (((index + 1) % 5) == 0)
                index++;

            if (matrix[x][y] != 0)
                int_to_str(btnm_map[index], (uint16_t)(1 << matrix[x][y]));
            else
                strcpy(btnm_map[index], " ");

            index++;
        }
    }
}

// 10进制
static char *int_to_str(char *str, uint16_t num)
{
    uint8_t i = 0; // 指示填充str
    if (num < 0)   // 如果num为负数，将num变正
    {
        num = -num;
        str[i++] = '-';
    }
    // 转换
    do
    {
        str[i++] = num % 10 + 48; // 取num最低位 字符0~9的ASCII码是48~57；简单来说数字0+48=48，ASCII码对应字符'0'
        num /= 10;                // 去掉最低位
    } while (num);                // num不为0继续循环

    str[i] = '\0';

    // 确定开始调整的位置
    uint8_t j = 0;
    if (str[0] == '-') // 如果有负号，负号不用调整
    {
        j = 1; // 从第二位开始调整
        ++i;   // 由于有负号，所以交换的对称轴也要后移1位
    }
    // 对称交换
    for (; j < (i / 2); j++)
    {
        // 对称交换两端的值 其实就是省下中间变量交换a+b的值：a=a+b;b=a-b;a=a-b;
        str[j] = str[j] + str[i - 1 - j];
        str[i - 1 - j] = str[j] - str[i - 1 - j];
        str[j] = str[j] - str[i - 1 - j];
    }

    return str; // 返回转换后的值
}

static uint8_t find_target(uint16_t array[MATRIX_SIZE], uint8_t x, uint8_t stop)
{
    uint8_t t;
    // if the position is already on the first, don't evaluate
    if (x == 0)
    {
        return x;
    }
    for (t = x - 1;; t--)
    {
        if (array[t] != 0)
        {
            if (array[t] != array[x])
            {
                // merge is not possible, take next position
                return t + 1;
            }
            return t;
        }
        else
        {
            // we should not slide further, return this one
            if (t == stop)
            {
                return t;
            }
        }
    }
    // we did not find a
    return x;
}

static bool slide_array(uint16_t *score, uint16_t array[MATRIX_SIZE])
{
    bool success = false;
    uint8_t x, t, stop = 0;

    for (x = 0; x < MATRIX_SIZE; x++)
    {
        if (array[x] != 0)
        {
            t = find_target(array, x, stop);
            // if target is not original position, then move or merge
            if (t != x)
            {
                // if target is zero, this is a move
                if (array[t] == 0)
                {
                    array[t] = array[x];
                }
                else if (array[t] == array[x])
                {
                    // merge (increase power of two)
                    array[t]++;
                    // increase score
                    *score += (uint32_t)1 << array[t];
                    // set stop to avoid double merge
                    stop = t + 1;
                }
                array[x] = 0;
                success = true;
            }
        }
    }
    return success;
}

static void rotate_matrix(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    uint8_t i, j, n = MATRIX_SIZE;
    uint16_t tmp;

    for (i = 0; i < (n / 2); i++)
    {
        for (j = i; j < (n - i - 1); j++)
        {
            tmp = matrix[i][j];
            matrix[i][j] = matrix[j][n - i - 1];
            matrix[j][n - i - 1] = matrix[n - i - 1][n - j - 1];
            matrix[n - i - 1][n - j - 1] = matrix[n - j - 1][i];
            matrix[n - j - 1][i] = tmp;
        }
    }
}

static bool move_up(uint16_t *score, uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    bool success = false;
    uint8_t x;

    for (x = 0; x < MATRIX_SIZE; x++)
    {
        success |= slide_array(score, matrix[x]);
    }
    return success;
}

static bool move_left(uint16_t *score, uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    bool success;

    rotate_matrix(matrix);

    success = move_up(score, matrix);
    rotate_matrix(matrix);
    rotate_matrix(matrix);
    rotate_matrix(matrix);

    return success;
}

static bool move_down(uint16_t *score, uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    bool success;

    rotate_matrix(matrix);
    rotate_matrix(matrix);

    success = move_up(score, matrix);
    rotate_matrix(matrix);
    rotate_matrix(matrix);

    return success;
}

static bool move_right(uint16_t *score, uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    bool success;

    rotate_matrix(matrix);
    rotate_matrix(matrix);
    rotate_matrix(matrix);

    success = move_up(score, matrix);
    rotate_matrix(matrix);

    return success;
}

static bool find_pair_down(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    bool success = false;
    uint8_t x, y;

    for (x = 0; x < MATRIX_SIZE; x++)
    {
        for (y = 0; y < (MATRIX_SIZE - 1); y++)
        {
            if (matrix[x][y] == matrix[x][y + 1])
                return true;
        }
    }
    return success;
}

static uint8_t count_empty(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    uint8_t x, y;
    uint8_t count = 0;

    for (x = 0; x < MATRIX_SIZE; x++)
    {
        for (y = 0; y < MATRIX_SIZE; y++)
        {
            if (matrix[x][y] == 0)
            {
                count++;
            }
        }
    }
    return count;
}

static lv_color_t get_num_color(uint16_t num)
{
    lv_color_t color;

    switch (num)
    {
    case 0:
        color = LV_100ASK_2048_NUMBER_EMPTY_COLOR;
        break;
    case 1:
        color = LV_100ASK_2048_NUMBER_EMPTY_COLOR;
        break;
    case 2:
        color = LV_100ASK_2048_NUMBER_2_COLOR;
        break;
    case 4:
        color = LV_100ASK_2048_NUMBER_4_COLOR;
        break;
    case 8:
        color = LV_100ASK_2048_NUMBER_8_COLOR;
        break;
    case 16:
        color = LV_100ASK_2048_NUMBER_16_COLOR;
        break;
    case 32:
        color = LV_100ASK_2048_NUMBER_32_COLOR;
        break;
    case 64:
        color = LV_100ASK_2048_NUMBER_64_COLOR;
        break;
    case 128:
        color = LV_100ASK_2048_NUMBER_128_COLOR;
        break;
    case 256:
        color = LV_100ASK_2048_NUMBER_256_COLOR;
        break;
    case 512:
        color = LV_100ASK_2048_NUMBER_512_COLOR;
        break;
    case 1024:
        color = LV_100ASK_2048_NUMBER_1024_COLOR;
        break;
    case 2048:
        color = LV_100ASK_2048_NUMBER_2048_COLOR;
        break;
    default:
        color = LV_100ASK_2048_NUMBER_2048_COLOR;
        break;
    }
    return color;
}

static bool game_over(uint16_t matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    bool ended = true;

    if (count_empty(matrix) > 0)
        return false;
    if (find_pair_down(matrix))
        return false;

    rotate_matrix(matrix);
    if (find_pair_down(matrix))
        ended = false;

    rotate_matrix(matrix);
    rotate_matrix(matrix);
    rotate_matrix(matrix);

    return ended;
}

static void Cont_Create(lv_obj_t *par)
{
    lv_obj_t *obj = lv_obj_create(par);
    // lv_obj_align(obj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
    lv_obj_set_size(obj, WINDOW_WIDTH, WINDOW_HEIGHT);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(obj, LV_COLOR_WHITE, LV_PART_MAIN);
    lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE); // Propagate the events to the parent too
    // lv_obj_add_event_cb(obj, (lv_event_cb_t)ContApps_EventHandler, LV_EVENT_GESTURE, NULL);
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
    lv_2048_funcbtn_create(Cont);
    lv_2048_gameinfo_create(Cont);
    game_cont = lv_100ask_2048_create(Cont);
    PageAnim_Create();
    Msg_Create(Cont);
    MsgAnim_Create();
    PageAnim_Play(false);
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
    (void)Page;
}
