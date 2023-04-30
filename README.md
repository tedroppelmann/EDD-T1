# Max Tree and filtering

This programme uses the Max Tree data structure to segment a greyscale image, and then uses this tree to generate a new image, to which a particular filter is applied.

## Requirements

You need to have installed the `libpng` library to read the an image as a matrix.

```sudo apt install libpng-dev```

## Compilation and execution
Compile:
```make```

Execute:
```./filters <input.png> <output.png> <filter_type> <A G | D>```

## Types of filters

Once we have created the Max Tree of an image, we will apply one of the following filters to create a piece of graphic art.

1. **Area filter:** This filter selects the neighbourhoods associated with tree nodes in an image that meet two conditions:
   1.  Each pixel in the neighbourhood is larger than a certain greyness value G.
   2.  The number of pixels in the neighbourhood is greater than a number A.

   If the neighbourhood meets both conditions, its pixels keep their colours. On the other hand, if a neighbourhood does not meet either condition, the pixels become the shade of grey of their parent at that time. If that pixel is black, its greyscale is kept at zero.
2. **Delta filter:** This filter selects the neighbourhoods whose difference in the number of pixels with respect to the neighbourhood of their parent is less than a D calculated as of its parent is less than a D calculated as:

$$ D = {parentPixels - childrenPixels \over parentPixels} $$

As in the previous filter, the neighbourhoods that do not meet the condition become the tone of the neighbourhood's parent, while those that do meet D keep their greyness. The neighbourhood associated to the root node is not considered, since the root does not have a parent. Also, if there is no variation with the parent node, the filter is not applied.

## Examples
Filter nodes with area greater than 100 pixels and greyness greater than 50:

```./filters tests/medium/mona_lisa.png out.png area 100 50```


Filter nodes with delta less than 0.25:

```./filters tests/hard/plate.png out.png delta 0.25```
