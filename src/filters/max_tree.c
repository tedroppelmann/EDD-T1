#include "max_tree.h"

/* Tranforma el indice en una coordenada (se necesita hacer free desde el invocador de la función) */
int* int_to_coord(int i)
{
    int cociente = (i+1)/width;
    int resto = (i+1)%width;
    int pos_x;
    int pos_y;

    if (resto == 0) //Es la ultima columna
    {
        pos_x = height - 1;
        pos_y = cociente - 1;
    }
    else if (resto == 1) //Es la primera columna
    {
        pos_x = 0;
        pos_y = cociente;
    }
    else if (i < width) //Es la primera fila
    {
        pos_x = i;
        pos_y = 0;
    }
    else if (cociente == (width - 1)) //Es la ultima fila
    {
        pos_x = resto - 1;
        pos_y = width - 1;
    }
    else //Son los de al medio
    {
        pos_x = resto - 1;
        pos_y = cociente;
    }
    int* array = calloc(2, sizeof(int));
    array[0] = pos_x;
    array[1] = pos_y;
    return array;
}

/* Transforma una coordenada en un índice */
int coord_to_int(int x,int y)
{
    int i = 0;
    if (x < width)
    {
        if (y < height)
        {
            i = width * y + x;
        }
    }
    return i;
}
/*LINK de ayuda para esta función: https://hackernoon.com/flood-fill-algorithm-with-recursive-function-sex3uvz */
bool valid(int i,int j)
{
    if(i<0 || i>=height || j<0 || j>=width)
        return false;
    int idx = coord_to_int(i, j);
    if (STATUS[idx] != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Se utiliza para buscar un pixel válido para empezar dentro de los pixeles del nodo */
int search_valid_pixel( MaxTree_Node* node, int grey_level)
{
    if (node->t_head_pixel)
    {
        Pixel* current = node->t_head_pixel;
        while (current)
        {
            if (current->color == grey_level)
            {
                return current->idx;
            }
            current = current->next;
        }
    }
    printf("################## ERROR AL BUSCAR PIXEL VALIDO ##########################");
    return -1;
}

/*  */
int* valid_pixel(int idx, MaxTree_Node* parent, int* ready)
{
    if (parent->t_head_pixel)
    {
        Pixel* current = parent->t_head_pixel;
        while (current)
        {
            if (current->idx == idx)
            {
                return ready;
            }
            current = current->next;
        }
    }
    ready[idx] = 1;
    return ready;
}

/* Busca un pixel valido para empezar sabiendo que no puedo usar los pixeles con ready[] = 1 */
int search_valid_pixel_child(int* pixels, int grey_level, int* ready)
{
    for (int i = 0; i < pixel_count; i++)
    {
        if (pixels[i] >= grey_level)
        {
            if (ready[i] != 1)
            {
                return i;
            }
        }
    }
    printf("################## ERROR AL BUSCAR PIXEL VALIDO  EN HIJOS ##########################");
    return -1;
}

/* Resetea el arreglo checked completo */
void reset_checked()
{
    for (int i = 0; i < pixel_count; i++)
    {
        checked[i] = 0;
    }
}

/* Agrega el pixel final al nodo */
void add_pixel(MaxTree_Node* node, Pixel* pixel)
{
    if (node->head_pixel)
    {
        node->tail_pixel->next = pixel;
        node->tail_pixel = pixel;
    }
    else
    node->head_pixel = pixel;
    node->tail_pixel = pixel;
}

/* Agrega el pixel al nodo a una lista que contiene todos los pixeles del vecindario */
void add_t_pixel(MaxTree_Node* node, Pixel* pixel)
{
    if (node->t_head_pixel)
    {
        node->t_tail_pixel->next = pixel;
        node->t_tail_pixel = pixel;
    }
    else
    node->t_head_pixel = pixel;
    node->t_tail_pixel = pixel;
}

/* Agrega un nodo hijo a la lista de nodos hijos del nodo padre */
void add_node(MaxTree_Node* node, MaxTree_Node* child_node)
{
    if (node->head_node)
    {
        node->tail_node->next_node = child_node;
        node->tail_node = child_node;
    }
    else
    node->head_node = child_node;
    node->tail_node = child_node;
}

/* Cuenta todos los pixeles "tentativos" que hay en un nodo (todos los de su vecinadrio) */
int count_node_t_pixels(MaxTree_Node* node)
{
    int count = 0;
    Pixel* current = node->t_head_pixel;
    while (current)
    {
        count += 1;
        current = current->next;
    }
    return count;
}

/* Retorna true si todos los pixeles tentativos del nodo son del mismo gris */
bool same_color(MaxTree_Node* node)
{
    int i;
    Pixel* current = node->t_head_pixel;
    while (current)
    {
        if (current->next)
        {
            if (current->color == current->next->color)
            {
                i += 1;
            }
        }
        current = current->next;
    }
    if (count_node_t_pixels(node) == i)
    {
        return true;
    } 
    else 
    {
        return false;
    }
}

/* Printea en terminal los pixeles tentativos de un nodo */
void print_t_pixels(MaxTree_Node* node)
{
    printf("\nPIXELES DEL NODO: ");
    Pixel* current = node->t_head_pixel;
    while (current)
    {
        printf("%i-",current->idx);
        current = current->next;
    }
    printf("\n");
    printf("GRIS DEL NODO: %i\n", node->grey_level);
}

/* Retorna el valor mínimo de grris que tiene el nodo */
int grey_jump(MaxTree_Node* node)
{
    Pixel* current = node->t_head_pixel;
    int actual_color = current->color;
    while (current)
    {
        if (current->next)
        {
            if (actual_color > current->next->color)
            {
                actual_color = current->next->color;
            }
        }
        current = current->next;
    }
    return actual_color;
}

/* Inicializa un nodo */
MaxTree_Node* MaxTree_Node__init()
{
    MaxTree_Node* node = calloc(1, sizeof(MaxTree_Node));
    node->next_node = NULL;
    return node;
}

/* Analiza recursivamente todos los pixeles de la imagen para determinar los validos para guardar en la lista definitiva de pixeles del nodo */
/* Idea sacada de: https://hackernoon.com/flood-fill-algorithm-with-recursive-function-sex3uvz */
static void MaxTree_Node__flood(int x, int y, int* pixels, int grey_level, MaxTree_Node* node)
{
    int idx = coord_to_int(x, y); 
    if (checked[idx] == true) // Ya fue revisado
    {
        return;
    }
    if (valid(x, y) == false) // Esta fuera de los margenes de la imagen
    {
        return;
    }
    if (pixels[idx] < grey_level) // Es pixel más oscuro
    {
        return;
    }
    if (pixels[idx] == grey_level) // Es pixel del mismo gris
    {
        Pixel* pixel = Pixel__init(idx, pixels[idx]);
        add_pixel(node, pixel);
        STATUS[idx] = 1;
    }
    checked[idx] = true; 
    MaxTree_Node__flood(x, (y - 1), pixels, grey_level, node);
    MaxTree_Node__flood(x, y + 1, pixels, grey_level, node);
    MaxTree_Node__flood(x - 1, y, pixels, grey_level, node);
    MaxTree_Node__flood(x + 1, y, pixels, grey_level, node);
}

/* Analiza recursivamente todos los pixeles de la imagen para determinar los validos para guardar en la lista tentaiva de pixeles del nodo (vecindario) */
/* Idea sacada de: https://hackernoon.com/flood-fill-algorithm-with-recursive-function-sex3uvz */
static void MaxTree_Node__child_flood(int x, int y, int* pixels, int grey_level, MaxTree_Node* node, int* ready, MaxTree_Node* parent)
{
    int idx = coord_to_int(x, y); 
    if (checked[idx] == true) // Ya fue revisado
    {
        return;
    }
    else if (valid(x, y) == false) // Esta fuera de los margenes de la imagen
    {
        return;
    }
    else if (pixels[idx] < grey_level) // Es pixel más oscuro
    {
        return;
    }
    
    Pixel* pixel = Pixel__init(idx, pixels[idx]);
    add_t_pixel(node, pixel);
    node->t_pixel_number += 1;

    counter += 1;
    ready[idx] = 1;

    checked[idx] = true; 
    MaxTree_Node__child_flood(x, (y - 1), pixels, grey_level, node, ready, parent);
    MaxTree_Node__child_flood(x, y + 1, pixels, grey_level, node, ready, parent);
    MaxTree_Node__child_flood(x - 1, y, pixels, grey_level, node, ready, parent);
    MaxTree_Node__child_flood(x + 1, y, pixels, grey_level, node, ready, parent);
    
    return;
}

/* Función recursiva que crea el Maxtree. Retorna la raiz.*/
MaxTree_Node* MaxTree_Node__create(int* pixels, MaxTree_Node* node, int grey_level)
{
    reset_checked();
    printf("\nNIVEL GRIS: %i", grey_level);
    printf("-%i", node->grey_level);
    node->t_number_of_pixels = count_node_t_pixels(node); //Cuenta la cantidad de t_pixeles del nodo
    int idx = 0;
    
    idx = search_valid_pixel(node, grey_level); //Buscamos un pixel válido para iniciar
    printf("\nPixel válido para empezar: %i\n", idx);
    int* coord = int_to_coord(idx);
    int x = coord[0];
    int y = coord[1];
    
    MaxTree_Node__flood(x, y, pixels, grey_level, node);
    free(coord);
    
    counter = 0;
    int* ready = calloc(pixel_count, sizeof(int));
    for (int i = 0; i < pixel_count; i++) // Sacamos los pixeles que ya están ocupados
    {
        if (STATUS[i] != 0)
        {
            ready[i] = 1;
        }
        valid_pixel(i, node, ready);
        if (ready[i] == 1)
        {
            counter += 1;
        }
    }
    print_t_pixels(node); //Printea los t_pixeles del nodo
    if (same_color(node) == false) // Busco hijos solo si es que existen diferentes grises dentro del nodo
    {
        printf("########## NECESEITA HIJOS ########\n");
        printf("Pixeles que están ocupados: %i\n",counter);
        while (counter < pixel_count)  //Busca los distintos grupos que se generan
        {
            reset_checked();
            idx = search_valid_pixel_child(pixels, grey_level, ready); //Buscamos un pixel válido para iniciar
            if (idx == -1)
            {
                printf("\nERROR\n");
                break;
            }

            printf("\nIDX válido para empezar hijos: %i", idx);
            
            int* coord = int_to_coord(idx); // Transformamos a coordenadas
            int x = coord[0];
            int y = coord[1];
            
            
            MaxTree_Node* child_node = MaxTree_Node__init();
            child_node->parent = node;
            add_node(node, child_node);

            MaxTree_Node__child_flood(x, y, pixels, grey_level, child_node, ready, node);

            free(coord); //liberamos memoria de coordenada

            child_node->grey_level = grey_jump(child_node);

            print_t_pixels(child_node);
        }
    }
    
    free(ready); //Liberamos ready
    counter = 0; //Reseteamos el counter

    printf("\nNODO PADRE:");
    Pixel* current = node->head_pixel;
    while (current)
    {
        printf("%i,", current->idx);
        current = current->next;
    }

    printf("\n#############################\n");
    printf("#############################");

   
    MaxTree_Node* actual;
    if (node->head_node)
    {
        actual = node->head_node;
        while (actual)
        {
            int jump = grey_jump(actual);
            MaxTree_Node__create(pixels, actual, jump);
            actual = actual->next_node;
        }
    }
    return node;
}

int main()
{
    pixel_count = 25;
    int P[25] = {3,1,0,2,1  ,1,3,0,2,2   ,0,0,1,0,0   ,1,2,0,2,2  ,3,2,0,2,2};
    height = 5;
    width = 5;

    STATUS = calloc(pixel_count, sizeof(int));
    checked = calloc(pixel_count, sizeof(bool)); //Ayuda a ver los pixeles ya revisados

    MaxTree_Node* node = MaxTree_Node__init();

    for (int i = 0; i < pixel_count; i++)
    {
        Pixel* pixel = Pixel__init(i, P[i]);
        add_t_pixel(node, pixel);
    }
    
    printf("INICIO\n");
    MaxTree_Node* root = MaxTree_Node__create(P, node, 0);

    free(checked);
    free(STATUS);
    
}