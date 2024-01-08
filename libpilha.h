#include <stdlib.h>

//implementacao de uma pilha atraves de um lista ligada

struct nodoP 
{
    char dado;
    struct nodoP *baixo;
};


typedef struct 
{
    struct nodoP *topo;
}pilha;

pilha *criaPilha();

struct nodoP *criaNodoP(char dado);

void push(pilha *p, struct nodoP *novo);

struct nodoP *pop(pilha *p);

void destroiPilha(pilha *p);

void printaPilha(pilha *p);