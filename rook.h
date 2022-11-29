#ifndef ROOK_H
#define ROOK_H
#include <iostream>
#include <vector>
#include "cell.h"
class Board;

class Rook : public Cell {
  Board *b;
 public:
  Rook(int row, char col, char piece, Board *b);
  void move(char colOld, int rowOld, char colNew, int rowNew) override; 
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow);
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
};

#endif
