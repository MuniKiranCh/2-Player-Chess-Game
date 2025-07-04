#include "King.h"
#include "../../include/Board.h"

King::King(bool isWhite) : Piece(isWhite) {}

bool King::isValidMove(int x1, int y1, int x2, int y2, const Board& board) const {
    // King moves one square in any direction (horizontally, vertically, or diagonally)
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

char King::getSymbol() const {
    return isWhite() ? 'K' : 'k';
}
