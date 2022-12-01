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
    } else if (command == "move") {
      char oldCol, newCol;
      int oldRow, newRow;
      input >> oldCol;
      input >> oldRow;
      input >> newCol;
      input >> newRow;
      if (whiteTurn) {
        if (b->isWhitePiece(oldRow, oldCol)) continue;
        cout << "Other person's turn" << endl;
      } else {
        if (!b->isWhitePiece(oldRow, oldCol)) continue;
        cout << "Other person's turn" << endl;
      }
      b->getPiecePtr(oldRow, oldCol)->move(oldCol, b->invertRow(oldRow),
                                            newCol, b->invertRow(newRow));
      b->updateBoards();
      if (whiteTurn) whiteTurn = false;
      whiteTurn = true;
    } else if (command == "resign") {

    } else {

    }
  }
  for(auto &ob : toDelete) delete ob;
}
