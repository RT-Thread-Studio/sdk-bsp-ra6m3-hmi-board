#include <rtthread.h>
//#include <rtdevice.h>

#include "netif/ethernetif.h"

#include "nicdrv.h"


/******************************************************************************
* receive fifo buf
*/
#define HOOK_RX_BUFSIZE 10

static uint8_t netfrmbuf[HOOK_RX_BUFSIZE][1024];
static int netfrmbuf_cnt[HOOK_RX_BUFSIZE];
static int netfrm_head = 0;
static int netfrm_tail = 0;
static int netfrm_full = 0;

/******************************************************************************
* store netif and old function addr
*/
static struct netif *netif = RT_NULL;
static netif_linkoutput_fn link_output;
static netif_input_fn input;

/******************************************************************************
* rx/tx hook function 
*/
/* get tx data */
static err_t _netif_linkoutput(struct netif *netif, struct pbuf *p)
{
	return link_output(netif, p);
}

/* get rx data */
static err_t _netif_input(struct pbuf *p, struct netif *inp)
{
	if(p->tot_len>=14)
	{
		char *data = p->payload;
		if(data[12]=='\x88' && data[13]=='\xa4') //filter for ethercat frame
		{
			if(netfrm_full == 0){
				pbuf_copy_partial(p, netfrmbuf[netfrm_tail], p->tot_len, 0);
				netfrmbuf_cnt[netfrm_tail] = p->tot_len;
				netfrm_tail = (netfrm_tail+1) % HOOK_RX_BUFSIZE;
				if(netfrm_tail==netfrm_head)
					netfrm_full = 1;
			}
		}
	}
    return input(p, inp);
}

/******************************************************************************
* hook install
*/
int install_hook(ecx_portt *port, const char *ifname)
{
	struct eth_device *device;
    rt_base_t level;
	
	netfrm_head = 0;
	netfrm_tail = 0;
	netfrm_full = 0;
	
	if(netif == RT_NULL){
		rt_kprintf("hook installing on  %s\n", ifname);
		device = (struct eth_device *)rt_device_find(ifname);
		if (device == RT_NULL){
			rt_kprintf("hook install error 'device == RT_NULL'\n");
			return 0;
		}
		if ((device->netif == RT_NULL) || (device->netif->linkoutput == RT_NULL)){
			rt_kprintf("hook install error '(device->netif == RT_NULL) || (device->netif->linkoutput == RT_NULL)'\n");
			return 0;
		}
		rt_kprintf("device %s found: 0x%x \n", ifname, (uint32_t)device);
	}else{
		rt_kprintf("device %s hook already installed, uninstall it before intalling a new one\n", ifname);
		return 0;
	}
    netif = device->netif;
	
    //install netdev hook
    level = rt_hw_interrupt_disable();
    link_output = netif->linkoutput;
    netif->linkoutput = _netif_linkoutput;

    input = netif->input;
    netif->input = _netif_input;
    rt_hw_interrupt_enable(level);
	//rt_kprintf("hook installed on %s\n", ifname);

	return 1;
}

/******************************************************************************
* hook uninstall
*/
int uninstall_hook(ecx_portt *port)
{
    rt_base_t level;
	
	//uninstall netdev hook
	if(netif != RT_NULL){
		level = rt_hw_interrupt_disable();
		netif->input = input;
		netif->linkoutput = link_output;
		netif = RT_NULL;
		rt_hw_interrupt_enable(level);
	}
	
	//rt_kprintf("hook uninstalled\n");
	return 1;
}

/******************************************************************************
* netdev send api
* when sucess return sent data len, otherwise return -1 
*/
int net_send(unsigned char *data, int len)
{
	struct pbuf *p;
	
	if(len<=0)
		return -1;
	
    p = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_POOL);
    
    if (p != NULL)
    {
		pbuf_take(p, data, len);
		
		_netif_linkoutput(netif,p);
        pbuf_free(p);
	}
	else{
		rt_kprintf("net_send alloc buffer error\n");
		return -1;
	}
	
	return len;
}

/******************************************************************************
* netdev send api
* return received data len 
*/
int net_recv(unsigned char *data, int max_len)
{
	if(netfrm_full == 0 && netfrm_tail==netfrm_head){
		return 0;
	}
	
	int total = netfrmbuf_cnt[netfrm_head];
	if(total > max_len) total = max_len;
	
	rt_memcpy(data, netfrmbuf[netfrm_head], total);
	netfrm_head = (netfrm_head+1) % HOOK_RX_BUFSIZE;
	if(netfrm_tail==netfrm_head)
		netfrm_full = 0;

	return total;
}


void net_hook_test(int argc, char **argv)
{
    unsigned char frame[] = "\xff\xff\xff\xff\xff\xff\x01\x01\x01\x01\x01\x01\x88\xa4\x0d\x10\
\x08\x01\x00\x00\x03\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

    install_hook(NULL, "e0");
    net_send(frame,60);
    rt_thread_mdelay(20000);
    uninstall_hook(NULL);
}
MSH_CMD_EXPORT(net_hook_test, net_hook_test sample on 'e0');
