#ifndef __zf_device_ips200_fb_h__
#define __zf_device_ips200_fb_h__

#include "zf_common_typedef.h"

#define IPS200_DEFAULT_PENCOLOR         (RGB565_RED    )                        // 默认的画笔颜色
#define IPS200_DEFAULT_BGCOLOR          (RGB565_WHITE  )                        // 默认的背景颜色


void    ips200_clear            (void);
void    ips200_full             (const uint16 color);
void    ips200_draw_point       (uint16 x, uint16 y, const uint16 color);
void    ips200_draw_line        (uint16 x_start, uint16 y_start, uint16 x_end, uint16 y_end, const uint16 color);

void    ips200_show_char        (uint16 x, uint16 y, const char dat);
void    ips200_show_string      (uint16 x, uint16 y, const char dat[]);
void    ips200_show_int         (uint16 x, uint16 y, const int32 dat, uint8 num);
void    ips200_show_uint        (uint16 x, uint16 y, const uint32 dat, uint8 num);
void    ips200_show_float       (uint16 x, uint16 y, const double dat, uint8 num, uint8 pointnum);

void    ips200_show_gray_image  (uint16 x, uint16 y, const uint8 *image, uint16 width, uint16 height);

void    ips200_init             (const char *path);


void ips200_show_binary_image(uint16_t x, uint16_t y, const uint8_t *image, uint16_t width, uint16_t height, const int midline[]);
void ips200_show_binary_image_DMX(uint16_t x, uint16_t y, const uint8_t *image, uint16_t width, uint16_t height, const int midline[]);
#endif