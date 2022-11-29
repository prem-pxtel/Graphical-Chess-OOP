#include <iostream>
#include <vector>
#include "rook.h"
#include "board.h"

Rook::Rook(char piece, Board *b)
  : Piece{piece}, b{b} {
    firstMove = true;
  }

// returns true if new cell is not blocked and in the path of the old cell
// otherwise, returns false
bool Rook::isInPath(char oldPiece, char oldCol, int oldRow, 
                     char newCol, int newRow) {
  if (oldPiece == 'r') {
    // two things for rook
    // it is bidirection so need to consider if its going left or right or 
    // up or down, then you need to check if from the spot it is now
    // to the spot it wants to go to, is there anything blocking its way.
    // if there is then dont let it move. if there isnt then let it move.
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
    } else { // left and right
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
    return true;
  } else { // oldPiece == 'R'
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
    } else { // left and right
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
    return true;
  }
}

bool Rook::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (b->isOccupied(newRow, newCol)) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  firstMove = false;
  return true;
}

void Rook::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  }
}
