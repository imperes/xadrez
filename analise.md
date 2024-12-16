# Análise orientada a objeto
> [!NOTE]
> <p>A <strong>análise</strong> orientada a objeto consiste na descrição do problema a ser tratado, duas primeiras etapas da tabela abaixo, a definição de casos de uso e a definição do domínio do problema.</p>


## Descrição Geral do domínio do problema

### Domínio do Problema: Jogo de Xadrez

O xadrez é um jogo de tabuleiro de posicionamento estratégico para dois jogadores, onde cada jogador faz o uso de 16 peças classificadas em 6 tipos de movimentações diferentes com o objetivo de colocar o rei adversário em uma posição em que ele não possa evitar ser capturado (xeque-mate). O jogo é ambientado em um tabuleiro xadrez de 8x8 casas, onde metade das casas são da cor branca e a outra metade pretas. O controle do jogo, a movimentação das peças e a detecção de condições de vitória e empate são os aspectos essenciais do sistema.

### Requisitos Funcionais

1. **Movimentação das Peças:**
    - O jogo deve permitir a movimentação das peças no tabuleiro de acordo com as regras do xadrez.
    - Deve ser possível mover as peças para casas válidas, e o sistema deve verificar se o movimento é permitido.

2. **Validação das Jogadas:**
    - O programa deve validar cada movimento de peça de acordo com as regras do jogo, impedindo movimentos ilegais.

3. **Controle de Turno:**
    - O jogo deve alternar entre os dois jogadores após cada movimento.

4. **Captura de Peças:**
    - As peças adversárias devem ser capturadas ao serem movidas para uma casa ocupada por uma peça do outro jogador.

5. **Xeque e Xeque-Mate:**
    - O sistema deve detectar quando o rei de um jogador está em xeque e impedir movimentos que não resolvam a ameaça de xeque.
    - O sistema deve detectar quando o jogo termina por xeque-mate ou empate.

6. **Interface Gráfica:**
    - O jogo pode ter uma interface gráfica para exibir o tabuleiro e as peças.

### Requisitos Não-Funcionais

1. **Desempenho:**
    - O jogo deve responder às ações dos jogadores, como realizar movimentos, detectar xeque e xeque-mate, e atualizar a interface.

2. **Facilidade de Uso:**
    - A interface deve simular um tabuleiro real de xadrez, os jogadores devem ser capazes de entender quais são as peças e executar seus movimentos.

3. **Portabilidade:**
    - O jogo deve ser executável ao menos em Windows.


## Diagrama de Casos de Uso

## Diagrama de Casos de Uso - Jogo de Xadrez

### Atores

- **Jogador 1**: O jogador que controla as peças brancas, iniciando sempre a partida.
- **Jogador 2**: O jogador que controla as peças pretas, sempre é o segundo a iniciar a partida.
- **Sistema**: O sistema controla as jogadas (validação das jogadas, troca de turnos, detecta condições de vitória, etc.), o fluxo da partida e traduz tudo em uma interface gráfica que simula um tabuleiro de xadrez real.

### Casos de Uso

#### 1. Início de Jogo
- **Ator**: Sistema
- Ao iniciar a partida, o sistema deve apresentar um tabuleiro de xadrez com dimensões de 8 x 8 casas, sendo estas alternadas entre casas pretas e brancas, com as peças dispostas nas posições oficiais do xadrez e com ícones reconhecíveis. O sistema também garante que a primeira jogada seja realizada obrigatoriamente pelo jogador com as peças brancas.

#### 2. Movimentar Peça
- **Atores**: Jogadores
- O jogador move uma peça de acordo com as regras do xadrez.

#### 3. Validar Movimento
- **Ator**: Sistema
- Após a jogada de cada participante, o sistema deve conferir se o movimento da peça é válido de acordo com as regras do xadrez, que são:
    - **Peão**: Anda uma casa para frente, exceto na jogada de abertura, onde ele pode andar duas casas.
    - **Torre**: Move-se por n casas livres no eixo "X" (cima e baixo) e no eixo "Y" (direita e esquerda).
    - **Cavalo**: Move-se em um formato de "L" (duas casas no eixo "Y" ou "X" e a casa de destino sendo imediatamente à direita ou à esquerda), podendo pular por cima de outras peças, desde que a casa de destino esteja livre de peças da mesma cor.
    - **Bispo**: Move-se em diagonal por n casas livres de sua cor no tabuleiro.
    - **Rainha**: Move-se por n casas livres no eixo "X", eixo "Y" e diagonais.
    - **Rei**: Move-se uma casa livre de sua cor no tabuleiro no eixo "X", eixo "Y" e diagonais.
- O sistema valida a jogada e atualiza o estado do tabuleiro. Caso a movimentação seja inválida, o sistema impede o movimento.

#### 4. Capturar Peça
- **Ator**: Sistema
- O sistema verifica se há uma peça adversária ocupando a casa de destino de uma peça movimentada. Caso haja, ela é capturada e removida do tabuleiro.

#### 5. Detectar Xeque
- **Ator**: Sistema
- O sistema verifica se o rei de um jogador está em xeque, ou seja, se está sob a ameaça de ser capturado por uma peça adversária. Se isso ocorrer, o sistema impede que o jogador faça movimentos que não resolvam o xeque.

#### 6. Detectar Xeque-Mate
- **Ator**: Sistema
- O sistema verifica se o rei está em uma situação de xeque-mate, ou seja, se o rei inimigo está em uma posição ameaçada que não pode ser revertida. Caso isso aconteça, o sistema declara a vitória do jogador adversário e encerra a partida.

#### 7. Alternar Turno
- **Ator**: Sistema
- Caso a jogada tenha sido legal, não haja mais nenhuma ameaça de xeque e não tenha ocorrido um xeque-mate, o sistema alterna o turno entre os dois jogadores.

### Fluxo de Trabalho

1. O sistema inicia o jogo mostrando o tabuleiro com as peças em posição inicial;
2. O jogador de brancas faz seu movimento (Movimentar Peça);
3. O sistema valida este movimento (Validar Movimento);
4. Se o movimento for válido, o sistema alterna o turno;
5. O jogador de pretas faz seu movimento (Movimentar Peça), e o processo se repete;
6. Durante o jogo, o sistema verifica se houve capturas de peças (Capturar Peças), se o rei está em xeque (Detectar Xeque) ou se ocorreu xeque-mate (Detectar Xeque-Mate);
7. Caso haja xeque, o jogador alvo deve resolver a situação para a partida prosseguir;
8. Caso o jogador não consiga se evadir do xeque, ocorre o xeque-mate, resultando na vitória do jogador adversário e encerrando a partida.

![Diagrama de Casos de Uso - Jogo de Xadrez](URL da imagem)
![Tabuleiro de Xadrez](https://link_da_imagem.com/imagem.jpg)

## Diagrama de Domínio do problema

Elaborar um diagrama conceitual do domínio do problema.


<div align="center">

[Retroceder](README.md) | [Avançar](projeto.md)

</div>
