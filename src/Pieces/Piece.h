#ifndef PIECE_H
#define PIECE_H

class Board; // Forward declaration

class Piece {
public:
    Piece(bool isWhite) : m_isWhite(isWhite) {}
    virtual ~Piece() {}
    virtual bool isValidMove(int x1, int y1, int x2, int y2, const Board& board) const = 0;
    virtual char getSymbol() const = 0;
    bool isWhite() const { return m_isWhite; }

private:
    bool m_isWhite;
};

#endif // PIECE_H
