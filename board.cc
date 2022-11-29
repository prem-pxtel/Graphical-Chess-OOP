#include <iostream>
#include <vector>
#include "blank.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "board.h"
#include "queen.h"
#include <utility>

Board::Board() {
  std::vector<Cell*> row1;
  row1.push_back(new Rook{1, 'a', 'r', this});
  row1.push_back(new Rook{1, 'b', 'n', this});
  row1.push_back(new Bishop{1, 'c', 'b', this});
  row1.push_back(new Queen{1, 'd', 'q', this});
  row1.push_back(new Rook{1, 'e', 'k', this});
  row1.push_back(new Bishop{1, 'f', 'b', this});
  row1.push_back(new Rook{1, 'g', 'n', this});
  row1.push_back(new Rook{1, 'h', 'r', this});
  board.push_back(row1);

  std::vector<Cell*> row;
  for (char j = 'a'; j <= 'h'; ++j) {
    row.push_back(new Pawn{2, j, 'p', this});
  }
  board.push_back(row);

  for (int i = 3; i <= 6; i++) {
    std::vector<Cell*> blankRow;
    for (char j = 'a'; j <= 'h'; ++j) {
      if (((j - 97) + i) % 2 == 0) {
        blankRow.push_back(new Blank{i, j, ' ', this});
      } else {
        blankRow.push_back(new Blank{i, j, '_', this});
      }
    }
    board.push_back(blankRow);
  }

  std::vector<Cell*> row7;
  for (char j = 'a'; j <= 'h'; ++j) {
    row7.push_back(new Pawn{7, j, 'P', this});
  }
  board.push_back(row7);

  std::vector<Cell*> row8;
  row8.push_back(new Rook{8, 'a', 'R', this});
  row8.push_back(new Rook{8, 'b', 'N', this});
  row8.push_back(new Bishop{8, 'c', 'B', this});
  row8.push_back(new Rook{8, 'd', 'Q', this});
  row8.push_back(new Rook{8, 'e', 'K', this});
  row8.push_back(new Bishop{8, 'f', 'B', this});
  row8.push_back(new Rook{8, 'g', 'N', this});
  row8.push_back(new Rook{8, 'h', 'R', this});
  board.push_back(row8);
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

void Board::swapPiece(int oldRow, int oldCol, int newRow, int newCol) {
  std::swap(board[oldRow - 1][oldCol - 97], board[newRow - 1][newCol - 97]);
}

void Board::updateBoards() { notifyObservers(); }

void Board::boardInit() {
  for (char j = 'a'; j <= 'h'; ++j) {  
    setPiece(2, j, 'p');
    setPiece(7, j, 'P');
  }
  setPiece(1, 'a', 'r');
  setPiece(1, 'b', 'n');
  setPiece(1, 'c', 'b');
  setPiece(1, 'd', 'q');
  setPiece(1, 'e', 'k');
  setPiece(1, 'f', 'b');
  setPiece(1, 'g', 'n');
  setPiece(1, 'h', 'r');
  setPiece(8, 'a', 'R');
  setPiece(8, 'b', 'N');
  setPiece(8, 'c', 'B');
  setPiece(8, 'd', 'Q');
  setPiece(8, 'e', 'K');
  setPiece(8, 'f', 'B');
  setPiece(8, 'g', 'N');
  setPiece(8, 'h', 'R');
}

void Board::removePiece(int row, char col) {
  if (isWhite(row, col)) {
    setPiece(row, col, ' ');
  } else {
    setPiece(row, col, '_');
  }
}

bool Board::isWhite(int row, int col) {
  if ((col + row) % 2 == 0) return false;
  return true; 
}

bool Board::isCell(int row, char col) {
  if (1 <= row && row <= 8 && 'a' <= col && col <= 'h') return true;
  return false;
}

bool Board::isOccupied(int row, char col) {
  char pieceAt = getPiece(row, col);
  if (pieceAt == ' ' || pieceAt == '_') return false;
  return true;
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
