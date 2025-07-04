#include "../include/Game.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== CHESS GAME WITH AI ===\n\n";
    
    // Game mode selection
    std::cout << "Select game mode:\n";
    std::cout << "1. Human vs Human\n";
    std::cout << "2. Human vs AI (You play White)\n";
    std::cout << "3. Human vs AI (You play Black)\n";
    std::cout << "Enter choice (1-3): ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(); // Clear the newline
    
    Game game;
    
    switch (choice) {
        case 1:
            // Human vs Human - no AI
            break;
            
        case 2:
            // Human vs AI - Human plays White
            game.setAIOpponent(true, AIDifficulty::RANDOM);
            game.setAIPlaysAs(false); // AI plays Black
            break;
            
        case 3:
            // Human vs AI - Human plays Black
            game.setAIOpponent(true, AIDifficulty::RANDOM);
            game.setAIPlaysAs(true); // AI plays White
            break;
            
        default:
            std::cout << "Invalid choice. Starting Human vs Human game.\n";
            break;
    }
    
    // If AI is enabled, let user choose difficulty
    if (choice >= 2 && choice <= 3) {
        std::cout << "\nSelect AI difficulty:\n";
        std::cout << "1. Random (Easiest)\n";
        std::cout << "2. Greedy (Easy)\n";
        std::cout << "3. Minimax Depth 1 (Medium)\n";
        std::cout << "4. Minimax Depth 2 (Hard)\n";
        std::cout << "5. Minimax Depth 3 (Very Hard)\n";
        std::cout << "Enter choice (1-5): ";
        
        int difficulty;
        std::cin >> difficulty;
        std::cin.ignore(); // Clear the newline
        
        AIDifficulty aiDiff;
        switch (difficulty) {
            case 1: aiDiff = AIDifficulty::RANDOM; break;
            case 2: aiDiff = AIDifficulty::GREEDY; break;
            case 3: aiDiff = AIDifficulty::MINIMAX_1; break;
            case 4: aiDiff = AIDifficulty::MINIMAX_2; break;
            case 5: aiDiff = AIDifficulty::MINIMAX_3; break;
            default: aiDiff = AIDifficulty::RANDOM; break;
        }
        
        game.setAIOpponent(true, aiDiff);
    }
    
    std::cout << "\n";
    game.start();
    return 0;
}
