#ifndef _zf_driver_file_h
#define _zf_driver_file_h


#include "zf_common_typedef.h"

int file_io_operation(const char *path, int flags, uint8 *buf, size_t size);
int8 file_read_string(const char *path, char *str);
int8 file_write_string(const char *path, char *str);


#define file_write_dat(path, value)                 file_io_operation(path, O_WRONLY, (uint8 *)&(value), sizeof(value))
#define file_read_dat(path, ret_value)              file_io_operation(path, O_RDONLY, (uint8 *)(ret_value), sizeof(*(ret_value)))


#endif

