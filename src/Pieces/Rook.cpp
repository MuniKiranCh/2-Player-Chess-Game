#include "Rook.h"
#include "../../include/Board.h"

Rook::Rook(bool isWhite) : Piece(isWhite) {}

bool Rook::isValidMove(int x1, int y1, int x2, int y2, const Board& board) const {
    // Rook moves only horizontally or vertically
    if (x1 != x2 && y1 != y2) {
        return false;
    }
    
    // Check if destination has own piece
    Piece* destPiece = board.getPiece(x2, y2);
    if (destPiece && destPiece->isWhite() == isWhite()) {
        return false;
    }
    
    if (x1 == x2) { // Vertical move
        int start = std::min(y1, y2) + 1;
        int end = std::max(y1, y2);
        for (int y = start; y < end; ++y) {
            if (board.getPiece(x1, y) != nullptr) {
                return false; // Blocked by another piece
            }
        }
        return true;
    } else if (y1 == y2) { // Horizontal move
        int start = std::min(x1, x2) + 1;
        int end = std::max(x1, x2);
        for (int x = start; x < end; ++x) {
            if (board.getPiece(x, y1) != nullptr) {
                return false; // Blocked by another piece
            }
        }
        return true;
    }
    return false; // Invalid move
}

char Rook::getSymbol() const {
    return isWhite() ? 'R' : 'r'; // Return uppercase for white, lowercase for black
}
