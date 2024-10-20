#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
    Knight(bool isWhite); // Constructor declaration

    bool isValidMove(int x1, int y1, int x2, int y2, const Board& board) const override; // Move validation declaration
    char getSymbol() const override; // Symbol function declaration
};

#endif // KNIGHT_H
