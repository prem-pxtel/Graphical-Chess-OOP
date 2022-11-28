#include <iostream>
#include <vector>
#include "board.h"

bool isWhite(int row, int col) {
  if ((col + row) % 2 == 0) return false;
  return true; 
}

Board::Board() {
  for (int i = 1; i <= 8; i++) {
    std::vector<Cell*> row;
    for (char j = 'a'; j <= 'h'; ++j) {
      if (((j - 97) + i) % 2 == 0) {
        row.push_back(new Cell{i, j, ' '});
      } else {
        row.push_back(new Cell{i, j, '_'});
      }
    }
    board.push_back(row);
  }
}

char Board::getPiece(int row, char col) const {
  int rowNum = row - 1;
  int colNum = col - 97;
  return board[rowNum][colNum]->piece;
}

void Board::setPiece(int row, char col, char p) {
  int rowNum = row - 1;
  int colNum = col - 97;
  board[rowNum][colNum]->piece = p;
}

void Board::updateBoards() { notifyObservers(); }

void Board::boardInit() {
  for (char j = 'a'; j <= 'h'; ++j) {  
    setPiece(2, j, 'p');
    setPiece(7, j, 'P');
  }
}

void Board::removePiece(int row, char col) {
  if (isWhite(row, col)) {
    setPiece(row, col, ' ');
  } else {
    setPiece(row, col, '_');
  }
}

bool Board::isCell(int row, char col) {
  if (1 <= row && row <= 8 && 'a' <= col && col <= 'h') return true;
  return false;
}

bool Board::isOccupied(int row, char col) {
  if (getPiece(row, col) != ' ' && getPiece(row, col) != '_') return true;
  return false;
}

void Board::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = getPiece(oldRow, oldCol);
  if (isCell(oldRow, oldCol) && isCell(newRow, newCol) 
      && isOccupied(oldRow, oldCol)) {
    removePiece(oldRow, oldCol);
    setPiece(newRow, newCol, oldPiece);
  }
}

std::ostream & operator<<(std::ostream &out, const Board *b) {
  for (int i = 1; i <= 8; i++) {
      for (int j = 'a'; j <= 'h'; ++j) {
          std::cout << b->getPiece(i, j) << " ";
      }
      std::cout << std::endl;
  }
  return out;
}
