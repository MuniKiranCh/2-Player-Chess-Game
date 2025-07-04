#include "Pawn.h"
#include "../../include/Board.h"

Pawn::Pawn(bool isWhite) : Piece(isWhite) {}

bool Pawn::isValidMove(int x1, int y1, int x2, int y2, const Board& board) const {
    int direction = isWhite() ? -1 : 1; // White moves up (decreasing row), black moves down (increasing row)

    // Check for en passant first
    if (isEnPassantMove(x1, y1, x2, y2, board)) {
        return board.canEnPassant(x1, y1, x2, y2);
    }

    // Normal move (one square forward)
    if (x2 == x1 + direction && y1 == y2) {
        return board.getPiece(x2, y2) == nullptr; // Destination must be empty
    }
    
    // First move can move two squares
    if ((isWhite() && x1 == 6 && x2 == 4 && y1 == y2) || 
        (!isWhite() && x1 == 1 && x2 == 3 && y1 == y2)) {
        // Check if both squares are empty
        int middleX = isWhite() ? 5 : 2;
        return board.getPiece(middleX, y1) == nullptr && 
               board.getPiece(x2, y2) == nullptr;
    }
    
    // Capture move (diagonal)
    if (x2 == x1 + direction && abs(y2 - y1) == 1) {
        Piece* destPiece = board.getPiece(x2, y2);
        return destPiece != nullptr && destPiece->isWhite() != isWhite(); // Must capture opponent piece
    }

    return false; // Invalid move
}

bool Pawn::isEnPassantMove(int x1, int y1, int x2, int y2, const Board& board) const {
    int direction = isWhite() ? -1 : 1;
    
    // En passant: pawn moves diagonally forward to an empty square
    if (x2 == x1 + direction && abs(y2 - y1) == 1) {
        // Destination must be empty
        if (board.getPiece(x2, y2) != nullptr) {
            return false;
        }
        
        // Check if there's an opponent pawn on the same rank that just moved two squares
        auto enPassantTarget = board.getEnPassantTarget();
        if (enPassantTarget.first == x2 && enPassantTarget.second == y2) {
            // Check if there's an opponent pawn on the same file
            Piece* adjacentPawn = board.getPiece(x1, y2);
            if (adjacentPawn && adjacentPawn->getSymbol() == (isWhite() ? 'p' : 'P') && 
                adjacentPawn->isWhite() != isWhite()) {
                return true;
            }
        }
    }
    
    return false;
}

char Pawn::getSymbol() const {
    return isWhite() ? 'P' : 'p'; // Return uppercase for white, lowercase for black
}
