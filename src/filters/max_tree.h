#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


#include "pixel.h"


int height; //Largo imagen
int width; //Ancho imagen
int pixel_count; //Cantidad de pixeles de la imagen
int* STATUS; //Estatus de cada pixel de la imagen
bool* checked;


/*
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
*/


struct max_tree_node;
typedef struct max_tree_node MaxTree_Node;

struct max_tree_node
{
    MaxTree_Node* parent;
    MaxTree_Node* head_node;
    MaxTree_Node* tail_node;
    MaxTree_Node* next_node;

    // Pixeles del nodo
    Pixel* head_pixel;
    Pixel* tail_pixel;
    int number_of_pixels;

    // Pixeles del vecindario
    Pixel* t_head_pixel;
    Pixel* t_tail_pixel;
    int t_number_of_pixels;

    bool diff_colors;
    int grey_level;
};

int* int_to_coord(int i);
int coord_to_int(int x,int y);
bool valid(int i,int j);
int* valid_pixel(int idx, MaxTree_Node* parent, int* ready);
int search_valid_pixel_child(int* ready, MaxTree_Node* node);
void reset_checked(MaxTree_Node* node);
void add_pixel(MaxTree_Node* node, Pixel* pixel);
void add_t_pixel(MaxTree_Node* node, Pixel* pixel);
void add_node(MaxTree_Node* node, MaxTree_Node* child_node);
int count_node_t_pixels(MaxTree_Node* node);
bool same_color(MaxTree_Node* node);
void print_t_pixels(MaxTree_Node* node);
int min_grey(MaxTree_Node* node);

MaxTree_Node* MaxTree_Node__init();
int* MaxTree_Node__filter(MaxTree_Node* node, int* revisados);
void MaxTree_Node__child_flood(int x, int y, int* pixels, int grey_level, MaxTree_Node* node, int count);
MaxTree_Node* MaxTree_Node__create(int* pixels, MaxTree_Node* node, int* revisados);

void print_maxtree_2(MaxTree_Node* root, int depth);
void print_maxtree(MaxTree_Node* root);

void return_array_2(MaxTree_Node* node, int* pixels);
void return_array(MaxTree_Node* root, int* pixels);

void change_color(MaxTree_Node* node, int new_color);
void area_filter(MaxTree_Node* root, int G, int A);
void area_filter_initial(MaxTree_Node* root, int G, int A);

void delta_filter(MaxTree_Node* root, float D);


