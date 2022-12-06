#include <iostream>
#include "graphicalob.h"
#include "window.h"

GraphicalOb::GraphicalOb(Board *b) 
  : b{b} {
  int cellWidth = 50;
  int winOffset = 30;
  window = new Xwindow{cellWidth*8 + winOffset*2, cellWidth*8 + winOffset*2};
  b->attach(this);
}

int invert(int oldRow) {
  float middle = 4.5;
  if (1 <= oldRow && oldRow <= 4) {
    return oldRow + (2 * (middle - oldRow));
  } else {
    return oldRow - (2 * (oldRow - middle));
  }
}

void GraphicalOb::notify() {
  int cellWidth = 50;
  int xOffset = 22;
  int yOffset = 29;
  int winOffset = 30;

  for (char col = 0; col < 8; ++col) {
    std::string colNum;
    colNum += col + 'A';
    window->drawString(cellWidth * col + xOffset + winOffset, 
                       winOffset / 2 + 5, colNum);
  }

  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      std::string rowNum;
      rowNum += std::to_string(invert(row + 1));
      window->drawString(winOffset / 2 - 3, 
                         cellWidth * row + yOffset + winOffset, rowNum);
      window->drawString(winOffset +  12 + (cellWidth * 8), 
                         cellWidth * row + yOffset + winOffset, rowNum);
      char cur = b->getPiece(row + 1, col + 'a');
      std::string pieceChar;
      pieceChar += cur;
      int colour;
      if ((row + col) % 2 == 0) colour = Xwindow::White;
      else colour = Xwindow::Orange;
      window->fillRectangle(cellWidth * col + winOffset, 
                            cellWidth * row + winOffset, 
                            cellWidth, cellWidth, colour);
      if (cur != ' ' && cur != '_') {
        window->drawString(cellWidth * col + xOffset + winOffset, 
                           cellWidth * row + yOffset + winOffset, pieceChar);
      }
    }
  }

  for (char col = 0; col < 8; ++col) {
    std::string colNum;
    colNum += col + 'A';
    window->drawString(cellWidth * col + xOffset + winOffset, 
                       cellWidth * 8 + winOffset + 19, colNum);
  }

}

GraphicalOb::~GraphicalOb() {
  b->detach(this);
  delete window;
}
