#ifndef CELL_H
#define CELL_H

class Cell {
 public:
  int row;
  char col;
  char piece;
  Cell(int row, char col, char piece) : row{row}, col{col}, piece{piece} {}
  virtual void move(char colOld, int rowOld, char colNew, int rowNew) = 0;
};

#endif
