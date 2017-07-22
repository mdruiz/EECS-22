/*********************************************************************/
/* PhotoLab.c: homework assignment #2, for EECS 22,  Fall 2014       */
/*                                                                   */
/* History:                                                          */
/* 10/07/14 Manjunath MV  updated for EECS22 assignment2 Fall2014    */
/* 10/03/13 Che-Wei Chang  updated for EECS22 assignment2 Fall2013   */
/* 10/02/12 Weiwei Chen  updated for EECS22 assignment2 Fall2012     */
/* 09/27/11 Weiwei Chen  updated for EECS22 assignment2 Fall2011     */
/* 11/11/04 Rainer Doemer:   update for EECS 10 formatting style     */
/* 11/10/04 Rustam Sengupta: initial template version                */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/
#define WIDTH  640		/* Image width */
#define HEIGHT 500		/* image height */
#define SLEN    80		/* maximum length of file names and string*/
#define SHUFF_HEIGHT_DIV 4      /* Height division for shuffling */
#define SHUFF_WIDTH_DIV 4       /* Width division for shuffling */
/*** function declarations ***/

void FillLight(int number, int lightWidth, unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT]);

void Posterize(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT],unsigned int pbits);

void Overlay(char fname[SLEN],unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT],int x_offset, int y_offset);
/* print a menu */
void	PrintMenu();

/* read image from a file */
int	ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int	SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void	BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* flip image vertically */
void	VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* mirror image horizontally */
void	HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void 	ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
		int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) ; 

/* sharpen the image */
void	Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* edge detection */
void	Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* add border */
void	AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
		char color[SLEN], int border_width);

/* Test all functions */
void	AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int	main()
{
	/*
 	* Two dimensional arrays to hold the current image data. One array
 	* for each color component
 	* */
	int x_offset, y_offset,number, lightWidth;
	unsigned int pbits;
	int select=0;
	char fname[SLEN];
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];
	int target_r, target_g, target_b;
	int threshold, replace_r, replace_g, replace_b;
/*	char color[SLEN];
	int border_width;*/
	/*  Please replace the following code with proper menu  */
	/*	with function calls for DIP operations		*/
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
        printf("\n End of while loop");
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

int
ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE           *File;
	char            Type[SLEN];
	int             Width, Height, MaxValue;
	int             x, y;
	char            ftype[] = ".ppm";
  	char            fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/

  	strcpy(fname_tmp, fname);
	strcat(fname_tmp, ftype);

	File = fopen(fname_tmp, "r");
	if (!File) {
		printf("Cannot open file \"%s\" for reading!\n", fname);
		return 1;
	}
	fscanf(File, "%79s", Type);
	if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
		printf("\nUnsupported file format!\n");
		return 2;
	}
	fscanf(File, "%d", &Width);
	if (Width != WIDTH) {
		printf("\nUnsupported image width %d!\n", Width);
		return 3;
	}
	fscanf(File, "%d", &Height);
	if (Height != HEIGHT) {
		printf("\nUnsupported image height %d!\n", Height);
		return 4;
	}
	fscanf(File, "%d", &MaxValue);
	if (MaxValue != 255) {
		printf("\nUnsupported image maximum value %d!\n", MaxValue);
		return 5;
	}
	if ('\n' != fgetc(File)) {
		printf("\nCarriage return expected!\n");
		return 6;
	}
	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = fgetc(File);
			G[x][y] = fgetc(File);
			B[x][y] = fgetc(File);
		}
	if (ferror(File)) {
		printf("\nFile error while reading from file!\n");
		return 7;
	}
	printf("%s was read successfully!\n", fname_tmp);
	fclose(File);
	return 0;
}

int
SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE	*File;
	int	x, y;
	char	SysCmd[SLEN * 5];

	char	ftype[] = ".ppm";
	char	fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
  	char	fname_tmp2[SLEN];

	strcpy(fname_tmp, fname);
	strcpy(fname_tmp2, fname);
	strcat(fname_tmp2, ftype);

	File = fopen(fname_tmp2, "w");
	if (!File) {
		printf("Cannot open file \"%s\" for writing!\n", fname);
		return 1;
	}
	fprintf(File, "P6\n");
	fprintf(File, "%d %d\n", WIDTH, HEIGHT);
	fprintf(File, "255\n");

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			fputc(R[x][y], File);
			fputc(G[x][y], File);
			fputc(B[x][y], File);
		}

	if (ferror(File)) {
		printf("\nFile error while writing to file!\n");
		return 2;
	}
	fclose(File);
	printf("%s was saved successfully. \n", fname_tmp2);

	/*
	 * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
	 * and make it world readable
	 */
	sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw3.tcsh %s", fname_tmp2);
	if (system(SysCmd) != 0) {
		printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
		return 3;
	}
	printf("%s.jpg was stored for viewing. \n", fname_tmp);

	return (0);
}


/* age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
  int x, y;

  for( y = 0; y < HEIGHT; y++ )
    for( x = 0; x < WIDTH; x++ ) {
      B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
      R[x][y] = (unsigned char) (B[x][y]*1.6);
      G[x][y] = (unsigned char) (B[x][y]*1.6);
  }
}

/* auto test*/
void
AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	char fname[SLEN] = "RingMall";
  	char sname[SLEN];

	ReadImage(fname, R, G, B);
	Aging(R, G, B);
  	strcpy(sname, "aging");
	SaveImage(sname, R, G, B);
	printf("Aging tested!\n\n");
	
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

	/*
 	*	 	
 	* Filling this part with the call to your DIP functions
 	*/				
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
void    VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])	{
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

void    HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])	{
	
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

void    Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])	{
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
void    Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])	{
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

void    AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT],
                 char color[SLEN], int border_width)	{

	
	printf("\"Border\" operation is done!\n");


}
