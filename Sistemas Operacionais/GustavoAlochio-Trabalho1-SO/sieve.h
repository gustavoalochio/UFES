#ifndef SIEVE_H_
#define SIEVE_H_

#include "fila.h"

#define VPRIMOS 9999 /* tamanho do vetor de 
primos de cada threads*/
#define NTHREADS 8 // numero de threads

/*Tipo Vector. Contem campos:
  - tamanho (string)
  - buf (vetor de int)
  */

typedef struct{
  int tamanho;
  int *buf;
}Vector;
//------------------MUTEX'S--------------------
pthread_mutex_t   mutexResult;
pthread_mutex_t   mutexSieve[NTHREADS];
pthread_mutex_t   mutexJaMandei;
pthread_cond_t    podeConsumirNumero[NTHREADS];
//---------------------------------------------
//------------------COND'S---------------------
pthread_cond_t    podeInserirNumero[NTHREADS];
pthread_cond_t    podeConsumirResultado;
pthread_cond_t    podeInserirResultado;
//---------------------------------------------
//------------------THREAD'S-------------------
pthread_t         workers[NTHREADS];
pthread_t         threadResult;
//---------------------------------------------
//---------------VARIÁVEIS GLOBAIS-------------
int               valorLimite; 
int               N, M, ret;
int               jaMandei;
Fila              **buffersSieve;
Fila              *resultados;/* buffer de comunicação
 da thread de resultado*/
Vector            **primos; /*Onde será armazenado 
os primos que foram indentificados pela sieve*/
Fila              *bufferResultado;/*buffer auxiliar 
para armazenar todos os resultados*/
//---------------------------------------------



/*Define um um vetor dinamico de tamanho N apontando para 
elementos do tipo Vector
* inputs: é passado como argumento o tamanho do vetor a ser
alocado
* output: uma fila alocada dinamicamente
* pre-condicao: um inteiro
* pos-condicao: Um vetor alocado dinamicamente com todos os
seus elementos zerados
*/
Vector *definirVector(int N);

/*Função que será utilizada por uma thread
* inputs: um parametro do tipo void
* output: 
* pre-condicao: uma thread criada com sua função
* pos-condicao: 
*/
void *threadResults(void *param);

/*Função para verificar se o numero passado é divisivel 
pelo primo da ID e do nivel passados como argumento
* inputs: um numero, uma ID  e um nivel
* output: um inteiro booleano dizendo se é ou não divisivel
* pre-condicao: o ID seja valido em 0 e 7
* pos-condicao: 
*/
int ehDivisivel(int numero, int ID, int nivel);

/*Função que será utilizada por uma thread que será um verificador
de numeros
* inputs: um parametro do tipo void
* output: 
* pre-condicao: thread criada
* pos-condicao: thread será finalizada
*/
void *threadSieve(void *param);

/*Define uma matriz do tipo Vector
* inputs: A quantidade de linha e colunas
* output: uma matriz dinamica
* pre-condicao: 
* pos-condicao: matriz zerada.
*/
Vector **definirMatrizVector(int N, int tamanho);

#endif /* SIEVE_H_ */
