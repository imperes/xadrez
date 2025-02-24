#include <QApplication>
#include "gameview.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GameView game;
    game.show();
    return a.exec();
}
