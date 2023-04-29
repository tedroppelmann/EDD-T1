# Max Tree 
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

```./filters tests/easy/test_1.png out.png area 5 60``` FUNCIONA

```./filters tests/easy/test_2.png out.png area 12 40``` FUNCIONA
```./filters tests/easy/test_2.png out.png area 50 5``` FUNCIONA
```./filters tests/easy/test_3.png out.png area 50 40``` FUNCIONA
```./filters tests/easy/test_4.png out.png area 18 30``` FUNCIONA

```./filters tests/medium/mona_lisa.png out.png area 5 30``` FUNCIONA
```./filters tests/medium/moon.png out.png area 20 50``` FUNCIONA

```./filters tests/hard/moon.png out.png area 500 7``` FUNCIONA
```./filters tests/hard/plate.png out.png area 100 60``` FUNCIONA
```./filters tests/hard/campus.png out.png area 200 0``` FUNCIONA





Filtrar nodos con delta menor a 0.25:
```./filters tests/img1 out.png delta 0.25```

```./filters tests/easy/test_1.png out.png delta 0.5``` FUNCIONA
```./filters tests/easy/test_2.png out.png delta 0.01``` FUNCIONA
```./filters tests/easy/test_3.png out.png delta 0.1``` FUNCIONA
```./filters tests/easy/test_3.png out.png delta 0.01``` FUNCIONA
```./filters tests/easy/test_4.png out.png delta 0.01``` FUNCIONA (habia que cambiar la raiz a 0)

```./filters tests/medium/mona_lisa.png out.png delta 0.25``` FUNCIONA
```./filters tests/medium/moon.png out.png delta 0.01``` FUNCIONA
```./filters tests/medium/moon.png out.png delta 0.05``` FUNCIONA


```./filters tests/hard/moon.png out.png delta 0.008``` FUNCIONA
```./filters tests/hard/plate.png out.png delta 0.005``` FUNCIONA
```./filters tests/hard/campus.png out.png delta 0.01``` FUNCIONA
```./filters tests/hard/campus.png out.png delta 0.03``` FUNCIONA
```./filters tests/hard/campus.png out.png delta 0.05``` FUNCIONA
```./filters tests/hard/moon.png out.png delta 0.008``` FUNCIONA

```./filters campus.png out.png delta 0.25```



