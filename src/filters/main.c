#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../imagelib/image.h"


#include "max_tree.h"



int main(int argc, char** argv)
{
    // Revisamos los argumentos
    if(argc < 4) {
        printf("Modo de uso: %s <input.png> <output.png> <command> [args]\n", argv[0]);
        return 1;
    }
    // Cargamos la imagen original desde el archivo
    Image* image = img_png_read_from_file(argv[1]);

    /* ------------- POR IMPLEMENTAR -------------- */
    /* Aqui debes crear el MaxTree de la imagen.    */
    
    /*
    pixel_count = 9;
    int P[9] = {0,0,0,0,0,0,0,0,0};
    height = 3;
    width = 3;
    */

    pixel_count = image->pixel_count;
    height = image->height;
    width = image->width;

    STATUS = calloc(pixel_count, sizeof(int));
    checked = calloc(pixel_count, sizeof(bool));
    int* revisados = calloc(pixel_count, sizeof(int));

    MaxTree_Node* node = MaxTree_Node__init();
    for (int i = 0; i < pixel_count; i++)
    {
        Pixel* pixel = Pixel__init(i, image->pixels[i]);
        add_t_pixel(node, pixel);
    }
    node->grey_level = min_grey(node);
    MaxTree_Node* root = MaxTree_Node__create(image->pixels, node, revisados);

    free(checked);
    free(STATUS);
    free(revisados);


    // Creamos una nueva imagen de igual tamaño, para el output
    Image* new_img = calloc(1, sizeof(Image));
    *new_img = (Image) {
        .height = image->height,
        .width = image->width,
        .pixel_count = image->pixel_count,
        .pixels = calloc(pixel_count, sizeof(int))
    };

    // Filtramos el arbol y lo guardamos en la imagen, segun el filtro que corresponda
    if (! strcmp("delta", argv[3]))
    {
        // Filtro DELTA
        float max_delta = atof(argv[4]);

        /* ------------- POR IMPLEMENTAR -------------- */
        /* Aqui debes implementar el filtro delta y     */
        /* guardar la imagen filtrada en new_img.       */
        delta_filter(root, max_delta);
        return_array(root, new_img->pixels);

    }
    else if (! strcmp("area", argv[3]))
    {
        // Filtro AREA-COLOR
        int min_area = atoi(argv[4]);
        int threshold = atoi(argv[5]);

        /* ------------- POR IMPLEMENTAR -------------- */
        /* Aqui debes implementar el filtro de area y   */
        /* guardar la imagen filtrada en new_img.       */
        area_filter_initial(root, threshold, min_area);
        return_array(root, new_img->pixels);
        
    }
    // Exportamos la nueva imagen
    printf("Guardando imagen en %s\n", argv[2]);
    img_png_write_to_file(new_img, argv[2]);
    printf("Listo!\n");

    // Liberamos los recursos
    img_png_destroy(image);
    img_png_destroy(new_img);

    // Terminamos exitosamente
    return 0;
}