
#ifndef DIPS_H
#define DIPS_H
#include "Constants.h"

void    BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


void    VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


void    HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


void    ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT],
                int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) ;


void    Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


void    Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


#endif

