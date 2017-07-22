

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Constants.h"
#include "DIPs.h"

void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
        int x, y;
        int Average;
        for( y = 0; y < HEIGHT; y++ )
                for( x = 0; x < WIDTH; x++ )
                {
                        Average = (B[x][y]+R[x][y]+G[x][y])/3;
                        B[x][y] = Average;
                        R[x][y] = Average;
                        G[x][y] = Average;
                }
        printf("\"Black & White\" operation is done!\n");
}
void    VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])   {
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
        for( y = 0; y < HEIGHT; y++ )
                for( x = 0; x < WIDTH; x++ )
                {
                        R[x][y] = rR[x][HEIGHT-y-1];
                        G[x][y] = rG[x][HEIGHT-y-1];
                        B[x][y] = rB[x][HEIGHT-y-1];
                }
        printf("\"VFlip\" operation is done!\n");
        }

void    HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {

        int x,y;
        for( y = 0; y < HEIGHT; y++ )
                for( x = 0; x < (WIDTH/2); x++ )
                {
                        R[x][y] = R[WIDTH-x-1][y];
                        G[x][y] = G[WIDTH-x-1][y];
                        B[x][y] = B[WIDTH-x-1][y];
                }
        printf("\"HMirror\" operation is done!\n");
        }

void    ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT],
                  int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {
        int x, y;
        for( y = 0; y < HEIGHT; y++)
                for( x = 0; x < WIDTH; x++ ){
                        if ((R[x][y] >= (target_r - threshold))&&(R[x][y] <= (target_r + threshold))&&(G[x][y] >= (target_g - threshold))&& (G[x][y] <= (target_g + threshold))&&(B[x][y] >= (target_b - threshold))&& (B[x][y] <= (target_b + threshold)))
                        {
                                R[x][y] = replace_r ;
                                G[x][y] = replace_g ;
                                B[x][y] = replace_b ;
                        }
                }
        printf("\"Color Filter\" operation is done!\n");
}

void    Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        int x=160,y=125;
        int z=16;
        unsigned char rb[z][x][y];
        unsigned char gb[z][x][y];
        unsigned char bb[z][x][y];
        for( y = 0; y < (HEIGHT/4); y++ )
                for( x = 0; x < (WIDTH/4); x++ )
                {
                        rb[0][x][y] =R[x][y];
                        rb[1][x][y] =R[x+160][y];
                        rb[2][x][y] =R[x+320][y];
                        rb[3][x][y] =R[x+480][y];
                        rb[4][x][y] =R[x][y+125];
                        rb[5][x][y] =R[x+160][y+125];
                        rb[6][x][y] =R[x+320][y+125];
                        rb[7][x][y] =R[x+480][y+125];
                        rb[8][x][y] =R[x][y+250];
                        rb[9][x][y] =R[x+160][y+250];
                        rb[10][x][y] =R[x+320][y+250];
                        rb[11][x][y] =R[x+480][y+250];
                        rb[12][x][y] =R[x][y+325];
                        rb[13][x][y] =R[x+160][y+325];
                        rb[14][x][y] =R[x+320][y+325];
                        rb[15][x][y] =R[x+480][y+325];

                        gb[0][x][y] =G[x][y];
                        gb[1][x][y] =G[x+160][y];
                        gb[2][x][y] =G[x+320][y];
                        gb[3][x][y] =G[x+480][y];
                        gb[4][x][y] =G[x][y+125];
                        gb[5][x][y] =G[x+160][y+125];
                        gb[6][x][y] =G[x+320][y+125];
                        gb[7][x][y] =G[x+480][y+125];
                        gb[8][x][y] =G[x][y+250];
                        gb[9][x][y] =G[x+160][y+250];
                        gb[10][x][y] =G[x+320][y+250];
                        gb[11][x][y] =G[x+480][y+250];
                        gb[12][x][y] =G[x][y+325];
                        gb[13][x][y] =G[x+160][y+325];
                        gb[14][x][y] =G[x+320][y+325];
                        gb[15][x][y] =G[x+480][y+325];

                        bb[0][x][y] =B[x][y];
                        bb[1][x][y] =B[x+160][y];
                        bb[2][x][y] =B[x+320][y];
                        bb[3][x][y] =B[x+480][y];
                        bb[4][x][y] =B[x][y+125];
                        bb[5][x][y] =B[x+160][y+125];
                        bb[6][x][y] =B[x+320][y+125];
                        bb[7][x][y] =B[x+480][y+125];
                        bb[8][x][y] =B[x][y+250];
                        bb[9][x][y] =B[x+160][y+250];
                        bb[10][x][y] =B[x+320][y+250];
                        bb[11][x][y] =B[x+480][y+250];
                        bb[12][x][y] =B[x][y+325];
                        bb[13][x][y] =B[x+160][y+325];
                        bb[14][x][y] =B[x+320][y+325];
                        bb[15][x][y] =B[x+480][y+325];
                }
        for( y = 0; y < (HEIGHT/4); y++ )
                 for( x = 0; x < (WIDTH/4); x++ ){
                         R[x][y]=rb[3][x][y];
                         R[x+160][y]=rb[7][x][y];
                         R[x+320][y]=rb[12][x][y];
                         R[x+480][y]=rb[0][x][y];
                         R[x][y+125]=rb[14][x][y];
                         R[x+160][y+125]=rb[9][x][y];
                         R[x+320][y+125]=rb[8][x][y];
                         R[x+480][y+125]=rb[1][x][y];
                         R[x][y+250]=rb[6][x][y];
                         R[x+160][y+250]=rb[5][x][y];
                         R[x+320][y+250]=rb[11][x][y];
                         R[x+480][y+250]=rb[10][x][y];
                         R[x][y+325]=rb[2][x][y];
                         R[x+160][y+325]=rb[15][x][y];
                         R[x+320][y+325]=rb[4][x][y];
                         R[x+480][y+325]=rb[13][x][y];

                         G[x][y]=gb[3][x][y];
                         G[x+160][y]=gb[7][x][y];
                         G[x+320][y]=gb[12][x][y];
                         G[x+480][y]=gb[0][x][y];
                         G[x][y+125]=gb[14][x][y];
                         G[x+160][y+125]=gb[9][x][y];
                         G[x+320][y+125]=gb[8][x][y];
                         G[x+480][y+125]=gb[1][x][y];
                         G[x][y+250]=gb[6][x][y];
                         G[x+160][y+250]=gb[5][x][y];
                         G[x+320][y+250]=gb[11][x][y];
                         G[x+480][y+250]=gb[10][x][y];
                         G[x][y+325]=gb[2][x][y];
                         G[x+160][y+325]=gb[15][x][y];
                         G[x+320][y+325]=gb[4][x][y];
                         G[x+480][y+325]=gb[13][x][y];

                         B[x][y]=bb[3][x][y];
                         B[x+160][y]=bb[7][x][y];
                         B[x+320][y]=bb[12][x][y];
                         B[x+480][y]=bb[0][x][y];
                         B[x][y+125]=bb[14][x][y];
                         B[x+160][y+125]=bb[9][x][y];
                         B[x+320][y+125]=bb[8][x][y];
                         B[x+480][y+125]=bb[1][x][y];
                         B[x][y+250]=bb[6][x][y];
                         B[x+160][y+250]=bb[5][x][y];
                         B[x+320][y+250]=bb[11][x][y];
                         B[x+480][y+250]=bb[10][x][y];
                         B[x][y+325]=bb[2][x][y];
                         B[x+160][y+325]=bb[15][x][y];
                         B[x+320][y+325]=bb[4][x][y];
                         B[x+480][y+325]=bb[13][x][y];
                }

        printf("\"Shuffle\" operation is done!\n");

}
void    Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])    {
        int x,y;
        unsigned char rR[WIDTH][HEIGHT];
        unsigned char rG[WIDTH][HEIGHT];
        unsigned char rB[WIDTH][HEIGHT];
        int new_R,new_G,new_B;
        for( y = 0; y < HEIGHT; y++ )
                for( x = 0; x < WIDTH; x++ )
                {
                        rR[x][y] = R[x][y];
                        rG[x][y] = G[x][y];
                        rB[x][y] = B[x][y];
                 }
        for( y = 0; y < HEIGHT; y++ )
                for( x = 0; x < WIDTH; x++ ){
                        if ((x!=0)&&(x!=649)&&(y!=0)&&(y!=499))
                        {
                                new_R=(8*R[x][y])-R[x-1][y-1]-R[x][y-1]-R[x+1][y-1]-R[x-1][y]-R[x+1][y]-R[x-1][y+1]-R[x][y+1]-R[x+1][y+1];
                                if (new_R > 255)
                                {
                                        rR[x][y]=255;
                                }
                                if (new_R < 0)
                                {
                                        rR[x][y]=0;
                                }
                                else
                                        rR[x][y]=new_R;

                                new_G=(8*G[x][y])-G[x-1][y-1]-G[x][y-1]-G[x+1][y-1]-G[x-1][y]-G[x+1][y]-G[x-1][y+1]-G[x][y+1]-G[x+1][y+1];
                                if (new_G > 255)
                                {
                                        rG[x][y]=255;
                                }
                                if (new_G < 0)
                                {
                                        rG[x][y]=0;
                                }
                                else
                                        rG[x][y]=new_G;

                                new_B=(8*B[x][y])-B[x-1][y-1]-B[x][y-1]-B[x+1][y-1]-B[x-1][y]-B[x+1][y]-B[x-1][y+1]-B[x][y+1]-B[x+1][y+1];
                                if (new_B > 255)
                                {
                                        rB[x][y]=255;
                                }
                                if (new_B < 0)
                                {
                                        rB[x][y]=0;
                                }
                                else
                                        rB[x][y]=new_B;
                        }
                }
        for( y = 0; y < HEIGHT; y++ )
                for( x = 0; x < WIDTH; x++ )
                {
                        R[x][y] = rR[x][y];
                        G[x][y] = rG[x][y];
                        B[x][y] = rB[x][y];
                  }

        printf("\"Edge\" operation is done!\n");
}


