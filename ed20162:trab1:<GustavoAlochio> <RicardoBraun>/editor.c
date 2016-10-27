#include "wiked.h"
#include "editor.h"
#include "pagina.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listaEditores {
    tEditor* edit;
    lEditor* proximo;
};

struct editor {
    char* nome;
};

struct contribuicao {
    tEditor* editor;
    char* txt;
    lCon* prox;
    int i; //se 0 foi removido;
};

struct sentinela {
    lCon* pri;
};

lEditor* IniciarEditor(lEditor* lEdi, tEditor* edi) {
    lEditor* ed = (lEditor*) malloc(sizeof (lEditor));
    ed->proximo = NULL;
    ed->edit = edi;
    if (lEdi == NULL)
        return ed;
    lEditor* aux2 = lEdi;
    lEditor* aux = lEdi;
    while (aux2 != NULL) {
        aux = aux2;
        aux2 = aux2->proximo;
    }
    aux->proximo = ed;
    return lEdi;
}

tEditor* EncontraEditor(char* nome, lEditor* listaEd) {
    lEditor* l = listaEd;
    lEditor* ant;
    while (1) {
        if (l == NULL) {
            return NULL;
        } else if (!strcmp(l->edit->nome, nome))
            return l->edit;
        l = l->proximo;
    }
}

tEditor* InsereEditor(char* nome) {
    tEditor* editor = (tEditor*) malloc(sizeof (tEditor));
    int i;
    i = strlen(nome);
    editor->nome = (char*) malloc(i * sizeof (char) + 1);
    strcpy(editor->nome, nome);
    return editor;
}

int RetiraEditor(lEditor *editor, char *nomeEditor) {
    lEditor* e = editor;
    lEditor* aux;
    while (e != NULL) {
        if (!strcmp(nomeEditor, e->edit->nome)) {
            LiberaEd(e->edit);
            aux->proximo = e->proximo;
            free(e);
            return 0;
        }
        aux = e;
        e = e->proximo;
    }
    return 1;
}

void LiberaEd(tEditor* editor){
    free(editor->nome);
    free(editor);
}

int InsereContribuicao(lEditor* ed, sCon* sentCon, char* editor, char* contribuicao) {
    tEditor* edit = EncontraEditor(editor, ed);
    if(edit == NULL)
        return 2;
    lCon* cont = (lCon*) malloc(sizeof (lCon));
    cont->i = 1;
    cont->editor = edit;
    cont->prox = NULL;
    if (sentCon->pri == NULL) {
        sentCon->pri = cont;
    } else {
        lCon* i = sentCon->pri;
        while (i->prox != NULL) {
            if(!strcmp(contribuicao, i->txt))
                return 1;
            i = i->prox;
        }
        i->prox = cont;
    }
    int t = strlen(contribuicao);
    cont->txt = (char*) malloc(sizeof (char)*(t + 1));
    strcpy(cont->txt, contribuicao);
    return 0;
}

int RetiraContribuicao(sCon* sentCon, char* editor, char* contribuicao) {
    lCon* cont = sentCon->pri;
    while (1) {
        if (!strcmp(cont->txt, contribuicao))
            break;
        cont = cont->prox;
        if(cont == NULL)
            return 2;

    }
    if(strcmp(cont->editor->nome, editor))
        return 1;
    cont->i = 0;
}

void ImprimirContri(sCon* sentCon, FILE* PAG) {
    lCon* auxCon = sentCon->pri;
    while (auxCon != NULL) {
        fprintf(PAG, "%s %s", auxCon->editor->nome, auxCon->txt);
        if (auxCon->i == 0)
            fprintf(PAG, " <<retirada>>\n");
        else
            fprintf(PAG, "\n");
        auxCon = auxCon->prox;
    }
}

void ImprimirTexto(sCon* sentCon, FILE* PAG) {
    lCon* auxCon = sentCon->pri;
    while (auxCon != NULL) {
        if (auxCon->i != 0) {
            FILE* txt = fopen(auxCon->txt, "r");
            char text[1000];
            fprintf(PAG, "\n\n-------- %s (%s) --------\n\n", auxCon->txt, auxCon->editor->nome);
            while (!feof(txt)) {
                fgets(text, 1000, txt);
                fprintf(PAG, "%s", text);
            }
            fclose(txt);
            auxCon = auxCon->prox;
        } else
            break;
    }
}

sCon* CriarSentinela(void) {
    sCon* sent = malloc(sizeof (sCon));
    sent->pri = NULL;
    return sent;
}

void LiberarEditor(lEditor* editor) {
    lEditor* antesEditor;
    while (editor != NULL) {
        free(editor->edit->nome);
        free(editor->edit);
        antesEditor = editor;
        editor = editor->proximo;
        free(antesEditor);
    }
}

void LiberarContri(sCon* sentinela) {
    lCon* c = sentinela->pri;
    lCon* auxC;
    while (c != NULL) {
        auxC = c;
        c = c->prox;
        free(auxC->txt);
        free(auxC);
    }
    free(sentinela);
}
