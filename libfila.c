#include<stdio.h>
#include <stdlib.h>
#include<time.h>

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


int ehVaziaL(lista *l)
{
    return l->cabeca == NULL;
}

lista *criaLista()
{
    lista *l = malloc(sizeof(lista));
    if(l == NULL) return NULL;
    l->cabeca = NULL;
    l->cauda = NULL;
    return l;
}

struct nodoL *criaNodoL(int cliente, int refeicao)
{
    struct nodoL *novo = malloc(sizeof(struct nodoL));
    if (novo == NULL) return NULL;
    novo->cliente = cliente;
    novo->refeicao = refeicao;
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

//A inserção feita na cauda
void enfilera(lista *l, struct nodoL *novo)
{
    if (ehVaziaL(l)) 
    {
        l->cabeca = novo;
        l->cauda = novo;
        return;
    }

    l->cauda->prox = novo;
    novo->ant = l->cauda;
    l->cauda = novo;
    novo->prox = NULL;
}

//popula lista com qnt pedidos aleatorios;
int populaAleatorio(lista *l, int qnt)
{
    srand(time(NULL));
    struct nodoL *novo;
    for(int i = 1; i <= qnt; i++)
    {
        novo = criaNodoL(i, (rand() % 6) + 1); //num aleatorio de 1 a 6
        if (novo == NULL) return 0;
        enfilera(l, novo);
    }
    return 1;
}

//remocao na cabeca
struct nodoL *desenfilera(lista *l)
{
    if (ehVaziaL(l)) return NULL; //lista ja esta vazia

    struct nodoL *removido = l->cabeca;
    if (removido->prox == NULL) //lista so tem um elemento
    {
        l->cabeca = NULL;
        l->cauda = NULL;
        removido->prox = NULL;
        removido->ant = NULL;
        return removido;
    }

    l->cabeca = removido->prox;
    removido->prox = NULL;
    removido->ant = NULL;
    return removido;
}

void destroiLista(lista *l)
{
    struct nodoL *aux;
    while(l->cabeca != NULL)
    {
        aux = desenfilera(l);
        free(aux);
    }
    free(l);
}


//funcao para testes, nao usada no jogo
void printaLista(lista *l)
{
    struct nodoL *aux = l->cabeca;
    while (aux != NULL)
    {
        printf("cliente: %d, refeicao: %d\n", aux->cliente, aux->refeicao);
        aux = aux->prox;
    }
    printf("\n");
    aux = l->cauda;
    while (aux != NULL)
    {
        printf("cliente: %d, refeicao: %d\n", aux->cliente, aux->refeicao);
        aux = aux->ant;
    }
    
}

void printaCincoPrimeiros(lista *l)
{
    struct nodoL *aux = l->cabeca;
    int i = 0;
    while ((aux != NULL) && (i < 5))
    {
        printf("[cliente %d | refeicao: %d]", aux->cliente, aux->refeicao);
        if((i != 4) && (aux->prox != NULL)) printf(" -> ");
        aux = aux->prox;
        i++;
    }
    printf("\n");
}

