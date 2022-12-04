#include <iostream>
#include "graphicalob.h"
#include "window.h"

GraphicalOb::GraphicalOb(Board *b) 
  : b{b} {
  window = new Xwindow{50 * 8, 50 * 8};
  b->attach(this);
}

void GraphicalOb::notify() {
  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      char cur = b->getPiece(row + 1, col + 'a');
      std::string pieceChar;
      pieceChar += cur;
      int colour;
      if ((row + col) % 2 == 1) colour = Xwindow::White;
      else colour = Xwindow::Green;
      window->fillRectangle(50 * col, 50 * row, 50, 50, colour);
      if (cur != ' ' && cur != '_') {
        window->drawString(50 * col + 23, 50 * row + 28, pieceChar);
      }
    }
  }
}

GraphicalOb::~GraphicalOb() {
  b->detach(this);
  delete window;
}
