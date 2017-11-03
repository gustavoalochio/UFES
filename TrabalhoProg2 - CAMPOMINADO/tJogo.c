#include<stdio.h>
#include "tJogo.h"

#define INVALIDA -1
#define ACABOU 0
#define CONTINUA 1

void RealizarJogo(tTabuleiro tabuleiro,tJogador jogador,char imprime[][N],
    int tabEspelho[][N],int tab[][N],char diretorio[])
{
    int GanhouPerdeu = 1;
    int i = 0;
    int contJogos = 1;
   	
    jogador.condicao = 3;
    
   	 do{
   	 
   	  	int x = tabuleiro.linhas, y = tabuleiro.colunas, jogada = 0;
   	  	
   	 	jogador.QtdJogadas = 0;
   	 	
		reiniciaJogo(tab,tabEspelho,tabuleiro);
		desenhaMatrizImpressao(tabuleiro,imprime);	    
		jogador = LeNome();	   
		imprimeSituacaoInicial(imprime,x,y);
		
		while(jogador.status != ACABOU)/*loop onde acontece cada jogo
		saindo desse loop começa-se outro jogo*/
		{	
			jogador = LeJogadas(jogador,jogada);			
			
			y = jogador.x[jogada];
			x = jogador.y[jogada];
			      
			jogador = FazJogada(jogador,tabuleiro,tab,imprime,y,x,jogada);
			
			if(jogador.status != INVALIDA)/*se jogada for invalida nao conta
			por tanto so soma uma jogada se nao for invalida*/
			{
				jogada++;
			}
			
			
			if(verificaSeGanhou(tabuleiro, imprime))
			{
				printf("%s Venceu!\n",jogador.nome);
				break;
			}
			
			if(jogador.status == ACABOU)/*Se o status for*/
			{
				printf("%s Perdeu!\n",jogador.nome);
				break;
			}
			
		}
				
		jogador.QtdJogadas = jogada;
				
		verificaMaiorImpacto(jogador, contJogos,diretorio);
		
		contJogos++;
			
	} while(continuarJogando());        
}

tJogador FazJogada(tJogador jogador,tTabuleiro tabuleiro,
    int tab[][N],char imprime[][N],int x,int y,int jogada)
{

    	int pInval = 0,jaAberta = 0;
    		    
        pInval = 0;
        jaAberta = 0;       
                  
        if(imprime[x][y] != tabuleiro.fechado 
            && !verificaSeTaFora(tabuleiro,x,y))
        {
           	jaAberta = 1;	   		
        }      
        else if(!verificaSeTaFora(tabuleiro,x,y))
        {
            if(tab[x][y] == 9)
            {
                imprime[x][y] = tabuleiro.Cbomba; 
                
                imprimeSituacao(tabuleiro,x,y,pInval,jaAberta
                    ,jogador,jogada,imprime); 
                    
                jogador.impacto[jogada] = 0;
                
                jogador.status = ACABOU;
                 
                return jogador;                    
            }         
            else
            {		
                jogador.impacto[jogada] = 0;
                jogador.impacto[jogada] 
                    = espandindoCasas(tabuleiro,x,y,tab,imprime);
                jogador.status = CONTINUA;
            }           
        }
        else
        {   	
            pInval = 1;        
        }
           
        imprimeSituacao(tabuleiro,x,y,pInval,jaAberta,jogador,jogada,imprime);
            

        if(pInval == 1 || jaAberta == 1)
        {
        	jogador.status = INVALIDA;
        	return jogador;
        }
            
     
  return jogador;
  
}
int espandindoCasas(tTabuleiro tabuleiro, 
    int jogadaX,int jogadaY,int tab[][N],char imprime[][N])
{
    int i = 0,j = 0,armazena = 0,impacto = 0;
    
    char visitados[tabuleiro.linhas][tabuleiro.linhas];
    
        	        
    i = jogadaX;
    j = jogadaY;
			

            if(tab[i][j] == 0)
            {
                tab[i][j] = 10;
                
                imprime[i][j] = tabuleiro.aberto;   
                
                impacto++;
                
                if((j - 1) >= 0 && (i - 1) >= 0)//diagonal superior esquerda//
                {                         
                    armazena = espandindoCasas(tabuleiro,i-1,j-1,tab,imprime);
                    impacto += armazena;       
                }
                
                if((i - 1) >= 0)//esquerda
                {   
                    armazena = espandindoCasas(tabuleiro,i-1,j,tab,imprime);
                    impacto += armazena;                   
                }
                
                if((j + 1) < tabuleiro.colunas && (i - 1) >= 0)//diagonal inferior esquerda
                {
                    armazena = espandindoCasas(tabuleiro,i-1,j+1,tab,imprime);
                    impacto += armazena;               
                }
                
                if((j - 1) >= 0)//cima
                {        
                    armazena = espandindoCasas(tabuleiro,i,j-1,tab,imprime);
                    impacto += armazena;
                }         
                if((j + 1) < tabuleiro.colunas)//baixo
                {            
                    armazena = espandindoCasas(tabuleiro,i,j+1,tab,imprime);
                    impacto += armazena;
                }
                if((j - 1) >= 0 && (i + 1) < tabuleiro.colunas)//diagonal superior direita
                {               
                    armazena = espandindoCasas(tabuleiro,i+1,j-1,tab,imprime);
                    impacto += armazena;
                }
                                  
                if((i + 1) < tabuleiro.linhas)//direita
                {  
                   armazena = espandindoCasas(tabuleiro,i+1,j,tab,imprime);
                   impacto += armazena;
                }
              
                if((j + 1) < tabuleiro.colunas && (i + 1) < tabuleiro.linhas)//diagonal inferior direita
                {                                   
		            armazena = espandindoCasas(tabuleiro,i+1,j+1,tab,imprime);
		            impacto += armazena; 	                         	          
                }                                        
        }
        else if(tab[i][j] > 0 && tab[i][j] < 9)
        {
            imprime[i][j] = tab[i][j] + '0';
            tab[i][j] = 10;
            return ++impacto;
        }
                         
    return impacto;
}

void imprimeSituacao(tTabuleiro tabuleiro,int pX,int pY,int pInval,
    int jaAberta,tJogador jogador,int jogada,char imprime[][N])
{
    int i = 0,j = 0,k = 0,bordaL = 0;
    
    char nomeArq[100];
      
        
        if(pInval == 1)
        {
            printf("Posicao invalida (FORA DO TABULEIRO)!\n");
        }   
        else if(jaAberta == 1)
        {
            printf("Posicao invalida (JA ABERTA)!\n");
        }
        else
        {
            printf("    ");
            for(i = 0;i < tabuleiro.linhas;i++)
                printf("%03d ",i);
            printf("\n");
            for(i = 0;i < tabuleiro.linhas;i++)
            {
                printf("%03d ",bordaL);
                bordaL++;
                for(j = 0;j < tabuleiro.colunas;j++)
                {
                    if(imprime[i][j] == tabuleiro.fechado)
                    {
                        for(k=0;k<3;k++)
                        {
                            printf("%c",imprime[i][j]);
                        }
                        printf(" ");
                    }
                    else
                    {
                        printf(" %c ",imprime[i][j]);
                        printf(" ");
                    }   
                          
                }
                printf("\n");
            }
         }
      
}

int continuarJogando()
{
    char condicao;
    printf("Jogar novamente? (s,n)\n");
    scanf("%c",&condicao);
    getchar();

    if(condicao == 'S' || condicao == 's') 
    {		    
       printf("Digitado (s)\n");

       return 1;	   
    }
    else
    {
        printf("Digitado (n)\n"); 
            return 0; 
    }
}

void reiniciaJogo(int tab[][N],int tabEspelho[][N],tTabuleiro tabuleiro)
{
    int i = 0,j = 0;
    
    for(i = 0;i < tabuleiro.linhas;i++)
    {
        for(j = 0;j < tabuleiro.colunas;j++)
        {
           tab[i][j] = tabEspelho[i][j];
        }
    }
}


int verificaMaiorImpacto(tJogador jogador, int contJogos,char diretorio[])
{
    int i = 0,j = 0,aux,jogadas = 0;
    
    int vetor[jogador.QtdJogadas];
   	jogadas = jogador.QtdJogadas;
   	    
    int aux_x, aux_y;
       
    for(i = 0 ;i < jogador.QtdJogadas; i++)
    {
        vetor[i] = i;
    }
        
    for(i = jogadas - 1; i >= 0; i--)//ordenação por bubble sort
    {
        for(j = 0; j < i ; j++) 
        {                 
            if(jogador.impacto[vetor[j]] < jogador.impacto[vetor[j+1]]) 
            {      
                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }
 
    char nomeArq[500];  
    sprintf(nomeArq, "%s/analiseJogo%02d.txt",diretorio,contJogos);
    FILE* arqOut = fopen(nomeArq,"w");
    
    
    if(!arqOut)
    {
        printf("ERRO: Nao foi possível salvar arquivo para analise.\n");
        return 0;
    }
    else
    {
        for(i = 0; i < jogadas; i++)
        {
        	
            if(jogador.impacto[vetor[i]] >= 0)
            {
                fprintf(arqOut,"JOGADA %d:", vetor[i]+1);
                fprintf(arqOut,"(%d,%d)",jogador.y[vetor[i]],jogador.x[vetor[i]]);
                fprintf(arqOut," %d\n",jogador.impacto[vetor[i]]);
            }
        }
        fclose(arqOut);
    }
    
    return 0;
}
