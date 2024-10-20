#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game {
public:
    Game();
    void start();

private:
    Board board;
    bool currentPlayer;

    bool makeMove(int x1, int y1, int x2, int y2);
};

#endif