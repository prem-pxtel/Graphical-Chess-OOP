#include <iostream>
#include "movingbox.h"

MovingBox::MovingBox(AsciiArt *canvas, int t, int b, int l, int r, 
                     char c, char dir)
    : Decorator{canvas}, t{t}, b{b}, l{l}, r{r}, c{c}, dir{dir} {}
    
char MovingBox::charAt(int row, int col, int tick) {
    if (dir == 'u') {
        if (t - tick <= row && row <= b - tick && l <= col && col <= r)
        return c;
    } else if (dir == 'd') {
        if (t + tick <= row && row <= b + tick && l <= col && col <= r)
        return c;
    } else if (dir == 'l') {
        if (l - tick <= col && col <= r - tick && t <= row && row <= b)
        return c;
    } else if (dir == 'r') {
        if (l + tick <= col && col <= r + tick && t <= row && row <= b)
        return c;
    }
    return canvas->charAt(row, col, tick);
}
