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

```./filters tests/easy/test_1.png out.png area 5 60```
```./filters tests/easy/test_2.png out.png area 100 50```
```./filters tests/easy/test_3.png out.png area 100 50```
```./filters tests/easy/test_4.png out.png area 100 50```

```./filters tests/medium/mona_lisa.png out.png area 100 50```
```./filters tests/medium/moon.png out.png area 20 5```


Filtrar nodos con delta menor a 0.25:
```./filters tests/img1 out.png delta 0.25```

```./filters tests/easy/test_1.png out.png delta 0.5```
```./filters tests/easy/test_2.png out.png delta 0.01```
```./filters tests/easy/test_3.png out.png delta 0.01```
```./filters tests/easy/test_4.png out.png delta 0.01```

```./filters tests/medium/mona_lisa.png out.png delta 0.25```
```./filters tests/medium/moon.png out.png delta 0.01```


```./filters tests/hard/moon.png out.png delta 0.25```
```./filters tests/hard/plate.png out.png delta 0.25```
```./filters tests/hard/campus.png out.png delta 0.25```

```./filters campus.png out.png delta 0.25```



