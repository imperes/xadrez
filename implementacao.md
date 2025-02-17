# Relatório de Implementação do Jogo de Xadrez

### 1. Introdução
Este documento descreve o processo de implementação do jogo de xadrez, incluindo as ferramentas utilizadas, as bibliotecas obrigatórias e as principais decisões técnicas tomadas durante o desenvolvimento. O objetivo do projeto foi criar um jogo de xadrez funcional e interativo utilizando C++ e Qt Creator .

---

### 2. Ferramentas Utilizadas
Para o desenvolvimento do jogo, utilizamos as seguintes ferramentas:

 - Linguagem de Programação : C++
 - Framework para Interface Gráfica : Qt Framework
 - IDE : Qt Creator
 - Sistema de Controle de Versão : Git
 - Bibliotecas Utilizadas :
   - QtWidgets : Para construção da interface gráfica
   - QtGraphicsScene : Para renderização de tabuleiro e peças
   - QtCore : Para manipulação de eventos e lógica de jogo

---

### 3. Estrutura do Projeto
O projeto foi organizado em uma estrutura modular, separando a lógica do jogo, a interface gráfica e as regras de movimentação das peças. A seguir, a estrutura dos arquivos principais:
````
ChessGame/
│── code/
│── Sources/
│   ├── main.cpp
│   ├── gameview.cpp
│   ├── boardview.cpp
│   ├── boardviewmodel.cpp
│   ├── boardfield.cpp
│   ├── basepawnmodel.cpp
│   ├── pawnpawnmodel.cpp
│   ├── knightpawnmodel.cpp
│   ├── bishoppawnmodel.cpp
│   ├── rookpawnmodel.cpp
│   ├── queenpawnmodel.cpp
│   ├── kingpawnmodel.cpp
│   ├── utils.cpp
│── Headers/
│   ├── gameview.h
│   ├── boardview.h
│   ├── boardviewmodel.h
│   ├── boardfield.h
│   ├── basepawnmodel.h
│   ├── pawnpawnmodel.h
│   ├── knightpawnmodel.h
│   ├── bishoppawnmodel.h
│   ├── rookpawnmodel.h
│   ├── queenpawnmodel.h
│   ├── kingpawnmodel.h
│   ├── utils.h
│── Images/ (Imagens das peças)
│── ChessGame.pro (Arquivo de configuração do Qt)
````

---

### 4. Implementação do Jogo
A implementação do jogo de xadrez envolveu os seguintes aspectos:

##### 4.1 Representação do Tabuleiro
O tabuleiro foi modelado usando uma aula BoardView, que utiliza QGraphicsScenepara desenhar as casas e organizar as peças. Cada casa do tabuleiro é representada pela classe BoardField.

##### 4.2 Representação das Peças
Cada peça é uma instância de uma classe derivada de BasePawnModel, que define um conjunto comum de propriedades e métodos para todas as peças:

 - PawnPawnModel(Peão)
 - KnightPawnModel(Cavalo)
 - BishopPawnModel(Bispo)
 - RookPawnModel(Torre)
 - QueenPawnModel(Rainha)
 - KingPawnModel(Rei)

Cada classe específica implementa a lógica de movimento da peça de acordo com as regras do xadrez.

##### 4.3 Movimentação das Peças
É validada pela classe BoardViewModel, que contém uma lógica para verificar se um movimento é válido com base nas regras do jogo.

 1. O jogador clica em uma peça.
 2. O sistema verifica se o turno está correto.
 3. O jogador seleciona um destino.
 4. O sistema valida a erros.
 5. Se for válido, a peça se move e gira alternadamente.

##### 4.4 Captura de Peças
Se uma peça tenta se mover para um espaço ocupado por uma peça adversária, a captura é processada removendo a peça capturada do tabuleiro.

##### 4.5 Regras Especiais Implementadas
Tivemos dificuldades nessa parte do projeto em algumas situações. Foi concluído apenas a promoção do peão.

❌ Roque : Validaria se o rei e a torre nunca se moveram e se não há peças entre eles.

✅ Promoção de Peão : Implementado na BoardViewModel, onde um peão que atinge a última linha do tabuleiro se transforma em uma rainha.

❌ En Passant : Permitiria que um peão capture outro que tenha avançado duas casas em seu primeiro movimento.

##### 4.6 Interface Gráfica
Uma interface foi construída utilizando QtWidgetse QGraphicsView. O GameViewgerenciamento da renderização do tabuleiro e da interação do usuário.

##### 4.7 Detecção de Xeque e Xeque-Mate
Uma lógica para detectar xeque e xeque-mate foi ruptura na BoardViewModel. O sistema verifica se o rei está sob ataque e impede que o jogador faça um movimento ilegal.

---

<div align="center">

[Retroceder](projeto.md) | [Início](analise.md)

</div>
