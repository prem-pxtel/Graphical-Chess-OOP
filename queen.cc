#include <iostream>
#include <vector>
#include "queen.h"
#include "board.h"

Queen::Queen(char piece, Board *b)
  : Piece{piece}, b{b} {}

// returns true if new cell is not blocked and in the path of the old cell
// otherwise, returns false
bool Queen::isInPath(char oldPiece, char oldCol, int oldRow, 
                     char newCol, int newRow) {
  if (oldPiece == 'q') {
    if(oldCol == newCol || oldRow == newRow){
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
    } else if (oldRow == newRow){ // left and right
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
    } else { // to the right
    if(oldCol < newCol){
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
    }
      else { // to the left
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
  } else { // oldPiece == 'Q'
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
    } else if (oldRow == newRow){ // left and right
      if (oldCol <= newCol) {
        for(int i = oldCol + 1; i <= newCol; ++i) {
          if (b->isOccupied(oldRow, i)) return false;
        }
      } else {
        for(int i = oldCol - 1; i >= newCol; --i) {
          if (b->isOccupied(oldRow, i)) return false;
        }
      }
    } else if (oldCol < newCol) { // to the right
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
    return true;
  }
}

bool Queen::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if (!(oldCol == newCol) || !(oldRow == newRow)) {
    if (abs((oldCol - newCol)) != abs((oldRow - newRow))) return false;
  }
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (b->isOccupied(newRow, newCol)) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  return true;
}

void Queen::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  }
}
