#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "cell.h"

class Board {
 public:
  std::vector<std::vector<Cell*>> board;
  Board();
};

std::ostream & operator<<(std::ostream &out, const Board *b);

#endif
