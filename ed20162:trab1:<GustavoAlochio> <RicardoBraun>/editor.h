/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   editor.h
 * Author: 2016101741
 *
 * Created on 27 de Setembro de 2016, 07:42
 */

#ifndef EDITOR_H
#define EDITOR_H

#include "wiked.h"
#include <stdio.h>

typedef struct sentinela sCon;

typedef struct editor tEditor;

typedef struct listaEditores lEditor;

typedef struct contribuicao lCon;

/*Função que insere o editor na lista de editores na ultima posição
* inputs: Lista de editores e editor
* output: Lista atualizada
* pre-condicao: Editor válido
* pos-condicao: Lista atualizada
*/
lEditor* IniciarEditor(lEditor* lEdi, tEditor* edi);

/*Função criada para fazer uma busca na lista
* de editores e encontra o editor desejado
* inputs: Lista de editores e nome do editor desejado
* output: Editor desejado
* pre-condicao: Lista válida
* pos-condicao: Editor encontrado
*/
tEditor* EncontraEditor(char* nome, lEditor* listaEd);

/*Função de cria o editor de acordo com as entradas fornecidas
* inputs: Nome do editor
* output: Editor criado
* pre-condicao: Entradas válidas
* pos-condicao: Editor criado
*/
tEditor* InsereEditor(char *nome);

/*Função para retirar um editor da lista de editores
* inputs: Nome do editor que deve ser retirado e a lista de editores
* output: Verdadeiro se o editor foi removido e falso se não foi
* pre-condicao: Editor válido e pertencente a lista
* pos-condicao: Lista atualizada sem o editor
*/
int RetiraEditor(lEditor *editor, char *nomeEditor);

/*Essa função cria uma contribuição e a insere dentro da pagina que
* contem a contribuição
* inputs: Lista de editores e o nome do editor como também a sentinela
* da lista de contribuições e o texto da contribuição
* output: Lista de contribuição atualizada
* pre-condicao: Contribuição válida
* pos-condicao: Lista atualizada
*/
int InsereContribuicao(lEditor* ed, sCon* sentCon, char* editor, char* contribuicao);

/*Essa função retira a contribuição de um dado editor
* inputs: Lista de editores e o nome do editor como também a sentinela
* da lista de contribuições e o texto da contribuição
* output: Lista de contribuição atualizada
* pre-condicao: Contribuição já existente
* pos-condicao: Lista atualizada
*/
int RetiraContribuicao(sCon* sentCon, char* editor, char* contribuicao);

/*Essa função libera toda a memória alocada pelo editor
* inputs: Editor que deve ser liberado
* output: Memória liberada
* pre-condicao: Editor válido
* pos-condicao: Toda mémoria alocada pelo editor desalocada
*/
void LiberarEditor(lEditor* editor);

/*Essa função libera toda a memória alocada pela contribuição
* inputs: Lista de contribuição que deve ser liberada
* output: Memória liberada
* pre-condicao: Lista de contribuição válida
* pos-condicao: Toda mémoria alocada pela contribuição desalocada
*/
void LiberarContri(sCon* sentinela);

/*Essa função imprime a contribuição
* inputs: Lista de contribuição e arquivo onde deve ser impresso
* output: Arquivo atualizadao com a impreção
* pre-condicao: Arquivo e lista válidos
* pos-condicao: Arquivo atualizado
*/
void ImprimirContri(sCon* auxCon,FILE* PAG);

/*Essa função cria a sentinela da lista de contribuições
* inputs: Nenhuma
* output: Sentinela de contribuição
* pre-condicao: Nenhuma
* pos-condicao: Sentinela criada com valores para lista NULL
*/
sCon* CriarSentinela(void);

/*Essa função cria libera o editor já definido
* inputs: Editor a ser liberado
* output: Espaço da memória desalocado
* pre-condicao: Editor válido
* pos-condicao: Memória desalocada
*/
void LiberaEd(tEditor* editor);

/*Essa função imprime o texto da contribuição
* inputs: Lista de contribuição e arquivo onde deve ser impresso
* output: Arquivo atualizadao com a impreção
* pre-condicao: Arquivo e lista válidos
* pos-condicao: Arquivo atualizado
*/
void ImprimirTexto(sCon* auxCon, FILE* PAG);

#endif /* EDITOR_H */
