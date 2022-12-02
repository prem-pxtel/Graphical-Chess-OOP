#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "subject.h"
class Piece;

class Board : public Subject {
  std::vector<std::vector<Piece*>> board;
 public:
  bool whitecheck = false;
  bool blackcheck = false;
  Board();
  ~Board();
  char getPiece(int row, char col) const override;
  void setPiece(int row, char col, char p) override;
  void removePiece(int row, char col);
  std::vector<std::vector<Piece*>> getBoard();
  Piece *getPiecePtr(int row, char col);
  friend std::ostream & operator<<(std::ostream &out, const Board *b);
  void swapPiece(int oldRow, int oldCol, int newRow, int newCol);
  void updateBoards();
  bool isCell(int row, char col);
  bool isOccupied(int row, char col);
  bool isWhite(int row, int col);
  bool isWhitePiece(int row, char col);
  bool check();
};

std::ostream & operator<<(std::ostream &out, const Board *b);

#endif

class Check;
