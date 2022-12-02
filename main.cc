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
    bool alreadymoved = false;
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
      try {
        if (!(input >> oldCol && input >> oldRow 
            && input >> newCol && input >> newRow)) {
          throw InvalidMove{};
        }
        if (!(promo == 'r' || promo == 'R' || promo == 'b' || promo == 'B'
             || promo == 'q' || promo == 'Q' || promo == ' ')) {
          throw InvalidMove {};
        }
        if (whiteTurn) {
          if (!b->isWhitePiece(invertRow(oldRow), oldCol)) 
          throw InvalidMove{};
          if(b->whitecheck == true){
        b->getPiecePtr(invertRow(oldRow), oldCol)
          ->move(oldCol, invertRow(oldRow), newCol, 
                        invertRow(newRow), promo);
        b->updateBoards();
        b->check();
        if(b->whitecheck == true){ // revert move here.
        b->getPiecePtr(invertRow(newRow), newCol)
          ->revertmove(oldCol, invertRow(oldRow), newCol, 
                        invertRow(newRow), promo);
          cout << "no no" << endl;
          throw InvalidMove{};
        }
        else{
          alreadymoved = true;
        }           
        }
        } else {
        if (b->isWhitePiece(invertRow(oldRow), oldCol)) 
          throw InvalidMove{};
        if(b->blackcheck == true){
        b->getPiecePtr(invertRow(oldRow), oldCol)
          ->move(oldCol, invertRow(oldRow), newCol, 
                        invertRow(newRow), promo);
        b->updateBoards();
        b->check();
        if(b->blackcheck == true){ // revert move here.
        b->getPiecePtr(invertRow(newRow), newCol)
          ->revertmove(oldCol, invertRow(oldRow), newCol, 
                        invertRow(newRow), promo);
          cout << "no no" << endl;
          throw InvalidMove{};
        }
        else{
          alreadymoved = true;
        }                    
        }
        }
        if(!alreadymoved){
        b->getPiecePtr(invertRow(oldRow), oldCol)
          ->move(oldCol, invertRow(oldRow), newCol, 
                        invertRow(newRow), promo);
        b->updateBoards();
        b->check();
        }
        if (whiteTurn) {
          cout << "Player 2's Turn" << endl;
          whiteTurn = false;
        } else {
          cout << "Player 1's Turn" << endl;
          whiteTurn = true;
        }
      } catch (InvalidMove) {
        cout << "Invalid Move." << endl;
      }
    } else if (command == "resign") {

    } else if (command == "setup") {

    } else continue;
  }
  for(auto &ob : toDelete) delete ob;
  delete b;
}
