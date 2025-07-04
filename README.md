
---

# **Chess Game in C++ (OOP)**  

## **Overview**  
This project is a **complete command-line-based Chess Game** implemented using **Object-Oriented Programming (OOP) principles in C++**. The game includes all essential chess functionalities such as piece movement, turn-based play, check detection, checkmate detection, stalemate detection, and comprehensive input validation. It serves as a fun way to play chess directly from the terminal and provides an excellent demonstration of C++ OOP concepts and game logic implementation.

**Latest Updates:**
- ✅ **Fixed coordinate system** - White pieces at bottom, Black pieces at top
- ✅ **Enhanced chess notation support** - Supports `e2 e4`, `Nf3`, `Qxf7` formats
- ✅ **Fixed checkmate detection** - Properly detects and announces checkmate
- ✅ **Removed # symbols** from empty squares for cleaner display
- ✅ **Improved pawn movement logic** - Correct direction and promotion
- ✅ **Added debug mode** for troubleshooting game states
- ✅ **Implemented Castling** - Both king-side (O-O) and queen-side (O-O-O) castling
- ✅ **Implemented En Passant** - Automatic pawn capture when opponent pawn moves two squares

---

## **Features**  
### **Core Chess Rules** ✅
- **Object-Oriented Design:** The game is built using C++ classes for each chess piece and game logic.  
- **Chessboard Setup:** Standard 8x8 chessboard with proper initial placement of pieces.  
- **Turn-based Gameplay:** Alternating turns between **White** and **Black** players.
- **Complete Move Validation:** Ensures that:
  - Players move only their own pieces.
  - Moves follow the rules for each piece (e.g., pawns move forward, rooks in straight lines).
  - Checks if a move is valid on the board boundaries.
  - Prevents moves that would leave the player's own king in check.
  - Validates piece capture logic (can only capture opponent pieces).
- **Check Detection:** Detects when a king is in check and prevents illegal moves.
- **Checkmate Detection:** Automatically detects checkmate and ends the game.
- **Stalemate Detection:** Detects stalemate situations and declares a draw.
- **Pawn Promotion:** Automatically promotes pawns to Queens when reaching the opposite end.
- **Castling:** Both king-side (O-O) and queen-side (O-O-O) castling with proper validation.
- **En Passant:** Automatic pawn capture when opponent pawn moves two squares forward.

### **Enhanced User Experience** ✅
- **Display Board:** The current state of the board is displayed after each move.
- **Game Status Display:** Shows check, checkmate, and stalemate status.
- **Move History:** Tracks and displays all moves made during the game.
- **Legal Move Display:** Shows all legal moves for any piece on the board.
- **Input-based Interaction:** Players input moves in the form of coordinates from the terminal.
- **Command System:** Special commands for help, history, status, and legal moves.
- **Error Handling:** Comprehensive error messages for invalid moves and inputs.

### **Advanced Features** ✅
- **Memory Management:** Proper memory allocation and deallocation with copy constructors and destructors.
- **Extensible Code Structure:** Easy to add more rules or extend functionality.
- **Game Statistics:** Tracks total moves and provides game summary.
- **Piece Movement Tracking:** Tracks which pieces have moved for castling validation.
- **En Passant Target Tracking:** Automatically manages en passant opportunities.

---

## **How to Build and Run**  

### **Prerequisites**  
- **C++ compiler** (GCC/Clang or MSVC)  
- **C++11 or later** support

### **Build Instructions**

1. **Clone the repository**:  
   ```bash
   git clone <repository_url>
   cd 2-Player-Chess-Game
   ```

2. **Compile using g++**:  
   ```bash
   # Standard version
   g++ -std=c++11 -I include src/*.cpp src/Pieces/*.cpp -o chessGame
   
   # Debug version (with additional output)
   g++ -std=c++11 -I include src/*.cpp src/Pieces/*.cpp -o chessGame_debug
   ```

3. **Run the game**:  
   ```bash
   # Standard version
   ./chessGame
   
   # Debug version
   ./chessGame_debug
   ```

---

## **How to Play**

### **Game Setup:**
- **White pieces** start at the bottom (rows 6-7) - **UPPERCASE** letters (K, Q, R, B, N, P)
- **Black pieces** start at the top (rows 0-1) - **lowercase** letters (k, q, r, b, n, p)
- **White always moves first**

### **Coordinate System:**
```
   a   b   c   d   e   f   g   h
 +---+---+---+---+---+---+---+---+
8| r | n | b | q | k | b | n | r | 8  ← Row 0 (Black pieces)
 +---+---+---+---+---+---+---+---+
7| p | p | p | p | p | p | p | p | 7  ← Row 1 (Black pawns)
 +---+---+---+---+---+---+---+---+
6|   |   |   |   |   |   |   |   | 6  ← Row 2
 +---+---+---+---+---+---+---+---+
5|   |   |   |   |   |   |   |   | 5  ← Row 3
 +---+---+---+---+---+---+---+---+
4|   |   |   |   |   |   |   |   | 4  ← Row 4
 +---+---+---+---+---+---+---+---+
3|   |   |   |   |   |   |   |   | 3  ← Row 5
 +---+---+---+---+---+---+---+---+
2| P | P | P | P | P | P | P | P | 2  ← Row 6 (White pawns)
 +---+---+---+---+---+---+---+---+
1| R | N | B | Q | K | B | N | R | 1  ← Row 7 (White pieces)
 +---+---+---+---+---+---+---+---+
   a   b   c   d   e   f   g   h
```

### **Input Move Format:**  
The game supports multiple input formats:

**A. Chess Notation (Recommended):**
```plaintext
e2 e4          # Pawn from e2 to e4
Nf3            # Knight to f3
Qxf7           # Queen captures on f7
O-O            # Kingside castling
O-O-O          # Queenside castling
```

**B. Algebraic Notation:**
```plaintext
e4             # Pawn to e4 (auto-finds which pawn)
Nf3            # Knight to f3 (auto-finds which knight)
exd5           # Pawn on e-file captures on d5
```

**C. Numeric Coordinates (Alternative):**
```plaintext
6 4 4 4        # From e2 to e4
```
Where:
- `(x1, y1)` is the **source** coordinate (where the piece is).
- `(x2, y2)` is the **destination** coordinate (where the piece moves to).

### **Special Moves:**

**Castling:**
- **King-side castling:** `O-O` or `0-0` - King moves to g1/g8, Rook moves to f1/f8
- **Queen-side castling:** `O-O-O` or `0-0-0` - King moves to c1/c8, Rook moves to d1/d8
- **Requirements:** King and rook must not have moved, no pieces between them, king not in check

**En Passant:**
- **Automatic:** When a pawn moves two squares forward, the opponent can capture it en passant
- **Example:** White plays d2-d4, Black responds with e7-e5, White can capture with d4xe5
- **Timing:** Only available on the very next move

**Pawn Promotion:**
- **Automatic:** Pawns automatically promote to Queen when reaching the opposite end
- **Future enhancement:** Choice of promotion piece (Rook, Bishop, Knight, Queen)

### **Piece Movement Rules:**

**Pawn (P/p):**
- Moves forward only (1 square, or 2 on first move)
- Captures diagonally forward only
- White pawns move UP (decreasing row numbers)
- Black pawns move DOWN (increasing row numbers)
- **En Passant:** Can capture opponent pawn that just moved two squares

**Knight (N/n):**
- L-shape movement (2 squares in one direction, 1 perpendicular)
- Can jump over pieces

**Bishop (B/b):**
- Moves diagonally any number of squares
- Cannot jump over pieces

**Rook (R/r):**
- Moves horizontally or vertically any number of squares
- Cannot jump over pieces

**Queen (Q/q):**
- Moves in any direction (horizontal, vertical, diagonal)
- Cannot jump over pieces

**King (K/k):**
- Moves 1 square in any direction
- Cannot move into check
- **Castling:** Can castle with rook if neither has moved

### **Special Commands:**
- `help` or `h` - Show help and commands
- `history` or `hist` - Show move history
- `status` or `s` - Show current game status
- `moves x y` - Show legal moves for piece at position (x,y)
- `board` or `b` - Redisplay the board
- `quit` or `exit` - Exit the game

### **Example Moves:**
- **White moves pawn from e2 to e4:**
  ```plaintext
  e2 e4
  ```
- **Black moves pawn from e7 to e5:**
  ```plaintext
  e7 e5
  ```
- **White knight to f3:**
  ```plaintext
  Nf3
  ```
- **White kingside castling:**
  ```plaintext
  O-O
  ```
- **Queen captures on f7:**
  ```plaintext
  Qxf7
  ```

### **Game Flow:**  
- The game alternates between **White** and **Black** turns.
- If a move is invalid, the program will notify the player and ask for another move.
- Check, checkmate, and stalemate are automatically detected and announced.

### **Endgame:**  
- **Checkmate:** When a king is in check and no legal moves can escape it.
- **Stalemate:** When a player has no legal moves but is not in check.
- **Game Statistics:** Total moves and complete move history are displayed.

### **Testing Castling and En Passant:**

**Test Castling (Scholar's Mate with Castling):**
```plaintext
e2 e4    # White pawn to e4
e7 e5    # Black pawn to e5
Qh5      # White queen to h5
Nc6      # Black knight to c6
Bc4      # White bishop to c4
Nf6      # Black knight to f6
O-O      # White kingside castling
```

**Test En Passant:**
```plaintext
d2 d4    # White pawn to d4
e7 e5    # Black pawn to e5
d4 e5    # White captures pawn
d7 d5    # Black pawn to d5 (en passant opportunity)
e5 d6    # White captures en passant
```

**Expected results:** 
- Castling should move both king and rook correctly
- En passant should capture the black pawn on d5

---

## **Classes and OOP Design**  

### **Piece Hierarchy:**
- **Piece (Base Class):**  
  Abstract class defining the general behavior of all chess pieces (e.g., validate movement).  

- **Derived Classes:**  
  Implement specific rules for each type of piece:  
  - `Pawn`: Can move forward, capture diagonally, promote to Queen, and capture en passant.
  - `Rook`: Moves in straight lines along rows or columns.
  - `Knight`: Moves in an "L" shape.
  - `Bishop`: Moves diagonally.
  - `Queen`: Moves in straight lines and diagonals.
  - `King`: Moves one square in any direction, can castle with rook.

### **Game Management:**
- **Board Class:**  
  Handles the 8x8 chessboard, including placing pieces, updating board state, printing the current board, check detection, game state management, castling validation, and en passant tracking.

- **Game Class:**  
  Manages the overall game flow, including turns, move validation, switching between players, move history, user interaction, and special move parsing.

## **Technical Implementation Highlights**

### **Memory Management:**
- Proper use of copy constructors and destructors
- Dynamic memory allocation for pieces
- RAII principles for resource management

### **Algorithm Complexity:**
- Check detection: O(n²) where n is board size
- Legal move generation: O(n²) per piece
- Game state evaluation: O(n²)
- Castling validation: O(1) with piece movement tracking
- En passant validation: O(1) with target square tracking

### **Design Patterns:**
- **Strategy Pattern:** Different move validation for each piece type
- **Factory Pattern:** Piece creation and copying
- **Observer Pattern:** Game state monitoring

### **New Features Implementation:**
- **Castling:** Piece movement tracking, validation logic, and notation parsing
- **En Passant:** Target square tracking, automatic detection, and capture logic
- **Enhanced Move Parsing:** Support for castling notation (O-O, O-O-O)

### **Resume-Ready Features:**
- **Object-Oriented Programming:** Complete class hierarchy with inheritance and polymorphism
- **Memory Management:** Copy constructors, destructors, RAII principles
- **Algorithm Implementation:** Check detection, legal move generation, game state evaluation
- **Error Handling:** Comprehensive input validation and error messages
- **Design Patterns:** Strategy pattern for piece movement, Factory pattern for piece creation
- **Data Structures:** 2D arrays, vectors, pairs, sets for game state management
- **Game Development:** Complete chess rule implementation with state management
- **User Interface:** Command-line interface with help system and multiple input formats
- **Advanced Chess Rules:** Castling and En Passant implementation

---

## **Sample Gameplay Output**

```
=== CHESS GAME ===
Type 'help' for commands, 'quit' to exit
Move format: Use chess notation (e.g., 'e2 e4' or 'Nf3')

    a   b   c   d   e   f   g   h
  +---+---+---+---+---+---+---+---+
 8 | r | n | b | q | k | b | n | r | 8
  +---+---+---+---+---+---+---+---+
 7 | p | p | p | p | p | p | p | p | 7
  +---+---+---+---+---+---+---+---+
 6 |   |   |   |   |   |   |   |   | 6
  +---+---+---+---+---+---+---+---+
 5 |   |   |   |   |   |   |   |   | 5
  +---+---+---+---+---+---+---+---+
 4 |   |   |   |   |   |   |   |   | 4
  +---+---+---+---+---+---+---+---+
 3 |   |   |   |   |   |   |   |   | 3
  +---+---+---+---+---+---+---+---+
 2 | P | P | P | P | P | P | P | P | 2
  +---+---+---+---+---+---+---+---+
 1 | R | N | B | Q | K | B | N | R | 1
  +---+---+---+---+---+---+---+---+
    a   b   c   d   e   f   g   h

Legend: K/k=King, Q/q=Queen, R/r=Rook, B/b=Bishop, N/n=Knight, P/p=Pawn
       Uppercase=White, Lowercase=Black

White's turn.
Enter move (e.g., 'e2 e4') or command: e2 e4

Move 1: e2 to e4

    a   b   c   d   e   f   g   h
  +---+---+---+---+---+---+---+---+
 8 | r | n | b | q | k | b | n | r | 8
  +---+---+---+---+---+---+---+---+
 7 | p | p | p | p | p | p | p | p | 7
  +---+---+---+---+---+---+---+---+
 6 |   |   |   |   |   |   |   |   | 6
  +---+---+---+---+---+---+---+---+
 5 |   |   |   |   |   |   |   |   | 5
  +---+---+---+---+---+---+---+---+
 4 |   |   |   |   | P |   |   |   | 4
  +---+---+---+---+---+---+---+---+
 3 |   |   |   |   |   |   |   |   | 3
  +---+---+---+---+---+---+---+---+
 2 | P | P | P | P |   | P | P | P | 2
  +---+---+---+---+---+---+---+---+
 1 | R | N | B | Q | K | B | N | R | 1
  +---+---+---+---+---+---+---+---+
    a   b   c   d   e   f   g   h

Black's turn.
Enter move (e.g., 'e2 e4') or command: O-O

Move 2: Kingside castling

    a   b   c   d   e   f   g   h
  +---+---+---+---+---+---+---+---+
 8 | r | n | b | q |   | r | k |   | 8
  +---+---+---+---+---+---+---+---+
 7 | p | p | p | p | p | p | p | p | 7
  +---+---+---+---+---+---+---+---+
 6 |   |   |   |   |   |   |   |   | 6
  +---+---+---+---+---+---+---+---+
 5 |   |   |   |   |   |   |   |   | 5
  +---+---+---+---+---+---+---+---+
 4 |   |   |   |   | P |   |   |   | 4
  +---+---+---+---+---+---+---+---+
 3 |   |   |   |   |   |   |   |   | 3
  +---+---+---+---+---+---+---+---+
 2 | P | P | P | P |   | P | P | P | 2
  +---+---+---+---+---+---+---+---+
 1 | R | N | B | Q | K | B | N | R | 1
  +---+---+---+---+---+---+---+---+
    a   b   c   d   e   f   g   h
```

---

## **Future Improvements**  
- **Pawn Promotion Options:** Allow choice of promotion piece (Rook, Bishop, Knight, Queen)
- **Undo Feature:** Allow players to undo their last move
- **AI Opponent:** Add computer player with different difficulty levels
- **Graphical Interface:** Add a GUI to make the game more interactive
- **Network Multiplayer:** Enable online play between players
- **Game Save/Load:** Persist game state to files
- **Move Timer:** Add time controls for blitz and rapid games
- **Draw Offers:** Implement draw by agreement, threefold repetition, fifty-move rule

### **File Structure:**
```
2-Player-Chess-Game/
├── include/          # Header files
│   ├── Board.h
│   └── Game.h
├── src/             # Source files
│   ├── main.cpp
│   ├── Board.cpp
│   ├── Game.cpp
│   └── Pieces/      # Piece implementations
├── README.md        # This file
├── chessGame.exe    # Compiled executable
├── test_checkmate.txt    # Test file for checkmate
└── test_castling_enpassant.txt  # Test file for new features
```

---

## **Contributing**  
Feel free to submit pull requests or raise issues if you find any bugs or want to add new features.