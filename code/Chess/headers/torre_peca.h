#ifndef TORRE_PECA_H
#define TORRE_PECA_H

#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include "iostream"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "base_pecas.h"

using namespace std;

class torre_peca : public base_pecas //classe filha torre
{
public:

    torre_peca(tipo peca, cor jogador, int y_atual, int x_atual);

    bool movimento_valido(int &y_mov, int &x_mov);
};


#endif // TORRE_PECA_H
