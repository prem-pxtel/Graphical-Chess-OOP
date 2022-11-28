#include <iostream>
#include "textob.h"
#include "studio.h"
#include "asciiart.h"
using std::cout;

TextOb::TextOb(Studio *s, int t, int b, int l, int r) 
  : subject{s}, t{t}, b{b}, l{l}, r{r} {
  subject->attach(this);
}

void TextOb::notify() {
  cout << '+';
  for (int j = l; j <= r; ++j) cout << '-';
  cout << '+' << std::endl;
  for (int i = t; i <= b; ++i) {
    cout << '|';
    for (int j = l; j <= r; ++j) {
      cout << subject->getState(i, j);
    }
    cout << '|' << std::endl;
  }
  cout << '+';
  for (int j = l; j <= r; ++j) cout << '-';
  cout << '+' << std::endl;
}

TextOb::~TextOb() {
  subject->detach(this);
}
