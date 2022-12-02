#include <iostream>
#include <vector>
#include "king.h"
#include "board.h"
#include "blank.h"

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
  b->swapPiece(oldRow, oldCol, newRow, newCol);
  delete b->getPiecePtr(oldRow, oldCol);
  b->getBoard()[oldRow - 1][oldCol - 'a'] = new Blank{' ', b};
  b->removePiece(oldRow, oldCol); // sets to either " " or "_"
}

void King::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidCastle(oldCol, oldRow, newCol, newRow)) {
    castle(oldRow, oldCol, newRow, newCol);
  } else if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  } else if (newRow == obstacleRow && newCol == obstacleCol 
             && b->isWhitePiece(oldRow, oldCol) 
             != b->isWhitePiece(newRow, newCol)
             && b->getPiece(newRow, newCol) != 'k'
             && b->getPiece(newRow, newCol) != 'K') {
    capture(oldRow, oldCol, newRow, newCol);
  }
  clearObs(); // setting obstacle data to unattainable values,
              // so that future captures aren't affected by past data
}

int King::getObsRow() {
  return obstacleRow;
}

char King::getObsCol() {
  return obstacleCol;
}

