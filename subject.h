#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  virtual char getPiece(int row, char col) const = 0;
  virtual void setPiece(int row, char col, char p) = 0;
  virtual ~Subject() = default;
};

#endif
