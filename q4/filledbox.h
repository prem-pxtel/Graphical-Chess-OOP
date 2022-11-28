#ifndef FILLEDBOX_H
#define FILLEDBOX_H
#include <iostream>
#include "decorator.h"
class AsciiArt;

class FilledBox : public Decorator {
 int t;
 int b;
 int l;
 int r;
 char c;
 public:
  FilledBox(AsciiArt *canvas, int t, int b, int l, int r, char c);
  char charAt(int row, int col, int tick) override;
};

#endif
