
#ifndef DIPS_H
#define DIPS_H
#include "Constants.h"
#include "Image.h"

IMAGE   *BlackNWhite(IMAGE *image);


IMAGE   *VFlip(IMAGE *image);


IMAGE   *HMirror(IMAGE *image);


IMAGE   *ColorFilter(IMAGE *image,int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) ;


IMAGE   *Shuffle(IMAGE *image);


IMAGE   *Edge(IMAGE *image);


#endif

