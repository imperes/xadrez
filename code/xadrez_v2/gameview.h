#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "piece.h"

class GameView : public QGraphicsView {
    Q_OBJECT

public:
    GameView(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;

private:
    QGraphicsScene *scene;
    Piece *tabuleiro[8][8] = {{nullptr}};
    Piece *selectedPiece = nullptr;
    PieceColor currentTurn;  // Cor do jogador atual (White ou Black)
    void setupBoard();
    void setupPieces();
    void capturePiece(int x, int y); // Função para remover peças capturadas
    QPointF getBoardPosition(int x, int y);
    bool isKingInCheck(PieceColor color);
    bool isCheckmate(PieceColor color);
    bool isSquareProtected(int x, int y, PieceColor attackerColor);
    bool gameOver = false;
    void showCheckmateMessage(PieceColor winner);
    void promotePawn(Piece* pawn, int x, int y);
    void resetGame();
    void highlightKingInCheck(PieceColor kingColor, bool isCheck);
    QGraphicsRectItem* kingCheckHighlight = nullptr; // Guarda o quadrado vermelho do Xeque

};

#endif // GAMEVIEW_H
