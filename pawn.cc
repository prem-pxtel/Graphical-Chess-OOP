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
  if (oldCol == newCol && oldRow == newRow) {
    throw InvalidMove{};
  }
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
  if (secondMove) {
    secondMove = false;
  }
  if (firstMove) {
    firstMove = false;
    secondMove = true;
  }
  return true;
}

bool Pawn::isValidCapture(char oldCol, int oldRow, 
                          char newCol, int newRow) {
  if (isInDiagonalPath(' ', oldCol, oldRow, newCol, newRow) 
      && b->isWhitePiece(oldRow, oldCol) 
      != b->isWhitePiece(newRow, newCol)
      && b->getPiece(newRow, newCol) != 'k'
      && b->getPiece(newRow, newCol) != 'K') {
    return true;
  }
  return false;
}

bool Pawn::isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                            char newCol, int newRow) {
  if (abs((newCol - oldCol)) != abs((newRow - oldRow))) return false;
  if (b->isWhitePiece(oldRow, oldCol)) {
    if (b->isCell(oldRow - 1, oldCol + 1) && 
        b->isOccupied(oldRow - 1, oldCol + 1)) {
      if (newRow == oldRow - 1 && newCol == oldCol + 1) {
        obstacleRow = oldRow - 1;
        obstacleCol = oldCol + 1;
        return true;
      }
    }
    if (b->isCell(oldRow - 1, oldCol - 1) &&
        b->isOccupied(oldRow - 1, oldCol - 1)) {
      if (newRow == oldRow - 1 && newCol == oldCol - 1) {
        obstacleRow = oldRow - 1;
        obstacleCol = oldCol - 1;
        return true;
      }
    }
  } else {
    if (b->isCell(oldRow + 1, oldCol + 1) &&
        b->isOccupied(oldRow + 1, oldCol + 1)) {
      if (newRow == oldRow + 1 && newCol == oldCol + 1) {
        obstacleRow = oldRow + 1;
        obstacleCol = oldCol + 1;
        return true;
      }
    }
    if (b->isCell(oldRow + 1, oldCol - 1) &&
        b->isOccupied(oldRow + 1, oldCol - 1)) {
      if (newRow == oldRow + 1 && newCol == oldCol - 1) {
        obstacleRow = oldRow + 1;
        obstacleCol = oldCol - 1;
        return true;
      }
    }
  }
  return false;
}

bool Pawn::isInDiagonalPathEnP(char oldPiece, char oldCol, int oldRow, 
                               char newCol, int newRow) {
  if (abs((newCol - oldCol)) != abs((newRow - oldRow))) return false;
  if (b->isWhitePiece(oldRow, oldCol)) {
    if (b->isCell(oldRow - 1, oldCol + 1)) {
      if (newRow == oldRow - 1 && newCol == oldCol + 1) {
        obstacleRow = oldRow - 1;
        obstacleCol = oldCol + 1;
        return true;
      }
    }
    if (b->isCell(oldRow - 1, oldCol - 1)) {
      if (newRow == oldRow - 1 && newCol == oldCol - 1) {
        obstacleRow = oldRow - 1;
        obstacleCol = oldCol - 1;
        return true;
      }
    }
  } else {
    if (b->isCell(oldRow + 1, oldCol + 1)) {
      if (newRow == oldRow + 1 && newCol == oldCol + 1) {
        obstacleRow = oldRow + 1;
        obstacleCol = oldCol + 1;
        return true;
      }
    }
    if (b->isCell(oldRow + 1, oldCol - 1)) {
      if (newRow == oldRow + 1 && newCol == oldCol - 1) {
        obstacleRow = oldRow + 1;
        obstacleCol = oldCol - 1;
        return true;
      }
    }
  }
  return false;
}

void Pawn::clearObs() {
  obstacleRow = 10;
  obstacleCol = 'z';
}

void Pawn::capture(int oldRow, char oldCol, int newRow, char newCol) {
  if (b->curTurn == b->enPassantTurn + 1 &&
      newRow == b->enPassantRow && newCol == b->enPassantCol) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol); // sets to either " " or "_"
    if (b->isWhitePiece(newRow, newCol)) {
      delete b->getPiecePtr(newRow + 1, newCol);
      b->getBoard()[newRow][newCol] = new Blank{' ', b};
    } else {
      delete b->getPiecePtr(newRow - 1, newCol);
      b->getBoard()[newRow - 2][newCol] = new Blank{' ', b};
    }
    b->getPiecePtr(oldRow, oldCol)->enPassantReady = false;
  } else {
    capturedPiece = b->getPiece(newRow, newCol);
    capturedPieceColour = b->isWhitePiece(newRow, newCol);
    if (capturedPiece == 'r' || capturedPiece == 'R'
        || capturedPiece == 'p' || capturedPiece == 'P'){
      capturedFirst = b->getPiecePtr(oldRow, oldCol)->firstMove;
    }
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    delete b->getPiecePtr(oldRow, oldCol);
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Blank{' ', b};
    b->removePiece(oldRow, oldCol); // sets to either " " or "_"
  }
}

bool Pawn::promoReady(char oldPiece, int newRow) {
  if (oldPiece == 'p') {
    if (newRow == 8) return true;
  } else if (oldPiece == 'P') {
    if (newRow == 1) return true;
  }
  return false;
}

bool Pawn::promote(char oldPiece, char newPiece, int newRow, char newCol) {
  if (oldPiece == 'p') {
    if (newPiece == 'r') {
      delete b->getPiecePtr(newRow, newCol);
      b->getBoard()[newRow - 1][newCol - 'a'] = new Rook{'r', b};
      return true;
    } else if (newPiece == 'n') {
      delete b->getPiecePtr(newRow, newCol);
      b->getBoard()[newRow - 1][newCol - 'a'] = new Knight{'n', b};
      return true;
    } else if (newPiece == 'b') {
      delete b->getPiecePtr(newRow, newCol);
      b->getBoard()[newRow - 1][newCol - 'a'] = new Bishop{'b', b};
      return true;
    } else if (newPiece == 'q') {
      delete b->getPiecePtr(newRow, newCol);
      b->getBoard()[newRow - 1][newCol - 'a'] = new Queen{'q', b};
      return true;
    }
  } else if (oldPiece == 'P') {
    if (newPiece == 'R') {
      delete b->getPiecePtr(newRow, newCol);
      b->getBoard()[newRow - 1][newCol - 'a'] = new Rook{'R', b};
      return true;
    } else if (newPiece == 'N') {
      delete b->getPiecePtr(newRow, newCol);
      b->getBoard()[newRow - 1][newCol - 'a'] = new Knight{'N', b};
      return true;
    } else if (newPiece == 'B') {
      delete b->getPiecePtr(newRow, newCol);
      b->getBoard()[newRow - 1][newCol - 'a'] = new Bishop{'B', b};
      return true;
    } else if (newPiece == 'Q') {
      delete b->getPiecePtr(newRow, newCol);
      b->getBoard()[newRow - 1][newCol - 'a'] = new Queen{'Q', b};
      return true;
    }
  }
  return false; // means newPiece was invalid
}

void Pawn::revertMove(char oldCol, int oldRow, 
                      char newCol, int newRow, char newPiece) {
  if (lastMoveCapture) {
    delete b->getPiecePtr(oldRow, oldCol); // delete the blank, create a new pointer of what was there before, and then swap them back
  if (capturedPiece == 'p') {
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Pawn{'p', b}; // add first move after this
    b->getPiecePtr(oldRow, oldCol)->firstMove = capturedFirst;
  }
  else if (capturedPiece == 'P') {
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Pawn{'P', b};
    b->getPiecePtr(oldRow, oldCol)->firstMove = capturedFirst;
  }
  else if (capturedPiece == 'r') {
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Rook{'r', b}; 
    b->getPiecePtr(oldRow, oldCol)->firstMove = capturedFirst;
  }
  else if (capturedPiece == 'R'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Rook{'R', b};
    b->getPiecePtr(oldRow, oldCol)->firstMove = capturedFirst;
  }
  else if (capturedPiece == 'n'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Knight{'n', b};
  }
  else if (capturedPiece == 'N'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Knight{'N', b};  
  }
  else if (capturedPiece == 'b'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Bishop{'b', b};
  }
  else if (capturedPiece == 'B'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Bishop{'B', b};
  }
  else if (capturedPiece == 'q'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Queen{'q', b};
  }
  else if (capturedPiece == 'Q'){
    b->getBoard()[oldRow - 1][oldCol - 'a'] = new Queen{'Q', b};  
  }
    b->swapPiece(oldRow, oldCol, newRow, newCol);
  }
  else {
    b->swapPiece(newRow, newCol, oldRow, oldCol);
    b->removePiece(newRow, newCol);
  }
}

bool Pawn::isValidEnPassant(char escapingPawn, int escapeRow, char escapeCol) {
  if (!secondMove) return false;
  char pieceToLeft = ' ';
  if (b->isCell(escapeRow, escapeCol - 1)) {
    pieceToLeft = b->getPiece(escapeRow, escapeCol - 1);
  }
  char pieceToRight = ' ';
  if (b->isCell(escapeRow, escapeCol + 1)) {
    pieceToRight = b->getPiece(escapeRow, escapeCol + 1);
  }
  if (escapingPawn == 'p') {
    if (pieceToLeft == 'P') {
      b->getPiecePtr(escapeRow, escapeCol - 1)->enPassantReady = true;
      return true;
    }
    if (pieceToRight == 'P') {
      b->getPiecePtr(escapeRow, escapeCol + 1)->enPassantReady = true;
      return true;
    }
  } else { // escaping pawn is a white pawn, 'P'
    if (pieceToLeft == 'p') {
      b->getPiecePtr(escapeRow, escapeCol - 1)->enPassantReady = true;
      return true;
    }
    if (pieceToRight == 'p') {
      b->getPiecePtr(escapeRow, escapeCol + 1)->enPassantReady = true;
      return true;
    }
  }
  return false;
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
    if (isValidEnPassant(oldPiece, newRow, newCol)) {
      b->enPassantTurn = b->curTurn;
      if (oldPiece == 'p') b->enPassantRow = newRow - 1; // the square skipped over
      else b->enPassantRow = newRow + 1;
      b->enPassantCol = newCol;
    }
    lastMoveCapture = false;
  } else if (b->isOccupied(newRow, newCol)) {
    if (isValidCapture(oldCol, oldRow, newCol, newRow)) {
        capture(oldRow, oldCol, obstacleRow, obstacleCol);
        lastMoveCapture = true;
        clearObs();
    }
    if (promoReady(oldPiece, newRow)) {
      if (promote(oldPiece, newPiece, newRow, newCol)) return;
      else {
        revertMove(oldCol, oldRow, newCol, newRow, newPiece);
        std::string errMsg = "Invalid Pawn Promotion.";
        throw InvalidMove{errMsg};
      }
    }
  } else if (isInDiagonalPathEnP(oldPiece, oldCol, oldRow, newCol, newRow)) {
    if (enPassantReady) {
      capture(oldRow, oldCol, newRow, newCol); // capture enPassant
    } else {
      throw InvalidMove{};
    }

  } else {
    throw InvalidMove{};
  }
}

int Pawn::getObsRow() {
  return obstacleRow;
}

char Pawn::getObsCol() {
  return obstacleCol;
}
