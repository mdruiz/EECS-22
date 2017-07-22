#include "ImageList.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Movie.h"

static IENTRY *NewImageEntry(IMAGE *image)
{
	IENTRY *e;
	e = (IENTRY *)malloc(sizeof(IENTRY));
	if (! e)
	{
		return NULL;
	}
	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;
	e->Image = image;
	return e;
}

static IMAGE *DeleteImageEntry(IENTRY *e)
{
	IMAGE *image;
	assert(e);
	image = e->Image;
	free(e);
	return image;
}

/* allocate a new image list */
ILIST *NewImageList(void)
{
	ILIST *List;
	if(!( List = (ILIST *)malloc(sizeof(ILIST))))
	{
		return NULL;
	}
	List->Length = 0;
	List->First = NULL;
	List->Last = NULL;
	
	return(List);
}

/* delete a image list (and all entries) */
void DeleteImageList(ILIST *l)
{
	IENTRY *e, *n;
	IMAGE *image;

	assert(l);
	e = l->First;
	while(e)
	{
		n = e->Next;
		image = DeleteImageEntry(e);
		DeleteImage(image);
		e = n;
	}
	free(l);
}

/* insert a frame into a list at the end*/
void AppendImage(ILIST *l, IMAGE *image)
{
	IENTRY *e = NULL;
	assert(l);
	assert(image);
	e = NewImageEntry(image);
	if(l->Last)
	{
		e->List = l;
		e->Next = NULL;
		e->Prev = l->Last;
		l->Last->Next = e;
		l->Last = e;
	}
	else
	{
		e->List = l;
		e->Next = NULL;
		e->Prev = NULL;
		l->First = e;
		l->Last = e;
	}
	l->Length++;
}

/* reverse an image list */
void ReverseImageList(ILIST *l)
{
	IENTRY *pCurrent, *pPrev, * pNext;
	assert(l);
	pCurrent = l->First;
	pPrev = l->First->Prev;
	pNext = l->First->Next;

	while(1)
	{
		pCurrent->Next = pPrev;
		pCurrent->Prev = pNext;
		if(pNext == NULL)
			break;
		pPrev = pCurrent;
		pCurrent = pNext;
		pNext = pNext->Next;
	}
	l->Last = l->First;
	l->First = pCurrent;
}

/*Crop frames from the list starting from SFrame to EFrame*/
void CropImageList(ILIST *l, unsigned int SFrame, unsigned int EFrame)
{
	int length, i;
	length = l->Length;

	for(i = 0;i < SFrame-1;i++)
	{
		/*RemoveFirstImage*/
		IENTRY *e = NULL;
		assert(l);
		if (l->First)
		{
			e = l->First;
			l->First = e->Next;
			if(l->First)
			{
				l->First->Prev = NULL;
			}
			else
			{
				assert(l->Last == e);
				l->Last = NULL;
			}
		l->Length--;
		DeleteImage(e->Image);
		DeleteImageEntry(e);
		}
	}
	
	for(i = 0;i < (length-EFrame);i++)
	{
		/*RemoveLastImage*/
		IENTRY *e = NULL;
		assert(l);
		if(l->Last)
		{
			e = l->Last;
			l->Last = e->Prev;
			if(l->Last)
			{
				l->Last->Next = NULL;
			}
			else
			{
				assert(l->First == e);
				l->First = NULL;
			}
		l->Length--;
		DeleteImage(e->Image);
		DeleteImageEntry(e);
		}
	}
}

/*Resize the images in the list*/
void ResizeImageList(ILIST *l, unsigned int percentage) 
{	
	int frames, i;
	assert(l);
	frames = l->Length;
	IENTRY *m;
	m = l->First;
	for(i = 0; i < frames; i++)
	{	
		YUV2RGBImage(m->Image);
		unsigned int    x, y, x1, y1, x2, y2, i, j, tmpR, tmpG, tmpB;
		unsigned int 	NEW_WIDTH, NEW_HEIGHT;
		unsigned int WIDTH;
		unsigned int HEIGHT;
		IMAGE *image_tmp;
		
		assert(m->Image);
		WIDTH 	= m->Image->Width;
		HEIGHT = m->Image->Height;
	
		if(percentage <= 0 || percentage > 500)
		{	
			printf("Resizing percentage %d%% is out of the range, Sorry! \n", percentage);
		}
	
		NEW_WIDTH = WIDTH * percentage / 100;
		NEW_HEIGHT = HEIGHT * percentage / 100;
		image_tmp = CreateImage(NEW_WIDTH, NEW_HEIGHT);
		
		for(x = 0; x < NEW_WIDTH; x ++){
			for(y = 0; y < NEW_HEIGHT; y++){
				x1 = (unsigned int)(x / (percentage / 100.00));
				y1 = (unsigned int)(y / (percentage / 100.00));
				x2 = (unsigned int)((x + 1) / (percentage / 100.00));
				y2 = (unsigned int)((y + 1) / (percentage / 100.00));
				tmpR = tmpB = tmpG = 0;
				
				if(percentage < 100){
					for(i = x1; i < x2; i ++){
						for(j = y1; j < y2; j ++){
							tmpR += GetPixelR(m->Image, i, j);
							tmpG += GetPixelG(m->Image, i, j);
							tmpB += GetPixelB(m->Image, i, j);
						}
					}
					SetPixelR(image_tmp, x, y, tmpR / ((x2 - x1) * (y2 - y1)));
					SetPixelG(image_tmp, x, y, tmpG / ((x2 - x1) * (y2 - y1)));
					SetPixelB(image_tmp, x, y, tmpB / ((x2 - x1) * (y2 - y1)));
	
				}
				else{
					SetPixelR(image_tmp, x, y, GetPixelR(m->Image, x1, y1));
					SetPixelG(image_tmp, x, y, GetPixelG(m->Image, x1, y1));
					SetPixelB(image_tmp, x, y, GetPixelB(m->Image, x1, y1));
				}
			}
		}	
		for(x = 0; x < NEW_WIDTH; x ++)
			for(y = 0; y < NEW_HEIGHT; y++)
			{
				SetPixelR(m->Image, x, y, GetPixelR(image_tmp,x,y));
				SetPixelG(m->Image, x, y, GetPixelG(image_tmp,x,y));
				SetPixelB(m->Image, x, y, GetPixelB(image_tmp,x,y));
			}
		DeleteImage(image_tmp);
		image_tmp = NULL;
		RGB2YUVImage(m->Image);
	
	/*	RGB2YUVImage(m->Image);
		m->Image->Width = NEW_WIDTH;
		m->Image->Height = NEW_HEIGHT;
		DeleteImage(m->Image);
		m->Image= NULL;	
		m->Image = image_tmp;
		RGB2YUVImage(m->Image);
	*/	if (m->Next != NULL)
		{
			m = m->Next;
		}
	}
}

/*Fast forward the video*/
unsigned int FastImageList(ILIST *l, unsigned int ff_factor) 
{
	int i, j, k, length, num;
	length = l->Length;
	for(i = 0;i < (length/ff_factor) ;i++)
	{
		l->First = l->First->Next;
		for(j = 0;j < (ff_factor - 1);j++)
		{
			IENTRY *e = NULL;
        		assert(l);
        		if (l->First)
        		{
        		        e = l->First;
	                	l->First = e->Next;
        	        	if(l->First)
                		{
                        		l->First->Prev = e->Prev; /*NULL;*/
                			e->Prev->Next = l->First;
				}
                		else
                		{
                		        assert(l->Last == e);
                		        l->Last = e->Prev;
					e->Prev->Next = NULL;
                			l->First = l->Last;
				}
        		l->Length--;
        		DeleteImage(e->Image);
        		DeleteImageEntry(e);
        		}
		}
	}
	num = length/ff_factor;
	if(length % ff_factor != 0)
		num++;
	for(k = 0;k < num -1;k++)
	{
		l->First = l->First->Prev;
	}
	return num; 
}



