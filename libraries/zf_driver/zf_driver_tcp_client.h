#ifndef _zf_driver_tcp_client_h
#define _zf_driver_tcp_client_h


#include "zf_common_typedef.h"

int8 tcp_client_init(const char *ip_addr, uint32 port);

uint32 tcp_client_send_data(const uint8 *buff, uint32 length);
uint32 tcp_client_read_data(uint8 *buff, uint32 length);


#endif
