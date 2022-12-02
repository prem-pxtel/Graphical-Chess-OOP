#include <iostream>
#include <vector>
#include <sstream>
#include "board.h"
#include "piece.h"
#include "textob.h"
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
    } else if (command == "resign") {

    } else if (command == "setup") {

    } else continue;
  }
  for(auto &ob : toDelete) delete ob;
}
