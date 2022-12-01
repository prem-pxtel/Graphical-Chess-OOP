#ifndef PIECE_H
#define PIECE_H

class Piece {
 public:
  char piece;
  bool firstMove;
  int obstacleRow = 10;
  char obstacleCol = 'z';
  Piece(char piece) : piece{piece} { firstMove = true; }
  virtual ~Piece() {}
  virtual void move(char colOld, int rowOld, char colNew, int rowNew) = 0;
  virtual void capture(int oldRow, char oldCol, int newRow, char newCol) = 0;
  virtual bool isValidMove(char oldPiece, char oldCol, int oldRow, char newCol, int newRow) = 0;
  virtual char ObstacleC() = 0;
  virtual int ObstacleR() = 0;
};

#endif
