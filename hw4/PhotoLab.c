/****************************************************************/
/*Mario Ruiz ID# 46301389	PhotoLab.c        		*/
/*								*/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Constants.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"
#include "Image.h"

void PrintMenu();

void    AutoTest(IMAGE *image);

int main()
{
	int percentage, W, H, max_iteration;
	int x_offset, y_offset,number, lightWidth;
        unsigned int pbits;
 
	IMAGE *image;
	int select=0;
        char fname[SLEN];
        int target_r, target_g, target_b;
        int threshold, replace_r, replace_g, replace_b;
	while (select != 18)
        {
        	PrintMenu();
                scanf("%d",&select);
                if (select == 1)
                {
                        printf("Please input the file name to load:");
                        scanf("%s",fname);
                        image = ReadImage(fname);
                }
                if (select ==  2)
                {
                        printf("Please input the file name to save:");
                        scanf("%s",fname);
                        SaveImage(fname,image);
                }
                if (select ==  3)
                {
                	BlackNWhite(image);
                }
                if (select == 4)
                {
                        VFlip(image);
                }
                if (select == 5)
                {
                        HMirror(image);
                }
                if (select == 6)
                {
			printf("Enter Red component for the target color: ");   
                        scanf("%d",&target_r);
                        printf("Enter Green component for the target color: ");
                        scanf("%d",&target_g);
                        printf("Enter Blue component for the target color: ");
                        scanf("%d",&target_b);
                        printf("Enter threshold for the color difference: ");
                        scanf("%d",&threshold);
                        printf("Enter value for Red component in the target color: ");
                        scanf("%d",&replace_r);
                        printf("Enter value for Green component in the target color: ");
                        scanf("%d",&replace_g);
                        printf("Enter value for Blue component in the target color: ");
                        scanf("%d",&replace_b);
                        ColorFilter(image,target_r,target_g,target_b,threshold,replace_r,replace_g,replace_b);
                }
                if (select == 7)
                {
                        Edge(image);
                }
                if (select == 8)
                {
                        Shuffle(image);
                }
                if (select == 9)
                {
                        printf("Enter the number of posterization bits (1 to 8):");
                        scanf("%d",&pbits);
                        Posterize(image,pbits);
                }
                if(select == 10)
		{
			printf("Please input number of lights:");
                        scanf("%d",&number);
                        printf("Please input the width of each light:");
                        scanf("%d",&lightWidth);
                        FillLight(image,number,lightWidth);
                }
                if(select == 11)
                {
                        printf("Please input the file name for the second image:");
                        scanf("%s",fname);
                        printf("Please input x coordinate of the overlay image:");
                        scanf("%d",&x_offset);
                        printf("Please input y coordinate of the overlay image:");
                        scanf("%d",&y_offset);
                        Overlay(fname,image,x_offset,y_offset);
                }
                if(select == 12)
                {
			printf("Cut and Paste operation done!\n");
                }
		if(select == 13)
		{
		/*resize*/
			printf("Please input the resizing percentage (integer between 1˜500): ");
			scanf("%d",&percentage);
			Resize( percentage,image);
		}
		if(select == 14)
		{
		/*rotate*/
			Rotate(image);
		}
		if(select == 15)
		{
		/*Mandelbrot*/
			printf("Please input the width of the mandelbrot image: ");
			scanf("%d",&W);
			printf("Please input the height of the mandelbrot image: ");
			scanf("%d",&H);
			printf("Please input the max iteration for the mandelbrot calculation: ");
			scanf("%d",&max_iteration);
			Mandelbrot( W, H, max_iteration);
		}
		if(select == 16)
		{
		/*Bonus:Add Border*/
			printf("\"Outer Border\" operation is done!\n");
		}
                if (select == 17)
                {
                        AutoTest(image);
                }
        }
        return(0);
}

void PrintMenu()
{
        printf("----------------------------------\n");
        printf("1:  Load a PPM image\n");
        printf("2:  Save an image in PPM and JPEG format\n");
        printf("3:  Change a color image to Black & White\n");
        printf("4:  Flip an image vertically\n");
        printf("5:  Mirror an image horizontally\n");
        printf("6:  Color filter an image\n");
        printf("7:  Sketch the edge of an image\n");
        printf("8:  Shuffle an image\n");
        printf("9:  Posterize the image\n");
        printf("10: Fill Lights to an image\n");
        printf("11: Overlay an image\n");
        printf("12: BONUS: Cut and Paste operartion on image\n");
	printf("13: Resize the image\n");
	printf("14: Rotate 90 degrees clockwise\n");
	printf("15: Generate the Mandelbrot image\n");
	printf("16: Bonus: Add border outside the image\n");
	printf("17: Test all functions\n");
        printf("18: Exit\n");
        printf("Please make your choice: ");
}

void
AutoTest(IMAGE *image)
{
        char fname[SLEN] = "RingMall";
        char sname[SLEN];


        image = ReadImage(fname);
        BlackNWhite(image);
        strcpy(sname, "bw");
        SaveImage(sname,image);
        printf("\"Black & White\" operation is done!\n\n");
	DeleteImage(image);

        image = ReadImage(fname);
        VFlip(image);
        strcpy(sname, "vflip");
        SaveImage(sname, image);
        printf("\"VFlip\" operation is done!\n\n");
	DeleteImage(image);

        image = ReadImage(fname);
        HMirror(image);
        strcpy(sname, "hmirror");
        SaveImage(sname, image);
        printf("\"HMirror\" operation is done!\n\n");
	DeleteImage(image);

        image = ReadImage(fname);
        ColorFilter(image,180,180,50,70,0,255,0);
        strcpy(sname, "colorfilter");
        SaveImage(sname, image);
        printf("\"Color Filter\" operation is done!\n\n");
	DeleteImage(image);

        image = ReadImage(fname);
        Edge(image);
        strcpy(sname, "Edge");
        SaveImage(sname, image);
        printf("\"Edge\" operation is done!\n\n");
	DeleteImage(image);

        image = ReadImage(fname);
        Shuffle(image);
        strcpy(sname, "Shuffle");
        SaveImage(sname, image);
        printf("\"Shuffle\" operation is done!\n\n");
	DeleteImage(image);

        image = ReadImage(fname);
        Posterize(image,7);
        strcpy(sname, "Poster");
        SaveImage(sname, image);
        printf("\"Posterize\" operation is done!\n\n");
	DeleteImage(image);

        image = ReadImage(fname);
        FillLight(image,200,20);
        strcpy(sname, "Light");
        SaveImage(sname, image);
        printf("\"FillLight\" operation is done!\n\n");
	DeleteImage(image);

        image = ReadImage(fname);
        Overlay("Peter",image,350,300);
        strcpy(sname, "Overlay_peter");
        SaveImage(sname, image);
        printf("\"Overlay\" operation is done!\n\n");
	DeleteImage(image);

        image = ReadImage(fname);
        Overlay("Spider",image,90,(-10));
        strcpy(sname, "Overlay_spider");
        SaveImage(sname, image);
        printf("\"Overlay\" operation is done!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
	image = Resize(175, image);
	SaveImage("bigresize", image);
	printf("Resizing big tested!\n\n");
	DeleteImage(image);

	image = ReadImage(fname);
        image = Resize(60, image);
        SaveImage("smallresize", image);
        printf("Resizing small tested!\n\n");
        DeleteImage(image);


	image = ReadImage(fname);
	image = Rotate(image);
	SaveImage("rotate", image);
	printf("Rotate 90 degrees clockwise tested!\n\n");
	DeleteImage(image);

/*	image = Mandelbrot(720, 538, 2000);
	SaveImage("mandelbrot", image);
	printf("Generate the mandelbrot image tested!\n\n");

	image = ReadImage(fname);
	image = AddOuterBorder(image, "black", 10) ;
	strcpy(sname, "outerborder");
	SaveImage(sname, image) ;
	printf("Bonus : Outer border tested!\n\n");
*/
}

