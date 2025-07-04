#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite);
    bool isValidMove(int x1, int y1, int x2, int y2, const Board& board) const override;
    char getSymbol() const override;
    bool isEnPassantMove(int x1, int y1, int x2, int y2, const Board& board) const; // Check if move is en passant
};

#endif // PAWN_H
