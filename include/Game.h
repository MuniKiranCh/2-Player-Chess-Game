#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <vector>
#include <string>

enum class AIDifficulty {
    RANDOM,
    GREEDY,
    MINIMAX_1,
    MINIMAX_2,
    MINIMAX_3
};

struct Move {
    int x1, y1, x2, y2;
    std::string notation;
    Move(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {
        notation = std::to_string(x1) + "," + std::to_string(y1) + " to " + 
                   std::to_string(x2) + "," + std::to_string(y2);
    }
};

class Game {
public:
    Game();
    void start();
    void displayHelp() const;
    void setAIOpponent(bool enabled, AIDifficulty difficulty = AIDifficulty::RANDOM);
    void setAIPlaysAs(bool playsAsWhite);
    
    // Save/Load methods
    bool saveGame(const std::string& filename) const;
    bool loadGame(const std::string& filename);
    bool exportPGN(const std::string& filename) const;
    bool importPGN(const std::string& filename);
    std::string getFEN() const;
    bool setFEN(const std::string& fen);
    void displaySaveLoadHelp() const;

private:
    Board board;
    bool currentPlayer; // true = white, false = black
    int moveCount;
    std::vector<Move> moveHistory;
    
    // AI variables
    bool aiEnabled;
    AIDifficulty aiDifficulty;
    bool aiPlaysAsWhite;
    
    // Helper methods
    bool makeMove(int x1, int y1, int x2, int y2);
    bool isValidMove(int x1, int y1, int x2, int y2) const;
    void displayMoveHistory() const;
    void displayGameStatus() const;
    void showLegalMoves(int x, int y) const;
    bool handleSpecialCommands(const std::string& input);
    void makeAIMove();
    int evaluatePosition() const;
    int minimax(Board& board, int depth, int alpha, int beta, bool maximizingPlayer) const;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> getAllLegalMoves(bool forWhite) const;
    void displayAISettings() const;
    
    // Chess notation helpers
    std::string getChessNotation(int x, int y) const;
    std::pair<int, int> parseChessNotation(const std::string& notation) const;
    
    // Game state methods
    bool isGameEnded() const;
    void announceGameEnd() const;
    
    // AI helper methods
    std::pair<std::pair<int, int>, std::pair<int, int>> getRandomMove() const;
    std::pair<std::pair<int, int>, std::pair<int, int>> getGreedyMove() const;
    std::pair<std::pair<int, int>, std::pair<int, int>> getMinimaxMove(int depth) const;
    int getPieceValue(char piece) const;
    
    // Move parsing methods
    std::pair<std::pair<int, int>, std::pair<int, int>> findPawnMove(int destX, int destY) const;
    std::pair<std::pair<int, int>, std::pair<int, int>> findPieceMove(char pieceType, int destX, int destY) const;
    std::pair<std::pair<int, int>, std::pair<int, int>> findPawnCapture(int fromFile, int destX, int destY) const;
    std::pair<std::pair<int, int>, std::pair<int, int>> parseCastlingNotation(const std::string& notation) const;
    std::pair<std::pair<int, int>, std::pair<int, int>> parseAlgebraicNotation(const std::string& notation) const;
    bool processInput(const std::string& input);
};

#endif