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

Board::Board() {
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

Board::~Board() {
  for (int i = 0; i < 8; ++i) {
    for (char j = 'a'; j < 'h'; ++j) {
      delete board[i][j];
    }
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
          if (!(getPiecePtr(i, j)->isValidMove(pic, j, i, wkingcol, wkingrow))) {
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
          if (!(getPiecePtr(i, j)->isValidMove(pic, j, i, bkingcol, bkingrow))) {
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
    if (whitecheck)
    { // only check if white pieces can defend its king
      for (int i = 1; i <= 8; ++i)
      {
        for (char j = 'a'; j <= 'h'; ++j)
        {
          if (isOccupied(i, j))
          { // check if pieces are occupied
            if (!(isWhitePiece(i, j)))
            { // if its a black piece
              if (getPiece(i, j) == 'p')
              {
                if (getPiecePtr(i, j)->isInDiagonalPath('p', j, i, checkcol, checkrow))
                {
                  // if capturable via pawn
                  getPiecePtr(i, j)->move(j, i, checkcol, checkrow, ' ');
                  if (!(check()))
                  { // if it solves the check then there is a move available
                    wmoves++;
                  }
                  getPiecePtr(checkrow, checkcol)->revertMove(j, i, checkcol, checkrow, ' ');
                  // revert the move
                }
                else
                { // check if the 8 spots around the king can be moved to by the black pieces to prevent the check
                  if (isCell(bkingrow, bkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcol + 1, bkingrow))
                    { // first spot
                      getPiecePtr(i, j)->move(j, i, bkingcol + 1, bkingrow, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol + 1, bkingrow, ' ');
                    }
                  }
                  if (isCell(bkingrow, bkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('P', j, i, bkingcol - 1, bkingrow))
                    { // second spot
                      getPiecePtr(i, j)->move(j, i, bkingcol - 1, bkingrow, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol - 1, bkingrow, ' ');
                    }
                  }
                  if (isCell(bkingrow + 1, bkingcol))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcol, bkingrow + 1))
                    { // third spot
                      getPiecePtr(i, j)->move(j, i, bkingcol, bkingrow + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol, bkingrow + 1, ' ');
                    }
                  }
                  if (isCell(bkingrow - 1, bkingcol))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcol, bkingrow - 1))
                    { // fourth spot
                      getPiecePtr(i, j)->move(j, i, bkingcol, bkingrow - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol, bkingrow - 1, ' ');
                    }
                  }
                  if (isCell(bkingrow + 1, bkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcol + 1, bkingrow + 1))
                    { // fifth spot
                      getPiecePtr(i, j)->move(j, i, bkingcol + 1, bkingrow + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol + 1, bkingrow + 1, ' ');
                    }
                  }
                  if (isCell(bkingrow - 1, bkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcol - 1, bkingrow - 1))
                    { // sixth spot
                      getPiecePtr(i, j)->move(j, i, bkingcol - 1, bkingrow - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol - 1, bkingrow - 1, ' ');
                    }
                  }
                  if (isCell(bkingrow + 1, bkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcol - 1, bkingrow + 1))
                    { // seventh spot
                      getPiecePtr(i, j)->move(j, i, bkingcol - 1, bkingrow + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol - 1, bkingrow + 1, ' ');
                    }
                  }
                  if (isCell(bkingrow - 1, bkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, bkingcol + 1, bkingrow - 1))
                    { // eigth spot
                      getPiecePtr(i, j)->move(j, i, bkingcol + 1, bkingrow - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol + 1, bkingrow - 1, ' ');
                    }
                  }
                }
              }
              else
              { // all the other pieces

                if (!(getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, checkcol, checkrow)))
                {
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
                    }
                  }
                }
                else
                { // check if the 8 spots around the king can be moved to by the black pieces to prevent the check
                  if (isCell(bkingrow, bkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcol + 1, bkingrow))
                    { // first spot
                      getPiecePtr(i, j)->move(j, i, bkingcol + 1, bkingrow, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol + 1, bkingrow, ' ');
                    }
                  }
                  else if (isCell(bkingrow, bkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcol - 1, bkingrow))
                    { // second spot
                      getPiecePtr(i, j)->move(j, i, bkingcol - 1, bkingrow, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol - 1, bkingrow, ' ');
                    }
                  }
                  else if (isCell(bkingrow + 1, bkingcol))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcol, bkingrow + 1))
                    { // third spot
                      getPiecePtr(i, j)->move(j, i, bkingcol, bkingrow + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol, bkingrow + 1, ' ');
                    }
                  }
                  else if (isCell(bkingrow - 1, bkingcol))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcol, bkingrow - 1))
                    { // fourth spot
                      getPiecePtr(i, j)->move(j, i, bkingcol, bkingrow - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol, bkingrow - 1, ' ');
                    }
                  }
                  else if (isCell(bkingrow + 1, bkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcol + 1, bkingrow + 1))
                    { // fifth spot
                      getPiecePtr(i, j)->move(j, i, bkingcol + 1, bkingrow + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol + 1, bkingrow + 1, ' ');
                    }
                  }
                  else if (isCell(bkingrow - 1, bkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcol - 1, bkingrow - 1))
                    { // sixth spot
                      getPiecePtr(i, j)->move(j, i, bkingcol - 1, bkingrow - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol - 1, bkingrow - 1, ' ');
                    }
                  }
                  else if (isCell(bkingrow + 1, bkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcol - 1, bkingrow + 1))
                    { // seventh spot
                      getPiecePtr(i, j)->move(j, i, bkingcol - 1, bkingrow + 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol - 1, bkingrow + 1, ' ');
                    }
                  }
                  else if (isCell(bkingrow - 1, bkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, bkingcol + 1, bkingrow - 1))
                    { // eigth spot
                      getPiecePtr(i, j)->move(j, i, bkingcol + 1, bkingrow - 1, ' ');
                      if (!(check()))
                      {
                        wmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, bkingcol + 1, bkingrow - 1, ' ');
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else
    { // only check if black pieces can defend its king
      for (int i = 1; i <= 8; ++i)
      {
        for (char j = 'a'; j <= 'h'; ++j)
        {
          if (isOccupied(i, j))
          { // check if pieces are occupied
            if (!(isWhitePiece(i, j)))
            { // if its a black piece
              if (getPiece(i, j) == 'p')
              {
                if (getPiecePtr(i, j)->isInDiagonalPath('p', j, i, checkcol, checkrow))
                { // if capturable via pawn

                  getPiecePtr(i, j)->move(j, i, checkcol, checkrow, ' ');
                  if (!(check()))
                  { // if it solves the check then there is a move available
                    bmoves++;
                  }
                  getPiecePtr(checkrow, checkcol)->revertMove(j, i, checkcol, checkrow, ' '); // revert the move
                }
                else
                { // check if the 8 spots around the king can be moved to by the black pieces to prevent the check
                  if (isCell(wkingrow, wkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, wkingcol + 1, wkingrow))
                    { // first spot
                      getPiecePtr(i, j)->move(j, i, wkingcol + 1, wkingrow, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol + 1, wkingrow, ' ');
                    }
                  }
                  if (isCell(wkingrow, wkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('P', j, i, wkingcol - 1, wkingrow))
                    { // second spot
                      getPiecePtr(i, j)->move(j, i, wkingcol - 1, wkingrow, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol - 1, wkingrow, ' ');
                    }
                  }
                  if (isCell(wkingrow + 1, wkingcol))
                  {

                    if (getPiecePtr(i, j)->isValidMove('p', j, i, wkingcol, wkingrow + 1))
                    { // third spot
                      getPiecePtr(i, j)->move(j, i, wkingcol, wkingrow + 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol, wkingrow + 1, ' ');
                    }
                  }
                  if (isCell(wkingrow - 1, wkingcol))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, wkingcol, wkingrow - 1))
                    { // fourth spot
                      getPiecePtr(i, j)->move(j, i, wkingcol, wkingrow - 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol, wkingrow - 1, ' ');
                    }
                  }
                  if (isCell(wkingrow + 1, wkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, wkingcol + 1, wkingrow + 1))
                    { // fifth spot
                      getPiecePtr(i, j)->move(j, i, wkingcol + 1, wkingrow + 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol + 1, wkingrow + 1, ' ');
                    }
                  }
                  if (isCell(wkingrow - 1, wkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, wkingcol - 1, wkingrow - 1))
                    { // sixth spot
                      getPiecePtr(i, j)->move(j, i, wkingcol - 1, wkingrow - 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol - 1, wkingrow - 1, ' ');
                    }
                  }
                  if (isCell(wkingrow + 1, wkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, wkingcol - 1, wkingrow + 1))
                    { // seventh spot
                      getPiecePtr(i, j)->move(j, i, wkingcol - 1, wkingrow + 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol - 1, wkingrow + 1, ' ');
                    }
                  }
                  if (isCell(wkingrow - 1, wkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove('p', j, i, wkingcol + 1, wkingrow - 1))
                    { // eigth spot
                      getPiecePtr(i, j)->move(j, i, wkingcol + 1, wkingrow - 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol + 1, wkingrow - 1, ' ');
                    }
                  }
                }
              }
              else
              { // all the other pieces

                if (!(getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, checkcol, checkrow)))
                {
                  int obstacleRow = getPiecePtr(i, j)->getObsRow();
                  char obstacleCol = getPiecePtr(i, j)->getObsCol();
                  if (isCell(obstacleRow, obstacleCol))
                  {
                    if (checkrow == obstacleRow && checkcol == obstacleCol && isWhitePiece(i, j) != isWhitePiece(obstacleRow, obstacleCol))
                    { // if capturable via other pieces

                      getPiecePtr(i, j)->move(j, i, checkcol, checkrow, ' ');
                      if (!(check()))
                      { // if it solves the check then there are moves available
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, checkcol, checkrow, ' ');
                    }
                  }
                }
                else
                { // check if the 8 spots around the king can be moved to by the black pieces to prevent the check
                  if (isCell(wkingrow, wkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcol + 1, wkingrow))
                    { // first spot
                      getPiecePtr(i, j)->move(j, i, wkingcol + 1, wkingrow, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol + 1, wkingrow, ' ');
                    }
                  }
                  else if (isCell(wkingrow, wkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcol - 1, wkingrow))
                    { // second spot
                      getPiecePtr(i, j)->move(j, i, wkingcol - 1, wkingrow, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol - 1, wkingrow, ' ');
                    }
                  }
                  else if (isCell(wkingrow + 1, wkingcol))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcol, wkingrow + 1))
                    { // third spot
                      getPiecePtr(i, j)->move(j, i, wkingcol, wkingrow + 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol, wkingrow + 1, ' ');
                    }
                  }
                  else if (isCell(wkingrow - 1, wkingcol))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcol, wkingrow - 1))
                    { // fourth spot
                      getPiecePtr(i, j)->move(j, i, wkingcol, wkingrow - 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol, wkingrow - 1, ' ');
                    }
                  }
                  else if (isCell(wkingrow + 1, wkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcol + 1, wkingrow + 1))
                    { // fifth spot
                      getPiecePtr(i, j)->move(j, i, wkingcol + 1, wkingrow + 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol + 1, wkingrow + 1, ' ');
                    }
                  }
                  else if (isCell(wkingrow - 1, wkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcol - 1, wkingrow - 1))
                    { // sixth spot
                      getPiecePtr(i, j)->move(j, i, wkingcol - 1, wkingrow - 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol - 1, wkingrow - 1, ' ');
                    }
                  }
                  else if (isCell(wkingrow + 1, wkingcol - 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcol - 1, wkingrow + 1))
                    { // seventh spot
                      getPiecePtr(i, j)->move(j, i, wkingcol - 1, wkingrow + 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol - 1, wkingrow + 1, ' ');
                    }
                  }
                  else if (isCell(wkingrow - 1, wkingcol + 1))
                  {
                    if (getPiecePtr(i, j)->isValidMove(getPiece(i, j), j, i, wkingcol + 1, wkingrow - 1))
                    { // eigth spot
                      getPiecePtr(i, j)->move(j, i, wkingcol + 1, wkingrow - 1, ' ');
                      if (!(check()))
                      {
                        bmoves++;
                      }
                      getPiecePtr(checkrow, checkcol)->revertMove(j, i, wkingcol + 1, wkingrow - 1, ' ');
                    }
                  }
                }
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
