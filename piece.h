#ifndef PIECE_H
#define PIECE_H

class Piece {
 public:
  char piece;
  bool firstMove;
  Piece(char piece) : piece{piece} { firstMove = true; }
  //virtual ~Piece() = 0;
  virtual void move(char colOld, int rowOld, char colNew, int rowNew) = 0;
  virtual void capture(int oldRow, char oldCol, int newRow, char newCol) = 0;
};

#endif
