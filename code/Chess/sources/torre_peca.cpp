#include "torre_peca.h"
#include "funcoes_auxiliares.h"

extern base_pecas* tabuleiro[8][8];  //TEM QUE ATIVAR ISSO POR ENQUANTO POIS SENAO ELE NAO ENXERGA O TABULEIRO

torre_peca::torre_peca(tipo peca, cor jogador, int y_atual, int x_atual) :
    base_pecas(peca, jogador, y_atual, x_atual) {}

bool torre_peca::movimento_valido(int &y_mov, int &x_mov)
{
    int dx = abs(x_atual - x_mov);
    int dy = abs(y_atual - y_mov);
    if((y_mov > 7 || y_mov < 0))
    {
        cout<<"JOGADA ILEGAL!"<<endl;
        return false;
    }
    else if((dx > 0 && dy == 0) || (dx == 0 && dy > 0))
    {
        if(testa_caminho(x_mov, y_mov, dx, dy, tabuleiro))
        {
            cout<<"JOGADA VALIDA!"<<endl;
            return true;
        }
    }
    cout<<"JOGADA ILEGAL!"<<endl;
    return false;
}

