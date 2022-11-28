#ifndef BLANK_H
#define BLANK_H
#include "asciiart.h"
#include <iostream>

class Blank: public AsciiArt {
 public:
  char charAt(int row, int col, int tick) override;
};

#endif
