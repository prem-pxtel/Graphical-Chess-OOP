#ifndef DECORATOR_H
#define DECORATOR_H
#include <iostream>
#include "board.h"

class Decorator : public Board {
 protected:
   Board *b;
 public:
  Decorator(Board *b);
  virtual ~Decorator();
  virtual void move() = 0;
  virtual void capture() = 0;
  virtual void promote() = 0;
  virtual void check() = 0;
  virtual void checkmate() = 0;
  virtual void stalemate() = 0;
};

#endif
