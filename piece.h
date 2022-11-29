#ifndef CELL_H
#define CELL_H

class Piece {
 public:
  char piece;
  Piece(char piece) : piece{piece} {}
  virtual void move(char colOld, int rowOld, char colNew, int rowNew) = 0;
};

#endif
