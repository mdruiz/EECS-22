
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Constants.h"
#include "Advanced.h"
#include "FileIO.h"

void FillLight(int number, int lightWidth, unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT])
{
        int vert=0,hori=0,newb,centre1=0,centre2=0,i=0,j=0,k=0,l=0,color1=0,value1=0,value2=0,value3=0;
        while(number!=0)
        {
                for(i=lightWidth;i<(HEIGHT-lightWidth);i++)
                        for(j=lightWidth;j<(WIDTH-lightWidth);j++)
                        {
                                srand(time(NULL));
                                centre1 = (rand() % HEIGHT ) +1;
                                centre2 = (rand() % WIDTH )+1;
                                color1= (rand() %3)+1;
                                if(color1==1)
                                {
                                        value1=255;
                                        value2=0;
                                        value3=0;
                                }
                                if(color1==2)
                                {
                                        value1=0;
                                        value2=255;
                                        value3=0;
                                }
                                if(color1==3)
                                {
                                        value1=0;
                                        value2=0;
                                        value3=255;
                                }
                                newb=lightWidth/2;
                                vert=0;
                                for(k=centre1;k<(centre1+lightWidth);k++)
                                {
                                        hori=0;
                                        for(l=centre2;l<(centre2+lightWidth);l++)
                                        {
                                                if(( k==(centre1+lightWidth/2)) || (l==(centre2+lightWidth/2))  ||(vert == centre1+(lightWidth/2)) || (hori==centre2+(lightWidth/2))|| (vert-hori==0)|| (vert- (lightWidth-hori)==0)  )
                                                {
                                                        R[k][l]=value1;
                                                        G[k][l]=value2;
                                                        B[k][l]=value3;
                                                }
                                                hori++;
                                        }
                                        vert++;
                                }
                        }
        number--;
        }
        printf("\"FillLight\" operation is done!\n");

}
void Posterize(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT],unsigned int pbits)
{
        int x, y, position,min=0, max=255;
        for (position=0; position < pbits; position++)
        {
                min= min + (1 << position);
                max= max << 1;
        }
        for( y = 0; y < HEIGHT; y++ )
                for( x = 0; x < WIDTH; x++ )
                {
                        R[x][y] = R[x][y] & max;
                        G[x][y] = G[x][y] & max;
                        B[x][y] = B[x][y] & max;

                        R[x][y] = R[x][y] | min;
                        G[x][y] = G[x][y] | min;
                        B[x][y] = B[x][y] | min;
                }
        printf("\"Posterize\" operation is done!\n");
}

void Overlay(char fname[SLEN],unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT],int x_offset, int y_offset)
{
        int x,y;
        unsigned char rR[WIDTH][HEIGHT];
        unsigned char rG[WIDTH][HEIGHT];
        unsigned char rB[WIDTH][HEIGHT];
        for( y = 0; y < HEIGHT; y++ )
                for( x = 0; x < WIDTH; x++ )
                {
                        rR[x][y] = R[x][y];
                        rG[x][y] = G[x][y];
                        rB[x][y] = B[x][y];
                }
        ReadImage(fname,R,G,B);
        for( y = 0; y < HEIGHT; y++ )
                for( x = 0; x < WIDTH; x++ )
                {
                        if( (x+x_offset) <640 && (y+y_offset) < 500)
                                if (R[x][y] < 250 && G[x][y] < 250 && B[x][y] < 250)
                                {
                                rR[x + x_offset][y + y_offset] = R[x][y];
                                rG[x + x_offset][y + y_offset] = G[x][y];
                                rB[x + x_offset][y + y_offset] = B[x][y];
                                }
                }
        for( y = 0; y < HEIGHT; y++ )
                for( x = 0; x < WIDTH; x++ )
                {
                R[x][y] = rR[x][y];
                G[x][y] = rG[x][y];
                B[x][y] = rB[x][y];
                }
        printf("\"Image Overlay\" operation is done!\n");
}





