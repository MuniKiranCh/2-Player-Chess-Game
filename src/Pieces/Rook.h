#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(bool isWhite);
    bool isValidMove(int x1, int y1, int x2, int y2, const Board& board) const override;
    char getSymbol() const override;
};

#endif // ROOK_H
