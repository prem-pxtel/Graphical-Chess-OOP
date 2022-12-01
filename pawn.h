#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include <vector>
#include "piece.h"
#include "board.h"

class Pawn : public Piece {
  Board *b;
  bool firstMove;
  int obstacleRow;
  char obstacleCol;
 public:
  Pawn(char piece, Board *b);
  void move(char colOld, int rowOld, char colNew, int rowNew) override;
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow);
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
  bool isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow);
};

#endif
