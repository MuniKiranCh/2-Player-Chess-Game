#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    King(bool isWhite); // Constructor declaration

    bool isValidMove(int x1, int y1, int x2, int y2, const Board& board) const override; // Move logic declaration
    char getSymbol() const override; // Symbol function declaration
};

#endif // KING_H
