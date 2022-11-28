#ifndef BLINKINGBOX_H
#define BLINKINGBOX_H
#include <iostream>
#include "decorator.h"
class AsciiArt;

class BlinkingBox : public Decorator {
 int t;
 int b;
 int l;
 int r;
 char c;
 public:
  BlinkingBox(AsciiArt *canvas, int t, int b, int l, int r, char c);
  char charAt(int row, int col, int tick) override;
};

#endif
