#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "cell.h"
#include "subject.h"

class Board : public Subject {
 public:
  std::vector<std::vector<Cell*>> board;
  Board();
  char getPiece(int row, int col) const override;
};

std::ostream & operator<<(std::ostream &out, const Board *b);

#endif
