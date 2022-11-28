#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "cell.h"
#include "subject.h"

class Board : public Subject {
  std::vector<std::vector<Cell*>> board;
 public:
  Board();
  char getPiece(int row, char col) const override;
  void setPiece(int row, char col, char p) override;
  void removePiece(int row, char col);
  std::vector<std::vector<Cell*>> getBoard() { return board; }
  friend std::ostream & operator<<(std::ostream &out, const Board *b);
  void updateBoards();
  void boardInit();
  void move(char colOld, int rowOld, char colNew, int rowNew);
  bool isCell(int row, char col);
  bool isOccupied(int row, char col);
  bool isValidMove(char oldPiece, char oldCol, int oldRow, 
                   char newCol, int newRow);
  bool isInPath(char oldPiece, char oldCol, int oldRow, 
                char newCol, int newRow);
};

std::ostream & operator<<(std::ostream &out, const Board *b);

#endif
