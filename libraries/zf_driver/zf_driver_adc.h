#ifndef _zf_driver_adc_h
#define _zf_driver_adc_h


#include "zf_common_typedef.h"




uint16  adc_convert(const char *path);
float adc_get_scale(const char *path);


#endif
