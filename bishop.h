#ifndef BISHOP_H
#define BISHOP_H
#include <iostream>
#include <vector>
#include "piece.h"
class Board;

class Bishop : public Piece {
  Board *b;
  int obstacleRow;
  char obstacleCol;
 public:
  Bishop(char piece, Board *b);
  ~Bishop();
  void move(char colOld, int rowOld, char colNew, int rowNew) override;
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow);
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
};

#endif
