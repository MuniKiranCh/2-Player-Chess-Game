#include "../include/Board.h"
#include "Pieces/Pawn.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"
#include "Pieces/Bishop.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"
#include <iostream>
#include <algorithm>

Board::Board() : gameOver(false), gameStatus("ongoing") {
    resetBoard();
}

Board::Board(const Board& other) : gameOver(other.gameOver), gameStatus(other.gameStatus) {
    // Initialize board with nullptr
    for (auto &row : board) {
        row.fill(nullptr);
    }
    
    // Copy pieces
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (other.board[i][j]) {
                board[i][j] = createPieceCopy(other.board[i][j]);
            }
        }
    }
}

Board::~Board() {
    // Clean up all pieces
    for (auto &row : board) {
        for (auto &piece : row) {
            delete piece;
        }
    }
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        // Clean up existing pieces
        for (auto &row : board) {
            for (auto &piece : row) {
                delete piece;
            }
        }
        
        // Copy new pieces
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (other.board[i][j]) {
                    board[i][j] = createPieceCopy(other.board[i][j]);
                } else {
                    board[i][j] = nullptr;
                }
            }
        }
        
        gameOver = other.gameOver;
        gameStatus = other.gameStatus;
    }
    return *this;
}

Piece* Board::createPieceCopy(Piece* original) const {
    if (!original) return nullptr;
    
    char symbol = original->getSymbol();
    bool isWhite = original->isWhite();
    
    switch (symbol) {
        case 'P': case 'p':
            return new Pawn(isWhite);
        case 'R': case 'r':
            return new Rook(isWhite);
        case 'N': case 'n':
            return new Knight(isWhite);
        case 'B': case 'b':
            return new Bishop(isWhite);
        case 'Q': case 'q':
            return new Queen(isWhite);
        case 'K': case 'k':
            return new King(isWhite);
        default:
            return nullptr;
    }
}

void Board::resetBoard() {
    for (auto &row : board) {
        row.fill(nullptr); // Initialize all squares to nullptr
    }
    setupPieces();
    gameOver = false;
    gameStatus = "ongoing";
}

void Board::setupPieces() {
    for (int i = 0; i < 8; ++i) {
        board[6][i] = new Pawn(true);  // White Pawns (row 6)
        board[1][i] = new Pawn(false); // Black Pawns (row 1)
    }

    board[7][0] = new Rook(true); board[7][7] = new Rook(true);
    board[0][0] = new Rook(false); board[0][7] = new Rook(false);

    board[7][1] = new Knight(true); board[7][6] = new Knight(true);
    board[0][1] = new Knight(false); board[0][6] = new Knight(false);

    board[7][2] = new Bishop(true); board[7][5] = new Bishop(true);
    board[0][2] = new Bishop(false); board[0][5] = new Bishop(false);

    board[7][3] = new Queen(true); board[7][4] = new King(true);
    board[0][3] = new Queen(false); board[0][4] = new King(false);
}

void Board::printBoard() const {
    std::cout << "\n";
    std::cout << "    a   b   c   d   e   f   g   h\n";
    std::cout << "  +---+---+---+---+---+---+---+---+\n";
    
    for (int i = 0; i < 8; ++i) {
        std::cout << " " << (8-i) << " |";
        for (int j = 0; j < 8; ++j) {
            if (board[i][j]) {
                std::cout << " " << board[i][j]->getSymbol() << " |";
            } else {
                // Create alternating colors for empty squares
                if ((i + j) % 2 == 0) {
                    std::cout << "   |";
                } else {
                    std::cout << "   |";
                }
            }
        }
        std::cout << " " << (8-i) << "\n";
        
        if (i < 7) {
            std::cout << "  +---+---+---+---+---+---+---+---+\n";
        }
    }
    
    std::cout << "  +---+---+---+---+---+---+---+---+\n";
    std::cout << "    a   b   c   d   e   f   g   h\n";
    std::cout << "\n";
    std::cout << "Legend: K/k=King, Q/q=Queen, R/r=Rook, B/b=Bishop, N/n=Knight, P/p=Pawn\n";
    std::cout << "       Uppercase=White, Lowercase=Black\n\n";
}

Piece* Board::getPiece(int x, int y) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) return nullptr;
    return board[x][y];
}

void Board::movePiece(int x1, int y1, int x2, int y2) {
    // Handle pawn promotion
    if (board[x1][y1] && board[x1][y1]->getSymbol() == 'P' && x2 == 0) {
        // White pawn reaching the top (row 0)
        delete board[x1][y1];
        board[x2][y2] = new Queen(true);
        board[x1][y1] = nullptr;
    } else if (board[x1][y1] && board[x1][y1]->getSymbol() == 'p' && x2 == 7) {
        // Black pawn reaching the bottom (row 7)
        delete board[x1][y1];
        board[x2][y2] = new Queen(false);
        board[x1][y1] = nullptr;
    } else {
        // Regular move
        board[x2][y2] = board[x1][y1];
        board[x1][y1] = nullptr;
    }
}

std::pair<int, int> Board::findKing(bool isWhiteKing) const {
    char kingSymbol = isWhiteKing ? 'K' : 'k';
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->getSymbol() == kingSymbol) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // King not found (shouldn't happen in valid game)
}

bool Board::isSquareUnderAttack(int x, int y, bool byWhite) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->isWhite() == byWhite) {
                if (board[i][j]->isValidMove(i, j, x, y, *this)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheck(bool isWhiteKing) const {
    auto kingPos = findKing(isWhiteKing);
    if (kingPos.first == -1) return false;
    return isSquareUnderAttack(kingPos.first, kingPos.second, !isWhiteKing);
}

bool Board::canMoveWithoutLeavingCheck(int x1, int y1, int x2, int y2, bool isWhiteKing) const {
    // Create a temporary board to test the move
    Board tempBoard = *this;
    
    // Make the move on temporary board
    tempBoard.board[x2][y2] = tempBoard.board[x1][y1];
    tempBoard.board[x1][y1] = nullptr;
    
    // Check if the king is still in check after the move
    return !tempBoard.isCheck(isWhiteKing);
}

bool Board::isValidMove(int x1, int y1, int x2, int y2) const {
    // Basic validation
    if (x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8 || 
        x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8) {
        return false;
    }
    
    Piece* piece = board[x1][y1];
    if (!piece) return false;
    
    // Check if destination has own piece
    Piece* destPiece = board[x2][y2];
    if (destPiece && destPiece->isWhite() == piece->isWhite()) {
        return false;
    }
    
    // Check if the move is valid for the piece
    if (!piece->isValidMove(x1, y1, x2, y2, *this)) {
        return false;
    }
    
    // Check if the move doesn't leave own king in check
    return canMoveWithoutLeavingCheck(x1, y1, x2, y2, piece->isWhite());
}

std::vector<std::pair<int, int>> Board::getLegalMoves(int x, int y) const {
    std::vector<std::pair<int, int>> legalMoves;
    Piece* piece = board[x][y];
    if (!piece) return legalMoves;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (isValidMove(x, y, i, j)) {
                legalMoves.push_back({i, j});
            }
        }
    }
    return legalMoves;
}

bool Board::hasLegalMoves(bool isWhiteKing) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->isWhite() == isWhiteKing) {
                if (!getLegalMoves(i, j).empty()) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(bool isWhiteKing) const {
    return isCheck(isWhiteKing) && !hasLegalMoves(isWhiteKing);
}

bool Board::isStalemate(bool isWhiteKing) const {
    return !isCheck(isWhiteKing) && !hasLegalMoves(isWhiteKing);
}

void Board::promotePawn(int x, int y, char pieceType) {
    if (!board[x][y]) return;
    
    bool isWhite = board[x][y]->isWhite();
    delete board[x][y];
    
    switch (pieceType) {
        case 'Q': case 'q':
            board[x][y] = new Queen(isWhite);
            break;
        case 'R': case 'r':
            board[x][y] = new Rook(isWhite);
            break;
        case 'B': case 'b':
            board[x][y] = new Bishop(isWhite);
            break;
        case 'N': case 'n':
            board[x][y] = new Knight(isWhite);
            break;
        default:
            board[x][y] = new Queen(isWhite); // Default to queen
    }
}

bool Board::isGameOver() const {
    return gameOver;
}

std::string Board::getGameStatus() const {
    return gameStatus;
}
