/*
   source code from https://club.rt-thread.org/ask/article/3ab411229774cf77.html
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <time.h>

#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME "rtc"
#include <rtdbg.h>

#define RTC_NAME "rtc" /* rt_hw_rtc_register("rtc") in rtc_drv.c*/

rt_sem_t rtc_init_sem = RT_NULL;

int user_rtc_init(void)
{
    rt_err_t ret = RT_EOK;
    time_t now;
    rt_device_t device = RT_NULL;

    /*创建初始化完成信号量*/
    rtc_init_sem = rt_sem_create("rtc init flag", 0, 0);

    if(rtc_init_sem == RT_NULL)
    {
        rt_kprintf("rtc sem init failed!\n");
        return RT_ERROR;
    }
    /*寻找设备*/
    device = rt_device_find(RTC_NAME);
    if (!device)
    {
        rt_kprintf("find %s failed!\n", RTC_NAME);
        return RT_ERROR;
    }
    /*初始化RTC设备*/
    if(rt_device_open(device, 0) != RT_EOK)
    {
        rt_kprintf("open %s failed!\n", RTC_NAME);
        return RT_ERROR;
    }
    /* 设置日期 */
    ret = set_date(2023, 8, 17);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC date failed\n");
        return ret;
    }
    /* 设置时间 */
    ret = set_time(14, 4, 50);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC time failed\n");
        return ret;
    }
    rt_sem_release(rtc_init_sem);
    /* 获取时间 */
    now = time(RT_NULL);
    rt_kprintf("RTC device init success,now time is %s\n", ctime(&now));
    return ret;
}

/*使用裝置初始化*/
INIT_ENV_EXPORT(user_rtc_init);

static time_t now;
void user_alarm_callback(rt_alarm_t alarm, time_t timestamp)
{
    now = time(RT_NULL);
    rt_kprintf("The alarm clock rings, now time is %s\n", ctime(&now));
    rt_alarm_stop(alarm);
}
void alarm_test(void)
{
    if(rt_sem_trytake(rtc_init_sem) != RT_EOK)
    {
        rt_kprintf("please init rtc first\n");
        return ;
    }
    struct rt_alarm_setup setup;
    struct rt_alarm * alarm = RT_NULL;
    static time_t now;
    struct tm p_tm;
    if (alarm != RT_NULL)
        return;
    /*获取当前时间戳，并把下一秒时间设置为闹钟时间 */
    now = time(NULL) + 5;
    gmtime_r(&now,&p_tm);
    setup.flag = RT_ALARM_SECOND;
    setup.wktime.tm_year = p_tm.tm_year;
    setup.wktime.tm_mon = p_tm.tm_mon;
    setup.wktime.tm_mday = p_tm.tm_mday;
    setup.wktime.tm_wday = p_tm.tm_wday;
    setup.wktime.tm_hour = p_tm.tm_hour;
    setup.wktime.tm_min = p_tm.tm_min;
    setup.wktime.tm_sec = p_tm.tm_sec;
    alarm = rt_alarm_create(user_alarm_callback, &setup);
    if(RT_NULL != alarm)
    {
        rt_alarm_start(alarm);
    }
    rt_sem_release(rtc_init_sem);
}

/*export msh cmd*/
MSH_CMD_EXPORT(alarm_test,a alarm test);
