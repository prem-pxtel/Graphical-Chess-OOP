#include <iostream>
#include <vector>
#include "bishop.h"
#include "board.h"
#include "blank.h"

Bishop::Bishop(char piece, Board *b)
  : Piece{piece}, b{b} {}

Bishop::~Bishop() {}

// returns true if new cell is not blocked and in the path of the old cell
// otherwise, returns false
bool Bishop::isInPath(char oldPiece, char oldCol, int oldRow, 
                     char newCol, int newRow) {
  if (oldPiece == 'b') {
    if (oldCol < newCol) { // to the right
      if (oldRow < newRow) { // down and right
        for (int i = oldRow + 1; i <= newRow; ++i) {
          oldCol++;
          if (b->isOccupied(i, oldCol)) {
            obstacleRow = i;
            obstacleCol = oldCol;
            return false;
          }
        }
      } else { // up and right
        for (int i = oldRow - 1; i >= newRow; --i) {
          oldCol++;
          if (b->isOccupied(i, oldCol)) {
            obstacleRow = i;
            obstacleCol = oldCol;
            return false;
          }
        }
      }
    } else { // to the left
      if (oldRow < newRow) { // down and left
        for(int i = oldCol - 1; i >= newCol; --i) {
          oldRow++;
          if (b->isOccupied(oldRow, i)) {
            obstacleRow = oldRow;
            obstacleCol = i;
            return false;
          }
        }
      } else { // up and left
        for(int i = oldCol - 1; i >= newCol; --i) {
          oldRow--;
          if (b->isOccupied(oldRow, i)) {
            obstacleRow = oldRow;
            obstacleCol = i;
            return false;
          }
        }
      }
    }
    return true;
  } else { // oldPiece == 'B'
    if (oldCol < newCol) { // to the right
      if (oldRow < newRow) { // down and right
        for (int i = oldRow + 1; i <= newRow; ++i) {
          oldCol++;
          if (b->isOccupied(i, oldCol)) {
            obstacleRow = i;
            obstacleCol = oldCol;
            return false;
          }
        }
      } else { // up and right
        for (int i = oldRow - 1; i >= newRow; --i) {
          oldCol++;
          if (b->isOccupied(i, oldCol)) {
            obstacleRow = i;
            obstacleCol = oldCol;
            return false;
          }
        }
      }
    } else { // to the left
      if (oldRow < newRow) { // down and left
        for(int i = oldCol - 1; i >= newCol; --i) {
          oldRow++;
          if (b->isOccupied(oldRow, i)) {
            obstacleRow = oldRow;
            obstacleCol = i;
            return false;
          }
        }
      } else { // up and left
        for(int i = oldCol - 1; i >= newCol; --i) {
          oldRow--;
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

bool Bishop::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if(abs((newCol - oldCol)) != abs((newRow - oldRow))) return false;
  if (!b->isCell(oldRow, oldCol)) return false;
  if (!b->isCell(newRow, newCol)) return false; 
  if (!b->isOccupied(oldRow, oldCol)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  return true;
}

void Bishop::capture(int oldRow, char oldCol, int newRow, char newCol) {
  b->swapPiece(oldRow, oldCol, newRow, newCol);
  delete b->getPiecePtr(oldRow, oldCol);
  b->getBoard()[oldRow - 1][oldCol - 'a'] = new Blank{' ', b};
  b->removePiece(oldRow, oldCol); // sets to either " " or "_"
}

void Bishop::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = b->getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    b->swapPiece(oldRow, oldCol, newRow, newCol);
    b->removePiece(oldRow, oldCol);
  } else if (newRow == obstacleRow && newCol == obstacleCol 
             && b->isWhitePiece(oldRow, oldCol) 
             != b->isWhitePiece(newRow, newCol)
             && b->getPiece(newRow, newCol) != 'k'
             && b->getPiece(newRow, newCol) != 'K') {
    capture(oldRow, oldCol, newRow, newCol);
  }
  obstacleRow = 10; // setting obstacle data to unattainable values,
  obstacleCol = 'z'; // so that future captures aren't affected by past data
}

int Bishop::ObstacleR(){
  return obstacleRow;
}

char Bishop::ObstacleC(){
  return obstacleCol;
}
