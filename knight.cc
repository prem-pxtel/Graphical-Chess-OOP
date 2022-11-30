#include <iostream>
#include <vector>
#include "knight.h"
#include "board.h"

Knight::Knight(char piece, Board *b)
  : Piece{piece}, b{b} {}
// returns true if new cell is not blocked and in the path of the old cell
// otherwise, returns false
bool Knight::isInPath(char oldPiece, char oldCol, int oldRow, 
                     char newCol, int newRow) {
  if (oldPiece == 'n') {
    return true;
  } else { // oldPiece == 'K'
    return true;
  }
}

bool Knight::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if(!((newRow == oldRow + 2) && (newCol == oldCol + 1)) || !((newRow == oldRow + 2) && (newCol == oldCol - 1))
   || !((newRow == oldRow - 2) && (newCol == oldCol + 1)) || !((newRow == oldRow - 2) && (newCol == oldCol - 1))
   || !((newRow == oldRow + 1) && (newCol == oldCol + 2)) || !((newRow == oldRow + 1) && (newCol == oldCol - 2))
   || !((newRow == oldRow - 1) && (newCol == oldCol + 2)) || !((newRow == oldRow - 1) && (newCol == oldCol - 2))) return false;

  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (b->isOccupied(newRow, newCol)) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  if (abs((newCol - oldCol)) == abs((newRow - oldRow))) return false;

  return true;
}

void Knight::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  }
}
