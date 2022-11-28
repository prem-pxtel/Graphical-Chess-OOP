#include <iostream>
#include "asciiart.h"
#include "blank.h"
#include "studio.h"
#include <vector>
#include <memory>
#include "filledbox.h"
#include "blinkingbox.h"
#include "movingbox.h"
#include "maskbox.h"
#include "textob.h"
#include "graphicalob.h"
#include "window.h"

std::vector<Observer*> toDelete;

int main () {
  AsciiArt *canvas = new Blank;

  Studio s{canvas};
  std::string command;

  while (std::cin >> command) {
    if (command == "render") {
      s.render();
    }
    else if (command == "animate") {
      int n;
      std::cin >> n;
      s.animate(n);
    }
    else if (command == "reset") {
      s.reset();
    }
    else if (command == "filledbox") {
      int top, bottom, left, right;
      char what;
      std::cin >> top >> bottom >> left >> right >> what;
      canvas = new FilledBox{canvas, top, bottom, left, right, what};
      s.picture() = canvas;
    }
    else if (command == "blinkingbox") {
      int top, bottom, left, right;
      char what;
      std::cin >> top >> bottom >> left >> right >> what;
      canvas = new BlinkingBox{canvas, top, bottom, left, right, what};
      s.picture() = canvas;
    }
    else if (command == "movingbox") {
      int top, bottom, left, right;
      char what, dir;
      std::cin >> top >> bottom >> left >> right >> what >> dir;
      canvas = new MovingBox{canvas, top, bottom, left, right, what, dir};
      s.picture() = canvas;
    }
    else if (command == "maskbox") {
      int top, bottom, left, right;
      char what;
      std::cin >> top >> bottom >> left >> right >> what;
      canvas = new MaskBox{canvas, top, bottom, left, right, what};
      s.picture() = canvas;
    }
    else if (command == "addtext") {
      int top, bottom, left, right;
      std::cin >> top >> bottom >> left >> right;
      Observer* ob1 = new TextOb{&s, top, bottom, left, right};
      toDelete.push_back(ob1);
    }
    else if (command == "addgraphics") {
      int top, bottom, left, right;
      std::cin >> top >> bottom >> left >> right;
      Observer* ob2 = new GraphicalOb{&s, top, bottom, left, right};
      toDelete.push_back(ob2);
    }
  }
  for(auto &ob : toDelete) delete ob;
}
