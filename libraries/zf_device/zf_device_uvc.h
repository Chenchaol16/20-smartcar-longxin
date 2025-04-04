#ifndef _zf_driver_uvc_h
#define _zf_driver_uvc_h


#include "zf_common_typedef.h"

#define UVC_WIDTH   160
#define UVC_HEIGHT  120
#define UVC_FPS     60

int8 uvc_camera_init(const char *path);
int8 wait_image_refresh();


extern uint8_t *rgay_image;
#endif
