#include "studio.h"
#include "asciiart.h"
#include "filledbox.h"
#include "blinkingbox.h"
#include "movingbox.h"
#include "maskbox.h"
#include "subject.h"

void Studio::reset() { ticks = 0; }

void Studio::render() {
  notifyObservers();
  ++ticks;
}

void Studio::animate(int numTicks) {
  for (int i = 0; i < numTicks; ++i) render();
}

char Studio::getState(int row, int col) const {
  return thePicture->charAt(row, col, ticks);
}

Studio::~Studio() { delete thePicture; }
