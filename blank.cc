#include <iostream>
#include <vector>
#include "blank.h"
#include "piece.h"
class Board;

Blank::Blank(char piece, Board *b) 
  : Piece{piece}, b{b} {
}

Blank::~Blank() {}

void Blank::move(char oldCol, int oldRow, char newCol, int newRow) {}

void Blank::capture(int oldRow, char oldCol, int newRow, char newCol) {}

bool Blank::isValidMove(char oldPiece, char oldCol, int oldRow, char newCol, int newRow){
  return false;
}
