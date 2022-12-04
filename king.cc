#include <iostream>
#include <vector>
#include "king.h"
#include "board.h"
#include "blank.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "pawn.h"
#include "knight.h"

King::King(char piece, Board *b)
  : Piece{piece}, b{b} {
    firstMove = true;
  }

King::~King() {}

// returns true if new cell is not blocked and in the path of the old cell
// otherwise, returns false
bool King::isInPath(char oldPiece, char oldCol, int oldRow, 
                     char newCol, int newRow) {
  if (oldPiece == 'k') {
    if (oldCol == newCol || oldRow == newRow) {
      if (oldCol == newCol) { // up and down
        if (oldRow <= newRow) {
          for (int i = oldRow + 1; i <= newRow; ++i) {
            if (b->isOccupied(i, oldCol)) {
              obstacleRow = i;
              obstacleCol = oldCol;
              return false;
            }
          }
        } else {
          for (int i = oldRow - 1; i >= newRow; --i) {
            if (b->isOccupied(i, oldCol)) {
              obstacleRow = i;
              obstacleCol = oldCol;
              return false;
            }
          }
        } 
      } else if (oldRow == newRow) { // left and right
        if (oldCol <= newCol) {
          for(int i = oldCol + 1; i <= newCol; ++i) {
            if (b->isOccupied(oldRow, i)) {
              obstacleRow = oldRow;
              obstacleCol = i;
              return false;
            }
          }
        } else {
          for(int i = oldCol - 1; i >= newCol; --i) {
            if (b->isOccupied(oldRow, i)) {
              obstacleRow = oldRow;
              obstacleCol = i;
              return false;
            }
          }
        }
      }
    } else {
      if (oldCol < newCol) { // to the right
        if (oldRow < newRow) { // down and right
          for (int i = oldRow + 1; i <= newRow; ++i) {
            oldCol++;
            if (b->isOccupied(i, oldCol)) {
              obstacleRow = i;
              obstacleCol = oldCol;
              return false;
            }
          }
        } else { // up and right
          for (int i = oldRow - 1; i >= newRow; --i) {
            oldCol++;
            if (b->isOccupied(i, oldCol)) {
              obstacleRow = i;
              obstacleCol = oldCol;
              return false;
            }
          }
        }
      } else { // to the left
        if (oldRow < newRow) { // down and left
          for(int i = oldCol - 1; i >= newCol; --i) {
            oldRow++;
            if (b->isOccupied(oldRow, i)) {
              obstacleRow = oldRow;
              obstacleCol = i;
              return false;
            }
          }
        } else { // up and left
          for(int i = oldCol - 1; i >= newCol; --i) {
            oldRow--;
            if (b->isOccupied(oldRow, i)) {
              obstacleRow = oldRow;
              obstacleCol = i;
              return false;
            }
          }
        }
      }
    }
    return true;
  } else { // oldPiece == 'K'
    if (oldCol == newCol || oldRow == newRow) {
      if (oldCol == newCol) { // up and down
        if (oldRow <= newRow) {
          for (int i = oldRow + 1; i <= newRow; ++i) {
            if (b->isOccupied(i, oldCol)) {
              obstacleRow = i;
              obstacleCol = oldCol;
              return false;
            }
          }
        } else {
          for (int i = oldRow - 1; i >= newRow; --i) {
            if (b->isOccupied(i, oldCol)) {
              obstacleRow = i;
              obstacleCol = oldCol;
              return false;
            }
          }
        } 
      } else if (oldRow == newRow) { // left and right
        if (oldCol <= newCol) {
          for(int i = oldCol + 1; i <= newCol; ++i) {
            if (b->isOccupied(oldRow, i)) {
              obstacleRow = oldRow;
              obstacleCol = i;
              return false;
            }
          }
        } else {
          for(int i = oldCol - 1; i >= newCol; --i) {
            if (b->isOccupied(oldRow, i)) {
              obstacleRow = oldRow;
              obstacleCol = i;
              return false;
            }
          }
        }
      }
    } else {
      if (oldCol < newCol) { // to the right
        if (oldRow < newRow) { // down and right
          for (int i = oldRow + 1; i <= newRow; ++i) {
            oldCol++;
            if (b->isOccupied(i, oldCol)) {
              obstacleRow = i;
              obstacleCol = oldCol;
              return false;
            }
          }
        } else { // up and right
          for (int i = oldRow - 1; i >= newRow; --i) {
            oldCol++;
            if (b->isOccupied(i, oldCol)) {
              obstacleRow = i;
              obstacleCol = oldCol;
              return false;
            }
          }
        }
      } else { // to the left
        if (oldRow < newRow) { // down and left
          for(int i = oldCol - 1; i >= newCol; --i) {
            oldRow++;
            if (b->isOccupied(oldRow, i)) {
              obstacleRow = oldRow;
              obstacleCol = i;
              return false;
            }
          }
        } else { // up and left
          for(int i = oldCol - 1; i >= newCol; --i) {
            oldRow--;
            if (b->isOccupied(oldRow, i)) {
              obstacleRow = oldRow;
              obstacleCol = i;
              return false;
            }
          }
        }
      }
    }
    return true;
  }
}

void King::clearObs() {
  obstacleRow = 10;
  obstacleCol = 'z';
}

bool King::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  int rowDiff = newRow - oldRow;
  int colDiff = newCol - oldCol;
  if (abs(rowDiff) > 1 || abs(colDiff) > 1) return false;
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  firstMove = false;
  return true;
}

bool King::isValidCastle(char oldCol, int oldRow, char newCol, int newRow) {
  if (oldRow != newRow) return false;
  if (newCol == oldCol - 2) {
    char pieceAtRook = b->getPiece(newRow, newCol - 2);
    if ((pieceAtRook == 'r' || pieceAtRook == 'R') 
       && (b->getPiecePtr(newRow, newCol - 2)->firstMove == true)) {
      if (b->isOccupied(newRow, newCol - 1)) return false;
      if (b->isOccupied(newRow, newCol)) return false;
      if (b->isOccupied(newRow, newCol + 1)) return false;
      return true;
    }
  } else if (newCol == oldCol + 2) {
    char pieceAtRook = b->getPiece(newRow, newCol + 1);
    if ((pieceAtRook == 'r' || pieceAtRook == 'R') 
       && (b->getPiecePtr(newRow, newCol + 1)->firstMove == true)) {
      if (b->isOccupied(newRow, newCol - 1)) return false;
      if (b->isOccupied(newRow, newCol)) return false;
      return true;
    }
  }
  return false;
}

void King::castle(int oldRow, char oldCol, int newRow, char newCol) {
  if (newCol == oldCol - 2) {
      b->swapPiece(oldRow, 'e', newRow, 'c');
      b->swapPiece(oldRow, 'a', newRow, 'd');
  } else {
    b->swapPiece(oldRow, 'e', newRow, 'g');
    b->swapPiece(oldRow,  'h', newRow, 'f');
  }
}

void King::capture(int oldRow, char oldCol, int newRow, char newCol) {
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

void King::move(char oldCol, int oldRow, 
                char newCol, int newRow, char newPiece) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidCastle(oldCol, oldRow, newCol, newRow)) {
    castle(oldRow, oldCol, newRow, newCol);
  } else if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
    lastMoveCapture = false;
  } else if (newRow == obstacleRow && newCol == obstacleCol 
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

void King::revertMove(char oldCol, int oldRow, 
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

bool King::isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  return false;
}

int King::getObsRow() {
  return obstacleRow;
}

char King::getObsCol() {
  return obstacleCol;
}

