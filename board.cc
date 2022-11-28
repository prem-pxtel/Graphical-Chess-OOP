#include <iostream>
#include <vector>
#include "board.h"

bool isWhite(int row, int col) {
  if ((col + row) % 2 == 0) return false;
  return true; 
}

Board::Board() {
  for (int i = 1; i <= 8; i++) {
    std::vector<Cell*> row;
    for (char j = 'a'; j <= 'h'; ++j) {
      if (((j - 97) + i) % 2 == 0) {
        row.push_back(new Cell{i, j, ' '});
      } else {
        row.push_back(new Cell{i, j, '_'});
      }
    }
    board.push_back(row);
  }
}

char Board::getPiece(int row, char col) const {
  int rowNum = row - 1;
  int colNum = col - 97;
  return board[rowNum][colNum]->piece;
}

void Board::setPiece(int row, char col, char p) {
  int rowNum = row - 1;
  int colNum = col - 97;
  board[rowNum][colNum]->piece = p;
}

void Board::updateBoards() { notifyObservers(); }

void Board::boardInit() {
  for (char j = 'a'; j <= 'h'; ++j) {  
    setPiece(2, j, 'p');
    setPiece(7, j, 'P');
  }
  setPiece(1, 'a', 'r');
  setPiece(1, 'b', 'n');
  setPiece(1, 'c', 'b');
  setPiece(1, 'd', 'q');
  setPiece(1, 'e', 'k');
  setPiece(1, 'f', 'b');
  setPiece(1, 'g', 'n');
  setPiece(1, 'h', 'r');
  setPiece(8, 'a', 'R');
  setPiece(8, 'b', 'N');
  setPiece(8, 'c', 'B');
  setPiece(8, 'd', 'Q');
  setPiece(8, 'e', 'K');
  setPiece(8, 'f', 'B');
  setPiece(8, 'g', 'N');
  setPiece(8, 'h', 'R');
}

void Board::removePiece(int row, char col) {
  if (isWhite(row, col)) {
    setPiece(row, col, ' ');
  } else {
    setPiece(row, col, '_');
  }
}

bool Board::isCell(int row, char col) {
  if (1 <= row && row <= 8 && 'a' <= col && col <= 'h') return true;
  return false;
}

bool Board::isOccupied(int row, char col) {
  char pieceAt = getPiece(row, col);
  if (pieceAt == ' ' || pieceAt == '_') return false;
  return true;
}

// returns true if new cell is not blocked and in the path of the old cell
// otherwise, returns false
bool Board::isInPath(char oldPiece, char oldCol, int oldRow, 
                     char newCol, int newRow) {
  if (oldPiece == 'p') { // need to add interaction where if its the first time
  // the pawn is moving, it should be allowed to move two pieces up not just one
  // diagonal pawn
    if (newRow < oldRow) return false;
    for (int i = oldRow + 1; i <= newRow; ++i) {
      if(isOccupied(i, oldCol)) return false;
    }
    return true;
  } else if (oldPiece == 'P') {
    if (newRow > oldRow) return false;
    for (int i = oldRow - 1; i >= newRow; --i) {
      if(isOccupied(i, oldCol)) return false;
    }
    return true;
  } else if (oldPiece == 'r') { // two things for rook
  // it is bidirection so need to consider if its going left or right or 
  // up or down, then you need to check if from the spot it is now
  // to the spot it wants to go to, is there anything blocking its way.
  // if there is then dont let it move. if there isnt then let it move.
  if (oldCol == newCol){ // up and down
    if(oldRow <= newRow){
    for(int i = oldRow + 1; i <= newRow; i++){
      if(isOccupied(i, oldCol)) return false;
    }
    }
    else{
      for(int i = oldRow - 1; i >= newRow; i--){
      if(isOccupied(i, oldCol)) return false;
    }
    }
  }
  else{ // left and right
    if(oldCol <= newCol){
      for(int i = oldCol + 1; i <= newCol; i++){
        if(isOccupied(oldRow, i)) return false;
      }
    }
    else{
      for(int i = oldCol - 1; i >= newCol; i--){
        if(isOccupied(oldRow, i)) return false;
      }
    }
  }
    return true;
  } else if (oldPiece == 'R') {
    if (oldCol == newCol){ // up and down
    if(oldRow <= newRow){
    for(int i = oldRow + 1; i <= newRow; i++){
      if(isOccupied(i, oldCol)) return false;
    }
    }
    else{
      for(int i = oldRow - 1; i >= newRow; i--){
      if(isOccupied(i, oldCol)) return false;
    }
    }
  }
    else{ // left and right
    if(oldCol <= newCol){
      for(int i = oldCol + 1; i <= newCol; i++){
        if(isOccupied(oldRow, i)) return false;
      }
    }
    else{
      for(int i = oldCol - 1; i >= newCol; i--){
        if(isOccupied(oldRow, i)) return false;
      }
    }
  }
    return true;
  } else if (oldPiece == 'n') {

    return true;
  } else if (oldPiece == 'N') {

    return true;
  } else if (oldPiece == 'b') {

    return true;
  } else if (oldPiece == 'B') {

    return true;
  } else if (oldPiece == 'q') {

    return true;
  } else if (oldPiece == 'Q') {

    return true;
  } else if (oldPiece == 'k') {

    return true;
  } else {
    
    return true;
  }
}

bool Board::isValidMove(char oldPiece, char oldCol, int oldRow, 
                        char newCol, int newRow) {
  if (!isCell(oldRow, oldCol)) return false;
  if (!isCell(newRow, newCol)) return false; 
  if (!isOccupied(oldRow, oldCol)) return false;
  if (isOccupied(newRow, newCol)) return false;
  if (!isInPath(oldPiece, oldCol, oldRow, newCol, newRow)) return false;
  if (oldCol == newCol && oldRow == newRow) return false;
  return true;
}

void Board::move(char oldCol, int oldRow, char newCol, int newRow) {
  char oldPiece = getPiece(oldRow, oldCol);
  if (isValidMove(oldPiece, oldCol, oldRow, newCol, newRow)) {
    removePiece(oldRow, oldCol);
    setPiece(newRow, newCol, oldPiece);
  }
}

std::ostream & operator<<(std::ostream &out, const Board *b) {
  for (int i = 1; i <= 8; i++) {
      for (int j = 'a'; j <= 'h'; ++j) {
          std::cout << b->getPiece(i, j) << " ";
      }
      std::cout << std::endl;
  }
  return out;
}
