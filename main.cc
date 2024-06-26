#include <iostream>
#include <vector>
#include <sstream>
#include "board.h"
#include "piece.h"
#include "textob.h"
#include "pawn.h"
#include "king.h"
#include "bishop.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "blank.h"
#include "graphicalob.h"
using std::cout;
using std::endl;

int invertRow(int oldRow) {
  float middle = 4.5;
  if (1 <= oldRow && oldRow <= 4) {
    return oldRow + (2 * (middle - oldRow));
  } else {
    return oldRow - (2 * (oldRow - middle));
  }
}

bool setup (Board *b) { // handles the entire setup process
  std::string commands;
  bool colourTurn = true;
  b->clearBoard();
  b->updateBoards();
  while (getline(std::cin, commands)) {
    std::istringstream inputs{commands};
    inputs >> commands;
    if (commands == "+") {
      char piece;
      char Col;
      int Row;
      if (!(inputs >> piece && inputs >> Col 
            && inputs >> Row)) {
              cout << "Invalid setup move." << endl;
      } else if (piece != 'p' && piece != 'P' && piece != 'r' && piece != 'R'
      && piece != 'K' && piece != 'k' && piece != 'b' && piece != 'B'
      && piece != 'n' && piece != 'N' && piece != 'q' && piece != 'Q') {
        cout << "Invalid piece." << endl;
      } else if (!(1 <= Row && Row <= 8)||!('a' <= Col && Col <= 'z')) {
        cout << "Invalid move" << endl;
      } else {
        delete b->getPiecePtr(invertRow(Row), Col);
        Row = Row - 1;
        Col = Col - 'a';
        if (piece == 'p' || piece == 'P') {
          b->getBoard()[Row][Col] = new Pawn {piece, b};
        }
        else if (piece == 'r' || piece == 'R') {
          b->getBoard()[Row][Col] = new Rook {piece, b};
        }
        else if (piece == 'K' || piece == 'k') {
          b->getBoard()[Row][Col] = new King {piece, b};
        }
        else if (piece == 'b' || piece == 'B') {
          b->getBoard()[Row][Col] = new Bishop {piece, b};
        }
        else if (piece == 'n' || piece == 'N') {
          b->getBoard()[Row][Col] = new Knight {piece, b};
        }
        else if (piece == 'q' || piece == 'Q') {
          b->getBoard()[Row][Col] = new Queen {piece, b};
        }
        b->updateBoards();
      }
    }
    else if (commands == "-") {
      char Col;
      int Row;
      if (!(inputs >> Col 
            && inputs >> Row)) {
              cout << "Invalid setup move." << endl;
      } else if (!(1 <= Row && Row <= 8)||!('a' <= Col && Col <= 'z')) {
        cout << "Invalid move" << endl;
      } else {
        if (b->isOccupied(Row, Col)) {
          delete b->getPiecePtr(invertRow(Row), Col);
          b->getBoard()[(Row - 1)][Col - 'a'] = new Blank {' ', b};
          b->removePiece(invertRow(Row), Col); // sets to either " " or "_"
          b->updateBoards();
        }
      }
    } else if (commands == "=") {
      std::string colour;
      if (!(inputs >> colour)) {
        cout << "Invalid color." << endl;
      } else if (colour != "black" && colour != "white") {
        cout << "Invalid color." << endl;
      } else {
        if (colour == "black") {
          colourTurn = false;
        } else {
          colourTurn = true;
        }
      }
    } else if (commands == "done") {
      char value = 'z';
      int blackking = 0;
      int whiteking = 0;
      int pawns = 0;
      for (int i = 1; i <= 8; i++) {
        for (char j = 'a'; j <= 'h'; j++) {
          value = b->getPiece(i, j);
          if (value == 'k') {
            blackking++;
          }
          else if (value == 'K') {
            whiteking++;
          }
          else if (((i == 1 && value == 'p') || (i == 1 && value == 'P')) 
                  || ((i == 8 && value == 'p') || (i == 8 && value == 'P'))) {
                    pawns++;
          }
        }
      }
        if (blackking == 1 && whiteking == 1 && pawns == 0) {
          b->check();
          if (!(b->whitecheck) && !(b->blackcheck)) {
            cout << "110" << endl;
            break;
          }
        }
        else {
          cout << "Please recheck your king count, if there are any pawns in the first and last row, or if any King is in check" << endl;
        }
    }
    else {
      cout << "Invalid Command." << endl;
    }
  }
  return colourTurn;
}

int main() {
  Board *b = new Board;
  std::vector<Observer*> toDelete;
  bool gameInProgress = false;
  b->turn = true;
  bool setupFinished = false;
  bool player1human;
  bool player2human;
  std::string command;
  while (getline(std::cin, command)) {
    bool alreadymoved = false;
    std::istringstream input{command};
    input >> command;
    if (command == "game") {
      gameInProgress = true;
      std::string player1, player2;
      input >> player1;
      input >> player2;
      if (player1 == "human") player1human = true;
      else if (player1 == "computer[1]") player1human = false;
      else if (player1 == "computer[2]" || player1 == "computer[3]" ||
               player1 == "computer[4]") {
        cout << "This AI level not currently supported. Please use level 1 for now." << endl;
        continue;     
      } else {
        cout << "Invalid Player Type." << endl;
        continue;
      }
      if (player2 == "human") player2human = true;
      else if (player2 == "computer[1]") player2human = false;
      else if (player2 == "computer[2]" || player2 == "computer[3]" ||
               player2 == "computer[4]") {
        cout << "This AI level not currently supported. Please use level 1 for now." << endl;
        continue;     
      } else {
        cout << "Invalid Player Type." << endl;
        continue;
      }
      if (!(setupFinished)) {
        b->init();
        for (auto &ob : toDelete) delete ob;
        Observer *ob1 = new TextOb{b};
        Observer *ob2 = new GraphicalOb{b};
        toDelete.push_back(ob1);
        toDelete.push_back(ob2);
        b->updateBoards();
      } else {
        b->updateBoards();
      }
      cout << "Player 1's Turn" << endl;
    } else if (command == "move") {
      if ((b->turn && player1human) 
          || (!b->turn && player2human)) {
        char oldCol, newCol;
        int oldRow, newRow;
        char promo = ' ';
        try {
          if (!(input >> oldCol && input >> oldRow 
              && input >> newCol && input >> newRow)) {            
            throw InvalidMove{};
          }
          input >> promo;
          if (!(promo == 'r' || promo == 'R' || promo == 'b' || promo == 'B'
              || promo == 'q' || promo == 'Q' || promo == ' ')) {
            throw InvalidMove{};
          }
          if (b->turn) {
            if (!b->isWhitePiece(invertRow(oldRow), oldCol)) {
            throw InvalidMove{};
            }
            if (b->whitecheck == true) {
              b->lastMoveOldRow = invertRow(oldRow);
              b->lastMoveOldCol = oldCol;
              b->lastMoveNewRow = invertRow(newRow);
              b->lastMoveNewCol = newCol;
              b->firstMoveOld = b->getPiecePtr(invertRow(oldRow), oldCol)
                                 ->firstMove;
              b->getPiecePtr(invertRow(oldRow), oldCol)
                ->move(oldCol, invertRow(oldRow), newCol, 
                       invertRow(newRow), promo);
              ++b->curTurn;
              bool undidLastVal = b->undidLast;
              b->check();
              if (b->whitecheck == true) { // revert move here.
              b->getPiecePtr(invertRow(newRow), newCol)
                ->revertMove(oldCol, invertRow(oldRow), newCol, 
                             invertRow(newRow), promo);
                --b->curTurn;
                b->undidLast = undidLastVal;
                b->updateBoards();
                throw InvalidMove{};
              } else {
                b->updateBoards();
                alreadymoved = true;
              }           
            }
          } else {
            if (b->isWhitePiece(invertRow(oldRow), oldCol)) {
              throw InvalidMove{};
            } 
            if (b->blackcheck == true) {
              b->lastMoveOldRow = invertRow(oldRow);
              b->lastMoveOldCol = oldCol;
              b->lastMoveNewRow = invertRow(newRow);
              b->lastMoveNewCol = newCol;
              b->firstMoveOld = b->getPiecePtr(invertRow(oldRow), oldCol)
                                 ->firstMove;
              b->getPiecePtr(invertRow(oldRow), oldCol)
                ->move(oldCol, invertRow(oldRow), newCol, 
                       invertRow(newRow), promo);
              ++b->curTurn;
              bool undidLastVal = b->undidLast;
              b->check();
              if (b->blackcheck == true) { // revert move here.
                b->getPiecePtr(invertRow(newRow), newCol)
                ->revertMove(oldCol, invertRow(oldRow), newCol, 
                             invertRow(newRow), promo);
                --b->curTurn;
                b->undidLast = undidLastVal;
                b->updateBoards();
                throw InvalidMove{};
              } else {
                b->updateBoards();
                alreadymoved = true;
              }                    
            }
          }
          if (!alreadymoved) {
            b->lastMoveOldRow = invertRow(oldRow);
            b->lastMoveOldCol = oldCol;
            b->lastMoveNewRow = invertRow(newRow);
            b->lastMoveNewCol = newCol;
            b->firstMoveOld = b->getPiecePtr(invertRow(oldRow), oldCol)
                               ->firstMove;
            b->getPiecePtr(invertRow(oldRow), oldCol)
            ->move(oldCol, invertRow(oldRow), newCol, 
                   invertRow(newRow), promo);
            ++b->curTurn;
            b->undidLast = false;
            b->updateBoards();
           if (b->moves()) {
              cout << "Note: There are moves available." << endl;
            } 
            if (b->check()) {
              if (!(b->moves())) {
                cout << "Checkmate! ";
                if (b->turn) {
                  cout << "White Wins!" << endl;
                  ++b->whitewins;
                }
                else {
                  cout << "Black Wins!" << endl;
                  ++b->blackwins;
                }
                b->clear();
                b->init();
                continue;
              } else {
                b->check();
              }
            }
            else {
              if (!(b->moves())) {
                cout << "Stalemate." << endl;
                b->whitewins += 0.5;
                b->blackwins += 0.5;
                b->clear();
                b->init();
                continue;
              }
            }
          }
          if (b->turn) {
            if (b->whitecheck || b->blackcheck) {
              cout << b->colourInCheck << " is in check." << endl;
            }
            cout << "Player 2's Turn" << endl;
            b->turn = false;
          } else {
            if (b->whitecheck || b->blackcheck) {
              cout << b->colourInCheck << " is in check." << endl;
            }
            cout << "Player 1's Turn" << endl;
            b->turn = true;
          }
        } catch (InvalidMove i) {
          cout << i.errMsg << endl;
          --b->curTurn;
        }
      } else { // Computer's Turn
        try {
          b->levelone();
          b->updateBoards();
          if (b->turn) b->turn = false;
          else b->turn = true;
          if (b->turn) cout << "Player 2's Turn" << endl;
          else cout << "Player 2's Turn" << endl;
          b->undidLast = false;
        } catch (InvalidMove i) {
          b->levelone();
          b->updateBoards();
          if (b->turn) b->turn = false;
          else b->turn = true;
          if (b->turn) cout << "Player 2's Turn" << endl;
          else cout << "Player 2's Turn" << endl;
          b->undidLast = false;
        }
      }
    } else if (command == "undo") {
      if (b->undidLast == false) {
        b->getPiecePtr(b->lastMoveNewRow, b->lastMoveNewCol)->revertMove(b->lastMoveOldCol, b->lastMoveOldRow, b->lastMoveNewCol, b->lastMoveNewRow, ' ');
        b->getPiecePtr(b->lastMoveOldRow, b->lastMoveOldCol)->firstMove = b->firstMoveOld;
        alreadymoved = false;
        b->updateBoards();
        if (b->turn) {
          b->turn = false;
          cout << "Last move undone. Player 2's turn again." << endl;
          b->undidLast = true;
        } else {
          b->turn = true;
          cout << "Last move undone. Player 1's turn again." << endl;
          b->undidLast = true;
        }
      } else {
        cout << "Last move already undone. You can only do this once!" << endl;
        continue;
      } 
    } else if (command == "resign") {
      if (b->turn) {
        cout << "Black Wins!" << endl;
        ++b->blackwins;
        b->clear();
        b->init();
      } else {
        cout << "White Wins!" << endl;
        ++b->whitewins;
        b->clear();
        b->init();
        b->turn = true;
      }
    } else if (command == "setup") { // have empty board and then call helper function
      if (!(gameInProgress)) {
        Observer *ob1 = new TextOb{b};
        Observer *ob2 = new GraphicalOb{b};
        toDelete.push_back(ob1);
        toDelete.push_back(ob2);
        b->turn = setup(b);
        setupFinished = true;
      }
      else {
        throw InvalidMove{};
      }
    } else {
      cout << "Invalid Command." << endl;
    }
  }
  gameInProgress = false;
  cout << "Final Score:" << endl;
  cout << "White: " << b->whitewins << endl;
  cout << "Black: " << b->blackwins << endl;

  for (auto &ob : toDelete) delete ob;
  delete b;
}
