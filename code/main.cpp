#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include "iostream"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "base_pecas.h"
#include "funcoes_auxiliares.h"

using namespace std;

base_pecas* tabuleiro[8][8] = {nullptr}; // Inicializando o tabuleiro vazio

int main()
{
    int x_mov, y_mov;
    cout << "INICIO DE JOGO " << endl;
    inicializa_tabuleiro(); //coloca as peC'as no tabuleiro nas posiC'C5es iniciais
    exibir_tabuleiro(); // Exibe o tabuleiro inicial

    //SELECIONA QUAL PECA MANIPULAR
    base_pecas * peca = tabuleiro[7][0];  // ponteiro que aponta para um objeto do tipo peC'a
    //TESTA PEAO BRANCO = tabuleiro[6][3];
    //TESTA PEAO PRETO = tabuleiro[1][1];
    //TESTA BISPO PRETO = tabuleiro[0][2];
    //TESTA BISPO BRANCO = tabuleiro[7][2];
    //TESTA CAVALO PRETO = tabuleiro[0][1];
    //TESTA CAVALO BRANCO = tabuleiro[7][1];
    //TESTA TORRE PRETO = tabuleiro[0][0];
    //TESTA TORRE BRANCO = tabuleiro[7][0];
    //TESTA DAMA PRETO = tabuleiro[0][4];
    //TESTA REI PRETO = tabuleiro[0][3];
    for(;;)
    {
        if(peca != nullptr) {
            cout << "MOVA A PECA "<< tipo_para_peca(peca->get_tipo())<<" "
                 <<cor_para_jogador(peca->get_cor())<<"(LINHA , COLUNA)"<< endl;
            cout<<"POSICAO ATUAL: "<<endl;
            peca -> imprime_posicao(); //imprime a posiC'C#o atual da peC'a
            cin >> x_mov >> y_mov;     //le as coordenadas inseridas
            peca->movimenta_peca(x_mov, y_mov, tabuleiro); //movimenta a peC'a caso permitido
            peca->imprime_posicao();  //imprime a posiC'C#o
            exibir_tabuleiro(); // Exibe o tabuleiro
        }
        else
        {
            cout << "Nulptr detected!!!" << endl;  //erro de posiC'C#o de memC3ria
            break;
        }
    }
    return 0;
}


