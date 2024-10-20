#include "../include/Game.h"
#include <iostream>

Game::Game() : board(), currentPlayer(true) {}

void Game::start() {
    board.printBoard();
    while (true) {
        std::cout << (currentPlayer ? "White" : "Black") << "'s turn.\n";
        std::cout << "Enter move (x1 y1 x2 y2): ";
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        if (makeMove(x1, y1, x2, y2)) {
            board.printBoard();
            currentPlayer = !currentPlayer;
        } else {
            std::cout << "Invalid move! Try again.\n";
        }
    }
}

bool Game::makeMove(int x1, int y1, int x2, int y2) {
    Piece* piece = board.getPiece(x1, y1);
    if (!piece || piece->isWhite() != currentPlayer) return false;
    if (!piece->isValidMove(x1, y1, x2, y2, board)) return false;
    board.movePiece(x1, y1, x2, y2);
    return true;
}
