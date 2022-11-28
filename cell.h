#ifndef CELL_H
#define CELL_H

class Cell {
 public:
  int row;
  char col;
  char piece;
  Cell(int row, char col, char piece = 'n') : row{row}, col{col}, piece{piece} {}
};

#endif
