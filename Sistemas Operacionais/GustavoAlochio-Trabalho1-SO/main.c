#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "fila.h"
#include "sieve.h"


int main(int argc, char **argv){

  //N = LIMITE DE NUMEROS
  //M = TAMANHO DO BUFFER DE COMUNICAÇÃO ENTRE THREADS 

  if(argc != 3){
    printf("Error: argumentos errados!\n");
  }

  sscanf(argv[1],"%d",&N);
  sscanf(argv[2],"%d",&M);

  int                   i;
  int                   ID[NTHREADS];
  pthread_attr_t        attr;
  pthread_mutexattr_t   attrMutex;
  pthread_condattr_t    attrCond;

  //-------------------- Inicializando tudo ------------------------------------
  pthread_attr_init(&attr);
  pthread_mutexattr_init(&attrMutex);
  pthread_condattr_init(&attrCond);

  for(int j = 0;j < NTHREADS; j++){
    ID[j] = j;
    pthread_mutex_init(&mutexSieve[j], &attrMutex);
    pthread_cond_init(&podeConsumirNumero[j], &attrCond);
    pthread_cond_init(&podeInserirNumero[j], &attrCond);
  }
  pthread_mutex_init(&mutexJaMandei, &attrMutex);
  pthread_mutex_init(&mutexResult, &attrMutex);
  pthread_cond_init(&podeInserirResultado, &attrCond); 
  pthread_cond_init(&podeConsumirResultado, &attrCond); 

  jaMandei = 0;
  valorLimite = sqrt(N);

  resultados = definir();
  buffersSieve = malloc(NTHREADS * sizeof(Fila*));
  for(int j = 0; j < NTHREADS; j++){
    buffersSieve[j] = definir();
  }
  primos = definirMatrizVector(NTHREADS,N);

  for(int k = 0; k < NTHREADS; k++){
    for (int j = 0; j < N-1; j++){
      primos[k]->buf[j] = 0;
    }
  }

  bufferResultado = definir();
  //-----------------------------------------------------------------------



  //--------------------Cria Threads ------------------------------------
  for(int j = 0; j < NTHREADS; j++) {
    pthread_create(&workers[j], &attr, threadSieve, &ID[j]);
  }  
  pthread_create(&threadResult, &attr, threadResults, NULL);
  //-----------------------------------------------------------------------

  int First = 0;//Váriavel da primeira posição de thread
  for(i = 2; i <= N; i++) {

    /*Busy wait para garantir que sempre haverá um espaço livre para inserção
    de numeros*/
    while(1){
      pthread_mutex_lock(&mutexJaMandei);
      if(jaMandei == (NTHREADS*M) - 1){
        pthread_mutex_unlock(&mutexJaMandei);
      }
      else{
        pthread_mutex_unlock(&mutexJaMandei);
        break;
      }
    }

    pthread_mutex_lock(&mutexSieve[First]);
      while(tamanho(buffersSieve[First]) == M) { 
        pthread_cond_wait(&podeInserirNumero[First], &mutexSieve[First]);
      }
      tipo_info *info = cria_info(i);


      inserir(buffersSieve[First], info);
      jaMandei++;
      pthread_cond_signal(&podeConsumirNumero[First]);
    pthread_mutex_unlock(&mutexSieve[First]);
  }

  for(int i = 0; i < NTHREADS; i++) {
    pthread_join(workers[i], NULL);
  }
  pthread_join(threadResult,NULL);

  return 0;
}