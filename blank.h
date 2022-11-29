#ifndef BLANK_H
#define BLANK_H
#include <iostream>
#include <vector>
#include "cell.h"
#include "board.h"

class Blank : public Cell {
  Board *b;
 public:
  Blank(int row, char col, char piece, Board *b);
  void move(char colOld, int rowOld, char colNew, int rowNew) override;
};

#endif
