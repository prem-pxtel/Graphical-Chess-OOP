#include <iostream>
#include "graphicalob.h"
#include "window.h"

GraphicalOb::GraphicalOb(Board *b) 
  : b{b} {
  int cellWidth = 50;
  window = new Xwindow{cellWidth * 8, cellWidth * 8};
  b->attach(this);
}

void GraphicalOb::notify() {
  int cellWidth = 50;
  int xOffset = 22;
  int yOffset = 29;
  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      char cur = b->getPiece(row + 1, col + 'a');
      std::string pieceChar;
      pieceChar += cur;
      int colour;
      if ((row + col) % 2 == 0) colour = Xwindow::White;
      else colour = Xwindow::Green;
      window->fillRectangle(cellWidth * col, cellWidth * row, 
                            cellWidth, cellWidth, colour);
      if (cur != ' ' && cur != '_') {
        window->drawString(cellWidth * col + xOffset, 
                           cellWidth * row + yOffset, pieceChar);
      }
    }
  }
}

GraphicalOb::~GraphicalOb() {
  b->detach(this);
  delete window;
}
