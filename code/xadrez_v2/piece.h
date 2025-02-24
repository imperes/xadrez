#ifndef PIECE_H
#define PIECE_H

#include <QGraphicsPixmapItem>

enum PieceType { Pawn, Rook, Knight, Bishop, Queen, King };
enum PieceColor { White, Black };

class Piece : public QGraphicsPixmapItem {
public:
    Piece(PieceType type, PieceColor color, int x, int y);
    void setPosition(int x, int y);
    bool isValidMove(int newX, int newY, Piece* board[8][8]);
    int getX() const { return xPos; }
    int getY() const { return yPos; }
    PieceColor getColor() const { return color; }
    PieceType getType() const { return type; }
    bool hasMovedBefore() const { return hasMoved; }
    void setMoved() { hasMoved = true; }

private:
    PieceType type;
    PieceColor color;
    int xPos, yPos;
    bool hasMoved = false;
};

#endif // PIECE_H
