#include <cstring>

char* reverse_rgb_data (const char *data, int width, int height, int bytes_per_pixel)
{
  char *result = new char [width * height * bytes_per_pixel];

  char *temp = result;

  int row_size = width * 3;

  for (int row = height - 1; row >= 0; row--)
     {
      memcpy (temp, &data [row * row_size ], row_size);

      temp += row_size;
     }

  return result;
}


char* rgb_to_rgba (const char *rgb_data, int w, int h)
{
  char *rgba_data = new char [w * h * 4];
  int source_size = w * h * 3;

  int c = 0;
  int i = 0;

  while (i < source_size)
       {
        rgba_data [c] = rgb_data [i];
        i++;
        c++;

        rgba_data [c] = rgb_data [i];
        i++;
        c++;

        rgba_data [c] = rgb_data [i];
        i++;
        c++;

        rgba_data [c] = 255;
        c++;
       }

  return rgba_data;
}


/*
image_get_region - copy image region, where
data - source
w, h - width and height of the source image
offset_x, offset_y - from where we want to copy (top left position)
size_w, size_h - width and height of destination image
bytes_per_pixel - bps of the source
*/

char* image_get_region (const char *data, int w, int h, int offset_x, int offset_y, int size_w, int size_h, int bytes_per_pixel)
{
  char *out_data = new char [size_w * size_h * bytes_per_pixel];
  
  int c = 0;
  
  for (int y = 0; y < size_h; y++)
  for (int x = 0; x < size_w; x++)
     {
      //y * w + x - w
      int offset = ((y + offset_y) * w + (x + offset_x) - w) * bytes_per_pixel;
      
      for (int i = 0; i < bytes_per_pixel; i++)
          {
           out_data [c++] = data[offset + i];
          }
     }
  
  return out_data;
}
