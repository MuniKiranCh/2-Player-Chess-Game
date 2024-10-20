
---

# **Chess Game in C++ (OOP)**  

## **Overview**  
This project is a **command-line-based Chess Game** implemented using **Object-Oriented Programming (OOP) principles in C++**. The game includes all essential chess functionalities such as piece movement, turn-based play, and input validation. It serves as a fun way to play chess directly from the terminal and provides a simple way to practice C++ OOP concepts.

---

## **Features**  
- **Object-Oriented Design:** The game is built using C++ classes for each chess piece and game logic.  
- **Chessboard Setup:** Standard 8x8 chessboard with proper initial placement of pieces.  
- **Turn-based Gameplay:** Alternating turns between **White** and **Black** players.  
- **Move Validation:** Ensures that:
  - Players move only their own pieces.
  - Moves follow the rules for each piece (e.g., pawns move forward, rooks in straight lines).
  - Checks if a move is valid on the board boundaries.
- **Display Board:** The current state of the board is displayed after each move.
- **Win Detection:** Can detect **Checkmate** and **Stalemate** (optional for further development).  
- **Input-based Interaction:** Players input moves in the form of coordinates from the terminal.
- **Extensible Code Structure:** Easy to add more rules or extend functionality, such as Castling or En Passant.

---

## **How to Build and Run**  

### **Prerequisites**  
- **C++ compiler** (GCC/Clang or MSVC)  

### **Build Instructions**

1. **Clone the repository**:  
   ```bash
   git clone <repository_url>
   cd ChessGame
   ```

2. **Compile using g++ (optional method)**:  
   ```bash
   g++ src/*.cpp src/Pieces/*.cpp -o chessGame
   ```

3. **Run the game**:  
   ```bash
   ./chessGame
   ```

---

## **How to Play**

1. **Starting the game:**  
   - The game starts with the chessboard displayed, and it’s **White's turn** to move first.

2. **Input Move Format:**  
   - Players will input **four integers** in the format:
     ```plaintext
     x1 y1 x2 y2
     ```
     Where:
     - `(x1, y1)` is the **source** coordinate (where the piece is).
     - `(x2, y2)` is the **destination** coordinate (where the piece moves to).

3. **Example Moves:**
   - **White moves pawn from (1,0) to (2,0):**
     ```plaintext
     1 0 2 0
     ```
   - **Black moves pawn from (6,1) to (5,1):**
     ```plaintext
     6 1 5 1
     ```

4. **Game Flow:**  
   - The game alternates between **White** and **Black** turns.
   - If a move is invalid, the program will notify the player and ask for another move.

5. **Endgame:**  
   - For simplicity, the game currently allows basic gameplay. You can add **Checkmate, Stalemate, or Draw detection** if needed.

---

## **Classes and OOP Design**  

- **Piece (Base Class):**  
  Abstract class defining the general behavior of all chess pieces (e.g., validate movement).  

- **Derived Classes:**  
  Implement specific rules for each type of piece:  
  - `Pawn`: Can move forward, capture diagonally.
  - `Rook`: Moves in straight lines along rows or columns.
  - `Knight`: Moves in an “L” shape.
  - `Bishop`: Moves diagonally.
  - `Queen`: Moves in straight lines and diagonals.
  - `King`: Moves one square in any direction.

- **Board Class:**  
  Handles the 8x8 chessboard, including placing pieces, updating board state, and printing the current board.

- **Game Class:**  
  Manages the overall game flow, including turns, move validation, and switching between players.

---

## **Sample Gameplay Output**

```
Initial Board:
  0 1 2 3 4 5 6 7
0 R - - - K - - R 
1 P P P P P P P P 
2 - - - - - - - - 
3 - - - - - - - - 
4 - - - - - - - - 
5 - - - - - - - - 
6 p p p p p p p p 
7 r - - - k - - r 

White's turn.
Enter your move (x1 y1 x2 y2):
1 0 2 0

  0 1 2 3 4 5 6 7
0 R - - - K - - R 
1 - P P P P P P P 
2 P - - - - - - - 
3 - - - - - - - - 
4 - - - - - - - - 
5 - - - - - - - - 
6 p p p p p p p p 
7 r - - - k - - r 

Black's turn.
Enter your move (x1 y1 x2 y2):
6 1 5 1
```

---

## **Future Improvements**  
- **Checkmate & Stalemate Detection:** Detect when the game ends in a checkmate or stalemate.
- **Castling and En Passant:** Implement special moves.
- **Undo Feature:** Allow players to undo their last move.
- **Graphical Interface:** Add a GUI to make the game more interactive.

---

## **Contributing**  
Feel free to submit pull requests or raise issues if you find any bugs or want to add new features.