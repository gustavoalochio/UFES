#include "wiked.h"
#include "editor.h"
#include "pagina.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int VerificarEntrada(char *s);

/*VerificarEntrada:
 * Retornar 1 :  INSEREPAGINA
 * Retornar 2 :  RETIRAPAGINA
 * Retornar 3 :  INSEREEDITOR
 * Retornar 4 :  INSERECONTRIBUICAO
 * Retornar 5 :  RETIRACONTRIBUICAO
 * Retornar 6 :  INSERELINK
 * Retornar 7 :  RETIRALINK
 * Retornar 8 :  CAMINHO
 * Retornar 9 :  IMPRIMEPAGINA
 * Retornar 10 : IMPRIMEWIKED
 * Retornar 11 : FIM
 * Retornar 12 : RETIRAEDITOR
 */


struct wiki {
    lEditor* ed;
    lPagina* pa;
};

tWiki* IniciarWiki(tWiki* wi) {
    wi = (tWiki*) malloc(sizeof (tWiki));
    wi->ed = NULL;
    wi->pa = NULL;
    return wi;
}

void ComecarWiki(tWiki* wi, char* dir) {
    char entrada[100];
    int i = -1, j = 0;

    FILE* entra = fopen(dir, "r");

    if(entra == NULL)
    {
      printf("ERRO de Leitura\n");
      return;
    }

    FILE* log = fopen("log.txt", "w+");

    do {
        fscanf(entra, "%s", entrada);
        i = VerificarEntrada(entrada);

        if (i == 1) {//INSEREPAGINA

            char nome[20], arquivo[20];
            fscanf(entra, "%s %s", nome, arquivo);
            tPagina* pagina = InserePagina(nome, arquivo);
            wi->pa = IniciarPagina(wi->pa, pagina);

        } else if (i == 2) {//RETIRAPAGINA

            char nome[20];
            fscanf(entra, "%s", nome);

            int i;

            i = RetiraPagina(nome, wi->pa);

            if (i == 1) {
                fprintf(log, "ERRO: A PAGINA %s NAO EXISTE.\n", nome);
            }

        } else if (i == 3) {//INSEREEDITOR

            char nome[20];
            fscanf(entra, "%s", nome);
            if (EncontraEditor(nome, wi->ed) != NULL)
                fprintf(log, "ERRO:O EDITOR %s JA EXISTE.\n", nome);
            else {
                tEditor* edi = InsereEditor(nome);
                wi->ed = IniciarEditor(wi->ed, edi);
            }

        } else if (i == 4) {//INSERECONTRIBUICAO

            char pagina[20], editor[20], arquivo[20];
            fscanf(entra, "%s %s %s", pagina, editor, arquivo);
            int k;
            tPagina* pag;
            pag = EncontraPag(pagina, wi->pa);

            if(pag == NULL)
            {
              fprintf(log, "ERRO:A PAGINA %s NAO EXISTE.\n", pagina);
            }
            else
            {
              k = InsereContribuicao(wi->ed, SentPag(pag), editor, arquivo);
              if (k == 1) {
                  fprintf(log, "ERRO:A CONTRIBUICAO %s JA EXISTE.\n", arquivo);
              } else if (k == 2)
                  fprintf(log, "ERRO:O EDITOR %s NAO EXISTE.\n", editor);
            }

        } else if (i == 5) {//RETIRACONTRIBUICAO

            char pagina[20], editor[20], contribuicao[20];
            fscanf(entra, "%s %s %s", pagina, editor, contribuicao);

            tPagina* pag;
            pag = EncontraPag(pagina, wi->pa);
            if (pag == NULL)
                fprintf(log, "ERRO: A PAGINA %s NAO EXISTE.\n", pagina);
            else {
                int k = RetiraContribuicao(SentPag(pag), editor, contribuicao);
                if (k == 1)
                    fprintf(log, "ERRO: ESTA CONTRIBUICAO NAO PERTENCE A ESTE EDITOR.\n");
                else if (k == 2)
                    fprintf(log, "ERRO: ESTA CONTRIBUICAO NAO EXISTE.\n");
            }

        } else if (i == 6) {//INSERELINK

            char pagOrigem[20], pagDestino[20];
            fscanf(entra, "%s %s", pagOrigem, pagDestino);

            int k = InsereLink(pagOrigem, pagDestino, wi->pa);
            if (k == 2)
                fprintf(log, "ERRO: A PAGINA %s NAO EXISTE.\n", pagOrigem);
            else if (k == 3)
                fprintf(log, "ERRO: A PAGINA %s NAO EXISTE.\n", pagDestino);

        } else if (i == 7) {//RETIRALINK

            char pagOrigem[20], pagDestino[20];
            fscanf(entra, "%s %s", pagOrigem, pagDestino);

            int k;

            k = RetiraLink(pagOrigem, pagDestino, wi->pa);

            if (k == 1) {
                fprintf(log, "ERRO: O LINK DE %s A %s NAO EXISTE.\n", pagOrigem, pagDestino);
            } else if (k == 2)
                fprintf(log, "ERRO: A PAGINA %s NAO EXISTE.\n", pagOrigem);
            else if (k == 3)
                fprintf(log, "ERRO: A PAGINA %s NAO EXISTE.\n", pagDestino);

        } else if (i == 8) {//CAMINHO
            int k;
            char pagOrigem[20], pagDestino[20];
            fscanf(entra, "%s %s", pagOrigem, pagDestino);

            k = Caminho(pagOrigem, pagDestino, wi->pa);

            if (k == 1)
                fprintf(log, "HA CAMINHO DA PAGINA %s PARA %s.\n", pagOrigem, pagDestino);
            else if (k == 2)
                fprintf(log, "ERRO: A PAGINA %s NAO EXISTE.\n", pagOrigem);
            else if (k == 3)
                fprintf(log, "ERRO: A PAGINA %s NAO EXISTE.\n", pagDestino);
            else
                fprintf(log, "NAO HA CAMINHO DA PAGINA %s PARA %s.\n", pagOrigem, pagDestino);



        } else if (i == 9) {//IMPRIMEPAGINA

            char pagina[10];
            fscanf(entra, "%s", pagina);
            tPagina* pag = EncontraPag(pagina, wi->pa);
            if (pag == NULL)
                fprintf(log, "A PAGINA %s NAO EXISTE.\n", pagina);
            else
                ImprimePagina(pag);

        } else if (i == 10) {//IMPRIMEWIKED

            ImprimeWikiED(wi);

        } else if (i == 11) {//FIM
            fclose(entra);
            fclose(log);
            Fim(wi);
            i = 0;

        } else if (i == 12) {//RETIRAEDITOR

            char nomeEditor[20];

            fscanf(entra, "%s", nomeEditor);

            int k;

            k = RetiraEditor(wi->ed, nomeEditor);

            if (k == 1) {
                fprintf(log, "Esse editor nao existe.\n");
            }
        } else {//Digitou errado

            fprintf(log, "Essa função não existe!\n");
        }
    } while (i);
}

void ImprimeWikiED(tWiki* wi) {
    lPagina* lista = wi->pa;
    while (lista != NULL) {
        ImprimePagina(RetornaPag(lista));
        lista = ProxListaPag(lista);

    }
}

tWiki* Fim(tWiki* wi) {
    LiberarPagina(wi->pa);
    LiberarEditor(wi->ed);
    free(wi);
    return NULL;
}

int VerificarEntrada(char * comando) {
    if (!strcmp(comando, "INSEREPAGINA")) {//inserepagina
        return 1;
    } else if (!strcmp(comando, "RETIRAPAGINA")) {//retirapagina
        return 2;
    } else if (!strcmp(comando, "INSEREEDITOR")) {//insereeditor
        return 3;
    } else if (!strcmp(comando, "INSERECONTRIBUICAO")) {//inserecontribuicao
        return 4;
    } else if (!strcmp(comando, "RETIRACONTRIBUICAO")) {//retiracontribuicao
        return 5;
    } else if (!strcmp(comando, "INSERELINK")) {//inserelink
        return 6;
    } else if (!strcmp(comando, "RETIRALINK")) {//retiralink
        return 7;
    } else if (!strcmp(comando, "CAMINHO")) {//imprimepagina
        return 8;
    } else if (!strcmp(comando, "IMPRIMEPAGINA")) { //imprimewikied
        return 9;
    } else if (!strcmp(comando, "IMPRIMEWIKED")) { //caminho
        return 10;
    } else if (!strcmp(comando, "FIM")) { //fim
        return 11;
    } else if (!strcmp(comando, "RETIRAEDITOR")) {
        return 12;
    } else {
        return 13;
    }
}
/*VerificarEntrada:
 * Retornar 1 :  INSEREPAGINA
 * Retornar 2 :  RETIRAPAGINA
 * Retornar 3 :  INSEREEDITOR
 * Retornar 4 :  INSERECONTRIBUICAO
 * Retornar 5 :  RETIRACONTRIBUICAO
 * Retornar 6 :  INSERELINK
 * Retornar 7 :  RETIRALINK
 * Retornar 8 :  CAMINHO
 * Retornar 9 :  IMPRIMEPAGINA
 * Retornar 10 : IMPRIMEWIKED
 * Retornar 11 : FIM
 * Retornar 12 : RETIRAEDITOR
 */
