#ifndef PIECE_H
#define PIECE_H

class Piece {
 public:
  char piece;
  bool firstMove;
  Piece(char piece) : piece{piece} {
    firstMove = true;
  }
  virtual void move(char colOld, int rowOld, char colNew, int rowNew) = 0;
};

#endif
