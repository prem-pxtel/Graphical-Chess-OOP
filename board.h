#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "cell.h"
#include "subject.h"

class Board : public Subject {
  std::vector<std::vector<Cell*>> board;
 public:
  Board();
  char getPiece(int row, int col) const override;
  std::vector<std::vector<Cell*>> getBoard() { return board; }
  friend std::ostream & operator<<(std::ostream &out, const Board *b);
  void updateBoards();
};

std::ostream & operator<<(std::ostream &out, const Board *b);

#endif
