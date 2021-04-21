#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


int height; //Largo imagen
int width; //Ancho imagen
int pixel_count;
int* STATUS; //Estatus de cada pixel de la imagen
int counter;

bool* checked;

struct pixel;
typedef struct pixel Pixel;

struct pixel
{
    int idx;
    Pixel* next;
    int color;
};

Pixel* Pixel__init(int idx, int color)
{
    Pixel* pixel = calloc(1, sizeof(Pixel));
    pixel->idx = idx;
    pixel->next = NULL;
    pixel->color = color;
    return pixel;
}

struct max_tree_node;
typedef struct max_tree_node MaxTree_Node;

struct max_tree_node
{
    MaxTree_Node* parent;
    MaxTree_Node* head_node;
    MaxTree_Node* tail_node;
    MaxTree_Node* next_node;

    Pixel* head_pixel;
    Pixel* tail_pixel;

    Pixel* t_head_pixel;
    Pixel* t_tail_pixel;
    int t_number_of_pixels;

    int pixel_number;
    int t_pixel_number;
    int grey_level;
};

int* int_to_coord(int i);
int coord_to_int(int x,int y);
bool valid(int i,int j);
int search_valid_pixel( MaxTree_Node* node, int grey_level);
int* valid_pixel(int idx, MaxTree_Node* parent, int* ready);
int search_valid_pixel_child(int* pixels, int grey_level, int* ready);
void reset_checked();
void add_pixel(MaxTree_Node* node, Pixel* pixel);
void add_t_pixel(MaxTree_Node* node, Pixel* pixel);
void add_node(MaxTree_Node* node, MaxTree_Node* child_node);
int count_node_t_pixels(MaxTree_Node* node);
bool same_color(MaxTree_Node* node);
void print_t_pixels(MaxTree_Node* node);
int grey_jump(MaxTree_Node* node);

MaxTree_Node* MaxTree_Node__init();
static void MaxTree_Node__flood(int x, int y, int* pixels, int grey_level, MaxTree_Node* node);
static void MaxTree_Node__child_flood(int x, int y, int* pixels, int grey_level, MaxTree_Node* node, int* ready, MaxTree_Node* parent);
MaxTree_Node* MaxTree_Node__create(int* pixels, MaxTree_Node* node, int grey_level);

