#include <iostream>
#include <vector>
#include "board.h"

Board::Board() {
  for (int i = 0; i < 8; i++) {
    std::vector<Cell*> row;
    for (int j = 0; j < 8; ++j) {
      if (i == 1) {
        row.push_back(new Cell{i, j, 'p'});
      } else if (i == 6) {
        row.push_back(new Cell{i, j, 'P'});
      } else if ((j + i) % 2 == 0) {
        row.push_back(new Cell{i, j, ' '});
      } else {
        row.push_back(new Cell{i, j, '_'});
      }
    }
    board.push_back(row);
  }
  board[0][0]->piece = 'r';
  board[0][1]->piece = 'n';
  board[0][2]->piece = 'b';
  board[0][3]->piece = 'q';
  board[0][4]->piece = 'k';
  board[0][5]->piece = 'b';
  board[0][6]->piece = 'n';
  board[0][7]->piece = 'r';
  board[7][0]->piece = 'R';
  board[7][1]->piece = 'N';
  board[7][2]->piece = 'B';
  board[7][3]->piece = 'Q';
  board[7][4]->piece = 'K';
  board[7][5]->piece = 'B';
  board[7][6]->piece = 'N';
  board[7][7]->piece = 'R';
}

char Board::getPiece(int row, int col) const {
  return board[row][col]->piece;
}

std::ostream & operator<<(std::ostream &out, const Board *b) {
  for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; ++j) {
          std::cout << b->getPiece(i, j) << " ";
      }
      std::cout << std::endl;
  }
  return out;
}
