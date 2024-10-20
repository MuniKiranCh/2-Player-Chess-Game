#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(bool isWhite);

    bool isValidMove(int x1, int y1, int x2, int y2, const Board& board) const override;
    char getSymbol() const override;

private:
    // Declare isPathBlocked as a private method
    bool isPathBlocked(int x1, int y1, int x2, int y2, const Board& board) const;
};

#endif // BISHOP_H
