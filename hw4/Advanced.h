

#ifndef ADVANCED
#define ADVANCED

#include "Constants.h"
#include "Image.h"

IMAGE *FillLight(IMAGE *image, int number, int lightWidth);

IMAGE *Posterize(IMAGE *image ,unsigned int pbits);

IMAGE *Overlay(char fname[SLEN],IMAGE *image,int x_offset, int y_offset);

IMAGE *Resize(unsigned int percentage, IMAGE *image);

IMAGE *Rotate(IMAGE *image);

IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration);

#endif
