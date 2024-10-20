#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(bool isWhite); // Constructor declaration

    bool isValidMove(int x1, int y1, int x2, int y2, const Board& board) const override; // Move validation declaration
    char getSymbol() const override; // Symbol function declaration

private:
    // Declare isPathBlocked as a private helper method
    bool isPathBlocked(int x1, int y1, int x2, int y2, const Board& board) const;
};

#endif // QUEEN_H
