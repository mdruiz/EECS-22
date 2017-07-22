/*********************************************************************/
/* MovieLab.c: homework assignment #5, for EECS 22,	Fall 2011    */
/*								     */
/* History:							     */
/* 10/30/11 Weiwei Chen	updated for EECS22 assignment5 FAll2011	     */
/* 10/30/11 Weiwei Chen	: initial template version		     */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Image.h"
#include "DIPs.h"
#include "ImageList.h"
#include "Movie.h"

/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/*read one frame from the movie */
IMAGE* ReadOneFrame(const char* fname, int nFrame, unsigned int W, unsigned H);

/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie);

/* Print the command line parameter usage of the program*/
void PrintUsage();

/* type define the function pointer to the DIP function	*/
typedef void MOP_F(IMAGE *image);

/* the function for perform DIP operations on the movie*/
void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP);


int main(int argc, char *argv[])
{
	int x = 0;
	int c = 0;
	int num = 0;
	int factor = 0, percent = 0, start = 0, end = 0;
	char *fin = NULL, *fout = NULL;
	int nframes = 0, width = 0, height = 0;
	MOVIE *movie;
	movie = NULL;
 /*entering while loop to check options entered*/
	while(x < argc)
	{
		/*specify input video*/
		if(0 == strcmp(&argv[x][0], "-i")) 
		{
			if(x < argc - 1)
			{
				fin = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(fin, argv[x + 1]);
				strcat( fin, ".yuv");
			}/*fi*/
			else
			{
				printf("Missing argument for input name!");
				free(fin);
				free(fout);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/

		/*specify output video*/
		if(0 == strcmp(&argv[x][0], "-o")) 
		{
			if(x < argc - 1)
			{
				fout = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(fout, argv[x + 1]);
				strcat( fout, ".yuv");
			}/*fi*/
			else
			{
				printf("Missing argument for output name!");
				free(fin);
				free(fout);
				return 5;
			}/*esle*/
			x += 2;
			continue;
		}/*fi*/
		if(0 == strcmp(&argv[x][0], "-f"))
		{
			if(x < argc - 1)
			{
				if (sscanf(argv[x+1], "%d", &nframes) != 1)
				{
					printf("\nMissing argument for number of frames!\n");
				}
			}
			else
			{
				printf("\nMissing argument for number of frames!\n");
				return 5;
			}
			x += 2;
			continue;
		}

		if(0 == strcmp(&argv[x][0], "-s"))
		{
			if(x < argc - 1)
			{
				if (sscanf(argv[x+1], "%dx%d", &width, &height) != 2)
				{
					printf("\nMissing argument for width and height!\n");
				}
			}
		
			else
			{
				printf("\nMissing argument for width and height!\n");
				return 5;
			}
			x += 2;
			continue;
		}
		
		/*help option*/
		if(0 == strcmp(&argv[x][0], "-h")) 
		{ 
			PrintUsage();
			free(fin);
			free(fout);
			return 0;
		}/*fi*/
	/**************************************************/
	/**************************************************/
		if(c == 0 && nframes && width && height) 
		{
			movie = CreateMovie(nframes,width,height);
			c++;
		}

		if(fin && movie)
		{
			ReadMovie(fin,nframes,width,height,movie);
		}

		if(0 == strcmp(&argv[x][0], "-bw"))
		{
			Movie_DIP_Operation(movie, BlackNWhite);
			printf("\n\"Black & White\" operation is done!\n");
			x++;
			continue;
		}
		
		if(0 == strcmp(&argv[x][0], "-vflip"))
		{	
			Movie_DIP_Operation(movie, VFlip);
			printf("\n\"VFlip\" operation is done!\n");
			x++;
			continue;
		}
		
		if(0 == strcmp(&argv[x][0], "-hmirror"))
		{	
			Movie_DIP_Operation(movie, HMirror);
			printf("\n\"HMirror\" operation is done!\n");
			x++;
			continue;
		}
		if(0 == strcmp(&argv[x][0], "-edge"))
		{	
			Movie_DIP_Operation(movie, Edge);
			printf("\n\"Edge\" operation is done!\n");
			x++;
			continue;
		}
		if(0 == strcmp(&argv[x][0], "-poster"))
		{
			Movie_DIP_Operation(movie, Posterize);
			printf("\n\"Posterize\" operation is done!\n");
			x++;
			continue;
		}
		if(0 == strcmp(&argv[x][0], "-resize"))
		{
			if (x < argc-1)
			{
				if (sscanf(argv[x+1], "%d", &percent) != 1)
				{
					printf("Missing argument for resize factor!");
				}
				if (percent < 1 || percent >500)
				{
					printf("Invalid resize factor! Must be [1-500]");
					return 5;
				}
			}
			else
			{
				printf("Missing argument for resize factor!");
				return 5;
			}
			ResizeImageList(movie->Frames,percent);
			printf("\n\"Resize\" operation is done!");	
			movie->Height = (movie->Height) *percent /100;
			movie->Width =  (movie->Width) *percent /100;
			printf(" New Width/Height = %dx%d\n",movie->Width, movie->Height);
			x += 2;
			continue;
		}
		if(0 == strcmp(&argv[x][0], "-cut"))
		{
			if (x < argc-1)
			{
				if (sscanf(argv[x+1], "%d-%d", &start, &end) != 2)
				{
					printf("Missing argument for cut!");
				}	
			}
			else
			{
				printf("Missing argument for cut!");
				return 5;
			}
			CropImageList(movie->Frames, start, end);
			printf("\n\"Crop\" operation is done!\n");
			x += 2;
			continue;
		}		
		if(0 == strcmp(&argv[x][0], "-fast"))
		{
			if (x < argc-1)
                        {
                                if (sscanf(argv[x+1], "%d", &factor) != 1)
                                {
                                        printf("Missing argument for fast!");
                                }
				if(factor < 1)
				{
					printf("Invalid fast factor! Must be [1+]");
					return 5;
				}
                        }
                        else
                        {
                                printf("Missing argument for fast!");
                                return 5;
                        }
                        num = FastImageList(movie->Frames, factor);
               
			printf("\n\"Fast\" operation is done!");
                        printf(" Number of Frames = %d\n", num);
			x += 2;
                        continue;

		}
		if(0 == strcmp(&argv[x][0], "-rvs"))
		{
			ReverseImageList(movie->Frames);
			printf("\n\"Reverse\" operation is done!\n");
			x++;
			continue;
		}

	/**************************************************/
        /**************************************************/
		x++;
	}/*elihw*/
	SaveMovie(fout,movie);
	DeleteMovie(movie);
	if(!fin){
		printf("Missing argument for input name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}

	if(!fout){
		printf("Missing argument for output name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}
	

	free(fin);
	free(fout);
	fin = NULL;
	fout = NULL;

	return 0;
}

void PrintUsage()
{
	printf("\nFormat on command line is:\n"
	"MovieLab [option]\n"
	"-i [file_name]    to provide the input file name\n"
	"-o [file_name]    to provide the	output file name\n"
	"-f [no_frames]    to determine how many frames desired in the input stream\n"
	"-s [WidthxHeight] to set resolution of the input stream (widthxheight)\n"
	"-j                to generate the movie with JuliaSet sequences\n"
	"-bw               to activate the conversion to black and white\n"
	"-vflip            to activate vertical flip\n"
	"-hmirror          to activate horizontal flip\n"
	"-edge             to activate edge filter\n"
	"-poster           to activate posterize filter\n"
	"-cut [Start-End]  to crop the frame from the video from frame Start to frame End\n"  
	"-resize [factor]  to resize the video with the provided factor [1-100]\n"
	"-fast   [factor]  to fast forward the video with the provided factor [1+]\n"
	"-rvs              to reverse the frame order of the input stream\n"
	"-h                to show this usage information\n"
	);
}

IMAGE* ReadOneFrame(const char *fname, int nFrame, unsigned int W, unsigned H)
{
        /*defining local variables*/
        FILE *file;

        unsigned int x, y;
        unsigned char ch;
        IMAGE* image ;

        /*checking error*/
        assert(fname);
        assert(nFrame >= 0);

        image = CreateImage(W, H) ;
        assert(image) ;

        /*opening file stream*/
        file = fopen(fname, "r");
        assert(file) ;

        /*find desired frame*/
        fseek(file, 1.5 * nFrame * W * H, SEEK_SET);

        for(y = 0; y < H; y ++){
                for(x = 0; x < W; x ++){
                        ch = fgetc(file);
                        SetPixelY(image, x, y, ch);
                }/*rof*/
        }

        for(y = 0; y < H ; y += 2){
                for(x = 0; x < W ; x += 2){
                        ch = fgetc(file);
                        SetPixelU(image, x, y, ch);
                        SetPixelU(image, x + 1, y, ch);
                        SetPixelU(image, x, y + 1, ch);
                        SetPixelU(image, x + 1, y + 1, ch);
                }
        }

        for(y = 0; y < H ; y += 2){
                for(x = 0; x < W ; x += 2){
                        ch = fgetc(file);
                        SetPixelV(image, x, y, ch);
                        SetPixelV(image, x + 1, y, ch);
                        SetPixelV(image, x, y + 1, ch);
                        SetPixelV(image, x + 1, y + 1, ch);
                }
        }

        /*checking for error*/

        assert(ferror(file) == 0) ;

        /*closing stream and terminating*/
        fclose(file);
        file = NULL;
        return image;
}


/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{	
	int i ; 
	int x, y;
	FILE *file;
	IENTRY *currFrame;

	 /*opening file stream*/
	 if(!(file = fopen(fname, "w"))){
			return 1;
	 }
	 
	 i = 0 ; 
	 printf("start savemovie, total frame %d\n", movie->NumFrames) ; 
	 currFrame = movie->Frames->First;
	 while(currFrame){
		for(y = 0; y < movie->Height; y ++){ 
			for(x = 0; x < movie->Width; x ++){
				fputc(GetPixelY(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetPixelU(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetPixelV(currFrame->Image, x, y), file);
			}
		}
		currFrame = currFrame->Next;	 
		i++ ; 
	 }

	 fclose(file);
	 file = NULL;

	 printf("The movie file %s has been written successfully! \n", fname);
	 printf("%d frames are written to the file %s in total \n", i, fname); 
	 return 0;
}

int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned int H, MOVIE *movie)
{
	int i;
	IMAGE *image;
	
	assert(fname);
	assert(movie);
	assert(movie->Frames);
	
	NewImageList();
	for(i = 0;i < nFrame;i++)
	{
		image = ReadOneFrame(fname,i,W,H);
		AppendImage(movie->Frames,image);
	}
	printf("The movie file %s.yuv has been read successfully!",fname);
	return 0;
}



/* the function for perform DIP operations on the movie*/
void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP)
{
	int frames, i;
	assert(movie);
	frames = movie->NumFrames;
	IENTRY *m;
	m = (movie->Frames->First);
	for(i = 0;i < frames;i++)
	{
		MovieOP(m->Image);
		if(m->Next != NULL)
		{
			m = m->Next;
		}
	}
}




