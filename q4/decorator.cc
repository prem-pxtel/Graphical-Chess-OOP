#include "decorator.h"

Decorator::Decorator(AsciiArt *canvas) : canvas{canvas} {}

Decorator::~Decorator() { delete canvas; }
