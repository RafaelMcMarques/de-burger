#include<stdlib.h>

//implementacao de uma fila atraves de uma lista duplamente encadeada

struct nodoL
{
    int cliente;
    int refeicao;
    struct nodoL *prox;
    struct nodoL *ant;
};

typedef struct
{
    struct nodoL *cabeca;
    struct nodoL *cauda;
} lista;

lista *criaLista();

struct nodoL *criaNodoL(int cliente, int refeicao);

//popula lista com pedidos aleatorios
int populaAleatorio(lista *l, int qnt);

//inserção feita cauda
void enfilera(lista *l, struct nodoL *novo);

//remocao feita na cabeca
struct nodoL *desenfilera(lista *l);

void destroiLista(lista *l);

void printaLista(lista *l);

void printaCincoPrimeiros(lista *l);

int ehVaziaL(lista *l);


