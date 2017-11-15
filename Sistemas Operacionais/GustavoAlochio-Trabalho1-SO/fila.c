#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fila.h"


Fila* definir(){
  /*Cria uma fila vazia. Deve ser usado antes de qualquer
  outra operação*/
  Fila* q = malloc(sizeof(Fila));

  q->inicio = NULL;
  q->fim = NULL;

  return q;
}


int vazia (Fila *q){
  /*Retorna 1 se fila não contém elementos, 0 caso
  contrário*/
  return (q->inicio == NULL);
}

tipo_info *cria_info(int numero){
  tipo_info *i = malloc(sizeof(tipo_info));

  i->numero = numero;

  return i;
}


tipo_elem *cria_elemento(tipo_info* i){
  
  tipo_elem *p = malloc(sizeof(tipo_elem));

  p->info = i;
  p->prox = NULL;

  return p;
}

void* inserir (Fila *q, tipo_info* info){
/*Adiciona um item no fim da fila q. Retorna true se
operação realizada com sucesso, false caso contrário*/
  tipo_elem *p = cria_elemento(info); 

  if (vazia(q)){
    q->inicio = p;
    q->fim = p;
  }
  else{
    q->fim->prox = p;
    q->fim = p;
  }
}

tipo_info* remover(Fila *q){
  /*Remove um item do início da fila q. Retorna true se
  operação realizada com sucesso, false caso contrário*/
  tipo_elem *p;

  if (vazia(q))
    return NULL;

  p = q->inicio;
  q->inicio = p->prox;

  if (q->inicio == NULL)
    q->fim = NULL;

  return p->info;
}

int tamanho (Fila *q){
/*Retorna o tamanho da fila*/
  tipo_elem *p;
  int cont = 0;
  p = q->inicio;
    if(vazia(q))
    return 0;

  while (p != NULL){
    cont ++;
    p = p->prox;
  }
  return cont;
}
