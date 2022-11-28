#include "decorator.h"
#include "board.h"

Decorator::Decorator(Board *b) : b{b} {}

Decorator::~Decorator() { delete b; }
