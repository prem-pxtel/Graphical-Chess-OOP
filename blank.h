#ifndef BLANK_H
#define BLANK_H
#include <iostream>
#include <vector>
#include "piece.h"
#include "board.h"

class Blank : public Piece {
  Board *b;
 public:
  Blank(char piece, Board *b);
  void move(char colOld, int rowOld, char colNew, int rowNew) override;
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
};

#endif
