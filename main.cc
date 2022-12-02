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
  std::string command;
  while (getline(std::cin, command)) {
    std::istringstream input{command};
    input >> command;
    if (command == "game") {
      Observer *ob1 = new TextOb{b};
      toDelete.push_back(ob1);
      b->updateBoards();
      cout << "Player 1's Turn" << endl;
    } else if (command == "move") {
      char oldCol, newCol;
      int oldRow, newRow;
      char promo = ' ';
      input >> oldCol;
      input >> oldRow;
      input >> newCol;
      input >> newRow;
      input >> promo;

      if (('a' <= oldCol && oldCol <= 'h') && (1 <= oldRow && oldRow <= 8)
          && ('a' <= newCol && newCol <= 'h') && (1 <= newRow && newRow <= 8)) {
        try {
          b->getPiecePtr(invertRow(oldRow), oldCol)
            ->move(oldCol, invertRow(oldRow), newCol, 
                          invertRow(newRow), promo);
          b->updateBoards();
          b->check();
        } catch (InvalidMove) {
          cout << "Invalid Move. You are retarded." << endl;
        }
      } else {
        cout << "Invalid Move." << endl;
      }
    }
    

/*      if (whiteTurn) {
        if (!b->isWhitePiece(invertRow(oldRow), oldCol)) continue;
        b->getPiecePtr(invertRow(oldRow), oldCol)
         ->move(oldCol, invertRow(oldRow), newCol, invertRow(newRow));
        b->updateBoards();
        whiteTurn = false;
        cout << "Player 2's Turn" << endl;
        b->check();
      } else {
        if (b->isWhitePiece(invertRow(oldRow), oldCol)) continue;
        b->getPiecePtr(invertRow(oldRow), oldCol)
         ->move(oldCol, invertRow(oldRow), newCol, invertRow(newRow));
        b->updateBoards();
        whiteTurn = true;
        cout << "Player 1's Turn" << endl;
        b->check();
      }
*/
     else if (command == "resign") {

    } else if (command == "setup") {

    } else continue;
  }
  for(auto &ob : toDelete) delete ob;
  delete b;
}
