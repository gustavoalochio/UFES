#include "wiked.h"
#include "editor.h"
#include "pagina.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pagina {
    sCon* cont;
    lLink* link;
    char* nome;
    char* txt;
};

struct listaPaginas {
    tPagina* pag;
    lPagina* proxima;
};

struct link {
    tPagina* pagLigada;
    lLink* outroLink;
};

void LiberaLinks(lLink* listaLinks);

lPagina* IniciarPagina(lPagina* lPag, tPagina* pag) {
    lPagina* pa = (lPagina*) malloc(sizeof (lPagina));
    pa->proxima = NULL;
    pa->pag = pag;
    if (lPag == NULL)
        return pa;
    lPagina* aux2 = lPag;
    lPagina* aux = lPag;
    while (aux2 != NULL) {
        aux = aux2;
        aux2 = aux2->proxima;
    }
    aux->proxima = pa;
    return lPag;
}

lPagina* ProxListaPag(lPagina* lista) {
    return lista->proxima;
}

tPagina* EncontraPag(char*nome, lPagina *lista) {
    lPagina* l = lista;
    if (l != NULL) {
        while (l != NULL) {
            if (!strcmp(l->pag->nome, nome)) {
                return l->pag;
            }
            l = l->proxima;
        }
        //PAGINA NAO FOI ENCONTRADA
    }
    return NULL;
}

tPagina* RetornaPag(lPagina* lPag) {
    return lPag->pag;
}

int Caminho(char* origem, char* destino, lPagina *lista) {
    tPagina* ori = EncontraPag(origem, lista);
    if(ori == NULL)
      return 0;
    tPagina* dest = EncontraPag(destino, lista);
    if(dest == NULL)
      return 0;
    lLink* listaLink = ori->link;
    if(ori == NULL)
        return 2;
    else if(dest == NULL)
        return 3;
    while (1) {
        if (listaLink->pagLigada == dest)
            return 1;
        else if (listaLink->outroLink == NULL)
            return 0;
        listaLink = listaLink->outroLink;
    }
}

int InsereLink(char* origem, char* destino, lPagina *lista) {
    tPagina* ori = EncontraPag(origem, lista);
    tPagina* dest = EncontraPag(destino, lista);
    if(ori == NULL)
        return 2;

    else if(dest == NULL)
        return 3;
        
    lLink* link = (lLink*) malloc(sizeof (lLink));
    link->pagLigada = dest;
    link->outroLink = NULL;
    if (ori->link == NULL) {
        ori->link = link;
    } else {
        lLink* aux = ori->link;
        while (1) {
            if (aux->outroLink == NULL) {
                aux->outroLink = link;
                return 0;
            }
            aux->outroLink;
        }
    }
}

int RetiraLink(char* origem, char* destino, lPagina *lista) {
    tPagina* ori = EncontraPag(origem, lista);
    tPagina* dest = EncontraPag(destino, lista);
    lLink* ant, *listaLink = ori->link;
    if(ori == NULL)
        return 2;
    else if(dest == NULL)
        return 3;
    if (ori->link->pagLigada == dest) {
        free(ori->link);
        ori->link = ori->link->outroLink;
        return 0;
    } else {
        while (1) {
            if (listaLink->pagLigada == dest) {
                ant->outroLink = listaLink->outroLink;
                free(listaLink);
                return 0;
            } else if (listaLink->outroLink == NULL) {
                return 1;
            }
            ant = listaLink;
            listaLink = listaLink->outroLink;
        }
    }
}

void ImprimePagina(tPagina* pagina) {
    FILE* PAG = fopen(pagina->txt, "w");
    lLink* auxLink = pagina->link;
    fprintf(PAG, "%s\n\n--> Historico de contribuicoes\n", pagina->nome);
    ImprimirContri(pagina->cont, PAG);
    fprintf(PAG, "\n--> Links\n");
    while (auxLink != NULL) {
        fprintf(PAG, "%s %s\n", auxLink->pagLigada->nome, auxLink->pagLigada->txt);
        auxLink = auxLink->outroLink;
    }
    fprintf(PAG, "\n--> Textos");
    ImprimirTexto(pagina->cont, PAG);

    fclose(PAG);
}

int RetiraPagina(char* nome, lPagina *lista) {
    tPagina* pag = EncontraPag(nome, lista);
    if (pag == NULL) {
        return 1;
    }
    free(pag->nome);
    free(pag->txt);
    LiberarContri(pag->cont);
    lLink* l = pag->link;
    lLink* auxL;
    while (l != NULL) {
        auxL = l;
        l = l->outroLink;
        free(auxL);
    }
    free(pag);
    return 0;
}

tPagina* InserePagina(char* nome, char* arquivo) {
    tPagina *novaPagina = (tPagina*) malloc(sizeof (tPagina));
    int t = strlen(nome);
    novaPagina->nome = (char*) malloc(t * sizeof (char) + 1);
    strcpy(novaPagina->nome, nome);

    t = strlen(arquivo);
    novaPagina->txt = (char*) malloc(t * sizeof (char) + 1);
    strcpy(novaPagina->txt, arquivo);

    novaPagina->cont = NULL;
    novaPagina->link = NULL;

    novaPagina->cont = CriarSentinela();

    return novaPagina;

}

void LiberarPagina(lPagina* pagina) {
    if (pagina != NULL) {
        lPagina* antesPagina;
        while (pagina != NULL) {
            LiberarContri(pagina->pag->cont);
            lLink* l = pagina->pag->link;
            lLink* auxL;
            while (l != NULL) {
                auxL = l;
                l = l->outroLink;
                free(auxL);
            }
            free(pagina->pag->nome);
            free(pagina->pag->txt);
            free(pagina->pag);
            antesPagina = pagina;
            pagina = pagina->proxima;
            free(antesPagina);
        }
    }
}

sCon* SentPag(tPagina* pag) {
    return pag->cont;
}
