#include "Pawn.h"
#include "../../include/Board.h"

Pawn::Pawn(bool isWhite) : Piece(isWhite) {}

bool Pawn::isValidMove(int x1, int y1, int x2, int y2, const Board& board) const {
    int direction = isWhite() ? 1 : -1; // White moves up, black moves down

    // Normal move
    if (x2 == x1 + direction && y1 == y2) {
        return true;
    }
    // First move can move two squares
    if ((isWhite() && x1 == 1 && x2 == 3 && y1 == y2) || (isWhite() == false && x1 == 6 && x2 == 4 && y1 == y2)) {
        return true;
    }
    // Capture move (diagonal)
    if (x2 == x1 + direction && abs(y2 - y1) == 1) {
        return board.getPiece(x2, y2) != nullptr; // Must capture an opponent piece
    }

    return false; // Invalid move
}

char Pawn::getSymbol() const {
    return isWhite() ? 'P' : 'p'; // Return uppercase for white, lowercase for black
}
