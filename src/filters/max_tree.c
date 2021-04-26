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
        pos_x = width - 1;
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
    if (x < width)
    {
        if (y < height)
        {
            return width * y + x;
        }
    }
    return -1;
}

/*Función sacada de: https://hackernoon.com/flood-fill-algorithm-with-recursive-function-sex3uvz */
bool valid(int i,int j)
{
    if(i<0 || i>=width || j<0 || j>=height)
        return false;
    else
    {
        return true;
    }
}

/* Busca un pixel valido en el vecindario para empezar sabiendo que no puedo usar los pixeles con ready[] = 1 */
int search_valid_pixel_child(int* revisados, MaxTree_Node* parent)
{
    Pixel* current = parent->t_head_pixel;
    while (current)
    {
        if (revisados[current->idx] != 1)
        {
            return current->idx;
        }
        current = current->next;
    }
    printf("################## ERROR AL BUSCAR PIXEL VALIDO  EN HIJOS ##########################");
    return -1;
}

/* Resetea los valores del checked que le interesan al nodo */
void reset_checked(MaxTree_Node* node)
{
    Pixel* current = node->t_head_pixel;
    while (current)
    {
        checked[current->idx] = 0;
        current = current->next;
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
    node->number_of_pixels += 1;
}

/* Agrega el pixel al nodo a una lista que contiene todos los pixeles del vecindario */
void add_t_pixel(MaxTree_Node* node, Pixel* pixel)
{
    if (pixel->color < node->grey_level)
    {
        node->grey_level = pixel->color;
    }
    
    if (node->t_head_pixel)
    {
        if (node->t_tail_pixel)
        {
            if (node->t_tail_pixel->color != pixel->color)
            {
                node->diff_colors = true;
            }
        }
        node->t_tail_pixel->next = pixel;
        node->t_tail_pixel = pixel;
    }
    else
    node->t_head_pixel = pixel;
    node->t_tail_pixel = pixel;
    node->t_number_of_pixels += 1;
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

/* Printea en terminal los pixeles tentativos de un nodo */
void print_t_pixels(MaxTree_Node* node)
{
    Pixel* current = node->t_head_pixel;
    while (current)
    {
        printf("%i-",current->idx);
        current = current->next;
    }
    printf("\n");
    printf("GRIS DEL NODO: %i\n", node->grey_level);
}

/* Inicializa un nodo */
MaxTree_Node* MaxTree_Node__init()
{
    MaxTree_Node* node = calloc(1, sizeof(MaxTree_Node));
    node->next_node = NULL;
    node->t_head_pixel = NULL;
    node->t_tail_pixel = NULL;
    node->diff_colors = false;
    node->grey_level = BIGVAL;
    return node;
}

/* Guarda solo los pixeles del mismo gris que el nodo */
int* MaxTree_Node__filter(MaxTree_Node* node, int* revisados)
{
    Pixel* current = node->t_head_pixel;
    while (current)
    {
        if (current->color == node->grey_level)
        {
            Pixel* pixel = Pixel__init(current->idx, current->color);
            add_pixel(node, pixel);
            STATUS[current->idx] = 1;
            revisados[current->idx] = 1;
            
        }
        current = current->next;
    }
    return revisados;
}


/* Analiza recursivamente todos los pixeles de la imagen para determinar los validos para guardar en la lista tentaiva de pixeles del nodo (vecindario) */
/* Idea sacada de: https://hackernoon.com/flood-fill-algorithm-with-recursive-function-sex3uvz */

void MaxTree_Node__child_flood1(int x, int y, int* pixels, int grey_level, MaxTree_Node* node)
{
    int idx = coord_to_int(x, y); //Transforma la coordenada a un índice
    if (valid(x, y) == false) // Esta fuera de los margenes de la imagen
    {
        return;
    }
    if (STATUS[idx] != 0)
    {
        return;
    }
    if (checked[idx] == true) // Ya fue revisado
    {
        return;
    }
    if (pixels[idx] < grey_level) // Es pixel más oscuro
    {
        return;
    } 
    if (pixels[idx] >= grey_level)
    {
        Pixel* pixel = Pixel__init(idx, pixels[idx]);
    
        add_t_pixel(node, pixel); // Agrego al vecindario
        
        checked[idx] = true;
        
        MaxTree_Node__child_flood1(x, y - 1, pixels, grey_level, node);
        MaxTree_Node__child_flood1(x, y + 1, pixels, grey_level, node);
        MaxTree_Node__child_flood1(x - 1, y, pixels, grey_level, node);
        MaxTree_Node__child_flood1(x + 1, y, pixels, grey_level, node);
    }
    return;
}


/* Cambio de la función anterior, ya que hacia stackoverflow al hacer un flood fill recursivo. Ahora se ocupa una fila FIFO */
/* Idea sacada de: https://stackoverflow.com/questions/30608448/flood-fill-recursive-stack-overflow */
void MaxTree_Node__child_flood(int i, int j, int* pixels, int grey_level, MaxTree_Node* node, MaxTree_Node* parent)
{
    struct Queue* queue = createQueue(pixel_count); 
    enqueue(queue, coord_to_int(i, j));

    while (!isEmpty(queue))
    {
        int idx = front(queue);
        int *coord = int_to_coord(idx); 
        int x = coord[0];
        int y = coord[1];
        free(coord);

        dequeue(queue);

        if (valid(x, y) == true)
        {
            if (STATUS[idx] == 0 && checked[idx] == false && pixels[idx] >= parent->grey_level)
            {
                Pixel* pixel = Pixel__init(idx, pixels[idx]);
                add_t_pixel(node, pixel);          
                checked[idx] = true;

                if (valid(x, y - 1))
                {
                    enqueue(queue, coord_to_int(x, y - 1));
                }
                if (valid(x, y + 1))
                {
                    enqueue(queue, coord_to_int(x, y + 1));
                }
                if (valid(x - 1, y))
                {
                    enqueue(queue, coord_to_int(x - 1, y));
                }
                if (valid(x + 1, y))
                {
                    enqueue(queue, coord_to_int(x + 1, y));
                }
            }
        }
    }
    free(queue);
}

/* Función recursiva que crea el Maxtree. Retorna la raiz.*/
MaxTree_Node* MaxTree_Node__create(int* pixels, MaxTree_Node* node, int* revisados)
{
    //Resetea las revisiones
    reset_checked(node);
    
    //Separa solo los pixeles del mismo gris del vecindario, los guarda y actualiza revisados
    revisados = MaxTree_Node__filter(node, revisados);  

    // Busco hijos solo si es que existen diferentes grises dentro del nodo
    if (node->diff_colors == true)                                                            
    {
        /*
        printf("\n########## NECESITA HIJOS ########\n");
        printf("Pixeles que están ocupados: %i\n",counter);
        */
        //Buscamos todos distintos vecindarios que se generan
        int count = 0;
        int limit = (node->t_number_of_pixels) - (node->number_of_pixels);
        /*
        printf("LIMIT: %i\n", limit);
        */
        while (count < limit)                 
        {
            //Buscamos un pixel válido para iniciar dentro del vecindario
            int idx = search_valid_pixel_child(revisados, node);                                  
            if (idx == -1)
            {
                printf("\nERROR\n");
                break;
            }
            /*
            printf("Pixel válido IDX: %i\n",idx);
            */
            // Transformamos índice a coordenadas
            int *coord = int_to_coord(idx); 
            int x = coord[0];
            int y = coord[1];
            free(coord);   
            
            MaxTree_Node* child_node = MaxTree_Node__init();                                  // Creo el nodo hijo
            child_node->parent = node;                                                        // Guarda el nodo padre en el nodo hijo
            add_node(node, child_node);                                                       // Guarda el nodo hijo en el nodo padre
        
            MaxTree_Node__child_flood(x, y, pixels, node->grey_level, child_node, node);

            count += child_node->t_number_of_pixels;

            MaxTree_Node__create(pixels, child_node, revisados);
        }
    }
    return node;
}

void print_maxtree_2(MaxTree_Node* root, int depth)
{
    MaxTree_Node* current = root->head_node;
    char spaces[4*depth + 1];
    for (int i = 0; i < 4*depth; i++)
    {
        spaces[i] = ' ';
    }
    spaces[4*depth - 1] = '\0';
    while (current)
    {
        Pixel* actual = current->head_pixel;
        printf("%s", spaces);
        printf("(%i)",current->grey_level);
        while (actual)
        {   
            if (actual->next)
            {
                printf("%i(%i)-", actual->idx,actual->color);
            }
            else printf("%i(%i)", actual->idx,actual->color);
            actual = actual->next;
        }
        printf("\n");
        print_maxtree_2(current, depth + 1);
        current = current->next_node;
    }
}

void print_maxtree(MaxTree_Node* root)
{
    printf("(%i)",root->grey_level);
    Pixel* current = root->head_pixel;
    while (current)
    {
        if (current->next)
        {
            printf("%i-", current->idx);
        }
        else printf("%i", current->idx);
        current = current->next;
    }
    printf("\n");
    print_maxtree_2(root, 1);
}

void return_array_2(MaxTree_Node* node, int* pixels)
{
    MaxTree_Node* current = node->head_node;
    while (current)
    {
        Pixel* actual = current->head_pixel;
        while (actual)
        {
            pixels[actual->idx] = actual->color;
            actual = actual->next;
        }
        return_array_2(current, pixels);
        current = current->next_node;
    }
}

void return_array(MaxTree_Node* root, int* pixels)
{
    Pixel* current = root->head_pixel;
    while (current)
    {
        pixels[current->idx] = current->color;
        current = current->next;
    }
    return_array_2(root, pixels);
}

void change_color(MaxTree_Node* node, int new_color)
{
    Pixel* current = node->head_pixel;
    while (current)
    {
        current->color = new_color;
        current = current->next;
    }
    node->grey_level = new_color;
    return;
}

void area_filter(MaxTree_Node* root, int G, int A)
{   
    MaxTree_Node* current = root->head_node;
    while (current)
    {
        if (current->grey_level > G && current->t_number_of_pixels > A)
        {
            // Cumple todas las condiciones
        }
        else if (current->parent && current->grey_level != 0)
        {
            change_color(current, current->parent->grey_level);
        }
        area_filter(current, G, A);
        current = current->next_node;
    }
}

void area_filter_initial(MaxTree_Node* root, int G, int A)
{
    if (root->grey_level > G && root->t_number_of_pixels > A)
    {
        // Cumple todas las condiciones
    }
    else if (root->grey_level != 0)
    {
        change_color(root, 0);
    }
    area_filter(root, G, A);
}

void delta_filter(MaxTree_Node* root, float D)
{   
    MaxTree_Node* current = root->head_node;
    while (current)
    {
        float numerador = (current->parent->t_number_of_pixels - current->t_number_of_pixels);
        float denominador = (current->parent->t_number_of_pixels);
        float cond = numerador/denominador;
        if (cond < D || current->grey_level == current->parent->grey_level)
        {
            // Cumple todas las condiciones
        }
        else if (current->parent && cond >= D && current->grey_level != 0)
        {
            change_color(current, current->parent->grey_level);
        }
        delta_filter(current, D);
        current = current->next_node;
    }
}

/*
int main()
{
    pixel_count = 25;
    int P[25] = 
    {3,0,0,0,2,
    3,0,0,0,1,
    0,0,4,0,2,
    1,2,3,1,2,
    2,1,3,0,1};
    height = 5;
    width = 5;

    STATUS = calloc(pixel_count, sizeof(int));
    checked = calloc(pixel_count, sizeof(bool));            //Ayuda a ver los pixeles ya revisados
    int* revisados = calloc(pixel_count, sizeof(int));
    
    MaxTree_Node* node = MaxTree_Node__init();

    for (int i = 0; i < pixel_count; i++)
    {
        Pixel* pixel = Pixel__init(i, P[i]);
        add_t_pixel(node, pixel);
    }
    node->grey_level = min_grey(node);

    MaxTree_Node* root = MaxTree_Node__create(P, node, revisados);

    print_maxtree_root(root);

    int* final_pixels = calloc(pixel_count, sizeof(int));
    return_array(root, final_pixels);
    for (int i = 0; i < pixel_count; i++)
    {
        printf("%i-",final_pixels[i]);
    }

    printf("\n");

    int* pixels = calloc(pixel_count, sizeof(int));
    return_array(root, pixels);
    area_filter_2(root, 1, 1, pixels);
    

    free(final_pixels);
    free(checked);
    free(STATUS);
}
*/