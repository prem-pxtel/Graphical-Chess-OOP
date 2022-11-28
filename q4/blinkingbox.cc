#include <iostream>
#include "blinkingbox.h"

BlinkingBox::BlinkingBox(AsciiArt *canvas, int t, int b, int l, int r, char c)
    : Decorator{canvas}, t{t}, b{b}, l{l}, r{r}, c{c} {}
    
char BlinkingBox::charAt(int row, int col, int tick) {
    if (t <= row && row <= b && l <= col && col <= r) {
        if (tick % 2 == 0) return c;
        else return ' ';
    }
    return canvas->charAt(row, col, tick);
}
