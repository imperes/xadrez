#ifndef XADREZ_H
#define XADREZ_H

#include <QWidget>

class Xadrez : public QWidget
{
    Q_OBJECT

public:
    Xadrez(QWidget *parent = nullptr);
    ~Xadrez();
};
#endif // XADREZ_H
