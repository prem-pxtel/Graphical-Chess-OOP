#ifndef KING_H
#define KING_H
#include <iostream>
#include <vector>
#include "piece.h"
class Board;

class King : public Piece {
  Board *b;
  bool firstMove;
 public:
  King(char piece, Board *b);
  void move(char colOld, int rowOld, char colNew, int rowNew) override; 
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow);
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
};

#endif
