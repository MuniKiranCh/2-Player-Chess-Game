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

private:
    Board board;
    bool currentPlayer; // true for white, false for black
    std::vector<Move> moveHistory;
    int moveCount;
    
    // AI settings
    bool aiEnabled;
    AIDifficulty aiDifficulty;
    bool aiPlaysAsWhite;
    
    bool makeMove(int x1, int y1, int x2, int y2);
    bool processInput(const std::string& input);
    void displayGameStatus() const;
    void displayMoveHistory() const;
    bool handleSpecialCommands(const std::string& input);
    std::string getMoveNotation(int x1, int y1, int x2, int y2) const;
    std::string getChessNotation(int x, int y) const;
    std::pair<int, int> parseChessNotation(const std::string& notation) const;
    std::pair<std::pair<int, int>, std::pair<int, int>> parseAlgebraicNotation(const std::string& notation) const;
    std::pair<std::pair<int, int>, std::pair<int, int>> findPawnMove(int destX, int destY) const;
    std::pair<std::pair<int, int>, std::pair<int, int>> findPieceMove(char pieceType, int destX, int destY) const;
    std::pair<std::pair<int, int>, std::pair<int, int>> findPawnCapture(int fromFile, int destX, int destY) const;
    std::pair<std::pair<int, int>, std::pair<int, int>> parseCastlingNotation(const std::string& notation) const;
    void showLegalMoves(int x, int y) const;
    bool isGameEnded() const;
    void announceGameEnd() const;
    
    // AI methods
    void makeAIMove();
    std::pair<std::pair<int, int>, std::pair<int, int>> getRandomMove() const;
    std::pair<std::pair<int, int>, std::pair<int, int>> getGreedyMove() const;
    std::pair<std::pair<int, int>, std::pair<int, int>> getMinimaxMove(int depth) const;
    int evaluatePosition() const;
    int minimax(Board& board, int depth, int alpha, int beta, bool maximizingPlayer) const;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> getAllLegalMoves(bool forWhite) const;
    int getPieceValue(char piece) const;
    void displayAISettings() const;
};

#endif