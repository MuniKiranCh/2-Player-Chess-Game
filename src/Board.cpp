#include "../include/Board.h"
#include "Pieces/Pawn.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"
#include "Pieces/Bishop.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"
#include <iostream>

Board::Board() {
    resetBoard();
}

void Board::resetBoard() {
    for (auto &row : board) {
        row.fill(nullptr); // Initialize all squares to nullptr
    }
    setupPieces();
}

void Board::setupPieces() {
    for (int i = 0; i < 8; ++i) {
        board[1][i] = new Pawn(true);  // White Pawns
        board[6][i] = new Pawn(false); // Black Pawns
    }

    board[0][0] = new Rook(true); board[0][7] = new Rook(true);
    board[7][0] = new Rook(false); board[7][7] = new Rook(false);

    board[0][1] = new Knight(true); board[0][6] = new Knight(true);
    board[7][1] = new Knight(false); board[7][6] = new Knight(false);

    board[0][2] = new Bishop(true); board[0][5] = new Bishop(true);
    board[7][2] = new Bishop(false); board[7][5] = new Bishop(false);

    board[0][3] = new Queen(true); board[0][4] = new King(true);
    board[7][3] = new Queen(false); board[7][4] = new King(false);
}

void Board::printBoard() const {
    std::cout << "  0 1 2 3 4 5 6 7\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < 8; ++j) {
            if (board[i][j])
                std::cout << board[i][j]->getSymbol() << " ";
            else
                std::cout << "- ";
        }
        std::cout << "\n";
    }
}

Piece* Board::getPiece(int x, int y) const {
    return board[x][y];
}

void Board::movePiece(int x1, int y1, int x2, int y2) {
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = nullptr;
}
