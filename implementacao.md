# Relatório de Implementação do Jogo de Xadrez

### 1. Introdução
Este relatório documenta a implementação do jogo de xadrez desenvolvido em C++ utilizando a biblioteca Qt. O objetivo do projeto foi criar um jogo funcional, permitindo a movimentação das peças seguindo as regras oficiais do xadrez, incluindo captura, xeque, xeque-mate, promoção de peão, roque e en passant.

---

### 2. Visão Geral da Implementação
O jogo foi implementado utilizando o paradigma de orientação a objetos, com classes bem definidas para as peças e para o tabuleiro. A interface gráfica foi desenvolvida com Qt, utilizando QGraphicsView para renderizar o tabuleiro e as peças.

##### 2.1. Estrutura do Código
O projeto é composto pelas seguintes classes:

 - GameView: Responsável pela interface gráfica, gestão do tabuleiro e regras de jogo.

 - Piece: Representa uma peça de xadrez, contendo informações sobre sua posição, tipo e cor.

 - Enumerações:

  - PieceType: Define os tipos de peças (Peão, Torre, Cavalo, Bispo, Rainha e Rei).

  - PieceColor: Define as cores das peças (Branco e Preto).

O projeto foi organizado em uma estrutura modular, separando a lógica do jogo, a interface gráfica e as regras de movimentação das peças. A seguir, a estrutura dos arquivos principais:
````
ChessGame/
│── xadrez_v2/
│── Sources/
│   ├── main.cpp
│   ├── gameview.cpp
│   ├── piece.cpp
│── Headers/
│   ├── gameview.h
│   ├── piece.h
│── Images/ (Imagens das peças)
│── ChessGame.pro (Arquivo de configuração do Qt)
````

---

### 3. Funcionalidades Implementadas
A implementação do jogo de xadrez envolveu os seguintes aspectos:

##### 3.1 Movimentação das Peças
Cada peça possui uma implementação específica para sua movimentação. A função isValidMove(int newX, int newY, Piece* board[8][8]) verifica se um movimento é permitido.

##### 3.2 Captura de Peças
Se uma peça tenta se mover para uma posição ocupada por uma peça adversária, a captura é realizada removendo a peça do tabuleiro.

##### 3.3 Roque
O roque foi implementado verificando se o rei e a torre envolvidos não foram movidos anteriormente e se não há peças no caminho. O movimento é realizado simultaneamente para o rei e a torre.

##### 3.4 Xeque e Xeque-Mate
A função isKingInCheck(PieceColor color) verifica se o rei está em xeque, e isCheckmate(PieceColor color) determina se há xeque-mate. Quando ocorre o xeque-mate, é exibida uma mensagem informando o vencedor.

##### 3.5 Promoção do Peão
Quando um peão alcança a oitava fileira, ele é promovido a uma rainha, substituindo a peça no tabuleiro com as propriedades de uma rainha.

##### 3.6 En Passant ❌
A captura en passant permitiria que um peão capturasse um peão adversário que tenha se movido duas casas a partir da posição inicial, conforme as regras oficiais do xadrez.

##### 3.7 Destacar Xeque
Quando um rei está em xeque, sua casa é destacada em vermelho. Se o rei sai do xeque, a cor do quadrado volta ao normal.
A função highlightKingInCheck(PieceColor kingColor, bool isCheck) é responsável por isso.

##### 3.8 Reiniciar Jogo
Quando ocorre xeque-mate, uma mensagem é exibida e após cinco segundos o jogo é reiniciado.

---

### 4. Considerações Finais
O jogo de xadrez foi implementado com sucesso, cobrindo todas as regras fundamentais do xadrez. Foram tomadas precauções para garantir que os movimentos fossem válidos e que regras avançadas fossem seguidas corretamente.

##### 4.1 Possíveis Melhorias Futuras

 - Implementar um sistema de cronômetro para limitar o tempo dos turnos.
 - Implementar um algoritmo de IA para jogar contra o computador.
 - Melhorias na interface gráfica para uma experiência mais imersiva.

---

<div align="center">

[Retroceder](projeto.md) | [Início](analise.md)

</div>
