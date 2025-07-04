#include "King.h"
#include "../../include/Board.h"

King::King(bool isWhite) : Piece(isWhite) {}

bool King::isValidMove(int x1, int y1, int x2, int y2, const Board& board) const {
    // Check if this is a castling move
    if (isCastlingMove(x1, y1, x2, y2)) {
        // Determine if it's king-side or queen-side castling
        bool isKingSide = (y2 > y1);
        return board.canCastle(isWhite(), isKingSide);
    }
    
    // Regular king move: one square in any direction
    if (abs(x2 - x1) > 1 || abs(y2 - y1) > 1) {
        return false;
    }
    
    // Check if destination has own piece
    Piece* destPiece = board.getPiece(x2, y2);
    if (destPiece && destPiece->isWhite() == isWhite()) {
        return false;
    }
    
    // Check if destination square is under attack (king cannot move into check)
    if (board.isSquareUnderAttack(x2, y2, !isWhite())) {
        return false;
    }
    
    return true;
}

bool King::isCastlingMove(int x1, int y1, int x2, int y2) const {
    // Castling: king moves 2 squares horizontally from starting position
    if (x1 != x2) return false; // Must stay on same rank
    
    // White king starts at (7, 4), Black king starts at (0, 4)
    int startY = isWhite() ? 4 : 4;
    int startX = isWhite() ? 7 : 0;
    
    // Must be at starting position
    if (x1 != startX || y1 != startY) return false;
    
    // Must move exactly 2 squares horizontally
    if (abs(y2 - y1) != 2) return false;
    
    return true;
}

char King::getSymbol() const {
    return isWhite() ? 'K' : 'k';
}
