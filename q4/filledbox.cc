#include <iostream>
#include "filledbox.h"

FilledBox::FilledBox(AsciiArt *canvas, int t, int b, int l, int r, char c)
    : Decorator{canvas}, t{t}, b{b}, l{l}, r{r}, c{c} {}
    
char FilledBox::charAt(int row, int col, int tick) {
    if (t <= row && row <= b && l <= col && col <= r) {
        return c;
    }
    return canvas->charAt(row, col, tick);
}
