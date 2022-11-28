#include <iostream>
#include <vector>
#include "board.h"
#include <sstream>
#include "textob.h"
#include "decorator.h"
#include "pawn.h"
using std::cout;
using std::endl;


int main() {
  std::vector<Observer*> toDelete;
  Board *b = new Board;
  std::string command;
  while (getline(std::cin, command)) {
    std::istringstream sock{command};
    sock >> command;
    if (command == "game") {
      Observer *ob1 = new TextOb{b};
      toDelete.push_back(ob1);
      b->boardInit();
      b->updateBoards();
    } else if (command == "move") {
      char oldCol;
      int oldRow;
      char newCol;
      int newRow;
      sock >> oldCol;
      sock >> oldRow;
      sock >> newCol;
      sock >> newRow;
      b->move(oldCol, oldRow, newCol, newRow);
      b->updateBoards();
    } else if (command == "resign") {

    } else {

    }
  }
  for(auto &ob : toDelete) delete ob;
}
