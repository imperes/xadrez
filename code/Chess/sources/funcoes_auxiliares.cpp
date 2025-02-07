#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include "iostream"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "base_pecas.h"

#include "base_pecas.h"
#include "bispo_peca.h"
#include "cavalo_peca.h"
#include "dama_peca.h"
#include "peao_peca.h"
#include "rei_peca.h"
#include "torre_peca.h"
#include "funcoes_auxiliares.h"

using namespace std;

extern base_pecas* tabuleiro[8][8];

const char* tipo_para_peca(tipo peca) // converte o tipo de peC'a para uma string, fins de impressC#o
{
    switch(peca)
    {
    case peao:
        return "PEAO";
    case torre:
        return "TORRE";
    case cavalo:
        return "CAVALO";
    case bispo:
        return "BISPO";
    case dama:
        return "DAMA";
    case rei:
        return "REI";
    default:
        return "NENHUMA";
    }
}

const char* cor_para_jogador(cor jogador) //converte o tipo de cor para uma string, fins de impressC#o
{
    if(jogador == 0)
    {
        return "PRETO";
    }
    return "BRANCO";
}

void inicializa_tabuleiro()  //inicializa as peC'as em suas posiC'C5es iniciais
{
    // Inicializando o tabuleiro
    int x = 0, y = 1;
    for (int i = 0; i < 8; i++)
    {
        tabuleiro[y][x] = new peao_peca(peao, preto, y, x);
        x++;
    }
    tabuleiro[0][0] = new torre_peca(torre, preto, 0, 0);
    tabuleiro[0][7] = new torre_peca(torre, preto, 0, 7);
    tabuleiro[0][1] = new cavalo_peca(cavalo, preto, 0, 1);
    tabuleiro[0][6] = new cavalo_peca(cavalo, preto, 0, 6);
    tabuleiro[0][2] = new bispo_peca(bispo, preto, 0, 2);
    tabuleiro[0][5] = new bispo_peca(bispo, preto, 0, 5);
    tabuleiro[0][4] = new dama_peca(dama, preto, 0, 4);
    tabuleiro[0][3] = new rei_peca(rei, preto, 0, 3);

    x = 0;
    y = 6;
    for (int i = 0; i < 8; i++)
    {
        //tabuleiro[y][x] = new peao_peca(peao, branco, y, x);
        x++;
    }
    tabuleiro[7][0] = new torre_peca(torre, branco, 7, 0);
    tabuleiro[7][7] = new torre_peca(torre, branco, 7, 7);
    tabuleiro[7][1] = new cavalo_peca(cavalo, branco, 7, 1);
    tabuleiro[7][6] = new cavalo_peca(cavalo, branco, 7, 6);
    tabuleiro[7][2] = new bispo_peca(bispo, branco, 7, 2);
    tabuleiro[7][5] = new bispo_peca(bispo, branco, 7, 5);
    tabuleiro[7][4] = new dama_peca(dama, branco, 7, 4);
    tabuleiro[7][3] = new rei_peca(rei, branco, 7, 3);
}

// Funcao que exibe o estado atual do tabuleiro
void exibir_tabuleiro()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (tabuleiro[i][j] == nullptr)
            {
                cout<<i<<j<<" ";  //imprime a coordenada da casa vazia

            }
            else
            {
                cout << tipo_para_peca(tabuleiro[i][j]->get_tipo())[0] <<
                    cor_para_jogador(tabuleiro[i][j]->get_cor())[0]<< " ";
                // Exibe a primeira letra do nome da peca (como P para peC#o)
                // Exibe a primeira letra da cor da peca
            }
        }
        cout << endl;
    }
}
