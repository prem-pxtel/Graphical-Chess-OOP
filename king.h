#ifndef KING_H
#define KING_H
#include <iostream>
#include <vector>
#include "piece.h"
class Board;

class King : public Piece {
  Board *b;
  bool firstMove;
  int obstacleRow;
  char obstacleCol;
 public:
  King(char piece, Board *b);
  //virtual ~King();
  void move(char colOld, int rowOld, char colNew, int rowNew) override; 
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
  void castle(int oldRow, char oldCol, int newRow, char newCol);
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow);
  bool isValidCastle(char oldCol, int oldRow, char newCol, int newRow);
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
};

#endif
