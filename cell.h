#ifndef CELL_H
#define CELL_H

class Cell {
 public:
  int row;
  int col;
  char piece;
  Cell(int row, int col, char piece = 'n') : row{row}, col{col}, piece{piece} {}
};

#endif
