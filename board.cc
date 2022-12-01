#include <iostream>
#include <vector>
#include <utility>
#include "board.h"
#include "blank.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "knight.h"

Board::Board() {
  std::vector<Piece*> row1;
  row1.push_back(new Rook{'r', this});
  row1.push_back(new Knight{'n', this});
  row1.push_back(new Bishop{'b', this});
  row1.push_back(new Queen{'q', this});
  row1.push_back(new King{'k', this});
  row1.push_back(new Bishop{'b', this});
  row1.push_back(new Knight{'n', this});
  row1.push_back(new Rook{'r', this});
  board.push_back(row1);

  std::vector<Piece*> row;
  for (char j = 'a'; j <= 'h'; ++j) {
    row.push_back(new Pawn{'p', this});
  }
  board.push_back(row);

  for (int i = 3; i <= 6; i++) {
    std::vector<Piece*> blankRow;
    for (char j = 'a'; j <= 'h'; ++j) {
      if (((j - 'a') + i) % 2 == 0) {
        blankRow.push_back(new Blank{'_', this});
      } else {
        blankRow.push_back(new Blank{' ', this});
      }
    }
    board.push_back(blankRow);
  }

  std::vector<Piece*> row7;
  for (char j = 'a'; j <= 'h'; ++j) {
    row7.push_back(new Pawn{'P', this});
  }
  board.push_back(row7);

  std::vector<Piece*> row8;
  row8.push_back(new Rook{'R', this});
  row8.push_back(new Knight{'N', this});
  row8.push_back(new Bishop{'B', this});
  row8.push_back(new Queen{'Q', this});
  row8.push_back(new King{'K', this});
  row8.push_back(new Bishop{'B', this});
  row8.push_back(new Knight{'N', this});
  row8.push_back(new Rook{'R', this});
  board.push_back(row8);
}

char Board::getPiece(int row, char col) const {
  int rowNum = row - 1;
  int colNum = col - 'a';
  return board[rowNum][colNum]->piece;
}

std::vector<std::vector<Piece*>> Board::getBoard() { return board; }

Piece * Board::getPiecePtr(int row, char col) {
  int rowNum = row - 1;
  int colNum = col - 'a';
  return board[rowNum][colNum];
}

void Board::setPiece(int row, char col, char p) {
  int rowNum = row - 1;
  int colNum = col - 'a';
  board[rowNum][colNum]->piece = p;
}

void Board::swapPiece(int oldRow, int oldCol, int newRow, int newCol) {
  std::swap(board[oldRow - 1][oldCol - 'a'], board[newRow - 1][newCol - 'a']);
}

void Board::updateBoards() { notifyObservers(); }

void Board::removePiece(int row, char col) {
  if (isWhite(row, col)) {
    setPiece(row, col, ' ');
  } else {
    setPiece(row, col, '_');
  }
}

bool Board::isWhite(int row, int col) {
  if ((col + row) % 2 == 0) return true;
  return false;
}

bool Board::isWhitePiece(int row, char col) {
  char value = getPiece(row, col);
  if ('A' <= value && value <= 'Z') {
    return true;
  }
  return false;
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

std::ostream & operator<<(std::ostream &out, const Board *b) {
  for (int i = 1; i <= 8; i++) {
    std::cout << 8 - i + 1 << " ";
    for (int j = 'a'; j <= 'h'; ++j) {
        std::cout << b->getPiece(i, j);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl << "  abcdefgh" << std::endl;
  return out;
}

// check is when a piece if moved in any of its possible moves could capture the king.
// looping through every piece 
// if it is a blank piece, continue, if it is a white piece, go through its ispath. 
// if the obstacle is the enemy king cout check, and then vice versa for black.

bool Board::check(){
  int wkingrow;
  char wkingcol;
  int bkingrow;
  char bkingcol;
  bool retval = false;
  for(int i = 1; i <= 8; i++){
    for(int j = 'a'; j<= 'h'; j++){
      char val = getPiece(i,j);
      if(val == 'K'){
        wkingrow = i;
        wkingcol = j;
      }
      else if (val == 'k'){
        bkingrow = i;
        bkingcol = j;
    }
  }
}
  for(int i = 1; i <= 8; i++){
    for(int j = 'a'; j <= 'h'; j++){ 
      if(isOccupied(i,j)){ // if occupied check if its checking the king.
      char pic = getPiece(i,j);
      if('a' <= pic && pic <= 'z'){ // checks if it can check the white king
//      std::cout << "wcheck" << std::endl;
        if(!(getPiecePtr(i,j)->isValidMove(pic, j, i, wkingcol, wkingrow))){
//          std::cout << wkingrow << std::endl;
//          std::cout << wkingcol << std::endl;
//          std::cout << "checkthrough" << std::endl;
          if(getPiecePtr(i,j)->ObstacleR() == wkingrow && getPiecePtr(i,j)->ObstacleC() == wkingcol){
            std::cout << "check" << std::endl;
            retval = true;          
            }
        }
      }
      else{ // checks if it can check the black king
//      std::cout << "bcheck" << std::endl;
//      std::cout << bkingrow << std::endl;
//      std::cout << bkingcol << std::endl;
      if(!(getPiecePtr(i,j)->isValidMove(pic, j, i, bkingcol, bkingrow))){
//        std::cout << "checkthrough" << std::endl;
          std::cout << getPiecePtr(i,j)->ObstacleR();
          std::cout << getPiecePtr(i,j)->ObstacleC() << std::endl;
          if(getPiecePtr(i,j)->ObstacleR() == bkingrow && getPiecePtr(i,j)->ObstacleC() == bkingcol){
            std::cout << "check" << std::endl;
            retval = true;
          }
        }
      }
      }
    }
  }
  return retval;
}
