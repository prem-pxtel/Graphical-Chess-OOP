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
  bool lastmovecapture = false;
  char capturedpiece;
  bool capturedfirst;
  bool capturedpiececolour;
 public:
  Bishop(char piece, Board *b);
  ~Bishop();
  void move(char colOld, int rowOld, char colNew, 
            int rowNew, char newPiece) override;
  void revertmove(char colOld, int rowOld, char colNew, 
            int rowNew, char newPiece) override;
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow) override;
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
  bool isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) override;
  int getObsRow() override;
  char getObsCol() override;
  void clearObs() override;
};

#endif
