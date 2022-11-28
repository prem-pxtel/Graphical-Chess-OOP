#include <iostream>
#include "maskbox.h"

MaskBox::MaskBox(AsciiArt *canvas, int t, int b, int l, int r, char c)
    : Decorator{canvas}, t{t}, b{b}, l{l}, r{r}, c{c} {}
    
char MaskBox::charAt(int row, int col, int tick) {
    if (canvas->charAt(row, col, tick) != ' ') {
        if (t <= row && row <= b && l <= col && col <= r) return c;
    }
    return canvas->charAt(row, col, tick);
}
