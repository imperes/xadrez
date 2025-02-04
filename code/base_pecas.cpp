#include "base_pecas.h"
#include "funcoes_auxiliares.h"

base_pecas::base_pecas(tipo peca, cor jogador, int y_atual, int x_atual)
{
    this -> peca = peca;
    this -> jogador = jogador;
    this -> x_atual = x_atual;
    this -> y_atual = y_atual;
}

bool base_pecas::movimento_valido(int &y_mov, int &x_mov){} //Aqui temos que tirar o "virtual" deixar só no cpp!

void base_pecas::movimenta_peca(int &y_mov, int &x_mov, base_pecas* tabuleiro[8][8])
{
    if(movimento_valido(y_mov, x_mov))
    {
        this -> y_anterior = this -> y_atual;
        this -> x_anterior = this -> x_atual;
        this -> x_atual = x_mov;
        this -> y_atual = y_mov;
        cout<<"posicao anterior ("<<x_anterior<<" , "<<y_anterior<<")"<<endl;
        cout<<"posicao atual ("<<y_atual<<" , "<<x_atual<<")"<<endl;
        tabuleiro[y_anterior][x_anterior] = nullptr;
        tabuleiro[y_atual][x_atual] = this;
        return;
    }
    return;
}

bool base_pecas::testa_caminho(int x_mov, int y_mov, int dx, int dy, base_pecas* tabuleiro[8][8])
{
    int passo, passo_x, passo_y;
    //INICIO DO TESTE DE CAMINHO HORIZONTAL E VERTICAL
    if(dx == 0)
    {
        passo = (y_mov > y_atual) ? 1 : -1;
        for(int i = y_atual + passo; i != y_mov; i+=passo)
        {
            if(tabuleiro[i][x_atual] != nullptr)
            {
                cout<<"pessa na frente na vertical"<<endl;
                return false;
            }
        }
        if(tabuleiro[y_mov][x_atual] != nullptr )
        {
            //confere se a peca na casa de destino C) da mesma cor
            if(get_cor() == tabuleiro[y_mov][x_atual]->get_cor())
            {
                cout << "Pessa no destino na vertical" << endl; //se for, nao come
                return false;
            }
            else //se for ele come uuuuuuuuiiiiiiii!!!!!
            {
                cout << "Pessa comida na vertical, ele gostaaaaa!" << endl;
                return true;
            }
        }
    }
    else if(dy == 0)
    {
        passo = (x_mov > x_atual) ? 1 : -1;
        for(int i = x_atual + passo; i != x_mov; i+=passo)
        {
            if(tabuleiro[y_atual][i] != nullptr)
            {
                cout<<"pessa na frente na horizontal"<<endl;
                return false;
            }
        }
        if(tabuleiro[y_atual][x_mov] != nullptr )
        {
            //compara a peca de destino com a peca movida
            if(get_cor() == tabuleiro[y_atual][x_mov]->get_cor())
            {
                cout << "Pessa no destino na horizontal" << endl; //se for igual, nao come
                return false;
            }
            else // se for ele come
            {
                cout << "Pessa comida na horizontal, ele gostaaaaa!" << endl;
                return true; // A peC'a pode capturar
            }
        }
    }
        //FINAL DO TESTE DE CAMINHO HORIZONTAL E VERTICAL
        //--------------------------------------------------------------------------------------------
        //INICIO DO TESTE DE CAMINHO DIAGONAL
    else if(dx == dy)
    {
        passo_x = (x_mov > x_atual) ? 1 : -1;
        passo_y = (y_mov > y_atual) ? 1 : -1;
        for(int i = y_atual + passo_y; i != y_mov; i+= passo_y)
        {
            for(int j = x_atual + passo_x; j != x_mov; j += passo_x)
            {
                if(tabuleiro[i][j] != nullptr)
                {
                    cout<<"peca na frente na diagonal"<<endl;
                    return false;
                }
            }
        }
        if(tabuleiro[y_mov][x_mov] != nullptr)
        {
            if(get_cor() == tabuleiro[y_mov][x_mov] -> get_cor())
            {
                cout<<"peca de mesma cor no destino, nao pode comer!"<<endl;
                return false;
            }
            else
            {
                cout<<"peca comida na casa de destino, uuuuuuiiiii ele gosta!!!"<<endl;
                return true;
            }
        }
    }
    return true;
        //FINAL DO TESTE DE CAMINHO DIAGONAL
}

void base_pecas::imprime_posicao()
{
    cout<<"PECA "<< tipo_para_peca(this -> peca)<<" "<<cor_para_jogador(this -> jogador)
    << " POSICAO ("<<this -> y_atual<<" , "<< this -> x_atual <<")"<<endl;
}

tipo base_pecas::get_tipo() const {
    return peca;
}

cor base_pecas::get_cor() {
    return jogador;
}

int base_pecas::getX() {
    return x_atual;
}

int base_pecas::getY() {
    return y_atual;
}

