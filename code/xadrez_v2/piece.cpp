#include "piece.h"
#include <QDebug>

Piece::Piece(PieceType type, PieceColor color, int x, int y)
    : type(type), color(color), xPos(x), yPos(y) {

    QString imgPath = ":/Images/";

    switch (type) {
    case Pawn:   imgPath += "pawn"; break;
    case Rook:   imgPath += "rook"; break;
    case Knight: imgPath += "knight"; break;
    case Bishop: imgPath += "bishop"; break;
    case Queen:  imgPath += "queen"; break;
    case King:   imgPath += "king"; break;
    }

    imgPath += (color == White) ? "_white.svg" : "_black.svg";

    QPixmap pixmap(imgPath);
    if (pixmap.isNull()) {
        qDebug() << "Erro ao carregar imagem:" << imgPath;
    } else {
        setPixmap(pixmap.scaled(70, 70));
    }

    setPosition(x, y);
}

void Piece::setPosition(int x, int y) {
    xPos = x;
    yPos = y;
    setPos(x * 75, y * 75);
}

// Função para verificar se o movimento é válido
bool Piece::isValidMove(int newX, int newY, Piece* board[8][8]) {
    int dx = abs(newX - xPos);
    int dy = abs(newY - yPos);

    // Se estiver tentando capturar peça da mesma cor, movimento inválido
    if (board[newY][newX] && board[newY][newX]->getColor() == color) {
        return false;
    }

    switch (type) {
    case Pawn:
        if (color == White) {
            if (newY == yPos - 1 && newX == xPos && !board[newY][newX]) return true; // Movimento normal
            if (newY == yPos - 2 && xPos == newX && yPos == 6 && !board[newY][newX] && !board[yPos - 1][xPos]){
                return true; // Duplo movimento inicial
            }
            if (newY == yPos - 1 && abs(newX - xPos) == 1 && board[newY][newX] && board[newY][newX]->getColor() != color) return true; // Captura diagonal
        } else {
            if (newY == yPos + 1 && newX == xPos && !board[newY][newX]) return true;
            if (newY == yPos + 2 && xPos == newX && yPos == 1 && !board[newY][newX] && !board[yPos + 1][xPos]) {
                return true;
            }
            if (newY == yPos + 1 && abs(newX - xPos) == 1 && board[newY][newX] && board[newY][newX]->getColor() != color) return true;
        }
        return false;

    case Rook:
        if (newX != xPos && newY != yPos) return false; // Só pode andar em linha reta
        for (int i = 1; i < std::max(dx, dy); i++) { // Verifica se há peças no caminho
            int stepX = (newX > xPos) ? xPos + i : (newX < xPos) ? xPos - i : xPos;
            int stepY = (newY > yPos) ? yPos + i : (newY < yPos) ? yPos - i : yPos;
            if (board[stepY][stepX]) return false;
        }
        return true;

    case Knight:
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2); // Movimento em "L"

    case Bishop:
        if (dx != dy) return false; // Tem que ser movimento diagonal
        for (int i = 1; i < dx; i++) {
            int stepX = (newX > xPos) ? xPos + i : xPos - i;
            int stepY = (newY > yPos) ? yPos + i : yPos - i;
            if (board[stepY][stepX]) return false;
        }
        return true;

    case Queen:
        if (dx == dy) { // Movimento diagonal
            for (int i = 1; i < dx; i++) {
                int stepX = (newX > xPos) ? xPos + i : xPos - i;
                int stepY = (newY > yPos) ? yPos + i : yPos - i;
                if (board[stepY][stepX]) return false;
            }
            return true;
        } else if (newX == xPos || newY == yPos) { // Movimento reto (torre)
            for (int i = 1; i < std::max(dx, dy); i++) {
                int stepX = (newX > xPos) ? xPos + i : (newX < xPos) ? xPos - i : xPos;
                int stepY = (newY > yPos) ? yPos + i : (newY < yPos) ? yPos - i : yPos;
                if (board[stepY][stepX]) return false;
            }
            return true;
        }
        return false;

    case King:
        if (dx <= 1 && dy <= 1) return true; // Movimento normal do rei

        // Roque
        if (!hasMoved && newY == yPos && dx == 2) {
            int rookX = (newX > xPos) ? 7 : 0; // Define a posição da torre
            Piece* rook = board[yPos][rookX];

            // Verifica se a torre existe e se nunca se moveu
            if (rook && rook->getType() == Rook && !rook->hasMovedBefore()) {
                int stepX = (newX > xPos) ? 1 : -1;

                // Verifica se há peças no caminho
                for (int i = xPos + stepX; i != rookX; i += stepX) {
                    if (board[yPos][i]) return false;
                }

                return true;
            }
        }
        return false;


    default:
        return false;
    }
}
