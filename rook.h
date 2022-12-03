#ifndef ROOK_H
#define ROOK_H
#include <iostream>
#include <vector>
#include "piece.h"
class Board;

class Rook : public Piece {
  Board *b;
  bool firstMove;
  int obstacleRow;
  char obstacleCol;
  bool lastMoveCapture = false;
  char capturedPiece;
  bool capturedFirst;
  bool capturedPieceColour;
 public:
  Rook(char piece, Board *b);
  ~Rook();
  void move(char colOld, int rowOld, 
            char colNew, int rowNew, char newPiece) override; 
  void revertMove(char colOld, int rowOld, 
            char colNew, int rowNew, char newPiece) override;             
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
