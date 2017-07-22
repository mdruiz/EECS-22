

#ifndef ADVANCED
#define ADVANCED

#include "Constants.h"

void FillLight(int number, int lightWidth, unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT]);

void Posterize(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT],unsigned int pbits);

void Overlay(char fname[SLEN],unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT],int x_offset, int y_offset);

#endif
