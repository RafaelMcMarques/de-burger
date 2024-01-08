#include<stdlib.h>

char **criaMapa(int tamy, int tamx);

char **leArquivoMapa(int *tamy, int *tamx, FILE *arquivo);

void printaMapa(char **mapa, int tamy, int tamx);

void destroiMapa(char **mapa, int tamy, int tamx);

char atualizaPosicao(char **mapa, int *posy, int *posx, char mov);

void printaCardapio(char **cardapio);

char **criaCardapio();

int verificaPedido(pilha *pedido_atual, lista *pedidos, char **cardapio);