#ifndef TTABULEIRO_H

    #define	TTABULEIRO_H
    #define N 1000
    #include <stdio.h>
    #include <stdlib.h>
    
    typedef struct{
    
	    char fechado;
	    char aberto;
	    char Cbomba;
	    int linhas;
	    int colunas;
	    int bombas;
            int status;
	        
    }tTabuleiro;
    
    tTabuleiro InicializaJogo(int tab[][N],char diretorio1[]);
    /*Essa função recebe como parametro uma matriz de inteiro e a string
    do diretorio digitado pelo usuario de onde estara o arquivo tabuleiro.txt
    para iniciar as configurações do tabuleiro retorna uma estrutura de dados
    tTabuleiro que contera todas as caracteristicas do tabuleiro*/
    
    int transformaTabuleiroParaInteiro(char matriz[][N],tTabuleiro tabuleiro
        ,int tab[][N]);
    /*Essa função recebe como parametro uma matriz de caracter e outra de 
    inteiros onde sera transformada a matriz de caracter para intero e salva na 
    matriz de inteiros para ser utilizada no programa*/
    
    void criaEspelho(int tab[][N],int tabEspelho[][N],int x,int y);
    /*Essa função cria uma matriz espelho da matriz de inteiro com o tamanho de 
    linhas e colunas ideal*/
    
    void desenhaMatrizImpressao(tTabuleiro tabuleiro,char imprime[][N]);
    /*Essa função recebe como parametro a estrutura tTabuleiro com as caracteri
    sticas do tabuleiro e a matriz de caracter, atribui os caracteres de impress
    ao a  essa matriz*/
    
    int numeroDeBombasVizinhas(int tab[][N]
        ,int tabEspelho[][N],tTabuleiro tabuleiro);
    /* Essa função percorre a matriz de inteiros que é passada como parametro
    e faz a contagem de cada casa do tabuleiro de quantas bombas ha nas oito
    vizinhanças e retorna o valor de bombas daquele tabuleiro que mais tarde
    sera usado em outra função*/
    
    int verificaSeGanhou(tTabuleiro tabuleiro,char imprime[][N]);
    /*Essa função percorre a matriz de caracteres e ve se o numero de casas
    ainda fechadas sera o numero de bombas do tabuleiro
    se der positovo retorna que o jogado ganhou*/
    
    int verificaSeTaFora(tTabuleiro tabuleiro, int pX,int pY);
    /*Esssa função verifica se a cordenada digitada ṕelo usuario esta fora do
    tabuleiro*/
    
    void imprimeSituacaoInicial(char imprime[][N],int x,int y);
    /*Essa função imprime o tabuleiro vazio sem nenhuma modificação ainda
    por isso chamada de situacao inicial onde nada foi feito*/
    
    
#endif	
