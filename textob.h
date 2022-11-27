#ifndef TEXTOB_H
#define TEXTOB_H
#include "observer.h"
#include "board.h"

class TextOb : public Observer {
  Board *subject;
 public:
  TextOb(Board *b); 
  void notify() override;
  ~TextOb();
};

#endif
