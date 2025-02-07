#include "peao_peca.h"
#include "funcoes_auxiliares.h"

peao_peca::peao_peca(tipo peca, cor jogador, int y_atual, int x_atual) :
    base_pecas(peca, jogador, y_atual, x_atual) {}

bool peao_peca::movimento_valido(int &y_mov, int &x_mov)
{
    int dx = 0, dy = 0;
    if(jogador == branco)
    {

        dx = abs(x_atual - x_mov);
        dy = -1*(y_mov - y_atual);
    }
    else
    {
        dx = abs(x_atual - x_mov);
        dy = -1*(y_atual - y_mov);
    }

    if((y_mov > 7 || y_mov < 0))
    {
        cout<<"JOGADA ILEGAL!"<<endl;
        return false;
    }
    else if((dy == 2 && dx == 0) && (primeira_jodada || dy == 1) && (dx == 0 && primeira_jodada))
    {
        primeira_jodada = !primeira_jodada;
        cout<<"JOGADA VALIDA!"<<endl;
        return true;
    }
    else if(dy == 1 && dx == 0 && !primeira_jodada)
    {
        cout<<"JOGADA VALIDA!"<<endl;
        return true;
    }
    cout<<"JOGADA ILEGAL!"<<endl;
    return false;
}
