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

char Board::getPiece(int row, int col) const {
  return board[row][col]->piece;
}

void Board::setPiece(int row, int col, char p) {
  board[row][col]->piece = p;
}

void Board::updateBoards() { notifyObservers(); }

void Board::boardInit() {
  for (int j = 0; j < 8; ++j) {  
    setPiece(1, j, 'p');
    setPiece(6, j, 'P');
  }
}

void Board::removePiece(int row, int col) {
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
  int rowNum = row - 1;
  int colNum = col - 97;
  if (getPiece(rowNum, colNum) != ' ' && getPiece(rowNum, colNum) != '_') return true;
  return false;
}

void Board::move(char colOld, int rowOld, char colNew, int rowNew) {
  int oldRowNum = rowOld - 1;
  int oldColNum = colOld - 97;
  int newRowNum = rowNew - 1;
  int newColNum = colNew - 97;
  if (isCell(rowOld, colOld) && isCell(rowNew, colNew) 
      && isOccupied(rowOld, colOld)) {
    char oldPiece = getPiece(oldRowNum, oldColNum);
    removePiece(oldRowNum, oldColNum);
    setPiece(newRowNum, newColNum, oldPiece);
  }
}

std::ostream & operator<<(std::ostream &out, const Board *b) {
  for (int i = 0; i <= 7; i++) {
      for (int j = 0; j <= 7; ++j) {
          std::cout << b->getPiece(i, j) << " ";
      }
      std::cout << std::endl;
  }
  return out;
}
