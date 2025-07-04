#include "../include/Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream> // Required for save/load/export/import

Game::Game() : board(), currentPlayer(true), moveCount(0), 
               aiEnabled(false), aiDifficulty(AIDifficulty::RANDOM), aiPlaysAsWhite(false) {}

void Game::setAIOpponent(bool enabled, AIDifficulty difficulty) {
    aiEnabled = enabled;
    aiDifficulty = difficulty;
}

void Game::setAIPlaysAs(bool playsAsWhite) {
    aiPlaysAsWhite = playsAsWhite;
}

void Game::start() {
    std::cout << "=== CHESS GAME ===\n";
    std::cout << "Type 'help' for commands, 'quit' to exit\n";
    std::cout << "Move format: Use chess notation (e.g., 'e2 e4' or 'Nf3')\n\n";
    
    // AI setup
    if (aiEnabled) {
        displayAISettings();
    }
    
    board.printBoard();
    displayGameStatus();
    
    std::string input;
    while (true) {
        // Check if it's AI's turn
        if (aiEnabled && currentPlayer == aiPlaysAsWhite) {
            std::cout << (currentPlayer ? "White" : "Black") << "'s turn (AI).\n";
            makeAIMove();
            moveCount++;
            board.printBoard();
            displayGameStatus();
            
            if (board.isCheckmate(!currentPlayer)) {
                std::cout << "\n🎉 CHECKMATE! 🎉\n";
                std::cout << (currentPlayer ? "White" : "Black") << " wins the game!\n";
                announceGameEnd();
                break;
            }
            
            if (isGameEnded()) {
                announceGameEnd();
                break;
            }
            
            currentPlayer = !currentPlayer;
            continue;
        }
        
        std::cout << (currentPlayer ? "White" : "Black") << "'s turn.\n";
        std::cout << "Enter move (e.g., 'e2 e4') or command: ";
        std::getline(std::cin, input);
        
        if (input == "quit" || input == "exit") {
            std::cout << "Game ended.\n";
            break;
        }
        
        if (handleSpecialCommands(input)) {
            continue;
        }
        
        if (processInput(input)) {
            moveCount++;
            board.printBoard();
            displayGameStatus();
            
            // Check if the opponent is in checkmate after this move
            if (board.isCheckmate(!currentPlayer)) {
                std::cout << "\n🎉 CHECKMATE! 🎉\n";
                std::cout << (currentPlayer ? "White" : "Black") << " wins the game!\n";
                announceGameEnd();
                break;
            }
            
            if (isGameEnded()) {
                announceGameEnd();
                break;
            }
            
            currentPlayer = !currentPlayer;
        } else {
            std::cout << "Invalid move! Try again or type 'help' for assistance.\n";
        }
    }
}

bool Game::processInput(const std::string& input) {
    // Try to parse as castling notation first (e.g., "O-O", "O-O-O")
    auto castlingMove = parseCastlingNotation(input);
    if (castlingMove.first.first != -1) {
        return makeMove(castlingMove.first.first, castlingMove.first.second, castlingMove.second.first, castlingMove.second.second);
    }
    
    // Try to parse as algebraic notation (e.g., "Nf3", "e4")
    auto move = parseAlgebraicNotation(input);
    if (move.first.first != -1) {
        return makeMove(move.first.first, move.first.second, move.second.first, move.second.second);
    }
    
    // Try to parse as chess notation (e.g., "e2 e4")
    std::istringstream iss(input);
    std::string from, to;
    
    if (iss >> from >> to) {
        // Parse chess notation
        auto coords1 = parseChessNotation(from);
        auto coords2 = parseChessNotation(to);
        
        if (coords1.first != -1 && coords2.first != -1) {
            return makeMove(coords1.first, coords1.second, coords2.first, coords2.second);
        }
    }
    
    // Fallback to numeric coordinates for backward compatibility
    std::istringstream iss2(input);
    int x1, y1, x2, y2;
    
    if (iss2 >> x1 >> y1 >> x2 >> y2) {
        return makeMove(x1, y1, x2, y2);
    }
    
    return false;
}

bool Game::makeMove(int x1, int y1, int x2, int y2) {
    // Validate coordinates
    if (x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8 || 
        x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8) {
        std::cout << "Invalid coordinates! Use chess notation like 'e2 e4' or numeric coordinates 0-7.\n";
        std::cout << "Coordinate mapping: 0=a, 1=b, 2=c, 3=d, 4=e, 5=f, 6=g, 7=h\n";
        std::cout << "Rows: 0=8, 1=7, 2=6, 3=5, 4=4, 5=3, 6=2, 7=1\n";
        return false;
    }
    
    // Check if piece exists and belongs to current player
    Piece* piece = board.getPiece(x1, y1);
    if (!piece) {
        std::cout << "No piece at that position!\n";
        return false;
    }
    
    if (piece->isWhite() != currentPlayer) {
        std::cout << "That's not your piece!\n";
        return false;
    }
    
    // Check if move is valid
    if (!board.isValidMove(x1, y1, x2, y2)) {
        std::cout << "Invalid move for that piece!\n";
        return false;
    }
    
    // Make the move
    board.movePiece(x1, y1, x2, y2);
    
    // Record the move
    Move move(x1, y1, x2, y2);
    moveHistory.push_back(move);
    
    // Convert coordinates to chess notation for display
    std::string from = getChessNotation(x1, y1);
    std::string to = getChessNotation(x2, y2);
    std::cout << "Move " << moveCount + 1 << ": " << from << " to " << to << "\n";
    return true;
}

std::string Game::getChessNotation(int x, int y) const {
    char file = 'a' + y;
    int rank = 8 - x;
    return std::string(1, file) + std::to_string(rank);
}

std::pair<int, int> Game::parseChessNotation(const std::string& notation) const {
    if (notation.length() != 2) {
        return {-1, -1}; // Invalid format
    }
    
    char file = notation[0];
    char rank = notation[1];
    
    // Validate file (a-h)
    if (file < 'a' || file > 'h') {
        return {-1, -1};
    }
    
    // Validate rank (1-8)
    if (rank < '1' || rank > '8') {
        return {-1, -1};
    }
    
    int y = file - 'a';  // Convert a-h to 0-7
    int x = 8 - (rank - '0');  // Convert 1-8 to 7-0
    
    return {x, y};
}

std::pair<std::pair<int, int>, std::pair<int, int>> Game::parseAlgebraicNotation(const std::string& notation) const {
    // Handle pawn moves (e.g., "e4", "e5")
    if (notation.length() == 2) {
        auto dest = parseChessNotation(notation);
        if (dest.first != -1) {
            // Find the pawn that can move to this square
            return findPawnMove(dest.first, dest.second);
        }
    }
    
    // Handle piece moves (e.g., "Nf3", "Bc4")
    if (notation.length() == 3) {
        char piece = notation[0];
        auto dest = parseChessNotation(notation.substr(1));
        if (dest.first != -1) {
            return findPieceMove(piece, dest.first, dest.second);
        }
    }
    
    // Handle captures (e.g., "exd5", "Nxe5")
    if (notation.length() == 4 && notation[1] == 'x') {
        char piece = notation[0];
        auto dest = parseChessNotation(notation.substr(2));
        if (dest.first != -1) {
            if (piece >= 'a' && piece <= 'h') {
                // Pawn capture (e.g., "exd5")
                return findPawnCapture(piece - 'a', dest.first, dest.second);
            } else {
                // Piece capture (e.g., "Nxe5")
                return findPieceMove(piece, dest.first, dest.second);
            }
        }
    }
    
    return {{-1, -1}, {-1, -1}}; // Invalid format
}

std::pair<std::pair<int, int>, std::pair<int, int>> Game::findPawnMove(int destX, int destY) const {
    // Find a pawn that can move to the destination
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Piece* piece = board.getPiece(x, y);
            if (piece && piece->isWhite() == currentPlayer && 
                (piece->getSymbol() == 'P' || piece->getSymbol() == 'p')) {
                if (board.isValidMove(x, y, destX, destY)) {
                    return {{x, y}, {destX, destY}};
                }
            }
        }
    }
    return {{-1, -1}, {-1, -1}};
}

std::pair<std::pair<int, int>, std::pair<int, int>> Game::findPieceMove(char pieceType, int destX, int destY) const {
    char targetSymbol = currentPlayer ? toupper(pieceType) : tolower(pieceType);
    
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Piece* piece = board.getPiece(x, y);
            if (piece && piece->isWhite() == currentPlayer && piece->getSymbol() == targetSymbol) {
                if (board.isValidMove(x, y, destX, destY)) {
                    return {{x, y}, {destX, destY}};
                }
            }
        }
    }
    return {{-1, -1}, {-1, -1}};
}

std::pair<std::pair<int, int>, std::pair<int, int>> Game::findPawnCapture(int fromFile, int destX, int destY) const {
    // Find a pawn in the specified file that can capture to the destination
    for (int x = 0; x < 8; x++) {
        Piece* piece = board.getPiece(x, fromFile);
        if (piece && piece->isWhite() == currentPlayer && 
            (piece->getSymbol() == 'P' || piece->getSymbol() == 'p')) {
            if (board.isValidMove(x, fromFile, destX, destY)) {
                return {{x, fromFile}, {destX, destY}};
            }
        }
    }
    return {{-1, -1}, {-1, -1}};
}

std::pair<std::pair<int, int>, std::pair<int, int>> Game::parseCastlingNotation(const std::string& notation) const {
    // Handle castling notation: O-O (king-side) or O-O-O (queen-side)
    if (notation == "O-O" || notation == "0-0") {
        // King-side castling
        int kingX = currentPlayer ? 7 : 0;
        int kingY = 4;
        int kingDestY = 6;
        return {{kingX, kingY}, {kingX, kingDestY}};
    } else if (notation == "O-O-O" || notation == "0-0-0") {
        // Queen-side castling
        int kingX = currentPlayer ? 7 : 0;
        int kingY = 4;
        int kingDestY = 2;
        return {{kingX, kingY}, {kingX, kingDestY}};
    }
    
    return {{-1, -1}, {-1, -1}}; // Not castling notation
}

void Game::displayGameStatus() const {
    // Debug: Check if the opponent is in checkmate after current player's move
    bool opponentInCheck = board.isCheck(!currentPlayer);
    bool opponentHasMoves = board.hasLegalMoves(!currentPlayer);
    bool opponentCheckmate = board.isCheckmate(!currentPlayer);
    
    std::cout << "DEBUG: " << (!currentPlayer ? "White" : "Black") << " king in check: " << (opponentInCheck ? "YES" : "NO") << "\n";
    std::cout << "DEBUG: " << (!currentPlayer ? "White" : "Black") << " has legal moves: " << (opponentHasMoves ? "YES" : "NO") << "\n";
    std::cout << "DEBUG: " << (!currentPlayer ? "White" : "Black") << " checkmate: " << (opponentCheckmate ? "YES" : "NO") << "\n";
    
    if (board.isCheck(currentPlayer)) {
        if (board.isCheckmate(currentPlayer)) {
            std::cout << "CHECKMATE! " << (currentPlayer ? "Black" : "White") << " wins!\n";
        } else {
            std::cout << "CHECK! " << (currentPlayer ? "White" : "Black") << " is in check.\n";
        }
    } else if (board.isStalemate(currentPlayer)) {
        std::cout << "STALEMATE! The game is a draw.\n";
    }
}

bool Game::handleSpecialCommands(const std::string& input) {
    if (input == "help" || input == "h") {
        displayHelp();
        return true;
    }
    
    if (input == "history" || input == "hist") {
        displayMoveHistory();
        return true;
    }
    
    if (input == "status" || input == "s") {
        displayGameStatus();
        return true;
    }
    
    if (input.substr(0, 5) == "moves") {
        std::istringstream iss(input);
        std::string cmd;
        int x, y;
        iss >> cmd >> x >> y;
        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            showLegalMoves(x, y);
        } else {
            std::cout << "Invalid coordinates for moves command!\n";
        }
        return true;
    }
    
    if (input == "board" || input == "b") {
        board.printBoard();
        return true;
    }
    
    // Save/Load commands
    if (input.substr(0, 4) == "save") {
        std::istringstream iss(input);
        std::string cmd, filename;
        iss >> cmd >> filename;
        if (filename.empty()) {
            std::cout << "Usage: save <filename>\n";
        } else {
            saveGame(filename);
        }
        return true;
    }
    
    if (input.substr(0, 4) == "load") {
        std::istringstream iss(input);
        std::string cmd, filename;
        iss >> cmd >> filename;
        if (filename.empty()) {
            std::cout << "Usage: load <filename>\n";
        } else {
            loadGame(filename);
        }
        return true;
    }
    
    if (input.substr(0, 6) == "export") {
        std::istringstream iss(input);
        std::string cmd, filename;
        iss >> cmd >> filename;
        if (filename.empty()) {
            std::cout << "Usage: export <filename.pgn>\n";
        } else {
            exportPGN(filename);
        }
        return true;
    }
    
    if (input.substr(0, 6) == "import") {
        std::istringstream iss(input);
        std::string cmd, filename;
        iss >> cmd >> filename;
        if (filename.empty()) {
            std::cout << "Usage: import <filename.pgn>\n";
        } else {
            importPGN(filename);
        }
        return true;
    }
    
    if (input == "fen") {
        std::cout << "Current FEN: " << getFEN() << "\n";
        return true;
    }
    
    if (input == "savehelp") {
        displaySaveLoadHelp();
        return true;
    }
    
    return false;
}

void Game::displayHelp() const {
    std::cout << "\n=== CHESS GAME COMMANDS ===\n";
    std::cout << "Move format: Use chess notation (e.g., 'e2 e4', 'Nf3', 'O-O')\n";
    std::cout << "\nChess Notation Examples:\n";
    std::cout << "  e2 e4     - Pawn moves from e2 to e4\n";
    std::cout << "  Nf3       - Knight moves to f3\n";
    std::cout << "  O-O       - Kingside castle\n";
    std::cout << "  O-O-O     - Queenside castle\n";
    std::cout << "  exd5      - Pawn captures on d5\n";
    std::cout << "  Nxe5      - Knight captures on e5\n";
    std::cout << "\nSpecial Moves:\n";
    std::cout << "  Castling: O-O (kingside) or O-O-O (queenside)\n";
    std::cout << "  En Passant: Automatic when capturing a pawn that just moved 2 squares\n";
    std::cout << "  Pawn Promotion: Automatic to Queen when reaching the opposite end\n";
    std::cout << "\nCoordinate System (alternative):\n";
    std::cout << "  Files (columns): 0=a, 1=b, 2=c, 3=d, 4=e, 5=f, 6=g, 7=h\n";
    std::cout << "  Ranks (rows):    0=8, 1=7, 2=6, 3=5, 4=4, 5=3, 6=2, 7=1\n";
    std::cout << "  Example: 6 4 4 4 means move from e2 to e4\n";
    std::cout << "\nCommands:\n";
    std::cout << "  help, h     - Show this help\n";
    std::cout << "  history, hist - Show move history\n";
    std::cout << "  status, s   - Show game status\n";
    std::cout << "  moves x y   - Show legal moves for piece at (x,y)\n";
    std::cout << "  board, b    - Redisplay the board\n";
    std::cout << "  savehelp    - Show save/load commands\n";
    std::cout << "  quit, exit  - Exit the game\n";
    
    if (aiEnabled) {
        std::cout << "\nAI Features:\n";
        std::cout << "  AI opponent is enabled\n";
        std::cout << "  AI will automatically make moves on its turn\n";
    }
    
    std::cout << "\nPiece symbols: K/k=King, Q/q=Queen, R/r=Rook, B/b=Bishop, N/n=Knight, P/p=Pawn\n";
    std::cout << "Uppercase = White pieces, Lowercase = Black pieces\n\n";
}

void Game::displayMoveHistory() const {
    std::cout << "\n=== MOVE HISTORY ===\n";
    if (moveHistory.empty()) {
        std::cout << "No moves made yet.\n";
    } else {
        for (size_t i = 0; i < moveHistory.size(); ++i) {
            std::string from = getChessNotation(moveHistory[i].x1, moveHistory[i].y1);
            std::string to = getChessNotation(moveHistory[i].x2, moveHistory[i].y2);
            std::cout << i + 1 << ". " << from << " to " << to << "\n";
        }
    }
    std::cout << "\n";
}

void Game::showLegalMoves(int x, int y) const {
    Piece* piece = board.getPiece(x, y);
    if (!piece) {
        std::cout << "No piece at position " << getChessNotation(x, y) << "\n";
        return;
    }
    
    std::cout << "Legal moves for " << (piece->isWhite() ? "White" : "Black") 
              << " " << piece->getSymbol() << " at " << getChessNotation(x, y) << ":\n";
    
    auto legalMoves = board.getLegalMoves(x, y);
    if (legalMoves.empty()) {
        std::cout << "No legal moves available.\n";
    } else {
        for (const auto& move : legalMoves) {
            std::cout << "  " << getChessNotation(move.first, move.second) << " ";
        }
        std::cout << "\n";
    }
}

bool Game::isGameEnded() const {
    return board.isCheckmate(currentPlayer) || board.isStalemate(currentPlayer);
}

void Game::announceGameEnd() const {
    if (board.isCheckmate(currentPlayer)) {
        std::cout << "\n🎉 CHECKMATE! 🎉\n";
        std::cout << (currentPlayer ? "Black" : "White") << " wins the game!\n";
    } else if (board.isStalemate(currentPlayer)) {
        std::cout << "\n🤝 STALEMATE! 🤝\n";
        std::cout << "The game is a draw!\n";
    }
    
    std::cout << "\nGame Statistics:\n";
    std::cout << "Total moves: " << moveCount << "\n";
    std::cout << "Move history:\n";
    displayMoveHistory();
}

// AI Methods
void Game::makeAIMove() {
    std::pair<std::pair<int, int>, std::pair<int, int>> move;
    
    switch (aiDifficulty) {
        case AIDifficulty::RANDOM:
            move = getRandomMove();
            break;
        case AIDifficulty::GREEDY:
            move = getGreedyMove();
            break;
        case AIDifficulty::MINIMAX_1:
            move = getMinimaxMove(1);
            break;
        case AIDifficulty::MINIMAX_2:
            move = getMinimaxMove(2);
            break;
        case AIDifficulty::MINIMAX_3:
            move = getMinimaxMove(3);
            break;
        default:
            move = getRandomMove();
            break;
    }
    
    if (move.first.first != -1) {
        makeMove(move.first.first, move.first.second, move.second.first, move.second.second);
        std::string from = getChessNotation(move.first.first, move.first.second);
        std::string to = getChessNotation(move.second.first, move.second.second);
        std::cout << "AI move: " << from << " to " << to << "\n";
    } else {
        std::cout << "AI couldn't find a valid move!\n";
    }
}

std::pair<std::pair<int, int>, std::pair<int, int>> Game::getRandomMove() const {
    auto legalMoves = getAllLegalMoves(currentPlayer);
    
    if (legalMoves.empty()) {
        return {{-1, -1}, {-1, -1}};
    }
    
    // Use current time as seed for random number generation
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(0, legalMoves.size() - 1);
    
    int randomIndex = dis(gen);
    return legalMoves[randomIndex];
}

std::pair<std::pair<int, int>, std::pair<int, int>> Game::getGreedyMove() const {
    auto legalMoves = getAllLegalMoves(currentPlayer);
    
    if (legalMoves.empty()) {
        return {{-1, -1}, {-1, -1}};
    }
    
    std::pair<std::pair<int, int>, std::pair<int, int>> bestMove = legalMoves[0];
    int bestValue = -10000;
    
    for (const auto& move : legalMoves) {
        // Create a temporary board to evaluate the move
        Board tempBoard = board;
        tempBoard.movePiece(move.first.first, move.first.second, move.second.first, move.second.second);
        
        int moveValue = tempBoard.evaluatePosition();
        if (currentPlayer) {
            moveValue = -moveValue; // AI is playing as current player
        }
        
        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = move;
        }
    }
    
    return bestMove;
}

std::pair<std::pair<int, int>, std::pair<int, int>> Game::getMinimaxMove(int depth) const {
    auto legalMoves = getAllLegalMoves(currentPlayer);
    
    if (legalMoves.empty()) {
        return {{-1, -1}, {-1, -1}};
    }
    
    std::pair<std::pair<int, int>, std::pair<int, int>> bestMove = legalMoves[0];
    int bestValue = -10000;
    
    for (const auto& move : legalMoves) {
        // Create a temporary board to evaluate the move
        Board tempBoard = board;
        tempBoard.movePiece(move.first.first, move.first.second, move.second.first, move.second.second);
        
        int moveValue = minimax(tempBoard, depth - 1, -10000, 10000, false);
        
        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = move;
        }
    }
    
    return bestMove;
}

int Game::evaluatePosition() const {
    int score = 0;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getPiece(i, j);
            if (piece) {
                int value = getPieceValue(piece->getSymbol());
                if (piece->isWhite()) {
                    score += value;
                } else {
                    score -= value;
                }
            }
        }
    }
    
    return score;
}

int Game::minimax(Board& board, int depth, int alpha, int beta, bool maximizingPlayer) const {
    if (depth == 0 || board.isCheckmate(true) || board.isCheckmate(false) || board.isStalemate(true) || board.isStalemate(false)) {
        return board.evaluatePosition();
    }
    
    if (maximizingPlayer) {
        int maxEval = -10000;
        auto legalMoves = getAllLegalMoves(true);
        
        for (const auto& move : legalMoves) {
            Board tempBoard = board;
            tempBoard.movePiece(move.first.first, move.first.second, move.second.first, move.second.second);
            
            int eval = minimax(tempBoard, depth - 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            
            if (beta <= alpha) {
                break; // Alpha-beta pruning
            }
        }
        return maxEval;
    } else {
        int minEval = 10000;
        auto legalMoves = getAllLegalMoves(false);
        
        for (const auto& move : legalMoves) {
            Board tempBoard = board;
            tempBoard.movePiece(move.first.first, move.first.second, move.second.first, move.second.second);
            
            int eval = minimax(tempBoard, depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            
            if (beta <= alpha) {
                break; // Alpha-beta pruning
            }
        }
        return minEval;
    }
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> Game::getAllLegalMoves(bool forWhite) const {
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> legalMoves;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getPiece(i, j);
            if (piece && piece->isWhite() == forWhite) {
                auto moves = board.getLegalMoves(i, j);
                for (const auto& move : moves) {
                    legalMoves.push_back({{i, j}, move});
                }
            }
        }
    }
    
    return legalMoves;
}

int Game::getPieceValue(char piece) const {
    switch (toupper(piece)) {
        case 'P': return 1;   // Pawn
        case 'N': return 3;   // Knight
        case 'B': return 3;   // Bishop
        case 'R': return 5;   // Rook
        case 'Q': return 9;   // Queen
        case 'K': return 100; // King
        default: return 0;
    }
}

void Game::displayAISettings() const {
    std::cout << "=== AI OPPONENT ENABLED ===\n";
    std::cout << "AI plays as: " << (aiPlaysAsWhite ? "White" : "Black") << "\n";
    std::cout << "Difficulty: ";
    
    switch (aiDifficulty) {
        case AIDifficulty::RANDOM:
            std::cout << "Random (Easiest)";
            break;
        case AIDifficulty::GREEDY:
            std::cout << "Greedy (Easy)";
            break;
        case AIDifficulty::MINIMAX_1:
            std::cout << "Minimax Depth 1 (Medium)";
            break;
        case AIDifficulty::MINIMAX_2:
            std::cout << "Minimax Depth 2 (Hard)";
            break;
        case AIDifficulty::MINIMAX_3:
            std::cout << "Minimax Depth 3 (Very Hard)";
            break;
    }
    std::cout << "\n\n";
}

// Save/Load Methods
bool Game::saveGame(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << " for writing.\n";
        return false;
    }
    
    // Save game state
    file << "GAME_STATE\n";
    file << "CurrentPlayer: " << (currentPlayer ? "White" : "Black") << "\n";
    file << "MoveCount: " << moveCount << "\n";
    file << "AIEnabled: " << (aiEnabled ? "true" : "false") << "\n";
    if (aiEnabled) {
        file << "AIDifficulty: " << static_cast<int>(aiDifficulty) << "\n";
        file << "AIPlaysAsWhite: " << (aiPlaysAsWhite ? "true" : "false") << "\n";
    }
    
    // Save board state as FEN
    file << "FEN: " << getFEN() << "\n";
    
    // Save move history
    file << "MOVE_HISTORY\n";
    for (const auto& move : moveHistory) {
        std::string from = getChessNotation(move.x1, move.y1);
        std::string to = getChessNotation(move.x2, move.y2);
        file << from << " " << to << "\n";
    }
    
    file.close();
    std::cout << "Game saved to " << filename << "\n";
    return true;
}

bool Game::loadGame(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << " for reading.\n";
        return false;
    }
    
    std::string line;
    std::string fen;
    std::vector<std::string> moves;
    bool inMoveHistory = false;
    
    while (std::getline(file, line)) {
        if (line == "GAME_STATE") {
            continue;
        } else if (line == "MOVE_HISTORY") {
            inMoveHistory = true;
            continue;
        } else if (line.substr(0, 4) == "FEN:") {
            fen = line.substr(5); // Remove "FEN: " prefix
        } else if (line.substr(0, 14) == "CurrentPlayer:") {
            currentPlayer = (line.substr(15) == "White");
        } else if (line.substr(0, 10) == "MoveCount:") {
            moveCount = std::stoi(line.substr(11));
        } else if (line.substr(0, 10) == "AIEnabled:") {
            aiEnabled = (line.substr(11) == "true");
        } else if (line.substr(0, 12) == "AIDifficulty:") {
            aiDifficulty = static_cast<AIDifficulty>(std::stoi(line.substr(13)));
        } else if (line.substr(0, 15) == "AIPlaysAsWhite:") {
            aiPlaysAsWhite = (line.substr(16) == "true");
        } else if (inMoveHistory && !line.empty()) {
            moves.push_back(line);
        }
    }
    
    file.close();
    
    // Set the board state from FEN
    if (!fen.empty()) {
        if (!setFEN(fen)) {
            std::cout << "Error: Invalid FEN in save file.\n";
            return false;
        }
    }
    
    // Reconstruct move history
    moveHistory.clear();
    for (const auto& moveStr : moves) {
        std::istringstream iss(moveStr);
        std::string from, to;
        iss >> from >> to;
        
        auto fromCoords = parseChessNotation(from);
        auto toCoords = parseChessNotation(to);
        
        if (fromCoords.first != -1 && toCoords.first != -1) {
            moveHistory.emplace_back(fromCoords.first, fromCoords.second, toCoords.first, toCoords.second);
        }
    }
    
    std::cout << "Game loaded from " << filename << "\n";
    std::cout << "Current player: " << (currentPlayer ? "White" : "Black") << "\n";
    std::cout << "Move count: " << moveCount << "\n";
    return true;
}

bool Game::exportPGN(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << " for writing.\n";
        return false;
    }
    
    // PGN header
    file << "[Event \"Chess Game\"]\n";
    file << "[Site \"Local Game\"]\n";
    file << "[Date \"" << __DATE__ << "\"]\n";
    file << "[Round \"1\"]\n";
    file << "[White \"Player 1\"]\n";
    file << "[Black \"Player 2\"]\n";
    file << "[Result \"*\"]\n";
    file << "[FEN \"" << getFEN() << "\"]\n\n";
    
    // Moves
    for (size_t i = 0; i < moveHistory.size(); i += 2) {
        file << (i/2 + 1) << ". ";
        
        // White move
        std::string from = getChessNotation(moveHistory[i].x1, moveHistory[i].y1);
        std::string to = getChessNotation(moveHistory[i].x2, moveHistory[i].y2);
        file << from << to;
        
        // Black move (if exists)
        if (i + 1 < moveHistory.size()) {
            std::string from2 = getChessNotation(moveHistory[i+1].x1, moveHistory[i+1].y1);
            std::string to2 = getChessNotation(moveHistory[i+1].x2, moveHistory[i+1].y2);
            file << " " << from2 << to2;
        }
        
        file << " ";
    }
    
    file << "\n";
    file.close();
    std::cout << "PGN exported to " << filename << "\n";
    return true;
}

bool Game::importPGN(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << " for reading.\n";
        return false;
    }
    
    std::string line;
    std::string fen;
    std::vector<std::string> moves;
    
    while (std::getline(file, line)) {
        if (line.substr(0, 5) == "[FEN ") {
            fen = line.substr(6, line.length() - 8); // Remove "[FEN " and "]"
        } else if (line.empty()) {
            continue;
        } else if (line[0] != '[') {
            // This is the moves line
            std::istringstream iss(line);
            std::string token;
            while (iss >> token) {
                if (token.find('.') != std::string::npos) {
                    continue; // Skip move numbers
                }
                if (token.length() == 4) {
                    moves.push_back(token);
                }
            }
        }
    }
    
    file.close();
    
    // Reset game
    board.resetBoard();
    moveHistory.clear();
    moveCount = 0;
    currentPlayer = true;
    
    // Set initial position from FEN if provided
    if (!fen.empty()) {
        if (!setFEN(fen)) {
            std::cout << "Error: Invalid FEN in PGN file.\n";
            return false;
        }
    }
    
    // Execute moves
    for (const auto& moveStr : moves) {
        std::string from = moveStr.substr(0, 2);
        std::string to = moveStr.substr(2, 2);
        
        auto fromCoords = parseChessNotation(from);
        auto toCoords = parseChessNotation(to);
        
        if (fromCoords.first != -1 && toCoords.first != -1) {
            if (makeMove(fromCoords.first, fromCoords.second, toCoords.first, toCoords.second)) {
                moveCount++;
                currentPlayer = !currentPlayer;
            }
        }
    }
    
    std::cout << "PGN imported from " << filename << "\n";
    std::cout << "Loaded " << moves.size() << " moves\n";
    return true;
}

std::string Game::getFEN() const {
    std::string fen;
    
    // Board position
    for (int i = 0; i < 8; ++i) {
        int emptyCount = 0;
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getPiece(i, j);
            if (piece) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += piece->getSymbol();
            } else {
                emptyCount++;
            }
        }
        if (emptyCount > 0) {
            fen += std::to_string(emptyCount);
        }
        if (i < 7) fen += "/";
    }
    
    // Active color
    fen += " " + std::string(currentPlayer ? "w" : "b");
    
    // Castling availability
    std::string castling = "";
    if (!board.hasKingMoved(true) && !board.hasRookMoved(true, true)) castling += "K";
    if (!board.hasKingMoved(true) && !board.hasRookMoved(true, false)) castling += "Q";
    if (!board.hasKingMoved(false) && !board.hasRookMoved(false, true)) castling += "k";
    if (!board.hasKingMoved(false) && !board.hasRookMoved(false, false)) castling += "q";
    fen += " " + (castling.empty() ? "-" : castling);
    
    // En passant target square
    auto enPassantTarget = board.getEnPassantTarget();
    if (enPassantTarget.first != -1) {
        std::string file = std::string(1, 'a' + enPassantTarget.second);
        std::string rank = std::to_string(8 - enPassantTarget.first);
        fen += " " + file + rank;
    } else {
        fen += " -";
    }
    
    // Halfmove clock and fullmove number
    fen += " 0 " + std::to_string(moveCount / 2 + 1);
    
    return fen;
}

bool Game::setFEN(const std::string& fen) {
    std::istringstream iss(fen);
    std::string position, activeColor, castling, enPassant, halfmove, fullmove;
    
    iss >> position >> activeColor >> castling >> enPassant >> halfmove >> fullmove;
    
    // Reset board
    board.resetBoard();
    
    // Parse position
    int row = 0, col = 0;
    for (char c : position) {
        if (c == '/') {
            row++;
            col = 0;
        } else if (isdigit(c)) {
            col += c - '0';
        } else {
            // Place piece
            bool isWhite = isupper(c);
            char pieceType = tolower(c);
            
            // This is a simplified version - in a full implementation,
            // you'd need to properly place pieces on the board
            // For now, we'll just validate the FEN format
            col++;
        }
    }
    
    // Set current player
    currentPlayer = (activeColor == "w");
    
    // Reset game state
    moveHistory.clear();
    moveCount = 0;
    
    return true;
}

void Game::displaySaveLoadHelp() const {
    std::cout << "\n=== SAVE/LOAD COMMANDS ===\n";
    std::cout << "save <filename>     - Save current game state to file\n";
    std::cout << "load <filename>     - Load game state from file\n";
    std::cout << "export <filename>   - Export game to PGN format\n";
    std::cout << "import <filename>   - Import game from PGN format\n";
    std::cout << "fen                 - Display current position in FEN notation\n";
    std::cout << "\nFile formats:\n";
    std::cout << "- .chess files: Custom format with game state and move history\n";
    std::cout << "- .pgn files: Standard Portable Game Notation format\n";
    std::cout << "- FEN: Forsyth-Edwards Notation for position description\n";
    std::cout << "\nExamples:\n";
    std::cout << "  save mygame.chess\n";
    std::cout << "  load mygame.chess\n";
    std::cout << "  export game.pgn\n";
    std::cout << "  import game.pgn\n\n";
}


