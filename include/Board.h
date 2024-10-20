#ifndef BOARD_H
#define BOARD_H

#include "../src/Pieces/Piece.h"
#include <array>

class Board {
public:
    Board();
    void resetBoard();
    void printBoard() const;
    Piece* getPiece(int x, int y) const;
    void movePiece(int x1, int y1, int x2, int y2);

private:
    std::array<std::array<Piece*, 8>, 8> board;
    void setupPieces();
};

#endif
