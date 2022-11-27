#include <iostream>
#include <vector>
#include "board.h"

int main() {
  Board *b = new Board;
  std::string command;

  while (std::cin >> command) {
    if(command == "game"){
      std::cout << b << std::endl;
    }
  }
}
