#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include <vector>
#include "piece.h"
#include "board.h"

class Pawn : public Piece {
  Board *b;
  int obstacleRow;
  char obstacleCol;
  bool lastMoveCapture = false;
  char capturedPiece;
  bool capturedFirst;
  bool capturedPieceColour;
 public:
  bool enPassantReady = false;
  Pawn(char piece, Board *b);
  ~Pawn();
  void move(char colOld, int rowOld, char colNew, 
            int rowNew, char newPiece) override;
  void revertMove(char colOld, int rowOld, char colNew, 
                  int rowNew, char newPiece) override;            
  void capture(int oldRow, char oldCol, int newRow, char newCol) override;
  bool promote(char oldPiece, char newPiece, int newRow, char newCol);
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow) override;
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
  bool isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) override;
  bool isInDiagonalPathEnP(char oldPiece, char oldCol, int oldRow, 
                                 char newCol, int newRow);
  bool promoReady(char oldPiece, int newRow);
  bool isValidEnPassant(char escapingPawn, int escapeRow, char escapeCol);
  int getObsRow() override;
  char getObsCol() override;
  void clearObs() override;
};

#endif
