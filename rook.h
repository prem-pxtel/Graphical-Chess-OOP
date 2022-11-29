#ifndef ROOK_H
#define ROOK_H
#include <iostream>
#include <vector>
#include "board.h"

class Rook : public Board {
  Board *b;
 public:
  Rook(Board *b);
  void move(char colOld, int rowOld, char colNew, int rowNew);
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow);
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
};

#endif
