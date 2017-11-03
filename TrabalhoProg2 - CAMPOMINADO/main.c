#include "tJogo.h"
#include "tTabuleiro.h"
#include "tJogador.h"
#include <stdio.h>
#include <stdlib.h>
#define N 1000

int main(int argc,char *argv[])
{
    if(argc < 1)
    {
        printf("ERRO: O diretorio de arquivos de configuração nao foi informado!");
        return 1;
    }
    char diretorio1[N];
    char diretorio2[N];
    
    sprintf(diretorio2,"%s",argv[1]);
    
    sprintf(diretorio1,"%s/tabuleiro.txt",argv[1]);
    
    
	tTabuleiro tabuleiro;
	tJogador jogador;
	int tab[N][N];        	
	   
    tabuleiro.status = 0;
    jogador.status = 0;
    tabuleiro = InicializaJogo(tab,diretorio1); 
    
    if(tabuleiro.status == -1)
    {
        printf("ERRO: O arquivo nao foi encontrado no diretorio %s!\n",diretorio1);
        return 1;
    }
    
    int tabEspelho[tabuleiro.linhas][N];	
    tabuleiro.bombas = numeroDeBombasVizinhas(tab,tabEspelho,tabuleiro);
    char imprime[tabuleiro.linhas][N];   
         
    RealizarJogo(tabuleiro,jogador,imprime,tabEspelho,tab,diretorio2);

    return 0;
}


