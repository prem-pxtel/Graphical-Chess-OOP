#ifndef MOVINGBOX_H
#define MOVINGBOX_H
#include <iostream>
#include "decorator.h"
class AsciiArt;

class MovingBox : public Decorator {
 int t;
 int b;
 int l;
 int r;
 char c;
 char dir;
 public:
  MovingBox(AsciiArt *canvas, int t, int b, int l, int r, char c, char dir);
  char charAt(int row, int col, int tick) override;
};

#endif
