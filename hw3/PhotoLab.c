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

void PrintMenu();

void    AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int main()
{
	int x_offset, y_offset,number, lightWidth;
        unsigned int pbits;
        int select=0;
        char fname[SLEN];
        unsigned char   R[WIDTH][HEIGHT];
        unsigned char   G[WIDTH][HEIGHT];
        unsigned char   B[WIDTH][HEIGHT];
        int target_r, target_g, target_b;
        int threshold, replace_r, replace_g, replace_b;
	while (select != 14)
        {
        	PrintMenu();
                scanf("%d",&select);
                if (select == 1)
                {
                        printf("Please input the file name to load:");
                        scanf("%s",fname);
                        ReadImage(fname,R,G,B);
                }
                if (select ==  2)
                {
                        printf("Please input the file name to save:");
                        scanf("%s",fname);
                        SaveImage(fname,R,G,B);
                }
                if (select ==  3)
                {
                        BlackNWhite(R,G,B);
                }
                if (select == 4)
                {
                        VFlip(R,G,B);
                }
                if (select == 5)
                {
                        HMirror(R,G,B);
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
                        ColorFilter(R,G,B,target_r,target_g,target_b,threshold,replace_r,replace_g,replace_b);
                }
                if (select == 7)
                {
                        Edge(R,G,B);
                }
                if (select == 8)
                {
                        Shuffle(R,G,B);
                }
                if (select == 9)
                {
                        printf("Enter the number of posterization bits (1 to 8):");
                        scanf("%d",&pbits);
                        Posterize(R,G,B,pbits);
                }
                if(select == 10)
		{
			printf("Please input number of lights:");
                        scanf("%d",&number);
                        printf("Please input the width of each light:");
                        scanf("%d",&lightWidth);
                        FillLight(number,lightWidth,R,G,B);
                }
                if(select == 11)
                {
                        printf("Please input the file name for the second image:");
                        scanf("%s",fname);
                        printf("Please input x coordinate of the overlay image:");
                        scanf("%d",&x_offset);
                        printf("Please input y coordinate of the overlay image:");
                        scanf("%d",&y_offset);
                        Overlay(fname,R,G,B,x_offset,y_offset);
                }
                if(select == 12)
                {

                }
                if (select == 13)
                {
                        AutoTest(R,G,B);
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
        printf("12:  BONUS: Cut and Paste operartion on image\n");
        printf("13: Test all functions\n");
        printf("14: Exit\n");
        printf("Please make your choice: ");
}

void
AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
        char fname[SLEN] = "RingMall";
        char sname[SLEN];


        ReadImage(fname, R, G, B);
        BlackNWhite(R,G,B);
        strcpy(sname, "bw");
        SaveImage(sname, R, G, B);
        printf("\"Black & White\" operation is done!\n\n");

        ReadImage(fname, R, G, B);
        VFlip(R,G,B);
        strcpy(sname, "vflip");
        SaveImage(sname, R, G, B);
        printf("\"VFlip\" operation is done!\n\n");

        ReadImage(fname, R, G, B);
        HMirror(R,G,B);
        strcpy(sname, "hmirror");
        SaveImage(sname, R, G, B);
        printf("\"HMirror\" operation is done!\n\n");

        ReadImage(fname, R, G, B);
        ColorFilter(R,G,B,180,180,50,70,0,255,0);
        strcpy(sname, "colorfilter");
        SaveImage(sname, R, G, B);
        printf("\"Color Filter\" operation is done!\n\n");

        ReadImage(fname, R, G, B);
        Edge(R,G,B);
        strcpy(sname, "edge");
        SaveImage(sname, R, G, B);
        printf("\"Edge\" operation is done!\n\n");

        ReadImage(fname, R, G, B);
        Shuffle(R,G,B);
        strcpy(sname, "shuffle");
        SaveImage(sname, R, G, B);
        printf("\"Shuffle\" operation is done!\n\n");

        ReadImage(fname, R, G, B);
        Posterize(R,G,B,7);
        strcpy(sname, "poster");
        SaveImage(sname, R, G, B);
        printf("\"Posterize\" operation is done!\n\n");

        ReadImage(fname, R, G, B);
        FillLight(200,20,R,G,B);
        strcpy(sname, "light");
        SaveImage(sname, R, G, B);
        printf("\"FillLight\" operation is done!\n\n");

        ReadImage(fname, R, G, B);
        Overlay("Peter",R,G,B,0,0);
        strcpy(sname, "overlay_peter");
        SaveImage(sname, R, G, B);
        printf("\"Overlay\" operation is done!\n\n");

        ReadImage(fname, R, G, B);
        Overlay("Spider",R,G,B,90,(-10));
        strcpy(sname, "overlay_spider");
        SaveImage(sname, R, G, B);
        printf("\"Overlay\" operation is done!\n\n");
}

