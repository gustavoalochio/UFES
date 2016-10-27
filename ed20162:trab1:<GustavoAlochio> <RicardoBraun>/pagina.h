/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   lista.h
 * Author: 2016101741
 *
 * Created on 22 de Setembro de 2016, 08:45
 */

#ifndef LISTA_H
#define LISTA_H

typedef struct pagina tPagina;

typedef struct listaPaginas lPagina;

typedef struct link lLink;

/*Essa função tem como objetivo iniciar a lista do
* tipo lPagina na qual contém o tipo tPagina
* inputs: Um valor válido para pag (tPagina)
* e uma lista do tipo lPagina
* output: A lista atualizada com o pag na ultima posição
* pre-condicao: Lista e item válidos
* pos-condicao: Nenhuma
*/
lPagina* IniciarPagina(lPagina* lPag, tPagina* pag);

/*Essa função busca dentro da lista de paginas uma pagina
* pag e a retorna
* inputs: Lista de paginas e a pagina que deve ser procurada
* podendo não existir
* output: Caso a pagina extista, ela é retornada, caso não exita
* retorna NULL
* pre-condicao: Lista válida
* pos-condicao: Nenhuma
*/
tPagina* EncontraPag(char*nome, lPagina *lista);

/*Essa função verifica qual é a lista seguinte e a retorna
* inputs: Lista de paginas
* output: Próxima lista de paginas
* pre-condicao: Lista válida
* pos-condicao: Nenhuma
*/
lPagina* ProxListaPag(lPagina* lista);

/*Essa função verifica qual é a pagina pertencente
* a posição da lista e a retorna
* inputs: Lista de paginas
* output: Pagina que pertence a posição atual da lista
* pre-condicao: Lista válida
* pos-condicao: Nenhuma
*/
tPagina* RetornaPag(lPagina* lPag);

/*Essa função tem como objetivo criar uma pagina
* a partir de valores dados
* inputs: Strings contendo nome da pagina e nome do arquivo
* output: Tipo tPagina criado e retornando um ponteiro do mesmo
* pre-condicao: Valores válidos
* pos-condicao: Ponteiro para tPagina criado e retornado
*/
tPagina* InserePagina(char* nome, char* arquivo);

/*Essa função retira a pagina, com o nome já definido, e retorna 1 caso consiga
* a remover e 0 caso não a encontre
* inputs: Lista de paginas e o nome da pagina na qual precisa remover
* output: Inteiro verificativo para definir se a pagina foi ou não foi removida
* pre-condicao: Lista válida
* pos-condicao: Lisat atualizada
*/
int RetiraPagina(char* nome, lPagina *lista);

/*Essa função tem como objetivo imprimir a pagina recebida
* inputs: Pagina que deve ser imprimida
* output: Arquivo com a pagina impressa
* pre-condicao: Pagina válida
* pos-condicao: Nenhuma
*/
void ImprimePagina(tPagina* pagina);

/*Essa função insere um link que liga duas pagina
* inputs: Nome das paginas que devem ser ligadas e a lista de paginas
* output: Paginas ligadas
* pre-condicao: Paginas válidas
* pos-condicao: Pagina origem atualizadas com o link
*/
int InsereLink(char* origem, char* destino, lPagina* lista);

/*Essa função retira o link que liga duas paginas
* inputs: Nome das paginas que devem ter o link removido e a lista de paginas
* output: Pagina origem sem o link
* pre-condicao: Paginas válidas e com link
* pos-condicao: Pagina origem atualizada sem o link
*/
int RetiraLink(char* origem, char* destino, lPagina* lista);

/*Essa função verifica se existe link que liga a pagina origem a
* pagina destino
* inputs: Nome das paginas que devem ser verificadas e a lista de paginas
* output: Verdadeiro se existe caminho e falso se não existe
* pre-condicao: Paginas válidas
* pos-condicao: Arquivo log atualizado
*/
int Caminho(char* origem, char* destino, lPagina* lista);

/*Essa função libera toda a memória alocada pela pagina
* inputs: Pagina que deve ser liberada
* output: Memória alocada
* pre-condicao: Pagina válida
* pos-condicao: Memória desalocada
*/
void LiberarPagina(lPagina* pagina);

/*Essa função retorna o sentinela que contem a lista de contribuições
* inputs: Pagina que contem o sentinela
* output: Sentinela da pagina
* pre-condicao: Pagina válida
* pos-condicao: Sentinela válido
*/
sCon* SentPag(tPagina* pag);

#endif /* LISTA_H */
