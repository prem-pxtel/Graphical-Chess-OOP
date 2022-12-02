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

bool Pawn::isValidPromotion(char oldPiece, char newPiece, int newRow) {
  if (oldPiece == 'p') {
    if (newRow == 8 && 'a' <= newPiece && newPiece <= 'z') return true;
  } else {
    if (newRow == 1 && 'A' <= newPiece && newPiece <= 'Z') return true;
  }
  return false;
}

void Pawn::promote(char oldPiece, char newPiece, int newRow, char newCol) {
  delete b->getPiecePtr(newRow, newCol);
  if (oldPiece == 'p') {
    if (newPiece == 'r') {
      b->getBoard()[newRow - 1][newCol - 'a'] = new Rook{'q', b};
    } else if (newPiece == 'n') {
      b->getBoard()[newRow - 1][newCol - 'a'] = new Knight{'q', b};
    } else if (newPiece == 'b') {
      b->getBoard()[newRow - 1][newCol - 'a'] = new Bishop{'q', b};
    } else {
      b->getBoard()[newRow - 1][newCol - 'a'] = new Queen{'q', b};
    }
  } else {
    if (newPiece == 'R') {
      b->getBoard()[newRow - 1][newCol - 'a'] = new Rook{'q', b};
    } else if (newPiece == 'N') {
      b->getBoard()[newRow - 1][newCol - 'a'] = new Knight{'q', b};
    } else if (newPiece == 'B') {
      b->getBoard()[newRow - 1][newCol - 'a'] = new Bishop{'q', b};
    } else {
      b->getBoard()[newRow - 1][newCol - 'a'] = new Queen{'q', b};
    }
  }
}

void Pawn::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  } else if (b->isOccupied(newRow, newCol)) {
    if (isInDiagonalPath(oldPiece, oldCol, oldRow, newCol, newRow) 
        && b->isWhitePiece(oldRow, oldCol) 
        != b->isWhitePiece(newRow, newCol)
        && b->getPiece(newRow, newCol) != 'k'
        && b->getPiece(newRow, newCol) != 'K') {
        capture(oldRow, oldCol, obstacleRow, obstacleCol);
    }
  }
  clearObs(); // setting obstacle data to unattainable values,
              // so that future captures aren't affected by past data
}

int Pawn::getObsRow() {
  return obstacleRow;
}

char Pawn::getObsCol() {
  return obstacleCol;
}
