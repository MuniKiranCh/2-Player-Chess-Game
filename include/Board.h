#ifndef BOARD_H
#define BOARD_H

#include "../src/Pieces/Piece.h"
#include <array>
#include <vector>
#include <string>

class Board {
public:
    Board();
    Board(const Board& other); // Copy constructor
    ~Board(); // Destructor
    Board& operator=(const Board& other); // Assignment operator
    
    void resetBoard();
    void printBoard() const;
    Piece* getPiece(int x, int y) const;
    void movePiece(int x1, int y1, int x2, int y2);
    
    // New methods for enhanced functionality
    bool isCheck(bool isWhiteKing) const;
    bool isCheckmate(bool isWhiteKing) const;
    bool isStalemate(bool isWhiteKing) const;
    bool hasLegalMoves(bool isWhiteKing) const;
    bool isValidMove(int x1, int y1, int x2, int y2) const;
    void promotePawn(int x, int y, char pieceType);
    std::pair<int, int> findKing(bool isWhiteKing) const;
    bool isSquareUnderAttack(int x, int y, bool byWhite) const;
    std::vector<std::pair<int, int>> getLegalMoves(int x, int y) const;
    bool isGameOver() const;
    std::string getGameStatus() const;

private:
    std::array<std::array<Piece*, 8>, 8> board;
    bool gameOver;
    std::string gameStatus; // "ongoing", "checkmate", "stalemate"
    void setupPieces();
    bool canMoveWithoutLeavingCheck(int x1, int y1, int x2, int y2, bool isWhiteKing) const;
    Piece* createPieceCopy(Piece* original) const; // Helper for copy constructor
};

#endif
