#include<stdio.h>
#include "tJogador.h"


tJogador LeJogadas(tJogador jogador,int jogada)
{
 
    char temp[100];
    int jogada1,jogada2;
    
	printf("%s Jogada: %d\n",jogador.nome,jogada+1);
	printf("Digite a posicao (x e y):\n");
	scanf("%d %d",&jogada1,&jogada2);
	getchar();
    printf("Digitado (%d,%d)\n",jogada1,jogada2);

	jogador.x[jogada] = jogada2;
	jogador.y[jogada] = jogada1;
	  
    return jogador;	
}

tJogador LeNome()
{
    tJogador jogador;
    jogador.status = 5;
    printf("Digite o nome do jogador:\n");  	
    scanf("%[^\n]",jogador.nome);
    getchar();
    printf("Digitado (%s)\n",jogador.nome);
    jogador.condicao = 1;
     
    return jogador;
}

