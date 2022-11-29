#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include <vector>
#include "cell.h"
class Board;

class Blank : public Cell {
  Board *b;
 public:
  Blank(int row, char col, char piece, Board *b);
  void move(char colOld, int rowOld, char colNew, int rowNew) override;
};

#endif
