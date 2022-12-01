#include <iostream>
#include <vector>
#include <sstream>
#include "board.h"
#include "piece.h"
#include "textob.h"
using std::cout;
using std::endl;

int main() {
  std::vector<Observer*> toDelete;
  Board *b = new Board;
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
      input >> oldCol;
      input >> oldRow;
      input >> newCol;
      input >> newRow;
      if (whiteTurn) {
        if (!b->isWhitePiece(b->invertRow(oldRow), oldCol)) continue;
        b->getPiecePtr(b->invertRow(oldRow), oldCol)
         ->move(oldCol, b->invertRow(oldRow), newCol, b->invertRow(newRow));
        b->updateBoards();
        whiteTurn = false;
        cout << "Player 2's Turn" << endl;
      } else {
        if (b->isWhitePiece(b->invertRow(oldRow), oldCol)) continue;
        b->getPiecePtr(b->invertRow(oldRow), oldCol)
         ->move(oldCol, b->invertRow(oldRow), newCol, b->invertRow(newRow));
        b->updateBoards();
        whiteTurn = true;
        cout << "Player 1's Turn" << endl;
      }
    } else if (command == "resign") {

    } else if (command == "setup") {

    } else continue;
  }
  for(auto &ob : toDelete) delete ob;
}
