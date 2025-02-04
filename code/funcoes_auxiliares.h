#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include "iostream"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "base_pecas.h"

using namespace std;

const char* cor_para_jogador(cor jogador);

const char* tipo_para_peca(tipo peca);

void inicializa_tabuleiro();

void exibir_tabuleiro();

#endif // FUNCOES_AUXILIARES_H
