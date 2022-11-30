#include <iostream>
#include <vector>
#include "king.h"
#include "board.h"

King::King(char piece, Board *b)
  : Piece{piece}, b{b} {
    firstMove = true;
  }

// returns true if new cell is not blocked and in the path of the old cell
// otherwise, returns false
bool King::isInPath(char oldPiece, char oldCol, int oldRow, 
                     char newCol, int newRow) {
  if (oldPiece == 'k') {
    if (oldCol == newCol || oldRow == newRow) {
      if (oldCol == newCol) { // up and down
        if (oldRow <= newRow) {
          for (int i = oldRow + 1; i <= newRow; ++i) {
            if (b->isOccupied(i, oldCol)) return false;
          }
        } else {
          for (int i = oldRow - 1; i >= newRow; --i) {
            if (b->isOccupied(i, oldCol)) return false;
          }
        } 
      } else if (oldRow == newRow) { // left and right
        if (oldCol <= newCol) {
          for(int i = oldCol + 1; i <= newCol; ++i) {
            if (b->isOccupied(oldRow, i)) return false;
          }
        } else {
          for(int i = oldCol - 1; i >= newCol; --i) {
            if (b->isOccupied(oldRow, i)) return false;
          }
        }
      }
    } else {
      if (oldCol < newCol) { // to the right
        if (oldRow < newRow) { // down and right
          for (int i = oldRow + 1; i <= newRow; ++i) {
            oldCol++;
            if (b->isOccupied(i, oldCol)) return false;
          }
        } else { // up and right
          for (int i = oldRow - 1; i >= newRow; --i) {
            oldCol++;
            if (b->isOccupied(i, oldCol)) return false;
          }
        }
      } else { // to the left
        if (oldRow < newRow) { // down and left
          for(int i = oldCol - 1; i >= newCol; --i) {
            oldRow++;
            if (b->isOccupied(oldRow, i)) return false;
          }
        } else { // up and left
          for(int i = oldCol - 1; i >= newCol; --i) {
            oldRow--;
            if (b->isOccupied(oldRow, i)) return false;
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
            if (b->isOccupied(i, oldCol)) return false;
          }
        } else {
          for (int i = oldRow - 1; i >= newRow; --i) {
            if (b->isOccupied(i, oldCol)) return false;
          }
        } 
      } else if (oldRow == newRow) { // left and right
        if (oldCol <= newCol) {
          for(int i = oldCol + 1; i <= newCol; ++i) {
            if (b->isOccupied(oldRow, i)) return false;
          }
        } else {
          for(int i = oldCol - 1; i >= newCol; --i) {
            if (b->isOccupied(oldRow, i)) return false;
          }
        }
      }
    } else {
      if (oldCol < newCol) { // to the right
        if (oldRow < newRow) { // down and right
          for (int i = oldRow + 1; i <= newRow; ++i) {
            oldCol++;
            if (b->isOccupied(i, oldCol)) return false;
          }
        } else { // up and right
          for (int i = oldRow - 1; i >= newRow; --i) {
            oldCol++;
            if (b->isOccupied(i, oldCol)) return false;
          }
        }
      } else { // to the left
        if (oldRow < newRow) { // down and left
          for(int i = oldCol - 1; i >= newCol; --i) {
            oldRow++;
            if (b->isOccupied(oldRow, i)) return false;
          }
        } else { // up and left
          for(int i = oldCol - 1; i >= newCol; --i) {
            oldRow--;
            if (b->isOccupied(oldRow, i)) return false;
          }
        }
      }
    }
    return true;
  }
}

bool King::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  int rowDiff = newRow - oldRow;
  int colDiff = newCol - oldCol;
  if (abs(rowDiff) > 1 || abs(colDiff) > 1) return false;
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (b->isOccupied(newRow, newCol)) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
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

void King::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidCastle(oldCol, oldRow, newCol, newRow)) {
    castle(oldRow, oldCol, newRow, newCol);
    return;
  }
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  }
}
