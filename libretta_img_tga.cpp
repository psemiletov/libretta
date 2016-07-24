#include <iostream>
#include <fstream>
#include <cstring>

#include "libretta_img_tga.h"
#include "libretta_img_utils.h"

using namespace std;


CTGAImage::CTGAImage (const char *fname)
{
  fstream myfile;
  myfile.open (fname, ifstream::in | ios::binary);

  data_rgb = 0;

  if (! myfile.is_open())
     return;
     
  int size = 0;

  myfile.seekg (0, ios::end);
  size = myfile.tellg();
  myfile.seekg (0, ios::beg);

  myfile.read (reinterpret_cast<char *>(&tga_header), sizeof (TTGAHeader));

//  cout << "bits = "  << (int)tga_header.bits << endl;

  int data_size = size - sizeof (struct TTGAHeader);

  if (tga_header.imagetype == 2) //RGB
     {       
      data_rgb = new char [data_size];
      myfile.read (data_rgb, data_size);
      myfile.close();
     }

  if (tga_header.imagetype == 10) //RGB+RLE
     {       
//      cout << "rle" << endl;
      char *temp_rgb = new char [data_size];
      myfile.read (temp_rgb, data_size);
      myfile.close();
     
      size_t image_size = tga_header.width * tga_header.height * (tga_header.bits / 8);
      size_t pixel_size = tga_header.bits / 8;

      data_rgb = new char [image_size];

      char length;
      size_t index = 0;
      char *current = &temp_rgb[0];

      
      while (index < image_size) 
            {
             if (*current & 0x80) // RLE chunk (High bit = 1)
                {
                 length = *current - 127;
                 current++; //move to pixels

                 for (char i = 0; i != length; ++i)
		     {
		      memcpy (&data_rgb[index], current, pixel_size);
		      index += pixel_size;
		     }
		  
                 current += pixel_size; 
                }
             else //normal chunk
                 {
                  length = *current + 1;
                  current++;
                  
                  for (char i = 0; i != length; ++i)
		     {
		      memcpy (&data_rgb[index], current, pixel_size); 
      		      index += pixel_size;
		      current += pixel_size;
         	     }
  
                 }
            }

	  delete []temp_rgb;
         }
      
      
      if (tga_header.ystart == 0)
         {
          char *t = reverse_rgb_data (data_rgb, tga_header.width, tga_header.height, /*3*/tga_header.bits / 8);
          delete [] data_rgb;
          data_rgb = t;
         }
}


CTGAImage::~CTGAImage()
{
  if (data_rgb)
      delete [] data_rgb;
}
