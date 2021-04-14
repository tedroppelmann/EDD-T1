# Base-T1-2021-1
Código base para tu tarea 1.

## Requerimientos
Debes tener instalada la librería `libpng` para poder leer las imágenes cómo matrices.  
Esta la puedes instalar con el comando:
```sudo apt install libpng-dev```

## Compilar y ejecutar
Compilar:
```make```

Ejecutar:
```./filters <input.png> <output.png> <tipo_de_filtro> <A G | D>```

## Ejemplos:
Filtrar nodos con area mayor a 100 pixeles y grisáceo mayor a 50:
```./filters tests/img1 out.png area 100 50```

Filtrar nodos con delta menor a 0.25:
```./filters tests/img1 out.png delta 0.25```
