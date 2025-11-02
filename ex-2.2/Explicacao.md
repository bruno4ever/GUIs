Primeiramente, foi feita uma enumeração com os estados possíveis.
O estado inicial é PARADO.

- Caso o evento recebido seja um pressionamento do botao do mouse dentro da área do quadrado, o estado muda para PRESSIONADO e é salvo a posição X e Y do mouse, e também a posição original do quadrado.
Também é calculado o deslocamento entre a borda do quadrado e a área em que o mouse foi pressionado, para que o quadrado siga corretamente o cursor na execução.

- Caso o evento recebido seja a tecla ESC e os estados atuais sejam PRESSIONADO ou ARRASTANDO, a posição original salva anteriormente é reestabelecida e o estado retorna para parado.

- Caso o mouse seja movido ainda no estado PRESSIONADO, o estado muda para ARRASTANDO e a posição do quadrado é atualizada, utilizando o deslocamento (distância entre a borda e o cursor), para que seja mantido o cursor encima da posição de clique original.

- Caso o evento recebido seja soltar o botão do mouse. Se o estado atual for PRESSIONADO, apenas muda o estado para PARADO. Se o estado atual for ARRASTANDO, é salva a posição atual do quadrado como a nova posição original, e o estado muda para PARADO.

Também foi adicionado um efeito de mudar levemente a cor do quadrado enquanto estiver sendo arrastado, diferenciando visualmente os estados PRESSIONADO e ARRASTANDO.
