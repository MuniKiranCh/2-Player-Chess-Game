#include "Knight.h"
#include "../../include/Board.h"

Knight::Knight(bool isWhite) : Piece(isWhite) {}

bool Knight::isValidMove(int x1, int y1, int x2, int y2, const Board& board) const {
    // Knight's unique move logic (L-shape)
    if (!((abs(x2 - x1) == 2 && abs(y2 - y1) == 1) || (abs(x2 - x1) == 1 && abs(y2 - y1) == 2))) {
        return false;
    }
    
    // Check if destination has own piece
    Piece* destPiece = board.getPiece(x2, y2);
    if (destPiece && destPiece->isWhite() == isWhite()) {
        return false;
    }
    
    return true; // Knight can jump over pieces, so no path checking needed
}

char Knight::getSymbol() const {
    return isWhite() ? 'N' : 'n';
}
