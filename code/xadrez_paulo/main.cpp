#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QBrush>
#include <QPen>
#include <iostream>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

using namespace std;

// Enum para seleção de peças
enum tipo
{
    peao,
    torre,
    cavalo,
    bispo,
    dama,
    rei
};

// Enum de cor da peça
enum cor
{
    preto,
    branco
};

// Classe base_pecas
class base_pecas
{
protected:
    enum tipo peca;
    enum cor jogador;
    int x_atual;
    int y_atual;

public:
    base_pecas(tipo peca, cor jogador, int x_atual, int y_atual)
        : peca(peca), jogador(jogador), x_atual(x_atual), y_atual(y_atual) {}

    virtual tipo getTipo() const { return peca; }  //Const aqui paar garantir que ninguém possa modificar o tipo
    virtual cor getCor() const { return jogador; } //e nem a cor da peça selecionada
    int getX() const { return x_atual; }           //nem a posição atual (são penas leitura métodos getters!!!!!)
    int getY() const { return y_atual; }
    void setX(int x) { x_atual = x; }
    void setY(int y) { y_atual = y; }

    // Método virtual para que cada classe filha teste a validade de seu movimento
    virtual bool validarMovimento(int x_destino, int y_destino, base_pecas* tabuleiro[8][8]) = 0;
};

// Classe peão
class peao_peca : public base_pecas
{
public:
    peao_peca(tipo peca, cor jogador, int x_atual, int y_atual)
        : base_pecas(peca, jogador, x_atual, y_atual) {}

    tipo getTipo() const override { return peao; }
    cor getCor() const override { return jogador; }

    //Aqui temos que usar o override para que a função abaixo possa sobreescrever dados na classe pai
    bool validarMovimento(int x_destino, int y_destino, base_pecas* tabuleiro[8][8]) override
    {
        // Movimentos do peão para a frente
        int direcao = (getCor() == branco) ? -1 : 1;  // Define a direção com base na cor da peça
            //caso for branco só vai para baixo(-1)
        //caso for preto só vai para cima(+1)

        // Verifica se a casa de destino está dentro dos limites do tabuleiro
        if (x_destino < 0 || x_destino >= 8 || y_destino < 0 || y_destino >= 8)
        {
            return false;
        }

        // Movimentos normais (uma casa para frente)
        if (x_destino == getX() && y_destino == getY() + direcao)
        {
            // Verifica se a casa de destino está vazia
            if (tabuleiro[y_destino][x_destino] == nullptr)
            {
                return true;
            }
        }

        //Movimentos especiais (primeiro movimento do peão, duas casas para frente)
        if(getY() == 6 && getCor() == branco && x_destino == getX() && y_destino == getY() + 2 * direcao)
        {
            if (tabuleiro[y_destino][x_destino] == nullptr && tabuleiro[getY() + direcao][x_destino] == nullptr)
            {
                return true;//Se não tiver peça na frente ele anda até 2 casas, senão ele é barrado!!!
            }
        }
        if(getY() == 1  && getCor() == preto && x_destino == getX() && y_destino == getY() + 2 * direcao)
        {
            if (tabuleiro[y_destino][x_destino] == nullptr && tabuleiro[getY() + direcao][x_destino] == nullptr)
            {
                return true; //Se não tiver peça na frente ele anda até 2 casas, senão ele é barrado!!!
            }
        }
        //testa se a casa destino não está vazia, se não testar antes da crash
        if((abs(getX()-x_destino) == abs(getY() - y_destino)) && (tabuleiro[y_destino][x_destino] != nullptr))
        {
            if(tabuleiro[y_destino][x_destino]->getCor()!= getCor()){return true;} //se tiver, e for adversário, come!
        }
        return false;
    }
};

// Classe torre
class torre_peca : public base_pecas
{
public:
    torre_peca(tipo peca, cor jogador, int x_atual, int y_atual)
        : base_pecas(peca, jogador, x_atual, y_atual) {}

    tipo getTipo() const override { return torre; }
    cor getCor() const override { return jogador; }

    bool validarMovimento(int x_destino, int y_destino, base_pecas* tabuleiro[8][8]) override
    {
        if (getY() == y_destino) //Verifica se o movimento é horizontal
        {
            // Movendo-se para a esquerda ou direita
            if (x_destino > getX()) // Movimento para a direita(do Bolso!!!!)
            {
                for (int i = getX() + 1; i < x_destino; ++i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[getY()][i] != nullptr)  // Se há uma peça no caminho
                    {
                        return false; //retorna falso
                    }
                }
            }
            else if (x_destino < getX()) // Movimento para a esquerda(do PT!!!)
            {
                for (int i = getX() - 1; i > x_destino; --i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[getY()][i] != nullptr)  // Se há uma peça no caminho
                    {
                        return false;  //retorna falso
                    }
                }
            }

            // Verifica a casa de destino
            if (tabuleiro[y_destino][x_destino] == nullptr || tabuleiro[y_destino][x_destino]->getCor() != getCor())
            {
                return true; // A casa de destino está vazia ou ocupada por uma peça adversária
            }
        }
        // LÓGICA ACIMA, SÓ QUE ESPELHADA PARA O EIXO Y!!!!
        else if (getX() == x_destino) //Verifica se o movimento é vertical
        {
            if (y_destino > getY()) //Se o movimento for para baixo
            {
                for (int i = getY() + 1; i < y_destino; ++i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[i][getX()] != nullptr)  // Se há uma peça no caminho
                    {
                        return false; //retorna falso
                    }
                }
            }
            else if (y_destino < getY()) // Movimento para cima
            {
                for (int i = getY() - 1; i > y_destino; --i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[i][getX()] != nullptr)  // Se há uma peça no caminho
                    {
                        return false;// retorna falso
                    }
                }
            }
            // Verifica a casa de destino
            if (tabuleiro[y_destino][x_destino] == nullptr || tabuleiro[y_destino][x_destino]->getCor() != getCor())
            {
                return true; // A casa de destino está vazia ou ocupada por uma peça adversária
            }
        }
        return false; // Caso não tenha validado o movimento
    }
};

// Classe bispo
class bispo_peca : public base_pecas
{
public:
    bispo_peca(tipo peca, cor jogador, int x_atual, int y_atual)
        : base_pecas(peca, jogador, x_atual, y_atual) {}

    tipo getTipo() const override { return bispo; }
    cor getCor() const override { return jogador; }

    bool validarMovimento(int x_destino, int y_destino, base_pecas* tabuleiro[8][8]) override
    {
        if (abs(getX() - x_destino) == abs(getY() - y_destino))
        {
            int passo_x = (x_destino > getX()) ? 1 : -1;
            int passo_y = (y_destino > getY()) ? 1 : -1;

            if (tabuleiro[y_destino][x_destino] != nullptr && tabuleiro[y_destino][x_destino]->getCor() == getCor())
            {
                return false;  // Não pode mover para uma casa com uma peça da mesma cor
            }

            for (int i = getY() + passo_y, j = getX() + passo_x;
                 i != y_destino && j != x_destino;
                 i += passo_y, j += passo_x)
            {
                if(tabuleiro[i][j] != nullptr){return false;}
            }
            return true;
        }
        return false;
    }
};

// Classe cavalo
class cavalo_peca : public base_pecas
{
public:
    cavalo_peca(tipo peca, cor jogador, int x_atual, int y_atual)
        : base_pecas(peca, jogador, x_atual, y_atual) {}

    tipo getTipo() const override { return cavalo; }
    cor getCor() const override { return jogador; }

    bool validarMovimento(int x_destino, int y_destino, base_pecas* tabuleiro[8][8]) override
    {
        if ((abs(x_destino - x_atual) == 1 && abs(y_destino - y_atual) == 2 ||
             abs(x_destino - x_atual) == 2 && abs(y_destino - y_atual) == 1)
            && (tabuleiro[y_destino][x_destino] == nullptr ||
                tabuleiro[y_destino][x_destino]->getCor() != getCor()))
        {
            return true;  // Movimento em L caso a casa for ocupada por uma peça de mesma
        }                 //cor, ele nega a movimentação
        return false;
    }
};

// Classe dama
class dama_peca : public base_pecas
{
public:
    dama_peca(tipo peca, cor jogador, int x_atual, int y_atual)
        : base_pecas(peca, jogador, x_atual, y_atual) {}

    tipo getTipo() const override { return dama; }
    cor getCor() const override { return jogador; }

    bool validarMovimento(int x_destino, int y_destino, base_pecas* tabuleiro[8][8]) override
    {
        if (getY() == y_destino) //Verifica se o movimento é horizontal
        {
            // Movendo-se para a esquerda ou direita
            if (x_destino > getX()) // Movimento para a direita(do Bolso!!!!)
            {
                for (int i = getX() + 1; i < x_destino; ++i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[getY()][i] != nullptr)  // Se há uma peça no caminho
                    {
                        return false; //retorna falso
                    }
                }
            }
            else if (x_destino < getX()) // Movimento para a esquerda(do PT!!!)
            {
                for (int i = getX() - 1; i > x_destino; --i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[getY()][i] != nullptr)  // Se há uma peça no caminho
                    {
                        return false;  //retorna falso
                    }
                }
            }
            // Verifica a casa de destino
            if (tabuleiro[y_destino][x_destino] == nullptr || tabuleiro[y_destino][x_destino]->getCor() != getCor())
            {
                return true; // A casa de destino está vazia ou ocupada por uma peça adversária
            }
        }
        // LÓGICA ACIMA, SÓ QUE ESPELHADA PARA O EIXO Y!!!!
        else if (getX() == x_destino) //Verifica se o movimento é vertical
        {
            if (y_destino > getY()) //Se o movimento for para baixo
            {
                for (int i = getY() + 1; i < y_destino; ++i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[i][getX()] != nullptr)  // Se há uma peça no caminho
                    {
                        return false; //retorna falso
                    }
                }
            }
            else if (y_destino < getY()) // Movimento para cima
            {
                for (int i = getY() - 1; i > y_destino; --i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[i][getX()] != nullptr)  // Se há uma peça no caminho
                    {
                        return false;// retorna falso
                    }
                }
            }
            // Verifica a casa de destino
            if (tabuleiro[y_destino][x_destino] == nullptr || tabuleiro[y_destino][x_destino]->getCor() != getCor())
            {
                return true; // A casa de destino está vazia ou ocupada por uma peça adversária
            }
        }
        if (abs(getX() - x_destino) == abs(getY() - y_destino))
        {
            int passo_x = (x_destino > getX()) ? 1 : -1;
            int passo_y = (y_destino > getY()) ? 1 : -1;

            if (tabuleiro[y_destino][x_destino] != nullptr && tabuleiro[y_destino][x_destino]->getCor() == getCor())
            {
                return false;  // Não pode mover para uma casa com uma peça da mesma cor
            }

            for (int i = getY() + passo_y, j = getX() + passo_x;
                 i != y_destino && j != x_destino;
                 i += passo_y, j += passo_x)
            {
                if(tabuleiro[i][j] != nullptr){return false;}
            }
            return true;
        }
        return false;
    }
};

// Classe rei
class rei_peca : public base_pecas
{
public:
    rei_peca(tipo peca, cor jogador, int x_atual, int y_atual)
        : base_pecas(peca, jogador, x_atual, y_atual) {}

    tipo getTipo() const override { return rei; }
    cor getCor() const override { return jogador; }

    bool validarMovimento(int x_destino, int y_destino, base_pecas* tabuleiro[8][8]) override
    {
        if ((getY() == y_destino) && (abs(getX() - x_destino) == 1)) //Verifica se o movimento é horizontal
        {
            // Movendo-se para a esquerda ou direita
            if (x_destino > getX()) // Movimento para a direita(do Bolso!!!!)
            {
                for (int i = getX() + 1; i < x_destino; ++i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[getY()][i] != nullptr)  // Se há uma peça no caminho
                    {
                        return false; //retorna falso
                    }
                }
            }
            else if (x_destino < getX()) // Movimento para a esquerda(do PT!!!)
            {
                for (int i = getX() - 1; i > x_destino; --i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[getY()][i] != nullptr)  // Se há uma peça no caminho
                    {
                        return false;  //retorna falso
                    }
                }
            }
            // Verifica a casa de destino
            if (tabuleiro[y_destino][x_destino] == nullptr || tabuleiro[y_destino][x_destino]->getCor() != getCor())
            {
                return true; // A casa de destino está vazia ou ocupada por uma peça adversária
            }
        }
        // LÓGICA ACIMA, SÓ QUE ESPELHADA PARA O EIXO Y!!!!
        else if ((getX() == x_destino) && (abs(getY() - y_destino) == 1)) //Verifica se o movimento é vertical
        {
            if (y_destino > getY()) //Se o movimento for para baixo
            {
                for (int i = getY() + 1; i < y_destino; ++i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[i][getX()] != nullptr)  // Se há uma peça no caminho
                    {
                        return false; //retorna falso
                    }
                }
            }
            else if (y_destino < getY()) // Movimento para cima
            {
                for (int i = getY() - 1; i > y_destino; --i)  // Verifica as casas entre a origem e o destino
                {
                    if (tabuleiro[i][getX()] != nullptr)  // Se há uma peça no caminho
                    {
                        return false;// retorna falso
                    }
                }
            }
            // Verifica a casa de destino
            if (tabuleiro[y_destino][x_destino] == nullptr || tabuleiro[y_destino][x_destino]->getCor() != getCor())
            {
                return true; // A casa de destino está vazia ou ocupada por uma peça adversária
            }
        }
        if (abs(getX() - x_destino) == abs(getY() - y_destino) && (abs(getX() - x_destino) == 1)) //Verifica mov. diagonal
        {
            int passo_x = (x_destino > getX()) ? 1 : -1;
            int passo_y = (y_destino > getY()) ? 1 : -1;

            if (tabuleiro[y_destino][x_destino] != nullptr && tabuleiro[y_destino][x_destino]->getCor() == getCor())
            {
                return false;  // Não pode mover para uma casa com uma peça da mesma cor
            }

            for (int i = getY() + passo_y, j = getX() + passo_x;
                 i != y_destino && j != x_destino;
                 i += passo_y, j += passo_x)
            {
                if(tabuleiro[i][j] != nullptr){return false;}
            }
            return true;
        }
        return false;
    }
};

// Classe Tabuleiro_de_Xadrez
class Tabuleiro_de_Xadrez : public QGraphicsView
{

public:
    //Quando no Main() é criado um tabuleiro, os métodos abaixo são iniciados
    Tabuleiro_de_Xadrez(QWidget *parent = nullptr) : QGraphicsView(parent) //Tabuleiro de Xadrez será gerenciada por QGraphicsView
    {
        cena = new QGraphicsScene(this); //Adiciona um objeto da classe QGraphicsScene e armazena um ponteiro cena
                                        //e o associa através do this ao estado de tabuleiro de xadrez
        setScene(cena); //Associa a cena criada acima com a classe QGraphicsView para exibí-la
        cena->setBackgroundBrush(QBrush(QColor(101, 67, 33))); //Pintar apenas o fundo da cena, sem afetar demais QWidgets

        Desenha_Tabuleiro(); //Percorre a cena adicionando as 8x8 casas do xadrez
        Adiciona_Pecas(); //Percorre as posições iniciais das peças e as desenha sobre as casas

        QPushButton* btnReset = new QPushButton("Resetar Tabuleiro", this); //Cria um botão interativo, com um texto,
                                                                    //o "this" significa que ele pertence à classe atual

        btnReset->setGeometry(690, 200, 150, 40);  //Ajuste do posicionamento do botão na cena
        btnReset->setStyleSheet("font-size: 14px; font-family: Arial; font-weight: bold; color: white;"
        " background-color: darkRed; border: 2px solid white; border-radius: 5px;");
        connect(btnReset, &QPushButton::clicked, this, &Tabuleiro_de_Xadrez::resetarTabuleiro);
        //conecta o botão a um signal da classe tabuleiro_de_xadrez um click de mouse nesse caso,
        //quando isso acontecer, ele chamará o método resetarTabuleiro()!

        TextoTurno = new QLabel(this); //Cria um novo QLabel e o coloca na cena peretencente ao tabuleiro
        TextoTurno->setGeometry(700, 110, 300, 40);  //Ajusta o posicionamento do QLabel criado

        numeroTurno = new QLabel(this); //Mesma coisa que acima
        numeroTurno->setGeometry(700, 80, 300, 40);  //pos em x, pos em y, largura em x, altura em y

        //Abaixo apenas a rotina de escrever o título + versão do código
        titulo1 = new QLabel(this); //Cria um novo QLabel e o coloca na cena peretencente ao tabuleiro
        titulo1->setGeometry(40, 110, 110, 40);  //Ajusta o posicionamento do QLabel criado
        titulo2 = new QLabel(this); //Cria um novo QLabel e o coloca na cena peretencente ao tabuleiro
        titulo2->setGeometry(70, 140, 110, 40);  //Ajusta o posicionamento do QLabel criado
        titulo3 = new QLabel(this); //Cria um novo QLabel e o coloca na cena peretencente ao tabuleiro
        titulo3->setGeometry(30, 170, 110, 40);  //Ajusta o posicionamento do QLabel criado
        titulo1->setStyleSheet("font-size: 16px; font-family: Arial; font-weight: bold; color: white;");
        titulo2->setStyleSheet("font-size: 16px; font-family: Arial; font-weight: bold; color: white;");
        titulo3->setStyleSheet("font-size: 16px; font-family: Arial; font-weight: bold; color: white;");
        titulo1 -> setText("XADREZÃO");
        titulo2 -> setText("DA");
        titulo3 -> setText("MASSA! Vr 3.7");
        //Fim da rotina de título. Depois tentar otimizar com uma função ex: escreve_textos(*label, texto, x, y)

        /*xqmate = new QLabel(this);
        xqmate -> setGeometry(300, 100, 300, 300);
        xqmate -> setStyleSheet("font-size: 36px; font-family: Comic-Sans; font-weight: bold; color: red;");
        xqmate -> setText("SE FODEU!!!!!");
        //GUARDANDO ESSA SURPRESINHA PRO XEQUE-MATE!!!!*/

        atualizarTurno();  //Inicializa o label com o turno atual
    }

protected:

    enum turno {BRANCAS, PRETAS}; //Possíveis jogadores do turno
    turno turno_jogador = BRANCAS; //Jogador do turno
    int turno_num = 0;   //Número do turno

    QLabel *TextoTurno;  //QLabel para exibir o turno atual
    QLabel *numeroTurno; //QLabel para exibir o número do turno atual
    QLabel *titulo1;
    QLabel *titulo2;
    QLabel *titulo3;
    //QLabel *xqmate; //guargando pro xeque-mate!

    //Método que detecta cliques do mouse e move as peças caso a posição do clique tenha alguma peça existente
    void mousePressEvent(QMouseEvent *event) override //método de QGraphicsView
    {
        int tamanho_da_casa = 57;
        int x = event->pos().x() / tamanho_da_casa; // Aqui pega a posição x e y do clique e as divide pelo tamanho
        int y = event->pos().y() / tamanho_da_casa; // da casa a fim de obter a linha e coluna da posição
        x -= 250 / 57;  //Fator de Correção do eixo x pelo aumento da largura!!!!
        if (x >= 0 && x < 8 && y >= 0 && y < 8) // Verifica se o mouse foi clicado dentro do tabuleiro
        {
            if (pecaSelecionada == nullptr) //Se a casa não tiver peça, não faz nada
            {
                if (tabuleiro[y][x] != nullptr) //Se tiver uma peça, ai segue a rotina abaixo
                {
                    base_pecas* peca = tabuleiro[y][x]; //Cria um ponteiro pra acessar a peça clicada

                    if ((peca->getCor() == branco && turno_jogador == BRANCAS) || //Verifica se a cor da peça
                        (peca->getCor() == preto && turno_jogador == PRETAS))     //selecionada bate com o turno do jogador
                    {
                        pecaSelecionada = peca; //Sea peça bater com o jogador do turno, atualiza posição com base no clique
                        posicaoInicialX = x;    //Posição inicial em x = x clicado
                        posicaoInicialY = y;    //Posição inicial em y = y clicado
                    }
                    else
                    {
                        return; //Se a peça não for do jogador do turno, impede o movimento
                    }
                }
            }
            else
            {
                if (pecaSelecionada->validarMovimento(x, y, tabuleiro))//Verifica se o movimento da peça é válido
                {
                    moverPeca(x, y);  //Caso o movimento seja válido, move a peça
                    turno_jogador = (turno_jogador == BRANCAS) ? PRETAS : BRANCAS;//E alterna o turno
                    atualizarTurno();  //atualiza o texto do turno
                }
                pecaSelecionada = nullptr; //Limpa o ponteiro da peça selecionada
            }
        }
    }

    //Método que atualiza a posição das peças tanto graficamente como em coordenadas
    void moverPeca(int x, int y)
    {
        base_pecas* peca_comida = tabuleiro[y][x]; //ponteiro para acessar a posição desejada
        if(peca_comida != nullptr)                 //Se o ponteiro estiver apontando para uma peça
        {
            QGraphicsItem* item_peca_comida = itemGrafico[peca_comida]; // Obtém o item gráfico da peça
            if (item_peca_comida != nullptr)    //verifica se a casa ainda possui um item gráfico
            {
                cena->removeItem(item_peca_comida);  // Remove o item gráfico da cena
                delete item_peca_comida;             // Deleta o item gráfico
            }
            tabuleiro[y][x] = nullptr;      // Limpa a posição no tabuleiro
        }
        tabuleiro[posicaoInicialY][posicaoInicialX] = nullptr; //Limpa o ponteiro da posição inicial da peça
        tabuleiro[y][x] = pecaSelecionada; //aloca a peça na nova coordenada x, y
        pecaSelecionada->setX(x); //Aciona o método setX em base_peca
        pecaSelecionada->setY(y); //Aciona o método setY em base_peca
                                  //Atualizando a posição da peça selecionada
        // Atualizar a posição do item gráfico associado à peça
        QGraphicsItem* item_peca = itemGrafico[pecaSelecionada]; //Ponteiro que busca a peça selecionada
            //acessa a posição onde a peça selecionada foi armazenada
        if (item_peca)
        {
            item_peca->setPos(x * 57, y * 57); //Aqui multiplicamos por 57 pois é o tamanho das casas
                //se não fizer isso, a peça fica em local errado!!!!!!!!
        }
    }

    void atualizarTurno()  //Função que indica o turno vigente na tela
    {
        if (turno_jogador == BRANCAS)
        {
            TextoTurno->setStyleSheet("font-size: 16px; font-family: Arial; font-weight: bold; color: white;");
            TextoTurno->setText("Turno: BRANCAS");
            turno_num += 1;
        }
        else
        {
            TextoTurno->setStyleSheet("font-size: 16px; font-family: Arial; font-weight: bold; color: black;");
            TextoTurno->setText("Turno: PRETAS");
            turno_num += 1;
        }
        numeroTurno->setStyleSheet("font-size: 16px; font-family: Arial; font-weight: bold; color: Red;");
        numeroTurno->setText(QString("Turno Número: %1").arg(turno_num));
    }

private:
    QGraphicsScene *cena;
    base_pecas* tabuleiro[8][8] = { nullptr }; //Matriz 8x8 de ponteiros nulos de base_pecas
    base_pecas* pecaSelecionada = nullptr;     //Índice que vai manipular a peça criada acima
    int posicaoInicialX = -1;
    int posicaoInicialY = -1; //Posições em x e y inexistentes, para nenhuma peça começar selecionada
    QMap<base_pecas*, QGraphicsPixmapItem*> itemGrafico; // Mapeamento entre peça e item gráfico ,ou seja,
                                                        //aloca cada peça em uma posição do mapa

    void Desenha_Tabuleiro()  // Função para desenhar o tabuleiro
    {
        int tamanho_da_casa = 57;
        for (int linha = 0; linha < 8; ++linha)
        {
            for (int coluna = 0; coluna < 8; ++coluna)
            {
                //addRect(pos x, pos y, largura da casa(57 px), altura da casa(57 px))
                QGraphicsRectItem *casa = cena->addRect(coluna * tamanho_da_casa, linha * tamanho_da_casa, tamanho_da_casa, tamanho_da_casa);
                if ((linha + coluna) % 2 == 0)
                    casa->setBrush(QBrush(Qt::white));//branco
                else
                    casa->setBrush(QBrush(QColor(184, 134, 11)));//passa valores RGB consultar tabela de cores
                                                            //e preenche a casa do tabuleiro com a cor escolhida
            }
        }
    }

    void resetarTabuleiro()  //Faz o reset do jogo através do botão de reset criado
    {
        for (int linha = 0; linha < 8; ++linha)
        {
            for (int coluna = 0; coluna < 8; ++coluna)
            {
                tabuleiro[linha][coluna] = nullptr;  //Varre o tabuleiro apagando todas as peças lógicas
            }
        }

        cena->clear();  //Limpa todas as imagens da cena (tabuleiro/peças)
        Desenha_Tabuleiro();  //Desenha o tabuleiro
        Adiciona_Pecas();    //Insere novamente as peças nas posições iniciais

        turno_jogador = BRANCAS;  // Reseta o turno para as brancas
        turno_num = 0;            //Reseta o número dos turnos
        atualizarTurno();         //Coloca o turno como Brancas no texto
    }

    // Função para adicionar as peças no tabuleiro
    void Adiciona_Pecas()
    {
        int tamanho_da_casa = 57;

        // Adiciona os peões brancos na linha 6
        //Qt::KeepAspectRatio usada para redimensionar corretamente a imagem com a casa
        //Qt::SmoothTransformation para deixar a peça sem bordas serrilhadas
        for (int coluna = 0; coluna < 8; ++coluna)
        {
            base_pecas* peao_branco = new peao_peca(peao, branco, coluna, 6);
            tabuleiro[6][coluna] = peao_branco;

            QPixmap peao_branco_img(":/new/prefix1/imagens/piaobranco.png");  // O caminho para a imagem
            peao_branco_img = peao_branco_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QGraphicsPixmapItem* peao_branco_item = cena->addPixmap(peao_branco_img);
            peao_branco_item->setPos(coluna * tamanho_da_casa, 6 * tamanho_da_casa);  // Ajuste de posição
            itemGrafico[peao_branco] = peao_branco_item;  // Mapeando a peça para o item gráfico
        }
        //Adiciona as duas torres brancas
        int coluna = 0;
        for (int i = 0; i < 2; ++i)
        {
            if(i == 1){coluna = 7;}

            base_pecas* torre_branco = new torre_peca(torre, branco, coluna, 7);
            tabuleiro[7][coluna] = torre_branco;

            QPixmap torre_branco_img(":/new/prefix1/imagens/torrebranca.png");  // O caminho para a imagem
            torre_branco_img = torre_branco_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QGraphicsPixmapItem* torre_branco_item = cena->addPixmap(torre_branco_img);
            torre_branco_item->setPos(coluna * tamanho_da_casa, 7 * tamanho_da_casa);  // Ajuste de posição
            itemGrafico[torre_branco] = torre_branco_item;  // Mapeando a peça para o item gráfico
        }
        //Adiciona os dois cavalos brancos
        coluna = 1;
        for (int i = 0; i < 2; ++i)
        {
            if(i == 1){coluna = 6;}

            base_pecas* cavalo_branco = new cavalo_peca(cavalo, branco, coluna, 7);
            tabuleiro[7][coluna] = cavalo_branco;

            QPixmap cavalo_branco_img(":/new/prefix1/imagens/cavalobranco.png");  // O caminho para a imagem
            cavalo_branco_img = cavalo_branco_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QGraphicsPixmapItem* cavalo_branco_item = cena->addPixmap(cavalo_branco_img);
            cavalo_branco_item->setPos(coluna * tamanho_da_casa, 7 * tamanho_da_casa);  // Ajuste de posição
            itemGrafico[cavalo_branco] = cavalo_branco_item;  // Mapeando a peça para o item gráfico
        }
        //Adiciona os dois bispos brancos
        coluna = 2;
        for (int i = 0; i < 2; ++i)
        {
            if(i == 1){coluna = 5;}

            base_pecas* bispo_branco = new bispo_peca(bispo, branco, coluna, 7);
            tabuleiro[7][coluna] = bispo_branco;

            QPixmap bispo_branco_img(":/new/prefix1/imagens/bispobranco.png");  // O caminho para a imagem
            bispo_branco_img = bispo_branco_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QGraphicsPixmapItem* bispo_branco_item = cena->addPixmap(bispo_branco_img);
            bispo_branco_item->setPos(coluna * tamanho_da_casa, 7 * tamanho_da_casa);  // Ajuste de posição
            itemGrafico[bispo_branco] = bispo_branco_item;  // Mapeando a peça para o item gráfico
        }
        //Adiciona a rainha branca
        coluna = 3;
        base_pecas* dama_branco = new dama_peca(dama, branco, coluna, 7);
        tabuleiro[7][coluna] = dama_branco;

        QPixmap dama_branco_img(":/new/prefix1/imagens/rainhabranca.png");  // O caminho para a imagem
        dama_branco_img = dama_branco_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem* dama_branco_item = cena->addPixmap(dama_branco_img);
        dama_branco_item->setPos(coluna * tamanho_da_casa, 7 * tamanho_da_casa);  // Ajuste de posição
        itemGrafico[dama_branco] = dama_branco_item;  // Mapeando a peça para o item gráfico
        //Adiciona o rei branco
        coluna = 4;
        base_pecas* rei_branco = new rei_peca(rei, branco, coluna, 7);
        tabuleiro[7][coluna] = rei_branco;

        QPixmap rei_branco_img(":/new/prefix1/imagens/reibranco.png");  // O caminho para a imagem
        rei_branco_img = rei_branco_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem* rei_branco_item = cena->addPixmap(rei_branco_img);
        rei_branco_item->setPos(coluna * tamanho_da_casa, 7 * tamanho_da_casa);  // Ajuste de posição
        itemGrafico[rei_branco] = rei_branco_item;  // Mapeando a peça para o item gráfico

        // Adiciona os peões pretos na linha 1
        for (int coluna = 0; coluna < 8; ++coluna)
        {
            base_pecas* peao_preto = new peao_peca(peao, preto, coluna, 1);
            tabuleiro[1][coluna] = peao_preto;

            QPixmap peao_preto_img(":/new/prefix1/imagens/piaopreto.png");  // O caminho para a imagem
            peao_preto_img = peao_preto_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QGraphicsPixmapItem* peao_preto_item = cena->addPixmap(peao_preto_img);
            peao_preto_item->setPos(coluna * tamanho_da_casa, 1 * tamanho_da_casa);  // Ajuste de posição
            itemGrafico[peao_preto] = peao_preto_item;  // Mapeando a peça para o item gráfico
        }

        //Adiciona as duas torres pretas
        coluna = 0;
        for (int i = 0; i < 2; ++i)
        {
            if(i == 1){coluna = 7;}

            base_pecas* torre_preto = new torre_peca(torre, preto, coluna, 0);
            tabuleiro[0][coluna] = torre_preto;

            QPixmap torre_preto_img(":/new/prefix1/imagens/torrepreta.png");  // O caminho para a imagem
            torre_preto_img = torre_preto_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QGraphicsPixmapItem* torre_preto_item = cena->addPixmap(torre_preto_img);
            torre_preto_item->setPos(coluna * tamanho_da_casa, 0 * tamanho_da_casa);  // Ajuste de posição
            itemGrafico[torre_preto] = torre_preto_item;  // Mapeando a peça para o item gráfico
        }
        //Adiciona os dois cavalos pretos
        coluna = 1;
        for (int i = 0; i < 2; ++i)
        {
            if(i == 1){coluna = 6;}

            base_pecas* cavalo_preto = new cavalo_peca(cavalo, preto, coluna, 0);
            tabuleiro[0][coluna] = cavalo_preto;

            QPixmap cavalo_preto_img(":/new/prefix1/imagens/cavalopreto.png");  // O caminho para a imagem
            cavalo_preto_img = cavalo_preto_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QGraphicsPixmapItem* cavalo_preto_item = cena->addPixmap(cavalo_preto_img);
            cavalo_preto_item->setPos(coluna * tamanho_da_casa, 0 * tamanho_da_casa);  // Ajuste de posição
            itemGrafico[cavalo_preto] = cavalo_preto_item;  // Mapeando a peça para o item gráfico
        }
        //Adiciona os dois bispos pretos
        coluna = 2;
        for (int i = 0; i < 2; ++i)
        {
            if(i == 1){coluna = 5;}

            base_pecas* bispo_preto = new bispo_peca(bispo, preto, coluna, 0);
            tabuleiro[0][coluna] = bispo_preto;

            QPixmap bispo_preto_img(":/new/prefix1/imagens/bispopreto.png");  // O caminho para a imagem
            bispo_preto_img = bispo_preto_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QGraphicsPixmapItem* bispo_preto_item = cena->addPixmap(bispo_preto_img);
            bispo_preto_item->setPos(coluna * tamanho_da_casa, 0 * tamanho_da_casa);  // Ajuste de posição
            itemGrafico[bispo_preto] = bispo_preto_item;  // Mapeando a peça para o item gráfico
        }
        //Adiciona a rainha preta
        coluna = 3;
        base_pecas* dama_preto = new dama_peca(dama, preto, coluna, 0);
        tabuleiro[0][coluna] = dama_preto;

        QPixmap dama_preto_img(":/new/prefix1/imagens/rainhapreta.png");  // O caminho para a imagem
        dama_preto_img = dama_preto_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem* dama_preto_item = cena->addPixmap(dama_preto_img);
        dama_preto_item->setPos(coluna * tamanho_da_casa, 0 * tamanho_da_casa);  // Ajuste de posição
        itemGrafico[dama_preto] = dama_preto_item;  // Mapeando a peça para o item gráfico
        //Adiciona o rei preto
        coluna = 4;
        base_pecas* rei_preto = new rei_peca(rei, preto, coluna, 0);
        tabuleiro[0][coluna] = rei_preto;

        QPixmap rei_preto_img(":/new/prefix1/imagens/reipreto.png");  // O caminho para a imagem
        rei_preto_img = rei_preto_img.scaled(tamanho_da_casa, tamanho_da_casa, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem* rei_preto_item = cena->addPixmap(rei_preto_img);
        rei_preto_item->setPos(coluna * tamanho_da_casa, 0 * tamanho_da_casa);  // Ajuste de posição
        itemGrafico[rei_preto] = rei_preto_item;  // Mapeando a peça para o item gráfico
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    Tabuleiro_de_Xadrez *tabuleiro = new Tabuleiro_de_Xadrez();
    mainWindow.setCentralWidget(tabuleiro);
    mainWindow.resize(870, 470);
    mainWindow.show();
    return app.exec();
}
