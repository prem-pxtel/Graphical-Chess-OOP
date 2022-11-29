#include <iostream>
#include <vector>
#include "board.h"
#include "pawn.h"
#include "rook.h"
#include <string>
#include <sstream>
#include "textob.h"
using std::cout;
using std::endl;

int main() {
  std::vector<Observer*> toDelete;
  Board *b = new Board;
  Pawn *p = new Pawn{b};
  Rook *r = new Rook{b};
  std::string command;
  while (getline(std::cin, command)) {
    std::istringstream input{command};
    input >> command;
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
      input >> oldCol;
      input >> oldRow;
      input >> newCol;
      input >> newRow;
      char piece = b->getPiece(oldRow, oldCol);
      if (piece == 'p' || piece == 'P') {
        p->move(oldCol, oldRow, newCol, newRow);
      } else if (piece == 'r' || piece == 'R') {
        r->move(oldCol, oldRow, newCol, newRow);
      }
      b->updateBoards();
    } else if (command == "resign") {

    } else {

    }
  }
  for(auto &ob : toDelete) delete ob;
}
