#include "Queen.h"
#include "../../include/Board.h"

Queen::Queen(bool isWhite) : Piece(isWhite) {}

bool Queen::isValidMove(int x1, int y1, int x2, int y2, const Board& board) const {
    // Queen moves in straight lines (like rook) or diagonally (like bishop)
    if (x1 != x2 && y1 != y2 && abs(x2 - x1) != abs(y2 - y1)) {
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

char Queen::getSymbol() const {
    return isWhite() ? 'Q' : 'q';
}

bool Queen::isPathBlocked(int x1, int y1, int x2, int y2, const Board& board) const {
    int stepX = (x2 > x1) ? 1 : (x2 < x1 ? -1 : 0); // Determine X direction (0 if x1 == x2)
    int stepY = (y2 > y1) ? 1 : (y2 < y1 ? -1 : 0); // Determine Y direction (0 if y1 == y2)
    int distance = std::max(abs(x2 - x1), abs(y2 - y1)); // Calculate the number of squares to move

    // Check every square along the path
    for (int i = 1; i < distance; ++i) {
        if (board.getPiece(x1 + i * stepX, y1 + i * stepY) != nullptr) {
            return true; // Path is blocked
        }
    }
    return false; // Path is clear
}
