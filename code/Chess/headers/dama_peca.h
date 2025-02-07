#ifndef DAMA_PECA_H
#define DAMA_PECA_H

#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include "iostream"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "base_pecas.h"

using namespace std;

class dama_peca : public base_pecas  //classe filha dama
{
public:
    dama_peca(tipo peca, cor jogador, int y_atual, int x_atual);

    bool movimento_valido(int &y_mov, int &x_mov);
};

#endif // DAMA_PECA_H
