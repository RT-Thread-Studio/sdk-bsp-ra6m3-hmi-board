#ifndef _netdev_hook_h_
#define _netdev_hook_h_

#ifdef __cplusplus
extern "C"
{
#endif

#include "osal.h"
#include "oshw.h"

int install_hook(ecx_portt *port, const char *ifname);

int uninstall_hook(ecx_portt *port);

int net_send(unsigned char *data, int len);

int net_recv(unsigned char *data, int len);

#ifdef __cplusplus
}
#endif

#endif
