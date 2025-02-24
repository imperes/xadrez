#include "gameview.h"
#include <QGraphicsRectItem>
#include <QTimer>
#include <QDebug>

GameView::GameView(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(601, 601);
    scene->setSceneRect(0, 0, 600, 600);

    currentTurn = White;  // Começa com as peças brancas
    setupBoard();
    setupPieces();
}

void GameView::setupBoard() {

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            QGraphicsRectItem *square = new QGraphicsRectItem(i * 75, j * 75, 75, 75);
            square->setBrush((i + j) % 2 == 0 ? QColor(125, 148, 93) : QColor(238, 238, 213)) ;
            scene->addItem(square);
        }
    }
}

void GameView::setupPieces() {
    for (int i = 0; i < 8; ++i) {
        tabuleiro[1][i] = new Piece(Pawn, Black, i, 1);
        scene->addItem(tabuleiro[1][i]);

        tabuleiro[6][i] = new Piece(Pawn, White, i, 6);
        scene->addItem(tabuleiro[6][i]);
    }

    tabuleiro[0][0] = new Piece(Rook, Black, 0, 0);
    tabuleiro[0][7] = new Piece(Rook, Black, 7, 0);
    tabuleiro[7][0] = new Piece(Rook, White, 0, 7);
    tabuleiro[7][7] = new Piece(Rook, White, 7, 7);

    tabuleiro[0][1] = new Piece(Knight, Black, 1, 0);
    tabuleiro[0][6] = new Piece(Knight, Black, 6, 0);
    tabuleiro[7][1] = new Piece(Knight, White, 1, 7);
    tabuleiro[7][6] = new Piece(Knight, White, 6, 7);

    tabuleiro[0][2] = new Piece(Bishop, Black, 2, 0);
    tabuleiro[0][5] = new Piece(Bishop, Black, 5, 0);
    tabuleiro[7][2] = new Piece(Bishop, White, 2, 7);
    tabuleiro[7][5] = new Piece(Bishop, White, 5, 7);

    tabuleiro[0][3] = new Piece(Queen, Black, 3, 0);
    tabuleiro[0][4] = new Piece(King, Black, 4, 0);
    tabuleiro[7][3] = new Piece(Queen, White, 3, 7);
    tabuleiro[7][4] = new Piece(King, White, 4, 7);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (tabuleiro[j][i])
                scene->addItem(tabuleiro[j][i]);
        }
    }
}

void GameView::mousePressEvent(QMouseEvent *event) {

    if (gameOver) {
        qDebug() << "Jogo encerrado! Não é possível fazer mais jogadas.";
        return;
    }

    QPointF clickedPos = mapToScene(event->pos());
    int x = clickedPos.x() / 75;
    int y = clickedPos.y() / 75;

    if (selectedPiece) {
        if (selectedPiece->isValidMove(x, y, tabuleiro)) {
            // Verifica se é uma captura
            if (tabuleiro[y][x] && tabuleiro[y][x]->getColor() != selectedPiece->getColor()) {
                // Se o Rei tentar capturar, verificar se a peça capturada está protegida
                if (selectedPiece->getType() == King) {
                    PieceColor opponentColor = (currentTurn == White) ? Black : White;
                    if (isSquareProtected(x, y, opponentColor)) {
                        qDebug() << "Movimento inválido: O rei não pode capturar uma peça protegida!";
                        return;
                    }
                }

                capturePiece(x, y); // Captura a peça adversária
            }
            // Após um movimento válido:
            if (selectedPiece->getType() == Pawn && (y == 0 || y == 7)) {
                promotePawn(selectedPiece, x, y);
            }

            // Verifica se o movimento é um Roque
            if (selectedPiece->getType() == King && abs(selectedPiece->getX() - x) == 2) {
                int rookX = (x > selectedPiece->getX()) ? 7 : 0; // Posição inicial da torre
                int newRookX = (x > selectedPiece->getX()) ? 5 : 3; // Nova posição da torre

                Piece* rook = tabuleiro[selectedPiece->getY()][rookX];

                if (rook && rook->getType() == Rook && !rook->hasMovedBefore()) {
                    // Move a torre para a nova posição
                    tabuleiro[selectedPiece->getY()][rookX] = nullptr;
                    rook->setPosition(newRookX, selectedPiece->getY());
                    tabuleiro[selectedPiece->getY()][newRookX] = rook;
                    rook->setMoved(); // Marca a torre como movida
                }
            }

            // Simula o movimento para verificar se deixa o rei em xeque
            Piece* temp = tabuleiro[y][x];
            tabuleiro[y][x] = selectedPiece;
            tabuleiro[selectedPiece->getY()][selectedPiece->getX()] = nullptr;
            int prevX = selectedPiece->getX();
            int prevY = selectedPiece->getY();
            selectedPiece->setPosition(x, y);


            if (isKingInCheck(currentTurn)) {
                qDebug() << "Rei está em xeque!";
                highlightKingInCheck(currentTurn, true); // Pinta de vermelho
                qDebug() << "Movimento ilegal: o rei está em xeque!";
                // Desfaz o movimento
                selectedPiece->setPosition(prevX, prevY);
                tabuleiro[selectedPiece->getY()][selectedPiece->getX()] = selectedPiece;
                tabuleiro[y][x] = temp;
                return;
            } else {
                highlightKingInCheck(currentTurn, false); // Remove o vermelho se o xeque for removido
            }

            // Atualiza o tabuleiro e marca que a peça já se moveu
            tabuleiro[y][x] = selectedPiece;
            selectedPiece->setMoved();

            // Alterna o turno
            currentTurn = (currentTurn == White) ? Black : White;

            // Verifica se o novo jogador está em xeque-mate
            if (isCheckmate(currentTurn)) {
                highlightKingInCheck(currentTurn, true); // Pinta de vermelho
                qDebug() << "Xeque-mate! O vencedor é " << ((currentTurn == White) ? "Preto" : "Branco");
                showCheckmateMessage((currentTurn == White) ? Black : White);
                gameOver = true; // Finaliza o jogo
            }
        } else {
            qDebug() << "Movimento inválido!";
        }
        selectedPiece = nullptr;
    } else if (tabuleiro[y][x] && tabuleiro[y][x]->getColor() == currentTurn) {
        selectedPiece = tabuleiro[y][x];
    }
}



void GameView::capturePiece(int x, int y) {
    if (tabuleiro[y][x]) { // Se houver uma peça na posição
        scene->removeItem(tabuleiro[y][x]); // Remove da cena
        delete tabuleiro[y][x]; // Libera a memória
        tabuleiro[y][x] = nullptr; // Marca a posição como vazia
    }
}

bool GameView::isKingInCheck(PieceColor color) {
    Piece* king = nullptr;

    // Encontra o rei do jogador atual
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tabuleiro[i][j] && tabuleiro[i][j]->getType() == King && tabuleiro[i][j]->getColor() == color) {
                king = tabuleiro[i][j];
                break;
            }
        }
    }

    if (!king) return false; // Se o rei não for encontrado, retorne falso

    // Verifica se alguma peça do oponente pode atacar o rei
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tabuleiro[i][j] && tabuleiro[i][j]->getColor() != color) {
                if (tabuleiro[i][j]->isValidMove(king->getX(), king->getY(), tabuleiro)) {
                    return true; // O rei está em xeque
                }
            }
        }
    }
    return false;
}

bool GameView::isCheckmate(PieceColor color) {
    if (!isKingInCheck(color)) return false; // Se o rei não estiver em xeque, não é xeque-mate

    // Testa se há algum movimento possível para sair do xeque
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* piece = tabuleiro[i][j];
            if (piece && piece->getColor() == color) { // Verifica as peças do jogador em xeque
                for (int newY = 0; newY < 8; newY++) {
                    for (int newX = 0; newX < 8; newX++) {
                        if (piece->isValidMove(newX, newY, tabuleiro)) {
                            // Simula o movimento para ver se sai do xeque
                            Piece* temp = tabuleiro[newY][newX];
                            tabuleiro[newY][newX] = piece;
                            tabuleiro[i][j] = nullptr;
                            int prevX = piece->getX();
                            int prevY = piece->getY();
                            piece->setPosition(newX, newY);

                            bool stillInCheck = isKingInCheck(color);

                            // Desfaz o movimento
                            piece->setPosition(prevX, prevY);
                            tabuleiro[i][j] = piece;
                            tabuleiro[newY][newX] = temp;

                            if (!stillInCheck) return false; // Se houver um movimento válido, não é xeque-mate
                        }
                    }
                }
            }
        }
    }

    return true; // Se nenhum movimento tirar o rei do xeque, é xeque-mate
}


bool GameView::isSquareProtected(int x, int y, PieceColor attackerColor) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* piece = tabuleiro[i][j];
            if (piece && piece->getColor() == attackerColor) {
                if (piece->isValidMove(x, y, tabuleiro)) {
                    return true; // A casa está protegida por uma peça do oponente
                }
            }
        }
    }
    return false; // Nenhuma peça inimiga protege essa casa
}

void GameView::showCheckmateMessage(PieceColor winner) {

    QString message = (winner == White) ? "Vitória das Brancas!" : "Vitória das Pretas!";
    QGraphicsTextItem* text = new QGraphicsTextItem(message);
    text->setFont(QFont("Arial", 24, QFont::Bold));
    text->setDefaultTextColor(Qt::red);
    text->setPos(150, 300);
    scene->addItem(text);

    // Criar um temporizador para reiniciar o jogo após 5 segundos (5000ms)
    QTimer::singleShot(5000, this, &GameView::resetGame);
}

void GameView::promotePawn(Piece* pawn, int x, int y) {
    // Salvar cor do peão antes de deletá-lo
    PieceColor color = pawn->getColor();

    // Remover o peão do tabuleiro antes de deletá-lo
    scene->removeItem(pawn);
    delete pawn;
    tabuleiro[y][x] = nullptr;

    // Criar a nova peça (Rainha por padrão)
    Piece* newPiece = new Piece(Queen, color, x, y);

    // Atualizar imagem da peça promovida
    QString imgPath = ":/Images/";
    imgPath += (color == White) ? "queen_white.svg" : "queen_black.svg";
    newPiece->setPixmap(QPixmap(imgPath).scaled(70, 70));

    // Adicionar a nova peça ao tabuleiro
    tabuleiro[y][x] = newPiece;
    scene->addItem(newPiece);

    // Definir a nova peça como ativa para continuar jogando
    selectedPiece = newPiece;

    qDebug() << "Peão promovido para Rainha!";
}

void GameView::resetGame() {
    // Remove todas as peças do tabuleiro
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (tabuleiro[y][x]) {
                scene->removeItem(tabuleiro[y][x]);
                delete tabuleiro[y][x];
                tabuleiro[y][x] = nullptr;
            }
        }
    }

    if (kingCheckHighlight) {
        scene->removeItem(kingCheckHighlight);
        delete kingCheckHighlight;
        kingCheckHighlight = nullptr;
    }

    // Remove mensagens de xeque-mate e elementos gráficos extras
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (dynamic_cast<QGraphicsTextItem*>(item) || dynamic_cast<QGraphicsRectItem*>(item)) {
            scene->removeItem(item);
            delete item;
        }
    }

    // **Recria a cena completamente**
    //delete scene; // Libera a memória da cena anterior
    //scene = new QGraphicsScene(this);
    //setScene(scene);

    // **Redesenha o tabuleiro**
    setupBoard();   // Redesenha o tabuleiro gráfico
    setupPieces();  // Reposiciona todas as
    gameOver = false;
    currentTurn = White;  // Começa com as peças brancas
}
void GameView::highlightKingInCheck(PieceColor kingColor, bool isCheck) {
    // Primeiro, remove qualquer destaque anterior (se houver)
    if (kingCheckHighlight) {
        scene->removeItem(kingCheckHighlight);
        delete kingCheckHighlight;
        kingCheckHighlight = nullptr;
    }

    // Se não for Xeque, apenas remove a marcação e sai
    if (!isCheck) {
        return;
    }

    // Encontra o rei no tabuleiro para pintá-lo de vermelho
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (tabuleiro[y][x] && tabuleiro[y][x]->getType() == King && tabuleiro[y][x]->getColor() == kingColor) {

                // Criar um retângulo vermelho semi-transparente sobre o rei
                kingCheckHighlight = new QGraphicsRectItem(x * 75, y * 75, 75, 75);
                kingCheckHighlight->setBrush(QColor(255, 0, 0, 80)); // Vermelho semi-transparente
                scene->addItem(kingCheckHighlight);

                return; // Sai do loop assim que encontrar o rei
            }
        }
    }
}
