#ifndef _zf_driver_udp_h
#define _zf_driver_udp_h


#include "zf_common_typedef.h"

int8 udp_init(const char *ip_addr, uint32 port);

uint32 udp_send_data(const uint8 *buff, uint32 length);
uint32 udp_read_data(uint8 *buff, uint32 length);

#endif
