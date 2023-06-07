#include "DisplayPrivate.h"

#define DBG_TAG "WLAN"
#define DBG_LVL DBG_LOG

#include <rtdbg.h>

typedef struct wifi_info
{
    char *ssid;
    char *password;
}wifi_info_t;


static struct rt_thread wifi_scan_thread;
static struct rt_thread wifi_connect_thread;
static rt_uint8_t wifi_scan_thread_stack[512];
static rt_uint8_t wifi_connect_thread_stack[1024];
static wifi_info_t Wifi_Info;

static rt_err_t wifi_scan_result_cache(struct rt_wlan_info *info)
{
    rt_err_t err = RT_EOK;
    if ((info == RT_NULL) || (info->ssid.len == 0)) return -RT_EINVAL;
    LOG_D("ssid:%s len:%d mac:%02x:%02x:%02x:%02x:%02x:%02x", info->ssid.val, info->ssid.len,
                  info->bssid[0], info->bssid[1], info->bssid[2], info->bssid[3], info->bssid[4], info->bssid[5]);
    return err;
}

static void user_ap_info_callback(int event, struct rt_wlan_buff *buff, void *parameter)
{
    struct rt_wlan_info *info = RT_NULL;
    int index = 0;
    int ret = RT_EOK;

    RT_ASSERT(event == RT_WLAN_EVT_SCAN_REPORT);
    RT_ASSERT(buff != RT_NULL);
    RT_ASSERT(parameter != RT_NULL);

    info = (struct rt_wlan_info *)buff->data;
    index = *((int *)(parameter));

    ret = wifi_scan_result_cache(info);
    if(ret == RT_EOK)
    {
		/*Print the info*/
		char ssid_s[40];
		sprintf(ssid_s, "%s", &(info->ssid.val[0]));
		LOG_I("Scan info :[%s]\n",ssid_s);
		WIFI_Add_List(ssid_s);
		index++;
		*((int *)(parameter)) = index;
    }
}

static void wifi_scan_thread_entry(void *parameter)
{
	struct rt_wlan_info *info = RT_NULL;
    int ret = 0;
    int i = 0;
    ret = rt_wlan_register_event_handler(RT_WLAN_EVT_SCAN_REPORT,user_ap_info_callback,&i);
    if(ret != RT_EOK)
    {
        LOG_E("Scan register user callback error:%d!\n",ret);
        return;
    }
    /*Todo: what can i do for it return val */
    ret = rt_wlan_scan_with_info(info);
    if(ret != RT_EOK)
    {
        LOG_E("Scan with info error:%d!\n",ret);
		return;
    }
}

int WiFi_Scan(void)
{
    rt_err_t err;
	
	if((wifi_scan_thread.stat & RT_THREAD_RUNNING) == RT_THREAD_RUNNING)
		return -1;

	err = rt_thread_init(&wifi_scan_thread, "WIFI_SCAN", wifi_scan_thread_entry, RT_NULL,
   &wifi_scan_thread_stack[0], sizeof(wifi_scan_thread_stack), 22, 0);
	if(err != RT_EOK)
	{
		LOG_E("Failed to create WIFI thread");
		return -1;
	}

	
	WIFI_List_Clear();
    rt_thread_startup(&wifi_scan_thread);
    return 0;
}

static void wifi_connect_thread_entry(void *parameter)
{
    wifi_info_t* wf = (wifi_info_t*)parameter;
	int ret = rt_wlan_connect(wf->ssid,wf->password);
	LOG_I("ssid: %s pwd: %s",wf->ssid,wf->password);
    wifi_join_event(ret);
}

int WiFi_Join(const char *ssid, const char *password)
{
    rt_err_t err;
    if((wifi_connect_thread.stat & RT_THREAD_RUNNING) == RT_THREAD_RUNNING)
		return -1;
    Wifi_Info.ssid = (char*)ssid;
    Wifi_Info.password = (char*)password;
	err = rt_thread_init(&wifi_connect_thread, "WIFI_JOIN", wifi_connect_thread_entry, &Wifi_Info,
   &wifi_connect_thread_stack[0], sizeof(wifi_connect_thread_stack), 22, 0);
	if(err != RT_EOK)
	{
		LOG_E("Failed to create WIFI thread");
		return -1;
	}
	rt_thread_startup(&wifi_connect_thread);
	return 0;
}
