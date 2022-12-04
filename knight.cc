#include <iostream>
#include <vector>
#include "knight.h"
#include "board.h"
#include "blank.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "pawn.h"

Knight::Knight(char piece, Board *b)
  : Piece{piece}, b{b} {}

Knight::~Knight() {}

void Knight::clearObs() {
  obstacleRow = 10;
  obstacleCol = 'z';
}

bool Knight::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if(!(((newRow == oldRow + 2) && (newCol == oldCol + 1)) 
      || ((newRow == oldRow + 2) && (newCol == oldCol - 1))
      || ((newRow == oldRow - 2) && (newCol == oldCol + 1)) 
      || ((newRow == oldRow - 2) && (newCol == oldCol - 1))
      || ((newRow == oldRow + 1) && (newCol == oldCol + 2)) 
      || ((newRow == oldRow + 1) && (newCol == oldCol - 2))
      || ((newRow == oldRow - 1) && (newCol == oldCol + 2)) 
      || ((newRow == oldRow - 1) && (newCol == oldCol - 2)))) return false;
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (b->isOccupied(newRow, newCol)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  return true;
}

void Knight::capture(int oldRow, char oldCol, int newRow, char newCol) {
  capturedPiece = b->getPiece(newRow, newCol);
  capturedPieceColour = b->isWhitePiece(newRow, newCol);
  if (capturedPiece == 'r' || capturedPiece == 'R'
      || capturedPiece == 'p' || capturedPiece == 'P'){
    capturedFirst = b->getPiecePtr(oldRow,oldCol)->firstMove;
  }
  b->swapPiece(oldRow, oldCol, newRow, newCol);
  delete b->getPiecePtr(oldRow, oldCol);
  b->getBoard()[oldRow - 1][oldCol - 'a'] = new Blank{' ', b};
  b->removePiece(oldRow, oldCol); // sets to either " " or "_"
}

void Knight::move(char oldCol, int oldRow, 
                  char newCol, int newRow, char newPiece) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
    lastMoveCapture = false;
  } else if (b->isOccupied(newRow, newCol) 
             && b->isWhitePiece(oldRow, oldCol) 
             != b->isWhitePiece(newRow, newCol)
             && b->getPiece(newRow, newCol) != 'k'
             && b->getPiece(newRow, newCol) != 'K') {
    capture(oldRow, oldCol, newRow, newCol);
    lastMoveCapture = true;
    clearObs();
  } else {
    throw InvalidMove{};
  }
}

void Knight::revertMove(char oldCol, int oldRow, 
                        char newCol, int newRow, char newPiece) {
  if (lastMoveCapture) {
    delete b->getPiecePtr(oldRow, oldCol); // delete the blank, create a new pointer of what was there before, and then swap them back
  if (capturedPiece == 'p') {
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Pawn{'p', b}; // add first move after this
    b->getPiecePtr(oldRow, oldCol)->firstMove = capturedFirst;
  }
  else if (capturedPiece == 'P') {
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Pawn{'P', b};
    b->getPiecePtr(oldRow, oldCol)->firstMove = capturedFirst;
  }
  else if (capturedPiece == 'r') {
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Rook{'r', b}; 
    b->getPiecePtr(oldRow, oldCol)->firstMove = capturedFirst;
  }
  else if (capturedPiece == 'R'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Rook{'R', b};
    b->getPiecePtr(oldRow, oldCol)->firstMove = capturedFirst;
  }
  else if (capturedPiece == 'n'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Knight{'n', b};
  }
  else if (capturedPiece == 'N'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Knight{'N', b};  
  }
  else if (capturedPiece == 'b'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Bishop{'b', b};
  }
  else if (capturedPiece == 'B'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Bishop{'B', b};
  }
  else if (capturedPiece == 'q'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Queen{'q', b};
  }
  else if (capturedPiece == 'Q'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Queen{'Q', b};  
  }
    b->swapPiece(oldRow, oldCol, newRow, newCol);
  }
  else {
    b->swapPiece(newRow, newCol, oldRow, oldCol);
    b->removePiece(newRow, newCol);
  }
}

bool Knight::isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
return false;
                        }

int Knight::getObsRow() {
  return obstacleRow;
}

char Knight::getObsCol() {
  return obstacleCol;
}
