#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

struct pixel;
typedef struct pixel Pixel;

struct pixel
{
    int idx;
    Pixel* next;
    int color;
};

Pixel* Pixel__init(int idx, int color);


