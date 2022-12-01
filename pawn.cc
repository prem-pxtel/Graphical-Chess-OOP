#include <iostream>
#include <vector>
#include "pawn.h"
#include "blank.h"
#include <utility>

Pawn::Pawn(char piece, Board *b) 
  : Piece{piece}, b{b} {
    firstMove = true;
}

// returns true if new cell is not blocked and in the path of the old cell
// otherwise, returns false
bool Pawn::isInPath(char oldPiece, char oldCol, int oldRow, 
                     char newCol, int newRow) {
  if (oldPiece == 'p') { // need to add interaction where if its the first time
  // the pawn is moving, it should be allowed to move two pieces up not just one
  // diagonal pawn
    if (newRow < oldRow) return false;
    for (int i = oldRow + 1; i <= newRow; ++i) {
      if(b->isOccupied(i, oldCol)) return false;
    }
    return true;
  } else if (oldPiece == 'P') {
    if (newRow > oldRow) return false;
    for (int i = oldRow - 1; i >= newRow; --i) {
      if(b->isOccupied(i, oldCol)) return false;
    }
  }
  return true;
}

bool Pawn::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  if (firstMove) {
    if(oldPiece == 'P'){
      if(newRow < oldRow - 2) return false;
    }
    else{
      if (newRow > oldRow + 2) return false;
    }
  } else {
    if(oldPiece == 'P'){
      if (newRow < oldRow - 1) return false;
    }
    else{
      if (newRow > oldRow + 1) return false;
    }
  } 
  firstMove = false;
  return true;
}

void Pawn::capture(int oldRow, char oldCol, int newRow, char newCol) {
  std::cout << "capturing" << std::endl;
  b->swapPiece(oldRow, oldCol, newRow, newCol);
  delete b->getPiecePtr(oldRow, oldCol);
  b->getBoard()[b->invertRow(oldRow) - 1][oldCol - 'a'] = new Blank{' ', b};
  b->removePiece(oldRow, oldCol); // sets to either " " or "_"
}

void Pawn::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  } else if (newRow == obstacleRow && newCol == obstacleCol 
             && b->isWhite(oldRow, oldCol) != b->isWhite(newRow, newCol)
             && b->getPiece(newRow, newCol) != 'k'
             && b->getPiece(newRow, newCol) != 'K') {
    capture(oldRow, oldCol, newRow, newCol);
  }
  obstacleRow = 10; // setting obstacle data to unattainable values,
  obstacleCol = 'z'; // so that future captures aren't affected by past data
}
