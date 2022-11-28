#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include "decorator.h"
class Board;

class Pawn : public Decorator {
 Board *b;
 int row;
 char col;
 bool colour;
 public:
  Pawn(Board *b, int row, char col, bool colour);
  void move() override;
  void capture() override;
  void promote() override;
  void check() override;
  void checkmate() override;
  void stalemate() override;
};

#endif
