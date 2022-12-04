#ifndef KING_H
#define KING_H
#include <iostream>
#include <vector>
#include "piece.h"
class Board;

class King : public Piece {
  Board *b;
  int obstacleRow;
  char obstacleCol;
  bool lastMoveCapture = false;
  char capturedPiece;
  bool capturedFirst;
  bool capturedPieceColour;
 public:
  King(char piece, Board *b);
  ~King();
  void move(char colOld, int rowOld, 
            char colNew, int rowNew, char newPiece) override; 
  void revertMove(char colOld, int rowOld, 
                  char colNew, int rowNew, char newPiece) override; 
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
  void castle(int oldRow, char oldCol, int newRow, char newCol);
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow) override;
  bool isValidCastle(char oldCol, int oldRow, char newCol, int newRow);
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
  bool isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) override;
  int getObsRow() override;
  char getObsCol() override;
  void clearObs() override;
};

#endif
