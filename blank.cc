#include <iostream>
#include <vector>
#include "blank.h"
#include "cell.h"
class Board;

Blank::Blank(int row, char col, char piece, Board *b) 
  : Cell{row, col, piece}, b{b} {
}

void Blank::move(char oldCol, int oldRow, char newCol, int newRow) {}
