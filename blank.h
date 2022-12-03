#ifndef BLANK_H
#define BLANK_H
#include <iostream>
#include <vector>
#include "piece.h"
#include "board.h"

class Blank : public Piece {
  Board *b;
  int obstacleRow;
  char obstacleCol;
  bool lastMoveCapture = false;
  char capturedPiece;
  bool capturedFirst;
  bool capturedPieceColour;
 public:
  Blank(char piece, Board *b);
  ~Blank();
  void move(char colOld, int rowOld, 
            char colNew, int rowNew, char newPiece) override;
  void revertMove(char colOld, int rowOld, 
                  char colNew, int rowNew, char newPiece) override;
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow) override;
  bool isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) override;
  int getObsRow() override;
  char getObsCol() override;
  void clearObs() override;
};

#endif
