/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: 2016101741
 *
 * Created on 22 de Setembro de 2016, 08:44
 */

#include <stdio.h>
#include <stdlib.h>
#include "wiked.h"
#include "editor.h"
#include "pagina.h"
/*
 *
 */
int main(int argc, char** argv) {
    if(argc < 2){
        printf("ERRO: FALTA ARQUIVO DE ENTRADA");
		return 1;
	}
    tWiki * wikiED;
    wikiED = IniciarWiki(wikiED);
    ComecarWiki(wikiED, argv[1]);
    return 0;
}
