#include "rei_peca.h"
#include "funcoes_auxiliares.h"

rei_peca::rei_peca(tipo peca, cor jogador, int y_atual, int x_atual)
    : base_pecas(peca, jogador, y_atual, x_atual) {}

bool rei_peca::movimento_valido(int &y_mov, int &x_mov)
{
    int dx = abs(x_atual - x_mov); // DiferenC'a em x
    int dy = abs(y_atual - y_mov); // DiferenC'a em y

    if((y_mov > 7 || y_mov < 0))
    {
        cout<<"JOGADA ILEGAL! CASA INEXISTENTE!"<<endl;
        return false;
    }
    else if (dx > 1 || dy > 1)
    {
        cout << "JOGADA ILEGAL! ANDOU MAIS QUE 1 CASA NA HORIZONTAL OU DIAGONAL" << endl;
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
