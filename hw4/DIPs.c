

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Constants.h"
#include "DIPs.h"

IMAGE  *BlackNWhite(IMAGE *image)
{
	int tmpR, tmpG, tmpB;
        int x, y;
        int Average;
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
        printf("\"Black & White\" operation is done!\n");
	return(image);
}
IMAGE   *VFlip(IMAGE *image)   {
	int x,y;
	int tmpR, tmpG, tmpB;
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
        printf("\"VFlip\" operation is done!\n");
	
	DeleteImage(tmp);
	return(image);
}

IMAGE   *HMirror(IMAGE *image) {

        int x,y;
	int tmpR, tmpG, tmpB;
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
        printf("\"HMirror\" operation is done!\n");
	return(image);
}

IMAGE    *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {
        int x, y;
	int tmpR, tmpG, tmpB;
        for( y = 0; y < image->Height; y++)
                for( x = 0; x < image->Width; x++ ){
			tmpR = GetPixelR(image, x, y);
			tmpG = GetPixelG(image, x, y);
			tmpB = GetPixelB(image, x, y);
                        if ((tmpR >= (target_r - threshold))&&(tmpR <= (target_r + threshold))&&(tmpG >= (target_g - threshold))&& (tmpG <= (target_g + threshold))&&(tmpB >= (target_b - threshold))&& (tmpB <= (target_b + threshold)))
                        {
				SetPixelR(image, x, y, replace_r);
				SetPixelG(image, x, y, replace_g);
				SetPixelB(image, x, y, replace_b);			
                        }
                }
        printf("\"Color Filter\" operation is done!\n");
	return(image);
}

IMAGE    *Shuffle(IMAGE *image) 
{
/*	int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
	int block_width = WIDTH/SHUFF_WIDTH_DIV;
	int block_height = HEIGHT/SHUFF_HEIGHT_DIV;
	int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
	int i, j;

	srand(time(NULL));
*/	/* Initialize block markers to not done (-1) */
/*	for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
		for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
			block[i][j] = -1;
		}
	}
	while (block_cnt > 0) {
*/		/* Generate a random pair of blocks */
/*		int dest_height = rand() % SHUFF_HEIGHT_DIV;
		int dest_width = rand() % SHUFF_WIDTH_DIV;
		int src_height = rand() % SHUFF_HEIGHT_DIV;
		int src_width = rand() % SHUFF_WIDTH_DIV;

*/		/* Check if these blocks are already swaped, if not swap blocks */
/*		if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1)) {
*/			/* Swap blocks */
/*			for (i = 0; i < block_height; i++) {
*/				/* Init src and dest height offset */
/*				int h_dest = ((dest_height * block_height) + i) % HEIGHT;
				int h_src  = ((src_height * block_height) + i) % HEIGHT; 
				for (j = 0; j < block_width; j++) {
					int temp;
*/					/* Init src and dest width offset */
/*					int w_src  = ((src_width * block_width) + j) % WIDTH; 
					int w_dest = ((dest_width * block_width) + j) % WIDTH;

					temp = R[w_dest][h_dest];
					R[w_dest][h_dest] = R[w_src][h_src];
					R[w_src][h_src] = temp;

					temp = G[w_dest][h_dest];
					G[w_dest][h_dest] = G[w_src][h_src];
					G[w_src][h_src] = temp;

					temp = B[w_dest][h_dest];
					B[w_dest][h_dest] = B[w_src][h_src];
					B[w_src][h_src] = temp;
				}
			}
*/			/* Set marker as done */
/*			block[dest_width][dest_height] = 1;
			block[src_width][src_height] = 1;
*/			/* Decrease block count */
/*			block_cnt -= 2;
 */			 /* Two blocks are swapped */
/*		}	
	}
*/
        printf("\"Shuffle\" operation is done!\n");
	return(image);
}
IMAGE    *Edge(IMAGE *image) 
{
/*        int             x, y, m, n, a, b;
        int             tmpR = 0;
        int             tmpG = 0;
        int             tmpB = 0;
	IMAGE *tmp;
	tmp = CreateImage(image->Width, image->Height);
	
        for (y = 0; y < image->Height; y++){
                for (x = 0; x < image->Width; x++) {
                        R_tmp[x][y] = R[x][y];
                        G_tmp[x][y] = G[x][y];
                        B_tmp[x][y] = B[x][y];
                }
        }

        for (y = 0; y < image->HEIGHT; y++){
                for (x = 0; x < image->WIDTH; x++){
                        for (n = -1; n <= 1; n++){
                                for (m = -1; m <= 1; m++) {
                                        a = x + m;
                                        b = y + n;
                                        if (a > image->WIDTH - 1)
                                                a = image->WIDTH - 1;
                                        if (a < 0)
                                                a = 0;
                                        if (b > image->HEIGHT - 1)
                                                b = image->HEIGHT - 1;
                                        if (b < 0)
                                                b = 0;

                                        if ((n==0)&&(m==0))
                                        {
                                                tmpR += 8*R_tmp[a][b] ;
                                                tmpG += 8*G_tmp[a][b] ;
                                                tmpB += 8*B_tmp[a][b] ;
                                        }
                                        else
                                        {
                                                tmpR -= R_tmp[a][b] ;
                                                tmpG -= G_tmp[a][b] ;
                                                tmpB -= B_tmp[a][b] ;
                                        }
				}
			}
			R[x][y] = (tmpR>255)? 255: (tmpR<0)? 0: tmpR ;
                        G[x][y] = (tmpG>255)? 255: (tmpG<0)? 0: tmpG ;
                        B[x][y] = (tmpB>255)? 255: (tmpB<0)? 0: tmpB ;
                        tmpR = tmpG = tmpB = 0;
                }
        }
*/
	printf("\"Edge\" operation is done!\n");
	return(image);
}








/*   {
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

*/
