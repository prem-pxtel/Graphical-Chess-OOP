#include <iostream>
#include "textob.h"
#include "board.h"
using std::cout;
using std::endl;

TextOb::TextOb(Board *b) 
  : subject{b} {
  subject->attach(this);
}

void TextOb::notify() {
  cout << subject << endl;
}

TextOb::~TextOb() {
  subject->detach(this);
}
