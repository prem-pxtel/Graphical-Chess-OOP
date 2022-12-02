#include <iostream>
#include <vector>
#include "pawn.h"
#include "blank.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include <utility>

Pawn::Pawn(char piece, Board *b) 
  : Piece{piece}, b{b} {
    firstMove = true;
}

Pawn::~Pawn() {}

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
  if (newCol != oldCol) return false;
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  if (firstMove) {
    if (oldPiece == 'P') {
      if(newRow < oldRow - 2) return false;
    }
    else {
      if (newRow > oldRow + 2) return false;
    }
  } else {
    if (oldPiece == 'P') {
      if (newRow < oldRow - 1) return false;
    }
    else {
      if (newRow > oldRow + 1) return false;
    }
  } 
  firstMove = false;
  return true;
}

bool Pawn::isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                            char newCol, int newRow) {
  if (b->isWhitePiece(oldRow, oldCol)) {
    if (b->isOccupied(oldRow - 1, oldCol + 1)) {
      obstacleRow = oldRow - 1;
      obstacleCol = oldCol + 1;
      return true;
    }
    if (b->isOccupied(oldRow - 1, oldCol - 1)) {
      obstacleRow = oldRow - 1;
      obstacleCol = oldCol - 1;
      return true;
    }
  } else {
    if (b->isOccupied(oldRow + 1, oldCol + 1)) {
      obstacleRow = oldRow + 1;
      obstacleCol = oldCol + 1;
      return true;
    }
    if (b->isOccupied(oldRow + 1, oldCol - 1)) {
      obstacleRow = oldRow + 1;
      obstacleCol = oldCol - 1;
      return true;
    }
  }
  return false;
}

void Pawn::clearObs() {
  obstacleRow = 10;
  obstacleCol = 'z';
}

void Pawn::capture(int oldRow, char oldCol, int newRow, char newCol) {
  b->swapPiece(oldRow, oldCol, newRow, newCol);
  delete b->getPiecePtr(oldRow, oldCol);
  b->getBoard()[oldRow - 1][oldCol - 'a'] = new Blank{' ', b};
  b->removePiece(oldRow, oldCol); // sets to either " " or "_"
}

bool Pawn::promoReady(char oldPiece, int newRow) {
  if (oldPiece == 'p') {
    if (newRow == 8) return true;
  } else if (oldPiece == 'P') {
    if (newRow == 1) return true;
  }
  return false;
}

void Pawn::promote(char oldPiece, char newPiece, int oldRow, char oldCol) {
  if (oldPiece == 'p') {
    if (newPiece == 'r') {
      delete b->getPiecePtr(oldRow, oldCol);
      b->getBoard()[oldRow - 1][oldCol - 'a'] = new Rook{'r', b};
      return;
    } else if (newPiece == 'n') {
      delete b->getPiecePtr(oldRow, oldCol);
      b->getBoard()[oldRow - 1][oldCol - 'a'] = new Knight{'n', b};
      return;
    } else if (newPiece == 'b') {
      delete b->getPiecePtr(oldRow, oldCol);
      b->getBoard()[oldRow - 1][oldCol - 'a'] = new Bishop{'b', b};
      return;
    } else if (newPiece == 'q') {
      delete b->getPiecePtr(oldRow, oldCol);
      b->getBoard()[oldRow - 1][oldCol - 'a'] = new Queen{'q', b};
      return;
    }
  } else if (oldPiece == 'P') {
    if (newPiece == 'R') {
      delete b->getPiecePtr(oldRow, oldCol);
      b->getBoard()[oldRow - 1][oldCol - 'a'] = new Rook{'R', b};
      return;
    } else if (newPiece == 'N') {
      delete b->getPiecePtr(oldRow, oldCol);
      b->getBoard()[oldRow - 1][oldCol - 'a'] = new Knight{'N', b};
      return;
    } else if (newPiece == 'B') {
      delete b->getPiecePtr(oldRow, oldCol);
      b->getBoard()[oldRow - 1][oldCol - 'a'] = new Bishop{'B', b};
      return;
    } else if (newPiece == 'Q') {
      delete b->getPiecePtr(oldRow, oldCol);
      b->getBoard()[oldRow - 1][oldCol - 'a'] = new Queen{'Q', b};
      return;
    }
  }
  throw InvalidMove{};
}

void Pawn::move(char oldCol, int oldRow, 
                char newCol, int newRow, char newPiece) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    if (promoReady(oldPiece, newRow)) {
      promote(oldPiece, newPiece, oldRow, oldCol);
    }
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  } else if (b->isOccupied(newRow, newCol)) {
    if (promoReady(oldPiece, newRow)) {
      promote(oldPiece, newPiece, oldRow, oldCol);
    }
    if (isInDiagonalPath(oldPiece, oldCol, oldRow, newCol, newRow) 
        && b->isWhitePiece(oldRow, oldCol) 
        != b->isWhitePiece(newRow, newCol)
        && b->getPiece(newRow, newCol) != 'k'
        && b->getPiece(newRow, newCol) != 'K') {
        capture(oldRow, oldCol, obstacleRow, obstacleCol);
    }
  } else {
    throw InvalidMove{};
  }
}

void Pawn::revertmove(char oldCol, int oldRow, 
                char newCol, int newRow, char newPiece){
b->swapPiece(newRow, newCol, oldRow, oldCol);
b->removePiece(newRow, newCol);
}

int Pawn::getObsRow() {
  return obstacleRow;
}

char Pawn::getObsCol() {
  return obstacleCol;
}
