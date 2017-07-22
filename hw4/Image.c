
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#include "Constants.h"
#include "Image.h"
#include "FileIO.h"


/* Get the color intensity of the Red channel of pixel (x, y) in image */
unsigned char GetPixelR(IMAGE *image, unsigned int x,  unsigned int y)
{
	unsigned char r;
	r = *((image->R)+(x+(y* (image->Width))));
	return(r);
}
/* Get the color intensity of the Green channel of pixel (x, y) in image */
unsigned char GetPixelG(IMAGE *image, unsigned int x,  unsigned int y)
{
	unsigned char g;
	g = *((image->G)+(x+(y* (image->Width))));
	return(g);
}
/* Get the color intensity of the Blue channel of pixel (x, y) in image */
unsigned char GetPixelB(IMAGE *image, unsigned int x,  unsigned int y)
{
	unsigned char b;
	b = *((image->B)+(x+(y* (image->Width))));
	return(b);
}
/* Set the color intensity of the Red channel of pixel (x, y) in image with value r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
/*	image-> *(R+(x+(y* (image->Width)))) = r ;
*/	/*printf("image width is %d",image->Width);
*/	
/*	unsigned char *tempR;
	tempR = (unsigned char *)malloc(500*640);
	tempR = image->R ;
 */   /*	temp = *(R+(x+(y* (image->Width))));*/
	
	*((image->R)+(x+(y* (image->Width)))) = r ;

/*	image->R = tempR;
*/
}
/* Set the color intensity of the Green channel of pixel (x, y) in image with value g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g){

	*(image->G+(x+(y* (image->Width)))) = g ;
}
/* Set the color intensity of the Blue channel of pixel (x, y) in image with value b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b){

	*(image->B+(x+(y* (image->Width)))) = b ;
}

/* allocate the memory space for the image structure         */
/* and the memory spaces for the color intensity values.     */
/* return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
 {
        IMAGE *image;
        image= (IMAGE*)malloc(sizeof(IMAGE));
        image->R = (unsigned char *)malloc(Width *Height);
        image->G = (unsigned char *)malloc(Width *Height);
        image->B = (unsigned char *)malloc(Width *Height);
	image-> Width = Width;
        image-> Height = Height;
        return(image);

}

/* release the memory spaces for the pixel color intensity values */
/* deallocate all the memory spaces for the image                 */
void DeleteImage(IMAGE *image){
	free(image->R);
	free(image->G);
	free(image->B);
	free(image);
}

