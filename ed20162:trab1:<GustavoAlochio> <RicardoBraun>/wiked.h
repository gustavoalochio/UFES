/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   wiked.h
 * Author: 2016101741
 *
 * Created on 27 de Setembro de 2016, 07:43
 */

#ifndef WIKED_H
#define WIKED_H

/*
Biblioteca criada para auxiliar a função main, onde ocorrerá
o processo de inicialização, impressão e finalização do programa.
O objetivo de criação dessa biblioteca é deixar o programa organizado.
*/

/*Estrutura de tipo opaco
* Lista principal, contendo
* as listas de editores e paginas.
*/
typedef struct wiki tWiki;

/*Essa função tem por objetivo iniciar a struct principal na qual contém
* duas listas e é denominada de wiki, onde se alocado espaço para
* esta mesma struct e aponta para as lista de editor e paginas em NULL.
* inputs: Ponteiro com valor lixo de struct do tipo tWiki;
* output: Ponteiro com valor uma struct do tipo tWiki
* pre-condicao: Nenhuma
* pos-condicao: Nenhuma
*/
tWiki* IniciarWiki(tWiki* wi);

/*Essa função será a função principal do programa,
* dando inicio às suas funções, ela utiliza a função
* auxiliar VerificaEntrada, onde olha qual função será
* iniciada, ex; RETIRALINK.
* inputs: Um ponteiro apontando para um valor do tipo tWiki e a string
* que contém o nome do arquivo de entrada
* output: Nenhum
* pre-condicao: Um ponteiro inicializado pela função IniciarWiki
* pos-condicao: Nenhuma
*/
void ComecarWiki(tWiki* wi, char* dir);

/*Essa função imprimirar em vários arquivos todas as
* paginas que estão contidas na wiki
* inputs: Um ponteiro apontando para um valor do tipo tWiki
* output: Nenhum
* pre-condicao: Nenhuma
* pos-condicao: Nenhuma
*/
void ImprimeWikiED(tWiki* wi);

/*Função de finalização do programa, onde será liberada toda a memória alocada por ele.
* inputs: O ponteiro do tipo tWiki de onde será liberada a memória
* output: Memória liberada
* pre-condicao: Tipo válido
* pos-condicao: Toda memória liberada
*/
tWiki* Fim(tWiki* wi);

#endif /* WIKED_H */

//EXEMPLO
/*Essa função tem por objetivo iniciar a lista principal
que seria denominada de wiki, onde é alocado espaço para
a lista de editores e paginas e redirecionando seus ponteiros
para o valor NULL.
* inputs: a lista, o cliente dono do imovel e o item a ser inserido
* output: a lista atualizada
* pre-condicao: lista, cliente e imovel validos
* pos-condicao: lista atualizada com o item inserido na primeira posicao
*/
