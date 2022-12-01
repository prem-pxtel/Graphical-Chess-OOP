#ifndef KNIGHT_H
#define KNIGHT_H
#include <iostream>
#include <vector>
#include "piece.h"
class Board;

class Knight : public Piece {
  Board *b;
  int obstacleRow;
  char obstacleCol;
 public:
  Knight(char piece, Board *b);
  ~Knight();
  void move(char colOld, int rowOld, char colNew, int rowNew) override; 
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow) override;
  int ObstacleR() override;
  char ObstacleC() override;
};

#endif
