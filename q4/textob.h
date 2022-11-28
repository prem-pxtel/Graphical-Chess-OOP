#ifndef TEXTOB_H
#define TEXTOB_H
#include "observer.h"
#include "studio.h"

class TextOb : public Observer {
  Studio *subject;
  int t;
  int b;
  int l;
  int r;
 public:
  TextOb(Studio* s, int t, int b, int l, int r); 
  void notify() override;
  ~TextOb();
};

#endif
