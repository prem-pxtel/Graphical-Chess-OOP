#include <iostream>
#include <vector>
#include "knight.h"
#include "board.h"
#include "blank.h"

Knight::Knight(char piece, Board *b)
  : Piece{piece}, b{b} {}

Knight::~Knight() {}

bool Knight::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if(!(((newRow == oldRow + 2) && (newCol == oldCol + 1)) 
      || ((newRow == oldRow + 2) && (newCol == oldCol - 1))
      || ((newRow == oldRow - 2) && (newCol == oldCol + 1)) 
      || ((newRow == oldRow - 2) && (newCol == oldCol - 1))
      || ((newRow == oldRow + 1) && (newCol == oldCol + 2)) 
      || ((newRow == oldRow + 1) && (newCol == oldCol - 2))
      || ((newRow == oldRow - 1) && (newCol == oldCol + 2)) 
      || ((newRow == oldRow - 1) && (newCol == oldCol - 2)))) return false;
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (b->isOccupied(newRow, newCol)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  return true;
}

void Knight::capture(int oldRow, char oldCol, int newRow, char newCol) {
  b->swapPiece(oldRow, oldCol, newRow, newCol);
  delete b->getPiecePtr(oldRow, oldCol);
  b->getBoard()[oldRow - 1][oldCol - 'a'] = new Blank{' ', b};
  b->removePiece(oldRow, oldCol); // sets to either " " or "_"
}

void Knight::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  } else if (b->isOccupied(newRow, newCol) 
             && b->isWhitePiece(oldRow, oldCol) 
             != b->isWhitePiece(newRow, newCol)
             && b->getPiece(newRow, newCol) != 'k'
             && b->getPiece(newRow, newCol) != 'K') {
    capture(oldRow, oldCol, newRow, newCol);
  }
  obstacleRow = 10; // setting obstacle data to unattainable values,
  obstacleCol = 'z'; // so that future captures aren't affected by past data
}

char Knight::ObstacleC(){
  return obstacleCol;
}

int Knight::ObstacleR(){
  return obstacleRow;
}
