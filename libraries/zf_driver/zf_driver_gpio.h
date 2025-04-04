#ifndef _zf_driver_gpio_h
#define _zf_driver_gpio_h


#include "zf_common_typedef.h"

void    gpio_set_level          (const char *path, uint8 dat);
uint8   gpio_get_level          (const char *path);


#endif
