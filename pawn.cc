#include <iostream>
#include "pawn.h"
#include "cell.h"
#include "decorator.h"
#include "board.h"

Pawn::Pawn(Board *b, int row, char col, bool colour)
    : Decorator{b}, row{row}, col{col}, colour{colour} {}

void Pawn::move() {
    
}
void Pawn::capture() {

}
void Pawn::promote() {

}
void Pawn::check() {

}
void Pawn::checkmate() {

}
void Pawn::stalemate() {

}
