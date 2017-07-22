#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "DIPs.h"
#include "Movie.h"

void BlackNWhite(IMAGE *image)
{	
	YUV2RGBImage(image);
	int tmpR, tmpG, tmpB;
        int x, y;
        int Average;
	
	assert(image);

        for( y = 0; y < image->Height; y++ )
                for( x = 0; x < image->Width; x++ )
                {
			tmpR = GetPixelR(image, x, y);			
			tmpG = GetPixelG(image, x, y);
			tmpB = GetPixelB(image, x, y);			
			Average = (tmpR + tmpG + tmpB)/3;
			SetPixelR(image, x, y, Average);
                        SetPixelG(image, x, y, Average);
			SetPixelB(image, x, y, Average);
                }
	RGB2YUVImage(image);
}
void VFlip(IMAGE *image)   
{
	YUV2RGBImage(image);
	int x,y;
	int tmpR, tmpG, tmpB;
	
	assert(image);
	
	IMAGE *tmp;
	tmp = CreateImage(image->Width, image->Height);

	for( y = 0; y < image->Height; y++ )
                for( x = 0; x < image->Width; x++ )
                {
			tmpR = GetPixelR(image, x, y);
                        SetPixelR(tmp, x, y, tmpR);
                        tmpG = GetPixelG(image, x, y);
                        SetPixelG(tmp, x, y, tmpG);
                        tmpB = GetPixelB(image, x, y);
                        SetPixelB(tmp, x, y, tmpB);
                }
        for( y = 0; y < image->Height; y++ )
                for( x = 0; x < image->Width; x++ )
                {
			tmpR = GetPixelR(tmp, x, ((image->Height)-y-1));
			SetPixelR(image, x, y, tmpR);
			tmpG = GetPixelG(tmp, x, ((image->Height)-y-1));
			SetPixelG(image, x, y, tmpG);
			tmpB = GetPixelB(tmp, x, ((image->Height)-y-1));
			SetPixelB(image, x, y, tmpB);
                }	
	RGB2YUVImage(image);
	DeleteImage(tmp);
}

void HMirror(IMAGE *image) 
{
	YUV2RGBImage(image);
        int x,y;
	int tmpR, tmpG, tmpB;

	assert(image);

        for( y = 0; y < image->Height; y++ )
                for( x = 0; x < ((image->Width)/2); x++ )
                {
			tmpR = GetPixelR(image, ((image->Width)-x-1), y);
			SetPixelR(image, x, y, tmpR);
			tmpG = GetPixelG(image, ((image->Width)-x-1), y);
                        SetPixelG(image, x, y, tmpG);
			tmpB = GetPixelB(image, ((image->Width)-x-1), y);
                        SetPixelB(image, x, y, tmpB);

                }
	RGB2YUVImage(image);
}

void Edge(IMAGE *image) 
{
	YUV2RGBImage(image);
        int             x, y, m, n, a, b;
        int             tmpR = 0;
        int             tmpG = 0;
        int             tmpB = 0;
	IMAGE *tmp;

	assert(image);

	tmp = CreateImage(image->Width, image->Height);
	
        for (y = 0; y < image->Height; y++){
                for (x = 0; x < image->Width; x++) {
                	SetPixelR(tmp, x, y, GetPixelR(image, x, y));
			SetPixelG(tmp, x, y, GetPixelG(image, x, y));
			SetPixelB(tmp, x, y, GetPixelB(image, x, y));
		}
        }

        for (y = 0; y < image->Height; y++){
                for (x = 0; x < image->Width; x++){
                        for (n = -1; n <= 1; n++){
                                for (m = -1; m <= 1; m++) {
                                        a = x + m;
                                        b = y + n;
                                        if (a > image->Width - 1)
                                                a = image->Width - 1;
                                        if (a < 0)
                                                a = 0;
                                        if (b > image->Height - 1)
                                                b = image->Height - 1;
                                        if (b < 0)
                                                b = 0;

                                        if ((n==0)&&(m==0))
                                        {
                                                tmpR += 8*GetPixelR(tmp, a, b);
                                                tmpG += 8*GetPixelG(tmp, a, b);
                                                tmpB += 8*GetPixelB(tmp, a, b);
                                        }
                                        else
                                        {
                                                tmpR -= GetPixelR(tmp, a, b);
                                                tmpG -= GetPixelG(tmp, a, b);
                                                tmpB -= GetPixelB(tmp, a, b);
                                        }
				}
			}
			SetPixelR(image, x, y, ((tmpR > 255)? 255 : (tmpR <0)? 0 : tmpR));
			SetPixelG(image, x, y, ((tmpG > 255)? 255 : (tmpG <0)? 0 : tmpG));
			SetPixelB(image, x, y, ((tmpB > 255)? 255 : (tmpB <0)? 0 : tmpB));
                        
			tmpR = tmpG = tmpB = 0;
                }
        }
	RGB2YUVImage(image);
	DeleteImage(tmp);
}

/* Posterization */
void Posterize( IMAGE *image)
{
	YUV2RGBImage(image);
	unsigned int pbits = 6;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	unsigned char maskzero[8] = {0xff-0x1, 0xff-0x2, 0xff-0x4, 0xff-0x8, 0xff-0x10, 0xff-0x20, 0xff-0x40, 0xff-0x80};
        unsigned char maskone[8]  = {0x0     , 0x1     , 0x3     , 0x7     , 0xf      , 0x1f     , 0x3f     , 0x7f     };
        int x, y;
	unsigned char temp;


	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

        for(x = 0; x < WIDTH; x ++)
        {
                for(y = 0; y < HEIGHT; y ++)
                {
			temp = GetPixelR(image, x, y);
                        temp &= maskzero[pbits - 1];
                        temp |= maskone[pbits - 1];
			SetPixelR(image, x, y, temp);

			temp = GetPixelG(image, x, y);
                        temp &= maskzero[pbits - 1];
                        temp |= maskone[pbits - 1];
			SetPixelG(image, x, y, temp);

			temp = GetPixelB(image, x, y);
                        temp &= maskzero[pbits - 1];
                        temp |= maskone[pbits - 1];
			SetPixelB(image, x, y, temp);
                }
        }
	RGB2YUVImage(image);
}


