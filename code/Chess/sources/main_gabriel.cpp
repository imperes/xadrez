#include "gameview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameview w;
    w.show();
    return a.exec();
}
