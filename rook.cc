#include <iostream>
#include <vector>
#include "rook.h"
#include "board.h"
#include "blank.h"
#include "pawn.h"
#include "knight.h"
#include "queen.h"
#include "bishop.h"

Rook::Rook(char piece, Board *b)
  : Piece{piece}, b{b} {
    firstMove = true;
  }

Rook::~Rook() {}

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
          if (b->isOccupied(i, oldCol)) {
            obstacleRow = i;
            obstacleCol = oldCol;
            return false;
          }
        }
      } else {
        for (int i = oldRow - 1; i >= newRow; --i) {
          if (b->isOccupied(i, oldCol)) {
            obstacleRow = i;
            obstacleCol = oldCol;
            return false;
          }
        }
      }
    } else { // left and right
      if (oldCol <= newCol) {
        for(int i = oldCol + 1; i <= newCol; ++i) {
          if (b->isOccupied(oldRow, i)) {
            obstacleRow = oldRow;
            obstacleCol = i;
            return false;
          }
        }
      } else {
        for(int i = oldCol - 1; i >= newCol; --i) {
          if (b->isOccupied(oldRow, i)) {
            obstacleRow = oldRow;
            obstacleCol = i;
            return false;
          }
        }
      }
    }
    return true;
  } else { // oldPiece == 'R'
    if (oldCol == newCol) { // up and down
      if (oldRow <= newRow) {
        for (int i = oldRow + 1; i <= newRow; ++i) {
          if (b->isOccupied(i, oldCol)) {
            obstacleRow = i;
            obstacleCol = oldCol;
            return false;
          }
        }
      } else {
        for (int i = oldRow - 1; i >= newRow; --i) {
          if (b->isOccupied(i, oldCol)) {
            obstacleRow = i;
            obstacleCol = oldCol;
            return false;
          }
        }
      }
    } else { // left and right
      if (oldCol <= newCol) {
        for(int i = oldCol + 1; i <= newCol; ++i) {
          if (b->isOccupied(oldRow, i)) {
            obstacleRow = oldRow;
            obstacleCol = i;
            return false;
          }
        }
      } else {
        for(int i = oldCol - 1; i >= newCol; --i) {
          if (b->isOccupied(oldRow, i)) {
            obstacleRow = oldRow;
            obstacleCol = i;
            return false;
          }
        }
      }
    }
    return true;
  }
}

void Rook::clearObs() {
  obstacleRow = 10;
  obstacleCol = 'z';
}

bool Rook::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if((oldCol != newCol) && (oldRow != newRow)) return false;
 // if() return false; // not let it move diagonally so ensure that its only moving either up or down or left or right
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  firstMove = false;
  return true;
}

void Rook::capture(int oldRow, char oldCol, int newRow, char newCol) {
  capturedpiece = b->getPiece(newRow, newCol);
  capturedpiececolour = b->isWhite(newRow, newCol);
  if(capturedpiece == 'r' || capturedpiece == 'R'
  || capturedpiece == 'p' || capturedpiece == 'P'){
    capturedfirst = b->getPiecePtr(oldRow,oldCol)->firstMove;
  }
  b->swapPiece(oldRow, oldCol, newRow, newCol);
  delete b->getPiecePtr(oldRow, oldCol);
  b->getBoard()[oldRow - 1][oldCol - 'a'] = new Blank{' ', b};
  b->removePiece(oldRow, oldCol); // sets to either " " or "_"
}

void Rook::move(char oldCol, int oldRow, 
                char newCol, int newRow, char newPiece) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
    lastmovecapture = false;
  } else if (newRow == obstacleRow && newCol == obstacleCol 
             && b->isWhitePiece(oldRow, oldCol) 
             != b->isWhitePiece(newRow, newCol)
             && b->getPiece(newRow, newCol) != 'k'
             && b->getPiece(newRow, newCol) != 'K') {
    capture(oldRow, oldCol, newRow, newCol);
    lastmovecapture = true;
    clearObs();
  } else {
    throw InvalidMove{};
  }
}

void Rook::revertmove(char oldCol, int oldRow, 
                 char newCol, int newRow, char newPiece) {
if(lastmovecapture){
delete b->getPiecePtr(oldRow, oldCol); // delete the blank, create a new pointer of what was there before, and then swap them back
if(capturedpiece == 'p'){
b->getBoard()[oldRow - 1][oldCol - 'a'] = new Pawn{'p', b}; // add first move after this
b->getPiecePtr(oldRow,oldCol)->firstMove = capturedfirst;
}
else if (capturedpiece == 'P'){
b->getBoard()[oldRow - 1][oldCol - 'a'] = new Pawn{'P', b};
b->getPiecePtr(oldRow,oldCol)->firstMove = capturedfirst;
}
else if (capturedpiece == 'r'){
b->getBoard()[oldRow - 1][oldCol - 'a'] = new Rook{'r', b}; 
b->getPiecePtr(oldRow,oldCol)->firstMove = capturedfirst;
}
else if (capturedpiece == 'R'){
b->getBoard()[oldRow - 1][oldCol - 'a'] = new Rook{'R', b};
b->getPiecePtr(oldRow,oldCol)->firstMove = capturedfirst;
}
else if (capturedpiece == 'n'){
b->getBoard()[oldRow - 1][oldCol - 'a'] = new Knight{'n', b};
}
else if (capturedpiece == 'N'){
b->getBoard()[oldRow - 1][oldCol - 'a'] = new Knight{'N', b};  
}
else if (capturedpiece == 'b'){
b->getBoard()[oldRow - 1][oldCol - 'a'] = new Bishop{'b', b};
}
else if (capturedpiece == 'B'){
b->getBoard()[oldRow - 1][oldCol - 'a'] = new Bishop{'B', b};
}
else if (capturedpiece == 'q'){
b->getBoard()[oldRow - 1][oldCol - 'a'] = new Queen{'q', b};
}
else if (capturedpiece == 'Q'){
b->getBoard()[oldRow - 1][oldCol - 'a'] = new Queen{'Q', b};  
}
b->swapPiece(oldRow, oldCol, newRow, newCol);
}
else{
b->swapPiece(newRow, newCol, oldRow, oldCol);
b->removePiece(newRow, newCol);
}
}

int Rook::getObsRow() {
  return obstacleRow;
}

char Rook::getObsCol() {
  return obstacleCol;
}
