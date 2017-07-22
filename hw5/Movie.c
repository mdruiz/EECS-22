#include "Movie.h"
#include <stdlib.h>
#include <assert.h>

/* allocate the memory space for the movie */
/* and the memory space for the frame list. */
/* return the pointer to the movie */
MOVIE *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H)
{
	MOVIE *movie;
	ILIST *l;
	if(!( movie = (MOVIE *)malloc(sizeof(MOVIE))))
	{
		return NULL;
	}
	if(!( l = (ILIST *)malloc(sizeof(ILIST))))
	{
		return NULL;
	}
	movie->Width = W;
	movie->Height = H;
	movie->NumFrames = nFrames;
	l = NewImageList();
	movie->Frames = l;

	return movie;
}

/*release the memory space for the frames and the frame list. */
/*release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	DeleteImageList(movie->Frames);
	free(movie);
}

/* convert a YUV image into a RGB image */
void YUV2RGBImage(IMAGE *Image)
{
	int tmpY, tmpU, tmpV, tmpR,tmpG, tmpB;
	int C,D,E, x,y;
	for (y = 0; y < Image->Height; y++)
		for (x = 0; x < Image->Width; x++) 
		{
			tmpY = GetPixelY(Image,x,y);
			tmpU = GetPixelU(Image,x,y);
			tmpV = GetPixelV(Image,x,y);

			C = tmpY - 16;
			D = tmpU - 128;
			E = tmpV - 128;
			
			tmpR = clip((298 * C +409 * E +128) >> 8);	
			tmpG = clip((298 * C -100 * D -208 * E +128) >> 8);
			tmpB = clip((298 * C +516 * D +128) >> 8);
	
			SetPixelR(Image,x,y,tmpR);
			SetPixelG(Image,x,y,tmpG);
			SetPixelB(Image,x,y,tmpB);
		}
}

/* convert a RGB image into a YUV image */
void RGB2YUVImage(IMAGE *Image)
{
	int tmpY, tmpU, tmpV, tmpR,tmpG, tmpB;
	int x,y;
	for (y = 0; y < Image->Height; y++)
        	for (x = 0; x < Image->Width; x++)
 		{
			tmpR = GetPixelR(Image,x,y);
			tmpG = GetPixelG(Image,x,y);
			tmpB = GetPixelB(Image,x,y);
			
			tmpY = clip(((66 * tmpR+129 * tmpG+25 * tmpB +128) >> 8) +16);
			tmpU = clip(((-38 * tmpR-74 * tmpG+112 * tmpB +128) >> 8) +128);
			tmpV = clip(((112 * tmpR-94 * tmpG-18 * tmpB +128) >> 8) +128);
		
			SetPixelY(Image,x,y,tmpY);
			SetPixelU(Image,x,y,tmpU);
			SetPixelV(Image,x,y,tmpV);
		}

}

int clip(int x)
{
	if(x <= 0)
	{
		return 0;
	}
	
	if(x >= 255 )
	{	
		return 255;
	}
	else
		return x;
}

