#ifndef GRAPHICALOB_H
#define GRAPHICALOB_H
#include "observer.h"
#include "board.h"
#include "window.h"

class GraphicalOb : public Observer {
  Board *b;
  Xwindow *window;
 public:
  GraphicalOb(Board *b); 
  void notify() override;
  ~GraphicalOb();
};

#endif
