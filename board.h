#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "subject.h"
class Cell;

class Board : public Subject {
  std::vector<std::vector<Cell*>> board;
 public:
  Board();
  char getPiece(int row, char col) const override;
  void setPiece(int row, char col, char p) override;
  void removePiece(int row, char col);
  std::vector<std::vector<Cell*>> getBoard() { return board; }
  friend std::ostream & operator<<(std::ostream &out, const Board *b);
  void swapPiece(int oldRow, char oldCol, int newRow, int newCol);
  void updateBoards();
  void boardInit();
  bool isCell(int row, char col);
  bool isOccupied(int row, char col);
  bool isWhite(int row, int col);
};

std::ostream & operator<<(std::ostream &out, const Board *b);

#endif
