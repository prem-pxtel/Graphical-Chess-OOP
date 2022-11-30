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
      b->getPiecePtr(oldRow, oldCol)->move(oldCol, b->invertRow(oldRow),
                                           newCol, b->invertRow(newRow));
      b->updateBoards();
    } else if (command == "resign") {

    } else {

    }
  }
  for(auto &ob : toDelete) delete ob;
}
