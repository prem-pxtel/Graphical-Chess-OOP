#include <iostream>
#include <vector>
#include "bishop.h"
#include "board.h"

Bishop::Bishop(int row, char col, char piece, Board *b)
  : Cell{row, col, piece}, b{b} {}

// returns true if new cell is not blocked and in the path of the old cell
// otherwise, returns false
bool Bishop::isInPath(char oldPiece, char oldCol, int oldRow, 
                     char newCol, int newRow) {
  if (oldPiece == 'b') {
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
    return true;
  } else { // oldPiece == 'B'
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
    return true;
  }
}

bool Bishop::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if(abs((oldCol - newCol)) != abs((oldRow - newRow))) return false;
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (b->isOccupied(newRow, newCol)) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  return true;
}

void Bishop::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  }
}
