#ifndef TJOGADOR_H

    #define	TJOGADOR_H
    #define N 1000
    #include <stdio.h>
    #include <stdlib.h>
    
    
    typedef struct{
    
	    char nome[N];
	    int QtdJogadas;
	    int condicao;
	    int x[N];
	    int y[N];
	   // int cont;
	    int impacto[N];
	    int status; //-1 perdeu, 0 continua, 1 ganhou
	    
    }tJogador;    
    
    
    tJogador LeJogadas(tJogador jogador,int jogada);
    /*Essa função entra como parametro uma estrutura jogador e qual e a jogada 
    da vez, lendo as coordenadas da jogada e imprimindo qual é a jogada e
    retorna para um vetor de coordenadas no tipo tJogador*/
    
    tJogador LeNome();
    /*Essa função le o nome do jogador, ela inicializa, com o pedido para 
    digitar o nome do jogador, e imprime qual foi o digitado e depois retorna
    um tipo tJogador onde sera armazenado o nome do jogador*/
    
#endif	
