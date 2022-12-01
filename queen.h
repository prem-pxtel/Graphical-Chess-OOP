#ifndef QUEEN_H
#define QUEEN_H
#include <iostream>
#include <vector>
#include "piece.h"
class Board;

class Queen : public Piece {
  Board *b;
  int obstacleRow;
  char obstacleCol;
 public:
  Queen(char piece, Board *b);
  ~Queen();
  void move(char colOld, int rowOld, char colNew, int rowNew) override; 
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
  bool isValidMoveb(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow);
  bool isValidMover(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow); 
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow) override;
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
  int ObstacleR() override;
  char ObstacleC() override;
};

#endif
