#include "pixel.h"

Pixel* Pixel__init(int idx, int color)
{
    Pixel* pixel = calloc(1, sizeof(Pixel));
    pixel->idx = idx;
    pixel->next = NULL;
    pixel->color = color;
    return pixel;
}

