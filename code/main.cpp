#include "xadrez.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Xadrez w;
    w.show();
    return a.exec();
}
