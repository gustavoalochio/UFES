#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "sieve.h"
#include "fila.h"


Vector *definirVector(int N){
  Vector *v = malloc(sizeof(Vector));

  v->buf = calloc((N - 1), sizeof(int));

  return v;
}

Vector **definirMatrizVector(int N, int tamanho){
  Vector **v = malloc(N * sizeof(Vector*));

  for(int i = 0; i < N; i++){
    v[i] = definirVector(tamanho);
  }

  return v;
}

tipo_info **definirVectorInfo(int tamanho){
  tipo_info **vector = malloc(tamanho * sizeof(tipo_info*));

  return vector;
}

int compara(const void* a,const void* b){

  tipo_info **info1 = (tipo_info**) a;
  tipo_info **info2 = (tipo_info**) b;

  int numero1 = (*info1)->numero;
  int numero2 = (*info2)->numero;

  return numero1 - numero2;
}

void *threadSieve(void *param){
  int ID = *((int*)param);
  int nextID = (ID + 1)%NTHREADS;

  while (1) {
    pthread_mutex_lock(&mutexSieve[ID]);
      while(tamanho(buffersSieve[ID]) == 0){
        pthread_cond_wait(&podeConsumirNumero[ID], &mutexSieve[ID]);
      } 
      tipo_info *n = remover(buffersSieve[ID]);
      pthread_cond_signal(&podeInserirNumero[ID]);
    pthread_mutex_unlock(&mutexSieve[ID]);

    //função para checar numero
    if(primos[ID]->buf[n->nivel] == 0){
      pthread_mutex_lock(&mutexResult);
        primos[ID]->buf[n->nivel] = n->numero;
        n->ehPrimo = 1;
        n->numThread = ID;

        while(tamanho(resultados) == M) { 
          pthread_cond_wait(&podeInserirResultado, &mutexResult);
        }

        inserir(resultados, n);
        pthread_cond_signal(&podeConsumirResultado);
      pthread_mutex_unlock(&mutexResult);
    }
    else if(ehDivisivel(n->numero, ID, n->nivel)){
      pthread_mutex_lock(&mutexResult);
        n->ehPrimo = 0;
        n->divisor = ehDivisivel(n->numero, ID, n->nivel);
        n->numThread = ID;

        while(tamanho(resultados) == M) { 
          pthread_cond_wait(&podeInserirResultado, &mutexResult);
        }
        inserir(resultados, n);
        pthread_cond_signal(&podeConsumirResultado);
      pthread_mutex_unlock(&mutexResult);
    }
    else{
      pthread_mutex_lock(&mutexSieve[nextID]);
        while(tamanho(buffersSieve[nextID]) == M){
          pthread_cond_wait(&podeInserirNumero[nextID],&mutexSieve[nextID]);
        }
        if (ID == NTHREADS - 1){
          n->nivel++;
        }
        inserir(buffersSieve[nextID],n);
        pthread_cond_signal(&podeConsumirNumero[nextID]);
      pthread_mutex_unlock(&mutexSieve[nextID]);
    }
  }
  return NULL;
}


void *threadResults(void *param){

  while(1){
    pthread_mutex_lock(&mutexResult);

    while(tamanho(resultados) == 0){
      pthread_cond_wait(&podeConsumirResultado, &mutexResult);
    }

    tipo_info *n = remover(resultados);
    pthread_mutex_lock(&mutexJaMandei);
    jaMandei--;
    pthread_mutex_unlock(&mutexJaMandei);

    inserir(bufferResultado,n);
    pthread_cond_signal(&podeInserirResultado);

    if(tamanho(bufferResultado) == N - 1){
      tipo_info **vectorInfo = definirVectorInfo(N - 1);
      for(int j = 0; j < N-1 ; j++){
        tipo_info *n = remover(bufferResultado);
        vectorInfo[j] = n;
      }

      qsort (vectorInfo, N-1, sizeof(tipo_info*),compara);
      
      for(int i = 0; i < N - 1; i++){
        tipo_info *info = vectorInfo[i];

        if(info->ehPrimo){
          printf("%d is prime (stored in sieve %d)\n", info->numero,
            info->numThread);
        }
        else{
          printf("%d divided by %d at sieve %d\n", info->numero,
            info->divisor,info->numThread);
        }
      }
      exit(0);
      //pthread_exit(&ret);
    }
    pthread_mutex_unlock(&mutexResult);
  }
}

int ehDivisivel(int numero, int ID, int nivel){
  Vector *p = primos[ID];
  if(numero%p->buf[nivel] == 0){//verifica se é divisivel pelo primo armazenado no buffer
    return p->buf[nivel];
  }
  else{
    return 0;
  }
}