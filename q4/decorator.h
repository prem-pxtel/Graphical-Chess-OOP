#ifndef DECORATOR_H
#define DECORATOR_H
#include <iostream>
#include "asciiart.h"

class Decorator : public AsciiArt {
 protected:
   AsciiArt *canvas;
 public:
  Decorator(AsciiArt *canvas);
  virtual ~Decorator();
};

#endif
