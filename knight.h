#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include <vector>
#include "piece.h"
class Board;

class Knight : public Piece {
  Board *b;
 public:
  Knight(char piece, Board *b);
  void move(char colOld, int rowOld, char colNew, int rowNew) override; 
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow);
};

#endif
