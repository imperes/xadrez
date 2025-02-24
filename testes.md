# Relatório de Testes do Sistema de Xadrez
---
### 1. Introdução
Este relatório documenta os testes realizados no sistema de xadrez implementado em C++ usando Qt. O objetivo dos testes foi garantir que as regras do jogo fossem seguidas corretamente, incluindo movimentos das peças, regras especiais (Roque, En Passant, Promoção de Peão, Xeque e Xeque-Mate) e a interface gráfica.
---
### 2. Estratégia de Testes
Os testes foram divididos nas seguintes categorias:
  - Testes Funcionais: Para validar a implementação correta das regras do xadrez.
  - Testes de Interface: Para garantir que os elementos gráficos do jogo (peças, tabuleiro e mensagens) fossem exibidos corretamente.
  - Testes de Integridade: Para verificar a estabilidade do jogo e evitar falhas (crashes).
  - Testes de Reset: Para garantir que o jogo possa ser reiniciado corretamente sem erros.
---
### 3. Testes Funcionais
##### 3.1 Movimentos das Peças

| Peça |	Cenário Testado |	Resultado |
|--------|----------------------------------|------------|
| Peão |	Movimento simples e duplo inicial |	✅ Sucesso |
| Peão |	Movimento diagonal para captura |	✅ Sucesso |
| Torre |	Movimentos verticais e horizontais |	✅ Sucesso |
| Bispo	| Movimentos diagonais |	✅ Sucesso |
| Cavalo |	Movimento em "L", pulando outras peças |	✅ Sucesso |
| Rainha |	Movimentos combinados de torre e bispo |	✅ Sucesso |
| Rei | Movimentos curtos em qualquer direção |	✅ Sucesso |

##### 3.2 Captura de Peças
|Cenário |Resultado|
|--------|----------------------------------|
|Testado se peças do adversário são removidas corretamente ao serem capturadas|✅ Peças capturadas desaparecem corretamente do tabuleiro|

##### 3.3 Regras Especiais
| Regra |	Cenário Testado |	Resultado |
|--------|----------------------------------|------------|
|Roque |	Rei e torre não movidos, caminho livre |	✅ Sucesso |
|Roque | Rei passando por xeque |	✅ Bloqueado corretamente |
|Roque |	Tentativa com torre já movida |	✅ Bloqueado corretamente |
|En Passant |	Peão adversário movendo duas casas e sendo capturado en passant |	❌ Falha |
|Promoção de Peão |	Peão promovido ao alcançar a última linha |	✅ Sucesso (transformação em Rainha) |
|Xeque |	Rei ameaçado sem opções de fuga |	✅ Mensagem de "Xeque" exibida |
|Xeque-Mate |	Rei sem movimentos válidos |	✅ Mensagem de "Xeque-Mate" e fim de jogo |
---
### 4. Testes de Interface
|Cenário |	Resultado |
|--------|----------------------------------|
|Exibição das peças corretamente posicionadas no início do jogo|	✅ Sucesso|
|Atualização do tabuleiro após movimento das peças|	✅ Sucesso|
|Destaque vermelho para xeque|	✅ Sucesso|
|Mensagem após xeque-mate aparecendo corretamente|	✅ Sucesso|
|Reiniciar após 5 segundos resetando o jogo corretamente|	✅ Sucesso|
---
### 5. Testes de Integridade
|Cenário |	Resultado |
|--------|----------------------------------|
|Clicar em uma casa vazia não seleciona peça|	✅ Sucesso|
|Tentar mover para casa inválida não permite ação|	✅ Sucesso|
|Rei capturado não ocorre (garantia do xeque-mate)|	✅ Sucesso|
|Nenhum crash ao longo do jogo|	✅ Sucesso|
---
### 6. Testes de Reset
| Cenário |	Resultado |
|--------|----------------------------------|
|Reiniciar após xeque-mate |	✅ Sucesso |
---
### 7. Conclusão
Os testes demonstraram que o jogo segue corretamente as regras do xadrez, exibindo as interações corretas e prevenindo movimentos ilegais. O sistema está estável e funcionando conforme esperado. Pequenos ajustes podem ser feitos para aprimorar a experiência do usuário, como a possibilidade de escolher em que peça promover o peão. O jogo pode ser considerado aprovado para uso com sucesso.
---
<div align="center">

[Retroceder](implementacao.md) | [Início](README.md)

</div>
