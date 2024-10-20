#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(bool isWhite);
    bool isValidMove(int x1, int y1, int x2, int y2, const Board& board) const override;
    char getSymbol() const override;
};

#endif // PAWN_H
