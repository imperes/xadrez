#ifndef BASE_PECAS_H
#define BASE_PECAS_H

#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include "iostream"
#include "stdio.h"
#include "string.h"
#include "math.h"

using namespace std;

enum tipo  //enum que classifica o tipo de peca
{
    peao,
    torre,
    cavalo,
    bispo,
    dama,
    rei
};

enum cor  //enum que classifica a cor ou jogador, da peca
{
    preto,
    branco
};

class base_pecas //classe pai, pecas
{
protected:

    enum tipo peca;
    enum cor jogador;

    int x_anterior;
    int y_anterior;
    int x_atual;
    int y_atual;
    bool primeira_jodada = true;

public:

    base_pecas(tipo peca, cor jogador, int y_atual, int x_atual);

    virtual bool movimento_valido(int &y_mov, int &x_mov) = 0;  //Deixar assim, no cpp a implementação é diferente!

    void movimenta_peca(int &y_mov, int &x_mov, base_pecas* tabuleiro[8][8]);

    bool testa_caminho(int x_mov, int y_mov, int dx, int dy, base_pecas* tabuleiro[8][8]);

    void imprime_posicao();

    tipo get_tipo() const;

    cor get_cor();

    int getX();

    int getY();
};


#endif // BASE_PECAS_H
