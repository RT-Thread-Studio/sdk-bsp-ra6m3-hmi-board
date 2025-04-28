/*
 * Licensed under the GNU General Public License version 2 with exceptions. See
 * LICENSE file in the project root for full license information
 */

#include <osal.h>
#include <time.h>
#include <sys/time.h>

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_common.h>

#include <bsp_api.h>
#include "board.h"

#define OS_THREAD_NAME      "soem_th"

static rt_uint32_t us_ticks;

void osal_timer_init(void)
{
	rt_uint32_t cmp = SysTick->LOAD;
    us_ticks = 1 * cmp / (1000000 / RT_TICK_PER_SECOND);
	rt_kprintf("rt-thread hwtimer5 1us = %d ticks\n", us_ticks);
}

#define  timercmp(a, b, CMP)                                \
  (((a)->tv_sec == (b)->tv_sec) ?                           \
   ((a)->tv_usec CMP (b)->tv_usec) :                        \
   ((a)->tv_sec CMP (b)->tv_sec))
#define  timeradd(a, b, result)                             \
  do {                                                      \
    (result)->tv_sec = (a)->tv_sec + (b)->tv_sec;           \
    (result)->tv_usec = (a)->tv_usec + (b)->tv_usec;        \
    if ((result)->tv_usec >= 1000000)                       \
    {                                                       \
       ++(result)->tv_sec;                                  \
       (result)->tv_usec -= 1000000;                        \
    }                                                       \
  } while (0)
#define  timersub(a, b, result)                             \
  do {                                                      \
    (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;           \
    (result)->tv_usec = (a)->tv_usec - (b)->tv_usec;        \
    if ((result)->tv_usec < 0) {                            \
      --(result)->tv_sec;                                   \
      (result)->tv_usec += 1000000;                         \
    }                                                       \
  } while (0)

#define USECS_PER_SEC   1000000
#define USECS_PER_TICK  (USECS_PER_SEC / CFG_TICKS_PER_SECOND)


/* Workaround for rt-labs defect 776.
 * Default implementation of udelay() didn't work correctly when tick was
 * shorter than one millisecond.
 */
//void udelay (uint32_t us)
//{
////   tick_t ticks = (us / USECS_PER_TICK) + 1;
////   task_delay (ticks);
//}

//int gettimeofday(struct timeval *tp, void *tzp)
//{
//   tick_t tick = tick_get();
//   tick_t ticks_left;

//   ASSERT (tp != NULL);

//   tp->tv_sec = tick / CFG_TICKS_PER_SECOND;

//   ticks_left = tick % CFG_TICKS_PER_SECOND;
//   tp->tv_usec = ticks_left * USECS_PER_TICK;
//   ASSERT (tp->tv_usec < USECS_PER_SEC);

//   return 0;
//}
void osal_time_diff(ec_timet *start, ec_timet *end, ec_timet *diff)
{
    // Calculate difference in seconds
    diff->sec = end->sec - start->sec;

    // Calculate difference in microseconds
    if (end->usec < start->usec) {
        // Borrow 1 second if the microseconds in end are less than in start
        diff->sec -= 1;
        diff->usec = (1000000 + end->usec) - start->usec;
    } else {
        diff->usec = end->usec - start->usec;
    }
}

int osal_usleep (uint32 usec)
{
	//udelay(usec);

	/*ajustment for precision*/
	//usec -= usec / 4080;
	usec -= usec / 1500;

	/*rt_hw_us_delay work for a delay less than 16us*/
	do{
		if(usec>=1000)
		{
			rt_hw_us_delay(1000);
			usec -= 1000;
		}else{
			rt_hw_us_delay(usec);
			usec = 0;
		}
	}while(usec>0);
	return 0;
}

int osal_gettimeofday(struct timeval *tv, struct timezone *tz)
{
//   return gettimeofday(tv, tz);
	RT_ASSERT (tv != NULL);

    rt_uint32_t timer_tick,rt_tick;

	rt_base_t level = rt_hw_interrupt_disable();
	timer_tick = SysTick->VAL;
	rt_tick = rt_tick_get();
	rt_hw_interrupt_enable(level);

	tv->tv_sec = rt_tick/1000;
	tv->tv_usec = (rt_tick % 1000)*1000 + timer_tick / us_ticks;

	return 0;
}

ec_timet osal_current_time (void)
{
   struct timeval current_time;
   ec_timet return_value;

   osal_gettimeofday (&current_time, 0);
   return_value.sec = current_time.tv_sec;
   return_value.usec = current_time.tv_usec;
   return return_value;
}

void osal_timer_start (osal_timert * self, uint32 timeout_usec)
{
   struct timeval start_time;
   struct timeval timeout;
   struct timeval stop_time;

   osal_gettimeofday (&start_time, 0);
   timeout.tv_sec = timeout_usec / USECS_PER_SEC;
   timeout.tv_usec = timeout_usec % USECS_PER_SEC;
   timeradd (&start_time, &timeout, &stop_time);

   self->stop_time.sec = stop_time.tv_sec;
   self->stop_time.usec = stop_time.tv_usec;
}

boolean osal_timer_is_expired (osal_timert * self)
{
   struct timeval current_time;
   struct timeval stop_time;
   int is_not_yet_expired;

   osal_gettimeofday (&current_time, 0);
   stop_time.tv_sec = self->stop_time.sec;
   stop_time.tv_usec = self->stop_time.usec;
   is_not_yet_expired = timercmp (&current_time, &stop_time, <);

   return is_not_yet_expired == 0;
}

void *osal_malloc(size_t size)
{
   return rt_malloc(size);
}

void osal_free(void *ptr)
{
   rt_free(ptr);
}


rt_thread_t osal_thread_create(rt_thread_t thandle, int stacksize, void *func, void *param)
{
    char tname[RT_NAME_MAX];
    static unsigned short counter = 0;

    rt_snprintf(tname, RT_NAME_MAX, "%s%d", OS_THREAD_NAME, counter++);

    thandle = rt_thread_create(tname, func, param, stacksize, 25, 10);
    rt_thread_startup(thandle);
    return thandle;
}

int osal_thread_create_rt(void *thandle, int stacksize, void *func, void *param)
{
//   thandle = task_spawn ("worker_rt", func, 15 ,stacksize, param);
//   if(!thandle)
//   {
//      return 0;
//   }
   return 1;
}
