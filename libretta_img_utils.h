#ifndef IMG_UTILS_H
#define IMG_UTILS_H

char* reverse_rgb_data (const char *data, int width, int height, int bytes_per_pixel);
char* rgb_to_rgba (const char *rgb_data, int w, int h);
char* image_get_region (const char *data, int w, int h, int offset_x, int offset_y, int size_w, int size_h, int bytes_per_pixel);



#endif