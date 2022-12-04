#include <iostream>
#include <vector>
#include <sstream>
#include "board.h"
#include "piece.h"
#include "textob.h"
#include "pawn.h"
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

int main() {
  Board *b = new Board;
  std::vector<Observer*> toDelete;
  bool whiteTurn = true;
  bool player1human;
  bool player2human;
  std::string command;
  while (getline(std::cin, command)) {
    bool alreadymoved = false;
    std::istringstream input{command};
    input >> command;
    if (command == "game") {
      std::string player1, player2;
      input >> player1;
      input >> player2;
      if (player1 == "human") player1human = true;
      else if (player1 == "computer") player1human = false;
      else {
        cout << "Invalid Player Type." << endl;
        continue;
      }
      if (player2 == "human") player2human = true;
      else if (player2 == "computer") player2human = false;
      else {
        cout << "Invalid Player Type." << endl;
        continue;
      }
      Observer *ob1 = new TextOb{b};
      toDelete.push_back(ob1);
      b->updateBoards();
      cout << "Player 1's Turn" << endl;
    } else if (command == "move") {
      if ((whiteTurn && player1human) 
          || (!whiteTurn && player2human)) {
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
          if (whiteTurn) {
            if (!b->isWhitePiece(invertRow(oldRow), oldCol)) 
            throw InvalidMove{};
            if(b->whitecheck == true) {
              b->getPiecePtr(invertRow(oldRow), oldCol)
                ->move(oldCol, invertRow(oldRow), newCol, 
                       invertRow(newRow), promo);
              b->check();
              if (b->whitecheck == true) { // revert move here.
              b->getPiecePtr(invertRow(newRow), newCol)
                ->revertMove(oldCol, invertRow(oldRow), newCol, 
                             invertRow(newRow), promo);
                b->updateBoards();
                throw InvalidMove{};
              } else {
                b->updateBoards();
                alreadymoved = true;
              }           
            }
          } else {
            if (b->isWhitePiece(invertRow(oldRow), oldCol)) 
              throw InvalidMove{};
            if (b->blackcheck == true) {
              b->getPiecePtr(invertRow(oldRow), oldCol)
                ->move(oldCol, invertRow(oldRow), newCol, 
                       invertRow(newRow), promo);
              ++b->curTurn;
              b->check();
              if (b->blackcheck == true) { // revert move here.
                b->getPiecePtr(invertRow(newRow), newCol)
                ->revertMove(oldCol, invertRow(oldRow), newCol, 
                             invertRow(newRow), promo);
                b->updateBoards();
                throw InvalidMove{};
              } else {
                b->updateBoards();
                alreadymoved = true;
              }                    
            }
          }
          if (!alreadymoved) {
            b->getPiecePtr(invertRow(oldRow), oldCol)
            ->move(oldCol, invertRow(oldRow), newCol, 
                   invertRow(newRow), promo);
            ++b->curTurn;
            b->updateBoards();
            if (b->check()) {
              if (b->checkmate()) {
                break;
              } else {
                b->check();
              }
            }
          }
          if (whiteTurn) {
            cout << "Player 2's Turn" << endl;
            whiteTurn = false;
          } else {
            cout << "Player 1's Turn" << endl;
            whiteTurn = true;
          }
        } catch (InvalidMove i) {
          cout << i.errMsg << endl;
          --b->curTurn;
        }
      } else { // Computer's Turn


      }
    } else if (command == "resign") {
      if (whiteTurn) {
        cout << "Black Wins!" << endl;
        ++b->blackwins;
      } else {
        cout << "White Wins!" << endl;
        ++b->whitewins;
      }
    } else if (command == "setup") {

    } else {
      cout << "Invalid Command." << endl;
    }
  }
  cout << "Final Score:" << endl;
  cout << "White: " << b->whitewins << endl;
  cout << "Black: " << b->blackwins << endl;

  for (auto &ob : toDelete) delete ob;
//  delete b; (causes Segmentation Fault at end of program)
}
