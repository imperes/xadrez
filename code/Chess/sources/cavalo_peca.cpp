#include "cavalo_peca.h"
#include "funcoes_auxiliares.h"

cavalo_peca::cavalo_peca(tipo peca, cor jogador, int y_atual, int x_atual)
        : base_pecas(peca, jogador, y_atual, x_atual) {}

bool cavalo_peca::movimento_valido(int &y_mov, int &x_mov)
{
    int dx = abs(x_atual - x_mov);
    int dy = abs(y_atual - y_mov);

    // verifica se andou 2 casas a frente e 1 ao lado

    // verifica se andou 1 casa a frente e 2 ao lado
    if((y_mov > 7 || y_mov < 0))
    {
        cout<<"JOGADA ILEGAL!"<<endl;
        return false;
    }
    else if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))
    {
        cout << "JOGADA VALIDA!" << endl;
        return true;
    }
    cout << "JOGADA ILEGAL!" << endl;
    return false;
}
