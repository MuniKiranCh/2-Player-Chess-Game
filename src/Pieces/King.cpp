#include "King.h"
#include "../../include/Board.h"

King::King(bool isWhite) : Piece(isWhite) {} // Constructor implementation

bool King::isValidMove(int x1, int y1, int x2, int y2, const Board& board) const {
    // King moves one square in any direction (horizontally, vertically, or diagonally)
    return (abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1);
}

char King::getSymbol() const {
    return isWhite() ? 'K' : 'k';
}
