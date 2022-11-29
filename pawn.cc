#include <iostream>
#include <vector>
#include "pawn.h"

Pawn::Pawn(Board *b) : b{b} {
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
      if(isOccupied(i, oldCol)) return false;
    }
    return true;
  } else if (oldPiece == 'P') {
    if (newRow > oldRow) return false;
    for (int i = oldRow - 1; i >= newRow; --i) {
      if(isOccupied(i, oldCol)) return false;
    }
    return true;
  } else if (oldPiece == 'r') {
    // two things for rook
    // it is bidirection so need to consider if its going left or right or 
    // up or down, then you need to check if from the spot it is now
    // to the spot it wants to go to, is there anything blocking its way.
    // if there is then dont let it move. if there isnt then let it move.
    if (oldCol == newCol) { // up and down
      if (oldRow <= newRow) {
        for (int i = oldRow + 1; i <= newRow; ++i) {
          if (isOccupied(i, oldCol)) return false;
        }
      } else {
        for (int i = oldRow - 1; i >= newRow; --i) {
          if (isOccupied(i, oldCol)) return false;
        }
      }
    } else { // left and right
      if (oldCol <= newCol) {
        for(int i = oldCol + 1; i <= newCol; ++i) {
          if (isOccupied(oldRow, i)) return false;
        }
      } else {
        for(int i = oldCol - 1; i >= newCol; --i) {
          if (isOccupied(oldRow, i)) return false;
        }
      }
    }
    return true;
  } else if (oldPiece == 'R') {
    if (oldCol == newCol) { // up and down
      if (oldRow <= newRow) {
        for (int i = oldRow + 1; i <= newRow; ++i) {
          if (isOccupied(i, oldCol)) return false;
        }
      } else {
        for (int i = oldRow - 1; i >= newRow; --i) {
          if (isOccupied(i, oldCol)) return false;
        }
      }
    } else { // left and right
      if (oldCol <= newCol) {
        for(int i = oldCol + 1; i <= newCol; ++i) {
          if (isOccupied(oldRow, i)) return false;
        }
      } else {
        for(int i = oldCol - 1; i >= newCol; --i) {
          if (isOccupied(oldRow, i)) return false;
        }
      }
    }
    return true;
  } else if (oldPiece == 'n') {

    return true;
  } else if (oldPiece == 'N') {

    return true;
  } else if (oldPiece == 'b') {

    return true;
  } else if (oldPiece == 'B') {

    return true;
  } else if (oldPiece == 'q') {

    return true;
  } else if (oldPiece == 'Q') {

    return true;
  } else if (oldPiece == 'k') {

    return true;
  } else {
    
    return true;
  }
}

bool Pawn::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (b->isOccupied(newRow, newCol)) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  if (firstMove) {
    if (newRow > oldRow + 2) return false;
  } else {
    if (newRow > oldRow + 1) return false;
  }
  return true;
}

void Pawn::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->removePiece(oldRow, oldCol);
    b->setPiece(newRow, newCol, oldPiece);
  }
}
