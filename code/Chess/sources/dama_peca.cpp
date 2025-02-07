#include "dama_peca.h"
#include "funcoes_auxiliares.h"

dama_peca::dama_peca(tipo peca, cor jogador, int y_atual, int x_atual)
    : base_pecas(peca, jogador, y_atual, x_atual) {}

bool dama_peca::movimento_valido(int &y_mov, int &x_mov)
{
    int dx = abs(x_atual - x_mov); // DiferenC'a em x
    int dy = abs(y_atual - y_mov); // DiferenC'a em y

    if((y_mov > 7 || y_mov < 0))
    {
        cout<<"JOGADA ILEGAL!"<<endl;
        return false;
    }
    else if (dx == dy)

    {
        cout << "JOGADA VALIDA!" << endl;
        return true;
    }
    else if((dx > 0 && dy == 0) || (dx == 0 && dy > 0))
    {
        cout<<"JOGADA VALIDA!"<<endl;
        return true;
    }
    cout<<"JOGADA ILEGAL!"<<endl;
    return false;
}
