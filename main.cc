#include <iostream>
#include <vector>
#include "board.h"
#include <sstream>
#include "textob.h"
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
      cout << b << endl;
      Observer *ob1 = new TextOb{b};
      toDelete.push_back(ob1);
    } else if (command == "move") {
      
      b->updateBoards();
    } else if (command == "resign") {

    } else {

    }
  }
  for(auto &ob : toDelete) delete ob;
}
