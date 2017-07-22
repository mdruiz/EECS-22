

#ifndef FILE_IO_H
#define FILE_IO_H
#include "Constants.h"

int     ReadImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


int     SaveImage(char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);




#endif
