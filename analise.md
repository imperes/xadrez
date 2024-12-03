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

Apresentar o diagram de casos de uso, identificando as funcionalidades do sistema assim como os atores envolvidos
 
## Diagrama de Domínio do problema

Elaborar um diagrama conceitual do domínio do problema.


<div align="center">

[Retroceder](README.md) | [Avançar](projeto.md)

</div>
