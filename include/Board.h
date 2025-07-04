#ifndef BOARD_H
#define BOARD_H

#include "../src/Pieces/Piece.h"
#include <array>
#include <vector>
#include <string>
#include <set>

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

    // Castling methods
    bool canCastle(bool isWhiteKing, bool isKingSide) const;
    bool performCastling(bool isWhiteKing, bool isKingSide);
    bool hasKingMoved(bool isWhiteKing) const;
    bool hasRookMoved(bool isWhiteKing, bool isKingSide) const;
    
    // En Passant methods
    bool canEnPassant(int x1, int y1, int x2, int y2) const;
    bool performEnPassant(int x1, int y1, int x2, int y2);
    void setEnPassantTarget(int x, int y);
    std::pair<int, int> getEnPassantTarget() const;
    void clearEnPassantTarget();
    
    // AI evaluation
    int evaluatePosition() const;

private:
    std::array<std::array<Piece*, 8>, 8> board;
    bool gameOver;
    std::string gameStatus; // "ongoing", "checkmate", "stalemate"
    
    // Castling tracking
    std::set<std::pair<int, int>> movedPieces; // Track which pieces have moved
    
    // En Passant tracking
    std::pair<int, int> enPassantTarget; // Square where en passant is possible (-1, -1) if none
    
    void setupPieces();
    bool canMoveWithoutLeavingCheck(int x1, int y1, int x2, int y2, bool isWhiteKing) const;
    Piece* createPieceCopy(Piece* original) const; // Helper for copy constructor
    void recordPieceMovement(int x, int y); // Record that a piece has moved
};

#endif
