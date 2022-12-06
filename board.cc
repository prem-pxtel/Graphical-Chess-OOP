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
using std::cout;
using std::endl;

Board::Board() {}

Board::~Board() {
  for (int i = 0; i < 8; ++i) {
    for (char j = 'a'; j < 'h'; ++j) {
      delete board[i][j];
    }
  }
}

void Board::init(){
  whitecheck = false;
  blackcheck = false;
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

  std::vector<Piece*> row2;
  for (char j = 'a'; j <= 'h'; ++j) {
    row2.push_back(new Pawn{'p', this});
  }
  board.push_back(row2);

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

void Board::clearBoard(){
    for (int i = 1; i <= 8; i++) {
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
    cout << 8 - i + 1 << " ";
    for (int j = 'a'; j <= 'h'; ++j) {
        cout << b->getPiece(i, j);
    }
    cout << endl;
  }
  cout << endl << "  abcdefgh" << endl;
  return out;
}

// check is when a piece if moved in any of its possible moves could capture the king.
// looping through every piece 
// if it is a blank piece, continue, if it is a white piece, go through its ispath. 
// if the obstacle is the enemy king cout check, and then vice versa for black.
bool Board::check() {
  bool retval = false;
  whitecheck = false;
  blackcheck = false;
  for (int i = 1; i <= 8; ++i) {
    for (int j = 'a'; j <= 'h'; ++j) {
      char val = getPiece(i, j);
      if (val == 'K') {
        wkingrow = i;
        wkingcol = j;
      } else if (val == 'k') {
        bkingrow = i;
        bkingcol = j;
      }
    }
  }
  for (int i = 1; i <= 8; ++i) {
    for (int j = 'a'; j <= 'h'; ++j) { 
      if (isOccupied(i, j)) { // if occupied check if its checking the king
        char pic = getPiece(i, j);
        if ('a' <= pic && pic <= 'z') { // checks if it can check the white king
        if(pic == 'p'){
          if(getPiecePtr(i, j)->isInDiagonalPath(pic, j, i, wkingcol, wkingrow)){
              colourInCheck = "White";
              checkrow = i;
              checkcol = j;
              whitecheck = true;
              retval = true;
              getPiecePtr(i, j)->clearObs();  
          }
       }
          else if ((pic != 'p') && !(getPiecePtr(i, j)->isValidMove(pic, j, i, wkingcol, wkingrow))) {
            if (getPiecePtr(i, j)->getObsRow() == wkingrow 
              && getPiecePtr(i, j)->getObsCol() == wkingcol) {
              colourInCheck = "White";
              checkrow = i;
              checkcol = j;
              whitecheck = true;
              retval = true;
              getPiecePtr(i, j)->clearObs();    
            }
          }
        } else { // checks if it can check the black king
        if(pic == 'P'){
          if(getPiecePtr(i, j)->isInDiagonalPath(pic, j, i, bkingcol, bkingrow)){
              colourInCheck = "Black";
              checkrow = i;
              checkcol = j;
              blackcheck = true;
              retval = true;
              getPiecePtr(i, j)->clearObs();  
          }
        }
         else if ((pic != 'P') && !(getPiecePtr(i, j)->isValidMove(pic, j, i, bkingcol, bkingrow))) {
            if (getPiecePtr(i, j)->getObsRow() == bkingrow 
                && getPiecePtr(i, j)->getObsCol() == bkingcol) {
              colourInCheck = "Black";
              checkrow = i;
              checkcol = j;
              blackcheck = true;
              retval = true;
              getPiecePtr(i, j)->clearObs();
            }
          }
        }
      }
    }
  }
  return retval;
}

bool Board::moves(){
  int moves = 0;
  bool firstm = false;
  if(!turn){ // white's turn to move.
  for(int i = 1; i <= 8; i++){
    for(char j = 'a'; j <= 'h'; j++){ // getting the piece that is actually doing the movement.
    if(isOccupied(i,j)){
      if(isWhitePiece(i,j)){ // checking if the spot on the grid is occupied and if it is , if its a white piece
        if(getPiece(i,j) == 'P'){ // checking if its a pawn
          firstm = getPiecePtr(i,j)->firstMove;
          for(int k = 1; k <= 8; k++){
            for(char l = 'a'; l <= 'h'; l++){
              if (!(j == l && i == k)){
              if(getPiecePtr(i,j)->isValidMove('P', j, i, l, k)){ // move it , then revert it, make sure to give it its firstmove property back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if(!(check())){
                moves++;
              }
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              else if (getPiecePtr(i,j)->isValidCapture(j, i, l, k)){ // capture, then revert, make sure to give first move properties back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if(!(check())){
                moves++;
              }              
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
            }
            }
          }
        }
        else{ // not a pawn
        char pic = getPiece(i,j);
        if(pic == 'Q' || pic == 'K' || pic == 'N' || pic == 'B' || pic == 'R'){
          firstm = getPiecePtr(i,j)->firstMove;
          for(int k = 1; k <= 8; k++){
            for(char l = 'a'; l <= 'h'; l++){
             if(getPiecePtr(i,j)->isValidMove(pic, j, i, l, k)){ // move it , then revert it, make sure to give it its firstmove property back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if(!(check())){
                moves++;
              }
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              else if (getPiecePtr(i,j)->isValidCapture(j, i, l, k)){ // capture, then revert, make sure to give first move properties back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if(!(check())){
                moves++;
              }
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
            }
            }
        }
        }
      }
    }
    }
  }
  }
  else{ // blacks turn to move
  for(int i = 1; i <= 8; i++){
    for(char j = 'a'; j <= 'h'; j++){ // getting the piece that is actually doing the movement.
    if(isOccupied(i,j)){
      if(!(isWhitePiece(i,j))){ // checking if the spot on the grid is occupied and if it is , if its a white piece
        if(getPiece(i,j) == 'p'){ // checking if its a pawn
          firstm = getPiecePtr(i,j)->firstMove;
          for(int k = 1; k <= 8; k++){
            for(char l = 'a'; l <= 'h'; l++){
              if (!(j == l && i == k)){
              if(getPiecePtr(i,j)->isValidMove('p', j, i, l, k)){ // move it , then revert it, make sure to give it its firstmove property back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if(!(check())){
                moves++;
              }
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              else if (getPiecePtr(i,j)->isValidCapture(j, i, l, k)){ // capture, then revert, make sure to give first move properties back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if(!(check())){
                moves++;
              }
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
            }
            }
          }
        }
        else{ // not a pawn
        char pic = getPiece(i,j);
        if(pic == 'q' || pic == 'k' || pic == 'n' || pic == 'b' || pic == 'r'){
          firstm = getPiecePtr(i,j)->firstMove;
          for(int k = 1; k <= 8; k++){
            for(char l = 'a'; l <= 'h'; l++){
             if(getPiecePtr(i,j)->isValidMove(pic, j, i, l, k)){ // move it , then revert it, make sure to give it its firstmove property back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if(!(check())){
                moves++;
              }
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              else if (getPiecePtr(i,j)->isValidCapture(j, i, l, k)){ // capture, then revert, make sure to give first move properties back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if(!(check())){
                moves++;
              }
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
            }
            }
        }
        }
      }
    }
    }
  }
  }
  if(moves > 0){
    return true;
  }
  else{
    return false;
  }
}

void Board::levelone(){
  bool firstm = false;
  if(turn){ // white's turn to move.
  for(int i = 1; i <= 8; i++){
    for(char j = 'a'; j <= 'h'; j++){ // getting the piece that is actually doing the movement.
    if(isOccupied(i,j)){
      if(isWhitePiece(i,j)){ // checking if the spot on the grid is occupied and if it is , if its a white piece
        if(getPiece(i,j) == 'P'){ // checking if its a pawn
          firstm = getPiecePtr(i,j)->firstMove;
          for(int k = 1; k <= 8; k++){
            for(char l = 'a'; l <= 'h'; l++){
              if (!(j == l && i == k)){
              if(getPiecePtr(i,j)->isValidMove('P', j, i, l, k)){ // move it , then revert it, make sure to give it its firstmove property back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if((check())){
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              }
              else if (getPiecePtr(i,j)->isValidCapture(j, i, l, k)){ // capture, then revert, make sure to give first move properties back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if((check())){
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }              
              }
            }
            }
          }
        }
        else{ // not a pawn
        char pic = getPiece(i,j);
        if(pic == 'Q' || pic == 'K' || pic == 'N' || pic == 'B' || pic == 'R'){
          firstm = getPiecePtr(i,j)->firstMove;
          for(int k = 1; k <= 8; k++){
            for(char l = 'a'; l <= 'h'; l++){
             if(getPiecePtr(i,j)->isValidMove(pic, j, i, l, k)){ // move it , then revert it, make sure to give it its firstmove property back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if((check())){
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              }
              else if (getPiecePtr(i,j)->isValidCapture(j, i, l, k)){ // capture, then revert, make sure to give first move properties back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if((check())){
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              }
            }
            }
        }
        }
      }
    }
    }
  }
  }
  else{ // blacks turn to move
  for(int i = 1; i <= 8; i++){
    for(char j = 'a'; j <= 'h'; j++){ // getting the piece that is actually doing the movement.
    if(isOccupied(i,j)){
      if(!(isWhitePiece(i,j))){ // checking if the spot on the grid is occupied and if it is , if its a white piece
        if(getPiece(i,j) == 'p'){ // checking if its a pawn
          firstm = getPiecePtr(i,j)->firstMove;
          for(int k = 1; k <= 8; k++){
            for(char l = 'a'; l <= 'h'; l++){
              if (!(j == l && i == k)){
              if(getPiecePtr(i,j)->isValidMove('p', j, i, l, k)){ // move it , then revert it, make sure to give it its firstmove property back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if((check())){
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              }
              else if (getPiecePtr(i,j)->isValidCapture(j, i, l, k)){ // capture, then revert, make sure to give first move properties back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if((check())){
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              }
            }
            }
          }
        }
        else{ // not a pawn
        char pic = getPiece(i,j);
        if(pic == 'q' || pic == 'k' || pic == 'n' || pic == 'b' || pic == 'r'){
          firstm = getPiecePtr(i,j)->firstMove;
          for(int k = 1; k <= 8; k++){
            for(char l = 'a'; l <= 'h'; l++){
             if(getPiecePtr(i,j)->isValidMove(pic, j, i, l, k)){ // move it , then revert it, make sure to give it its firstmove property back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if((check())){
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              }
              else if (getPiecePtr(i,j)->isValidCapture(j, i, l, k)){ // capture, then revert, make sure to give first move properties back
              getPiecePtr(i,j)->firstMove = firstm;
              getPiecePtr(i,j)->move(j, i, l, k,' ');
              if((check())){
              getPiecePtr(k,l)->revertMove(j, i, l, k,' ');
              getPiecePtr(i,j)->firstMove = firstm;
              }
              }
            }
            }
        }
        }
      }
    }
    }
  }
  }
}

