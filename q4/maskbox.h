#ifndef MASKBOX_H
#define MASKBOX_H
#include <iostream>
#include "decorator.h"
class AsciiArt;

class MaskBox : public Decorator {
 int t;
 int b;
 int l;
 int r;
 char c;
 public:
  MaskBox(AsciiArt *canvas, int t, int b, int l, int r, char c);
  char charAt(int row, int col, int tick) override;
};

#endif
