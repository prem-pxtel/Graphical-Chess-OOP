#include <iostream>
#include "graphicalob.h"
#include "window.h"

GraphicalOb::GraphicalOb(Studio *s, int t, int b, int l, int r) 
  : subject{s}, t{t}, b{b}, l{l}, r{r} {
  window = new Xwindow{(10*(r-l+1)), (10*(b-t+1))};
  subject->attach(this);
}

void GraphicalOb::notify() {
  int colour;
  for (int row = t; row <= b; ++row) {
    for (int col = l; col <= r; ++col) {
      char cur = subject->getState(row, col);
      if ('a' <= cur && cur <= 'z') {
        colour = Xwindow::Red;
      } else if ('A' <= cur && cur <= 'Z') {
        colour = Xwindow::Green;
      } else if ('0' <= cur && cur <= '9') {
        colour = Xwindow::Blue;
      } else if (cur == ' ') {
        colour = Xwindow::White;
      } else {
        colour = Xwindow::Black;
      }
      window->fillRectangle(10 * (col - l), 10 * (row - t), 10, 10, colour);
    }
  }
}

GraphicalOb::~GraphicalOb() {
  subject->detach(this);
  delete window;
}
