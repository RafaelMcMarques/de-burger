#include <stdio.h>
#include <stdlib.h>

struct nodoP 
{
    char dado;
    struct nodoP *baixo;
};


typedef struct 
{
    struct nodoP *topo;
}pilha;



pilha *criaPilha()
{
    pilha *nova_pilha = malloc(sizeof(pilha));
    if (nova_pilha == NULL) return NULL;
    nova_pilha->topo = NULL;
    return nova_pilha;
}

struct nodoP *criaNodoP(char dado)
{
    struct nodoP *novo = malloc(sizeof(struct nodoP));
    if (novo == NULL) return NULL;
    novo->dado = dado;
    novo->baixo = NULL;
    return novo;
}

int ehVaziaP(pilha *p)
{
    return (p->topo == NULL);
}

void push(pilha *p, struct nodoP *novo)
{
    novo->baixo = p->topo;
    p->topo = novo;
}

struct nodoP *pop(pilha *p)
{
    if (ehVaziaP(p))
    {
        printf("a pilha ja esta vazia\n");
        return NULL;
    }
    struct nodoP *antigo_topo = p->topo;
    p->topo = antigo_topo->baixo;
    antigo_topo->baixo = NULL;
    return antigo_topo;
}

void destroiPilha(pilha *p)
{
    struct nodoP *aux;
    while(p->topo != NULL)
    {
        aux = pop(p);
        free(aux);
    }
    free(p);
}

//printa a pilha no sentido fim-topo
void printaPilha(pilha *p)
{
    struct nodoP *aux = p->topo;
    while(aux != NULL)
    {
        printf("[%c] ", aux->dado);
        aux = aux->baixo;
    }   
    printf("\n\n");
}