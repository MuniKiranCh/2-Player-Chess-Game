#include "Knight.h"
#include "../../include/Board.h"

Knight::Knight(bool isWhite) : Piece(isWhite) {}

bool Knight::isValidMove(int x1, int y1, int x2, int y2, const Board& board) const {
    // Knight's unique move logic (L-shape)
    return (abs(x2 - x1) == 2 && abs(y2 - y1) == 1) || (abs(x2 - x1) == 1 && abs(y2 - y1) == 2);
}

char Knight::getSymbol() const {
    return isWhite() ? 'N' : 'n';
}
