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
              cout << "White is in check." << endl; 
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
              cout << "White is in check." << endl; 
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
              cout << "White is in check." << endl; 
              checkrow = i;
              checkcol = j;
              whitecheck = true;
              retval = true;
              getPiecePtr(i, j)->clearObs();  
          }
        }
         else if ((pic != 'P') && !(getPiecePtr(i, j)->isValidMove(pic, j, i, bkingcol, bkingrow))) {
            if (getPiecePtr(i, j)->getObsRow() == bkingrow 
                && getPiecePtr(i, j)->getObsCol() == bkingcol) {
              cout << "Black is in check." << endl;
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

bool Board::checkmate()
{
  int bmoves = 0;
  int wmoves = 0;
  if (whitecheck || blackcheck)
  {
    bool firstm = false;
    if (blackcheck)
    { // only check if black pieces can defend its king
    int bkingroworiginal = bkingrow;
    char bkingcoloriginal = bkingcol;
    for (int i = 1; i <= 8; ++i)
      {
        for (char j = 'a'; j <= 'h'; ++j)
        {
          if (isOccupied(i, j))
          { // check if pieces are occupied
            if (!(isWhitePiece(i, j)))
            { // if its a white piece
              if (getPiece(i, j) == 'p')
              {
                if (getPiecePtr(i, j)->isInDiagonalPath('p', j, i, checkcol, checkrow))
                { // if capturable via pawn

                  getPiecePtr(i, j)->move(j, i, checkcol, checkrow, ' ');
                  if (!(check()))
                  { // if it solves the check then there is a move available
                    wmoves++;
                  }
                  getPiecePtr(checkrow, checkcol)->revertMove(j, i, checkcol, checkrow, ' '); // revert the move
                }
                else
                { // check if the 8 spots around the king can be moved to by the black pieces to prevent the check
                  if (isCell(bkingroworiginal, bkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(bkingroworiginal == i && bkingcoloriginal + 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcoloriginal + 1, bkingroworiginal))
                    { // first spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal + 1, bkingroworiginal, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal, bkingcoloriginal + 1)->revertMove(j, i, bkingcoloriginal + 1, bkingroworiginal, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                  }
                }
                  if (isCell(bkingroworiginal, bkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(bkingroworiginal == i && bkingcoloriginal - 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcoloriginal - 1, bkingroworiginal))
                    { // second spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal - 1, bkingroworiginal, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal, bkingcoloriginal - 1)->revertMove(j, i, bkingcoloriginal - 1, bkingroworiginal, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                   }
                  }
                  if (isCell(bkingroworiginal + 1, bkingcoloriginal))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(bkingroworiginal + 1 == i && bkingcoloriginal == j)){
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcoloriginal, bkingroworiginal + 1))
                    { // third spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal, bkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal + 1, bkingcoloriginal)->revertMove(j, i, bkingcoloriginal, bkingroworiginal + 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                  }
                  }
                  if (isCell(bkingroworiginal - 1, bkingcoloriginal))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(bkingroworiginal - 1 == i && bkingcoloriginal == j)){
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcoloriginal, bkingroworiginal - 1))
                    { // fourth spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal, bkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal - 1, bkingcoloriginal)->revertMove(j, i, bkingcoloriginal, bkingroworiginal - 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                  }
                  }
                  if (isCell(bkingroworiginal + 1, bkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(bkingroworiginal + 1 == i && bkingcoloriginal + 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcoloriginal + 1, bkingroworiginal + 1))
                    { // fifth spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal + 1, bkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal + 1, bkingcoloriginal + 1)->revertMove(j, i, bkingcoloriginal + 1, bkingroworiginal + 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                  }
                  }
                  if (isCell(bkingroworiginal - 1, bkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(bkingroworiginal - 1 == i && bkingcoloriginal - 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcoloriginal - 1, bkingroworiginal - 1))
                    { // sixth spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal - 1, bkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal - 1, bkingcoloriginal - 1)->revertMove(j, i, bkingcoloriginal - 1, bkingroworiginal - 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                  }
                  }
                  if (isCell(bkingroworiginal + 1, bkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(bkingroworiginal + 1 == i && bkingcoloriginal - 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcoloriginal - 1, bkingroworiginal + 1))
                    { // seventh spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal - 1, bkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal + 1, bkingcoloriginal - 1)->revertMove(j, i, bkingcoloriginal - 1, bkingroworiginal + 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                    }
                  }
                  if (isCell(bkingroworiginal - 1, bkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(bkingroworiginal - 1 == i && bkingcoloriginal + 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcoloriginal + 1, bkingroworiginal - 1))
                    { // eigth spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal + 1, bkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal - 1, bkingcoloriginal + 1)->revertMove(j, i, bkingcoloriginal + 1, bkingroworiginal - 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                    }
                  }
                }
              }
              else if (getPiece(i, j) == 'R' || getPiece(i, j) == 'Q' || getPiece(i, j) == 'K'
                     || getPiece(i, j) == 'B' || getPiece(i, j) == 'N') 
              { // all the other pieces
              // include wkingoriginal col and row and should fix everything related to king issues.
                if (!(getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, checkcol, checkrow)))
                {
                  firstm = getPiecePtr(i, j)->firstMove;
                  int obstacleRow = getPiecePtr(i, j)->getObsRow();
                  char obstacleCol = getPiecePtr(i, j)->getObsCol();
                  if (isCell(obstacleRow, obstacleCol))
                  {
                    if (checkrow == obstacleRow && checkcol == obstacleCol && isWhitePiece(i, j) != isWhitePiece(obstacleRow, obstacleCol))
                    { // if capturable via other pieces
                      getPiecePtr(i, j)->move(j, i, checkcol, checkrow, ' ');
                      if (!(check()))
                      { // if it solves the check then there are moves available
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, checkcol, checkrow, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                }
                if (!(getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, checkcol, checkrow)))
                { // check if the 8 spots around the king can be moved to by the white pieces to prevent the check
                  if (isCell(bkingroworiginal, bkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcoloriginal + 1, bkingroworiginal))
                    { // first spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal + 1, bkingroworiginal, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal, bkingcoloriginal + 1)->revertMove(j, i, bkingcoloriginal + 1, bkingroworiginal, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(bkingroworiginal, bkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcoloriginal - 1, bkingroworiginal))
                    { // second spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal - 1, bkingroworiginal, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal, bkingcoloriginal - 1)->revertMove(j, i, bkingcoloriginal - 1, bkingroworiginal, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(bkingroworiginal + 1, bkingcoloriginal))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcoloriginal, bkingroworiginal + 1))
                    { // third spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal, bkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal + 1, bkingcoloriginal)->revertMove(j, i, bkingcoloriginal, bkingroworiginal + 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(bkingroworiginal - 1, bkingcoloriginal))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcoloriginal, bkingroworiginal - 1))
                    { // fourth spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal, bkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal - 1, bkingcoloriginal)->revertMove(j, i, bkingcoloriginal, bkingroworiginal - 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(bkingroworiginal + 1, bkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcoloriginal + 1, bkingroworiginal + 1))
                    { // fifth spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal + 1, bkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal + 1, bkingcoloriginal + 1)->revertMove(j, i, bkingcoloriginal + 1, bkingroworiginal + 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(bkingroworiginal - 1, bkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcoloriginal - 1, bkingroworiginal - 1))
                    { // sixth spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal - 1, bkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal - 1, bkingcoloriginal - 1)->revertMove(j, i, bkingcoloriginal - 1, bkingroworiginal - 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(bkingroworiginal + 1, bkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcoloriginal - 1, bkingroworiginal + 1))
                    { // seventh spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal - 1, bkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal + 1, bkingcoloriginal - 1)->revertMove(j, i, bkingcoloriginal - 1, bkingroworiginal + 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                   if (isCell(bkingroworiginal - 1, bkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcoloriginal + 1, bkingroworiginal - 1))
                    { // eigth spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, bkingcoloriginal + 1, bkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(bkingroworiginal - 1, bkingcoloriginal + 1)->revertMove(j, i, bkingcoloriginal + 1, bkingroworiginal - 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                } // where it ends
              }
            }
          }
        }
      }
    }
    else
    { // only check if white pieces can defend its king
int wkingroworiginal = wkingrow;
char wkingcoloriginal = wkingcol;
      for (int i = 1; i <= 8; ++i)
      {
        for (char j = 'a'; j <= 'h'; ++j)
        {
          if (isOccupied(i, j))
          { // check if pieces are occupied
            if ((isWhitePiece(i, j)))
            { // if its a white piece
              if (getPiece(i, j) == 'P')
              {
                if (getPiecePtr(i, j)->isInDiagonalPath('P', j, i, checkcol, checkrow))
                { // if capturable via pawn

                  getPiecePtr(i, j)->move(j, i, checkcol, checkrow, ' ');
                  if (!(check()))
                  { // if it solves the check then there is a move available
                    wmoves++;
                  }
                  getPiecePtr(checkrow, checkcol)->revertMove(j, i, checkcol, checkrow, ' '); // revert the move
                }
                else
                { // check if the 8 spots around the king can be moved to by the black pieces to prevent the check
                  if (isCell(wkingroworiginal, wkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(wkingroworiginal == i && wkingcoloriginal + 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('P', j, i, wkingcoloriginal + 1, wkingroworiginal))
                    { // first spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal + 1, wkingroworiginal, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal, wkingcoloriginal + 1)->revertMove(j, i, wkingcoloriginal + 1, wkingroworiginal, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                  }
                }
                  if (isCell(wkingroworiginal, wkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(wkingroworiginal == i && wkingcoloriginal - 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('P', j, i, wkingcoloriginal - 1, wkingroworiginal))
                    { // second spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal - 1, wkingroworiginal, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal, wkingcoloriginal - 1)->revertMove(j, i, wkingcoloriginal - 1, wkingroworiginal, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                   }
                  }
                  if (isCell(wkingroworiginal + 1, wkingcoloriginal))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(wkingroworiginal + 1 == i && wkingcoloriginal == j)){
                    if (getPiecePtr(i, j)->isValidMove('P', j, i, wkingcoloriginal, wkingroworiginal + 1))
                    { // third spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal, wkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal + 1, wkingcoloriginal)->revertMove(j, i, wkingcoloriginal, wkingroworiginal + 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                  }
                  }
                  if (isCell(wkingroworiginal - 1, wkingcoloriginal))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(wkingroworiginal - 1 == i && wkingcoloriginal == j)){
                    if (getPiecePtr(i, j)->isValidMove('P', j, i, wkingcoloriginal, wkingroworiginal - 1))
                    { // fourth spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal, wkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal - 1, wkingcoloriginal)->revertMove(j, i, wkingcoloriginal, wkingroworiginal - 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                  }
                  }
                  if (isCell(wkingroworiginal + 1, wkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(wkingroworiginal + 1 == i && wkingcoloriginal + 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('P', j, i, wkingcoloriginal + 1, wkingroworiginal + 1))
                    { // fifth spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal + 1, wkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal + 1, wkingcoloriginal + 1)->revertMove(j, i, wkingcoloriginal + 1, wkingroworiginal + 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                  }
                  }
                  if (isCell(wkingroworiginal - 1, wkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(wkingroworiginal - 1 == i && wkingcoloriginal - 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('P', j, i, wkingcoloriginal - 1, wkingroworiginal - 1))
                    { // sixth spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal - 1, wkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal - 1, wkingcoloriginal - 1)->revertMove(j, i, wkingcoloriginal - 1, wkingroworiginal - 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                  }
                  }
                  if (isCell(wkingroworiginal + 1, wkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(wkingroworiginal + 1 == i && wkingcoloriginal - 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('P', j, i, wkingcoloriginal - 1, wkingroworiginal + 1))
                    { // seventh spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal - 1, wkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal + 1, wkingcoloriginal - 1)->revertMove(j, i, wkingcoloriginal - 1, wkingroworiginal + 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                    }
                  }
                  if (isCell(wkingroworiginal - 1, wkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if(!(wkingroworiginal - 1 == i && wkingcoloriginal + 1 == j)){
                    if (getPiecePtr(i, j)->isValidMove('P', j, i, wkingcoloriginal + 1, wkingroworiginal - 1))
                    { // eigth spot
                      getPiecePtr(i, j)->firstMove = firstm;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal + 1, wkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal - 1, wkingcoloriginal + 1)->revertMove(j, i, wkingcoloriginal + 1, wkingroworiginal - 1, ' ');
                      getPiecePtr(i, j)->firstMove = firstm;
                    }
                    }
                  }
                }
              }
              else if (getPiece(i, j) == 'R' || getPiece(i, j) == 'Q' || getPiece(i, j) == 'K'
                     || getPiece(i, j) == 'B' || getPiece(i, j) == 'N') 
              { // all the other pieces
              // include wkingoriginal col and row and should fix everything related to king issues.
                if (!(getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, checkcol, checkrow)))
                {
                  firstm = getPiecePtr(i, j)->firstMove;
                  int obstacleRow = getPiecePtr(i, j)->getObsRow();
                  char obstacleCol = getPiecePtr(i, j)->getObsCol();
                  if (isCell(obstacleRow, obstacleCol))
                  {
                    if (checkrow == obstacleRow && checkcol == obstacleCol && isWhitePiece(i, j) != isWhitePiece(obstacleRow, obstacleCol))
                    { // if capturable via other pieces
                      getPiecePtr(i, j)->move(j, i, checkcol, checkrow, ' ');
                      if (!(check()))
                      { // if it solves the check then there are moves available
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, checkcol, checkrow, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                }
                if (!(getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, checkcol, checkrow)))
                { // check if the 8 spots around the king can be moved to by the white pieces to prevent the check
                  if (isCell(wkingroworiginal, wkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcoloriginal + 1, wkingroworiginal))
                    { // first spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal + 1, wkingroworiginal, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal, wkingcoloriginal + 1)->revertMove(j, i, wkingcoloriginal + 1, wkingroworiginal, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(wkingroworiginal, wkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcoloriginal - 1, wkingroworiginal))
                    { // second spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal - 1, wkingroworiginal, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal, wkingcoloriginal - 1)->revertMove(j, i, wkingcoloriginal - 1, wkingroworiginal, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(wkingroworiginal + 1, wkingcoloriginal))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcoloriginal, wkingroworiginal + 1))
                    { // third spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal, wkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal + 1, wkingcoloriginal)->revertMove(j, i, wkingcoloriginal, wkingroworiginal + 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(wkingroworiginal - 1, wkingcoloriginal))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcoloriginal, wkingroworiginal - 1))
                    { // fourth spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal, wkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal - 1, wkingcoloriginal)->revertMove(j, i, wkingcoloriginal, wkingroworiginal - 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(wkingroworiginal + 1, wkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcoloriginal + 1, wkingroworiginal + 1))
                    { // fifth spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal + 1, wkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal + 1, wkingcoloriginal + 1)->revertMove(j, i, wkingcoloriginal + 1, wkingroworiginal + 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(wkingroworiginal - 1, wkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcoloriginal - 1, wkingroworiginal - 1))
                    { // sixth spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal - 1, wkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal - 1, wkingcoloriginal - 1)->revertMove(j, i, wkingcoloriginal - 1, wkingroworiginal - 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                  if (isCell(wkingroworiginal + 1, wkingcoloriginal - 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcoloriginal - 1, wkingroworiginal + 1))
                    { // seventh spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal - 1, wkingroworiginal + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal + 1, wkingcoloriginal - 1)->revertMove(j, i, wkingcoloriginal - 1, wkingroworiginal + 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                   if (isCell(wkingroworiginal - 1, wkingcoloriginal + 1))
                  {
                    firstm = getPiecePtr(i, j)->firstMove;
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcoloriginal + 1, wkingroworiginal - 1))
                    { // eigth spot
                    firstm = getPiecePtr(i, j)->firstMove;
                      getPiecePtr(i, j)->move(j, i, wkingcoloriginal + 1, wkingroworiginal - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(wkingroworiginal - 1, wkingcoloriginal + 1)->revertMove(j, i, wkingcoloriginal + 1, wkingroworiginal - 1, ' ');
                      firstm = getPiecePtr(i, j)->firstMove;
                    }
                  }
                } // where it ends
              }
            }
          }
        }
      }
    }
    if (whitecheck)
    {
      if (wmoves == 0)
      {
        cout << "Checkmate! Black wins!" << endl;
        ++blackwins;
        return true;
      }
    }
    else
    {
      if (bmoves == 0)
      {
        cout << "Checkmate! White wins!" << endl;
        ++whitewins;
        return true;
      }
    }
  }
  return false;
}
