#include<stdio.h>
#include<stdlib.h>
#include "libpilha.h"
#include "libfila.h"
#include "libdeburger.h"



int main()
{
    //abre arquivo do mapa
    FILE *arquivo = fopen("mapa.txt", "r");
    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo do mapa!\n");
        return 1;
    }

    //variaveis do mapa
    int tamy; int tamx;
    char **mapa;
    char mov; char item = ' ';
    mapa = leArquivoMapa(&tamy, &tamx, arquivo);
    if (mapa == NULL)
    {
        printf("Impossível alocar memoria!\n");
        return 1;
    }

    //variaveis do personagem
    int entregasErradas = 0;
    int refeicoesDescartadas = 0;
    int venceu = 0;
    int perdeu = 0;
    int posy = tamy/2;
    int posx = tamx/2;
    mapa[posy][posx] = '&';

    //cria pedido atual(pilha), lista de pedidos(fila) e cardapio
    lista *pedidos = criaLista();
    if(pedidos == NULL)
    {
        printf("Impossível alocar memoria!\n");
        return 1;
    }
    pilha *pedidoAtual = criaPilha();
    if(pedidoAtual == NULL)
    {
        printf("Impossível alocar memoria!\n");
        return 1;
    }
    char **cardapio = criaCardapio();
     if(cardapio == NULL)
    {
        printf("Impossível alocar memoria!\n");
        return 1;
    }

    //define dificuldade
    system("clear");
    int dificuldade;
    printf("Dificuldade do jogo(numero de pedidos na fila): ");
    scanf("%d", &dificuldade);
    getchar();
    if(!populaAleatorio(pedidos, dificuldade))
    {
        printf("Impossível alocar memoria!\n");
        return 1;
    }

    system("clear");
    //loop do jogo
    while(!venceu && !perdeu)
    {
        //printa menu do jogo
        printf("DESCARTES: %d | ERROS: %d\n\n", refeicoesDescartadas, entregasErradas);
        printaMapa(mapa, tamy, tamx);
        printaCincoPrimeiros(pedidos);
        printf("\nPEDIDO ATUAL: "); printaPilha(pedidoAtual);
        printf("CARDAPIO: \n");printaCardapio(cardapio);
        printf("\n\nSEU MOVIMENTO(wasd): ");

        //movimenta personagem
        scanf("%c", &mov);
        getchar();
        //movimenta persongem e armazena item em que ele encostou
        item = atualizaPosicao(mapa, &posy, &posx, mov);

        //chama evento ao enconstar em algum item: 

        //entregou refeicao
        if (item == '@')
        {
            if(!verificaPedido(pedidoAtual ,pedidos, cardapio))
            {
                entregasErradas++;
            }
            desenfilera(pedidos);
            destroiPilha(pedidoAtual);
            pedidoAtual = criaPilha();
        }

        //descartou refeicao
        else if(item == 'o')
        {
            refeicoesDescartadas++;
            destroiPilha(pedidoAtual);
            pedidoAtual = criaPilha();
        }

        //adicionou ingrediente a refeicao
        else if((item != ' ') && (item != '-' && (item != '|')))
        {
            struct nodoP *novo;
            novo = criaNodoP(item);
            if (novo == NULL)
            {
                printf("Impossível alocar memoria!\n");
                return 1;
            }
            push(pedidoAtual, novo);
        }

        //verifica condicoes de game over ou de vitoria
        if((entregasErradas == 3) || (refeicoesDescartadas == 5)) perdeu = 1;
        else if (ehVaziaL(pedidos)) venceu = 1;
        
        system("clear");       
    }

    if (perdeu) printf("VOCE PERDEU!\n");
    else printf("VOCE VENCEU!\n");

    //libera memoria
    free(cardapio);
    destroiPilha(pedidoAtual);
    destroiLista(pedidos);
    destroiMapa(mapa, tamy,tamx);
}