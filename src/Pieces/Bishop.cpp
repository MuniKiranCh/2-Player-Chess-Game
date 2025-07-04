#include "Bishop.h"
#include "../../include/Board.h"

Bishop::Bishop(bool isWhite) : Piece(isWhite) {}

bool Bishop::isValidMove(int x1, int y1, int x2, int y2, const Board& board) const {
    // Bishop moves only diagonally
    if (abs(x2 - x1) != abs(y2 - y1)) {
        return false;
    }
    
    // Check if destination has own piece
    Piece* destPiece = board.getPiece(x2, y2);
    if (destPiece && destPiece->isWhite() == isWhite()) {
        return false;
    }
    
    // Check if path is blocked
    return !isPathBlocked(x1, y1, x2, y2, board);
}

char Bishop::getSymbol() const {
    return isWhite() ? 'B' : 'b';
}

bool Bishop::isPathBlocked(int x1, int y1, int x2, int y2, const Board& board) const {
    int stepX = (x2 > x1) ? 1 : -1;
    int stepY = (y2 > y1) ? 1 : -1;
    
    for (int i = 1; i < abs(x2 - x1); ++i) {
        if (board.getPiece(x1 + i * stepX, y1 + i * stepY) != nullptr) {
            return true; // Path is blocked
        }
    }
    return false; // Path is clear
}