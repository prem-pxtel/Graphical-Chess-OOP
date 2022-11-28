#ifndef GRAPHICALOB_H
#define GRAPHICALOB_H
#include "observer.h"
#include "studio.h"
#include "window.h"

class GraphicalOb : public Observer {
  Studio *subject;
  Xwindow *window;
  int t;
  int b;
  int l;
  int r;
 public:
  GraphicalOb(Studio *s, int t, int b, int l, int r); 
  void notify() override;
  ~GraphicalOb();
};

#endif
