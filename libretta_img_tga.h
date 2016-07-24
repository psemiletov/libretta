#ifndef IMG_TGA_H
#define IMG_TGA_H

//#include <cinttypes> 

#pragma pack(push, 1)


struct TTGAHeader
{
  unsigned char identsize;          // size of ID field that follows 18 byte header (0 usually)
  unsigned char colourmaptype;      // type of colour map 0=none, 1=has palette
  unsigned char imagetype;          // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

  unsigned short int colourmapstart;     // first colour map entry in palette
  unsigned short int colourmaplength;    // number of colours in palette
  unsigned char colourmapbits;      // number of bits per palette entry 15,16,24,32

  unsigned short int xstart;             // image x origin
  unsigned short int ystart;             // image y origin, if > 0 - top left is the start of coords

  unsigned short int width;              // image width in pixels
  unsigned short int height;             // image height in pixels
  unsigned char bits;               // image bits per pixel 8,16,24,32
  unsigned char descriptor;         // image descriptor bits (vh flip bits)
};

#pragma pack(pop)


class CTGAImage
{
public:

  TTGAHeader tga_header;

  char *data_rgb;

  CTGAImage (const char *fname);
  ~CTGAImage();

};

#endif
