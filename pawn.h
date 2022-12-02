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
  ~Pawn();
  void move(char colOld, int rowOld, char colNew, 
            int rowNew, char newPiece) override;
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
  void promote(char oldPiece, char newPiece, int newRow, char newCol);
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow) override;
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
  bool isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow);
  bool promoReady(char oldPiece, int newRow);
  int getObsRow() override;
  char getObsCol() override;
  void clearObs() override;
};

#endif
