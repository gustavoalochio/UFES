#include <stdio.h>
#include "tTabuleiro.h"

tTabuleiro InicializaJogo(int tab[][N],char diretorio1[])
{
    tTabuleiro tabuleiro;
    tabuleiro.status = 0;
    FILE* pFile = fopen(diretorio1,"r");
    
    if(pFile == NULL)
    {
        printf("ERRO: O diretorio de arquivos de configuração nao foi informado!"
                "\n");
        tabuleiro.status = -1;
        return tabuleiro;
    }
    
	int i = 0;
	char matriz[N][N];
	
	fscanf(pFile,"%c%c%c\n",&tabuleiro.fechado,&tabuleiro.Cbomba,&tabuleiro.aberto);
            
	fscanf(pFile,"%d %d\n",&tabuleiro.linhas,&tabuleiro.colunas);
        
    for(i = 0;i < tabuleiro.linhas;i++)
		fscanf(pFile,"%[^\n]\n",matriz[i]);
		  
	transformaTabuleiroParaInteiro(matriz,tabuleiro,tab);    
	
	fclose(pFile);	    
		
	return tabuleiro;	
}

int transformaTabuleiroParaInteiro(char matriz[][N],tTabuleiro tabuleiro,int tab[][N])
{	
    int i = 0, j = 0,x,y;
    
    for(i = 0;i < tabuleiro.linhas; i++)
    {
        for(j = 0; j < tabuleiro.colunas ;j++)
        {
            if(matriz[i][j] == '1')
                tab[i][j] = 1;
                                
            if(matriz[i][j] == '0') 
                tab[i][j] = 0;
        } 
    }
    
	return 0;
}
void criaEspelho(int tab[][N],int tabEspelho[][N],int x,int y)
{
    int i = 0,j = 0; 
    for(i = 0;i < x; i++)
    {
        for(j = 0; j < y;j++)
        {
            tabEspelho[i][j] = tab[i][j];
        }
	}
}

void desenhaMatrizImpressao(tTabuleiro tabuleiro,char imprime[][N])
{
   int i = 0,j = 0;
   
    for(i = 0;i < tabuleiro.linhas; i++)
    {
        for(j = 0; j < tabuleiro.colunas;j++)
        { 
           imprime[i][j] = tabuleiro.fechado;            
        }
    }            
}

int numeroDeBombasVizinhas(int tab[][N],int tabEspelho[][N],tTabuleiro tabuleiro)
{
    int i = 0,j = 0,cont_bomba = 0,bombas = 0,x,y;
    criaEspelho(tab,tabEspelho,tabuleiro.linhas,tabuleiro.colunas);
    x = tabuleiro.linhas;
    y = tabuleiro.colunas;
    
    for(i=0;i < x;i++)
     {
        for(j=0;j < y;j++)
        {
            if(tab[i][j] == 0)
            {
                if((j - 1) >= 0 && (i - 1) >= 0)
                {
                    if(tabEspelho[i - 1][j - 1] == 1)
                        cont_bomba++;
                }
                if((i - 1) >= 0)
                {
                    if(tabEspelho[i - 1][j] == 1)
                        cont_bomba++;
                }
                if((j + 1) < y && (i - 1) >= 0)
                {
                    if(tabEspelho[i - 1][j + 1] == 1)
                        cont_bomba++;
                }
                if((j - 1) >= 0)
                {
                    if(tabEspelho[i][j - 1] == 1)
                        cont_bomba++;
                }         
                if((j + 1) < y)
                {
                    if(tabEspelho[i][j +1] == 1)
                        cont_bomba++;
                }
                 if((j - 1) >= 0 && (i + 1) < x)
                {
                    if(tabEspelho[i + 1][j - 1] == 1)
                        cont_bomba++;
                }                   
                if((i + 1) < x)
                {   
                    if(tabEspelho[i + 1][j] == 1)
                        cont_bomba++;
                }
              
                if((j + 1) < y && (i + 1) < x)
                {   
                    if(tabEspelho[i + 1][j + 1] == 1)
                        cont_bomba++;    
                }
              
                if(cont_bomba > 0)
                    tab[i][j] = cont_bomba;   
                
                cont_bomba = 0;          
            }
            else
            {
                tab[i][j] = 9;
                bombas++;
            }
        }
    }
    
    for(i = 0;i < x;i++)
    {
       for(j = 0;j < y;j++)
       {
            tabEspelho[i][j] = tab[i][j];
       }
    }
    
    return bombas;
}
int verificaSeGanhou(tTabuleiro tabuleiro, char imprime[][N])
{
    int i = 0, j = 0, cont = 0;
    
    for(i = 0;i < tabuleiro.linhas; i++)
    {
        for(j = 0; j < tabuleiro.colunas;j++)
        {
            if(imprime[i][j] == tabuleiro.fechado)
                cont++;
        }
    }
 
    if(cont == tabuleiro.bombas)
        return 1;
    else
        return 0;
}
int verificaSeTaFora(tTabuleiro tabuleiro, int pX, int pY)
{
    if(pX >= tabuleiro.linhas || pY >= tabuleiro.colunas || pX < 0 || pY < 0 )
    {
        return 1;
    }
    
  return 0;
}

void imprimeSituacaoInicial(char imprime[][N],int x,int y)
{
    int i = 0,j = 0,k = 0,bordaL = 0;
      
    printf("    ");
    
    for(i = 0;i < x;i++)
        printf("%03d ",i);
        
    printf("\n");
    
    for(i = 0;i < y;i++)
    {
        printf("%03d ",bordaL);
        bordaL++;
        for(j = 0;j < y;j++)
        {
            for(k=0;k<3;k++)
            {
                printf("%c",imprime[i][j]);
            }
            printf(" ");
                     
        }
        printf("\n");
    }
}






