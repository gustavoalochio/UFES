#ifndef FILA_H_
#define FILA_H_

/*Tipo tipo_info. Contem campos:
  - numero (int)
  - nivel (int) - essa variável é utilizada como parametro
  de comparação indicando a posição a ser comparada.
  - ehPrimo ("int" - será utilizada como boolean)
  - divisor (int) - para armazenar o divisor do numero
  - numThread (int) - numero da thread em que foi indentificado
  */

typedef struct inf{
  int numero;
  int nivel;
  int ehPrimo;
  int divisor;
  int numThread;
}tipo_info;

/*Tipo tipo_elem. Contem campos:
  - info (tipo_info) - aponta para um tipo_info
  - elem (struct elem) - aponta para a proxima struct elem
  */
typedef struct elem{
	tipo_info *info;
	struct elem *prox;
}tipo_elem;

/*Tipo Fila. Contem campos:
  - inicio (tipo_elem) - aponta para o inicio da fila
  - fim (tipo_elem) - aponta para o fim da fila
  */
typedef struct{
  tipo_elem *inicio;
  tipo_elem *fim;
}Fila;


/*Define um tipo de estrutura de dados fila
* inputs: 
* output: uma fila alocada dinamicamente
* pre-condicao: 
* pos-condicao: Ao final é necessário ter uma fila alocada dinamicamente
com seu inicio e fim apontados para NULL
*/
Fila* definir();

/*Verifica se uma fila está vazia
* inputs: Uma fila alocada e existente.
* output: um booleano dizendo se está vazia ou não
* pre-condicao: Fila existente
* pos-condicao: Fila não pode ser alterada.
*/
int vazia (Fila *q);

/*Cria e aloca dinamicamente uma struct para o as informações 
* inputs: um numero a ser armazenado na estrutura
* output: uma estrutura alocada dinamicamente
* pre-condicao: um numero do tipo int deve ser passado como parametro
* pos-condicao: uma struct não nula
*/
tipo_info *cria_info(int numero);

/*Insere uma struct do tipo info na fila que tambem é passada como
parametro
* inputs: Uma fila existente, uma struct do tipo_info existente
* output: nenhum
* pre-condicao: Deve ser passado como parâmetro uma fila existente,
 uma struct do tipo_info existente
* pos-condicao: Ao final da função a fila tem um novo elemento ao seu
final.
*/
void* inserir (Fila *q, tipo_info *info);

/*Remove um elemento da fila, mas não da free nele, pois posteriormente
será utilizado, retornando-o
* inputs: Uma fila existente
* output: Um elemento do tipo_info
* pre-condicao: A fila não pode estar vazia
* pos-condicao: Ao final será retornado um elemento do tipo_info existente
que foi retirado da fila
*/
tipo_info* remover(Fila *q);

/*Verifica o tamanho da fila
* inputs: Uma fila existente
* output: O tamanho da fila
* pre-condicao: A fila deve existir.
* pos-condicao: Será retornado um valor inteiro onde esse será utilizado
pela chamada de função.
*/
int tamanho (Fila *q);

/*Cria e aloca uma estrutura do tipo elemento que será utilizado na fila
* inputs: uma estrutura do tipo info
* output: é retornado uma estrutura do tipo_elem que será utilizado dentro da fila
* pre-condicao: uma estrutura do tipo info valida
* pos-condicao: é retornada uma estrutura do tipo_elem não nula com seu ponteiro
prox apontada para nulo
*/
tipo_elem *cria_elemento(tipo_info *info);

#endif /* FILA_H_ */
