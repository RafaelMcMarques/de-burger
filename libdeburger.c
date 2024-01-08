#include <stdlib.h>
#include <stdio.h>
#include "libfila.h"
#include "libpilha.h"
#define MAX 50


int QNTREFEICOES = 6;
char XBURGER[5] = {'P','Q','H' , 'p' , '\0'}; //1
char XSALADA[6] = {'P', 'S', 'H', 'p', '\0'}; //2
char COMBO1[7] = {'R', 'F', 'P', 'Q' , 'H', 'p', '\0' }; //3
char COMBO2[7] =  {'R', 'F', 'P', 'S', 'H', 'p', '\0' }; //4
char VEGETARIANO[6] ={'R', 'F', 'P', 'Q', 'p', '\0'}; //5
char VEGANO[6] = {'R', 'F', 'S', '\0'}; //6

/*o cardapio é um array bidimensional onde cardapio[i] 
contem os ingredientes da refeicao i + 1 */
char **criaCardapio()
{
    char **cardapio = malloc(QNTREFEICOES * (sizeof(char *)));
    if(cardapio == NULL) return NULL;
    cardapio[0] = XBURGER;
    cardapio[1] = XSALADA;
    cardapio[2] = COMBO1;
    cardapio[3] = COMBO2;
    cardapio[4] = VEGETARIANO;
    cardapio[5] = VEGANO;
    return cardapio;
}

//aloca memoria para matriz do mapa
char **criaMapa(int tamy, int tamx)
{
    char **mapa = malloc(tamy * sizeof(char *));
    if (mapa == NULL) return NULL;
    for(int i = 0; i < tamy; i++)
    {
        mapa[i] = malloc(tamx * sizeof(char));
        if (mapa[i] == NULL) return NULL;
    }
    return mapa;
}

//retorna matriz lida do arquivo, coloca o tamanho da matriz em tamy e tamx
char **leArquivoMapa(int *tamy, int *tamx, FILE *arquivo)
{
    char **mapa;
    //le tamanho do mapa
    fscanf(arquivo, "%d %d", tamy, tamx);
    if ((*tamy > MAX) || (*tamx > MAX))
    {
        printf("Tamanho de mapa invalido!\n");
        fclose(arquivo);
        return 0;
    }
    
    //aloca memoria para a matriz
    mapa = criaMapa(*tamy, *tamx);
    if (mapa == NULL)
    {
        fclose(arquivo);
        return NULL;
    }

    //le o mapa
    for (int i = 0; i < *tamy; i++)
        for (int j = 0; j < *tamx; j++)
        {
            fscanf(arquivo, "%c", &mapa[i][j]);
        }
    fclose(arquivo);
    return mapa;
}

void printaMapa(char **mapa, int tamy, int tamx)
{
    for(int i = 0; i < tamy; i++)
    {
        for(int j = 0; j < tamx; j++)
            printf("%c", mapa[i][j]);
    }
    printf("\n\n");
}

void destroiMapa(char **mapa, int tamy, int tamx)
{
    for (int i = 0; i < tamy; i++) free(mapa[i]);
    free(mapa);
}


//atualiza posicao do personagem no mapa baseado no movimento, retorna item que encostou
char atualizaPosicao(char **mapa, int *posy, int *posx, char mov)
{
    int posyAntiga = *posy;
    int posxAntiga = *posx;
    mapa[posyAntiga][posxAntiga] = ' '; //limpa pos antiga
    if(mov == 'w') *posy = *posy - 1;
    if(mov == 's') *posy = *posy + 1;
    if(mov == 'd') *posx = *posx + 1;
    if(mov == 'a') *posx = *posx - 1;

    char item = mapa[*posy][*posx];

    if (item != ' ') //posicao nao esta vaga
    {
        *posy = posyAntiga;
        *posx = posxAntiga;
    }
    mapa[*posy][*posx] = '&'; //atualiza posicao personagem
    return item;
}

void printaCardapio(char **cardapio)
{
    for (int i = 0; i < QNTREFEICOES ;i++)
    {
        printf("%d - ", i + 1); //numero da reficao
        for (int j = 0; cardapio[i][j] != '\0'; j++)
            printf("[%c] ", cardapio[i][j]);
        printf("\n");
    }
}

int verificaPedido(pilha *pedido_atual, lista *pedidos, char **cardapio)
{
    int refeicao = pedidos->cabeca->refeicao - 1; //indice da refeicao no cardapio
    struct nodoP *aux = pedido_atual->topo;
    int i;
    for(i = 0; (cardapio[refeicao][i] != '\0') && (aux != NULL); i++)
    {
        if (aux->dado != cardapio[refeicao][i])
            return 0;
        aux = aux->baixo;
    }
    //só retorna true se a pilha e cardapio[refeicao] tem mesmo tamanho e sao iguais
    if ((aux == NULL) && (cardapio[refeicao][i] == '\0'))
        return 1;

    return 0;
}