#include "zf_driver_adc.h"
#include "zf_driver_file.h"


uint16 adc_convert(const char *path)
{
    uint16 adc_reg = 0;

	char str[10] = {0};
	file_read_string(path, str);
	adc_reg = atoi(str);
    
    return adc_reg;
}

float adc_get_scale(const char *path)
{
	float scale = 0;

	char str[20] = {0};
	file_read_string(path, str);

	scale = atof(str);
    
    return scale;
}

