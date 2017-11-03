#ifndef TJOGO_H

    #define	TJOGO_H
    #define N 1000
    
    #include "tTabuleiro.h"
    #include "tJogador.h"
    #include <stdio.h>
    #include <stdlib.h>
     
    void RealizarJogo(tTabuleiro tabuleiro,tJogador jogador
        ,char imprime[][N],int tabEspelho[][N],int tab[][N],char diretorio[]);
    /*Essa função será a função principal do jogo onde ocorre a logica,
    sera passado como parametro um tipo tTabuleiro e tJogador, 
    e uma matriz de caracter e outra de inteiros*/
    
    void imprimeSituacao(tTabuleiro tabuleiro,int pX,int pY,
        int pInval,int jaAberta,tJogador jogador,int jogada,char imprime[][N]);
    /*Essa função recebe como parametro, um tipo tTabuleiro, coordenadas da 
    jogada e algumas condicoes de jogada invalida e tambem o numero da jogada,
     imprimido no arquivo a matriz de caracteres imprime,
     o nome do jogador no arquivo de saida a cada jogada feita pelo jogador, 
     ela também imprime se a casa da jogada ja foi aberta ou esta fora do 
     tabuleiro*/ 
       
    int continuarJogando();
    /*Essa função pergunta ao usuario se ele deseja continuar ou nao jogando 
    digitando 's' para continuar e 'n' para nao continuar jogando */
    
    tJogador FazJogada(tJogador jogador,tTabuleiro tabuleiro,
	int tab[][N],char imprime[][N],int x,int y,int jogada);
    /*Essa funçao recebe como parametro a uma matriz de caracter e outra de 
    inteiro, e as coordenadas da jogada e o numero da jogada, com isso ela
    faz acontecer a jogada, se for bomba acaba o jogo, se for um vazio chama
    a função de recursao flood fill (espandindoCasas) e se for invalida
    atribui o valor a estruta tJogador que tambem é retornada pela mesma*/
    
    int espandindoCasas(tTabuleiro tabuleiro
        , int jogadaX,int jogadaY, int tab[][N],char imprime[][N]);
    /* A função como ja diz espande as casas,é utilizada na função FazJogada,
     onde ela utiliza o algoritmo de flood fill, para abrir as casas vazias
      até encontrar contadores de bomba verificando as oito casas vizinhas*/
    
    int verificaMaiorImpacto(tJogador jogador, int contJogos,char diretorio[]);
    /*A função verifica, faz a ordenação por bubble sort, do maior impacto para 
    o menor, imprimindo todo essa ordenação em um arquivo de saida que
    saira na mesma pasta dos arquivos do jogo, e faz um contador com que
    toda vez que inicia um novo jogo crie uma arquivo .txt novo para as novas
    jogada*/
    
    
    void reiniciaJogo(int tab[][N],int tabEspelho[][N],tTabuleiro tabuleiro);
    /*Essa função limpa o tabuleiro que foi modificado em outras funções
    para se começar um novo jogo fazendo com que se reutilize o mesmo espaço*/
    
#endif	
