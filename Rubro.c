//
// Created by tiago on 07/06/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "Rubro.h"

typedef struct no{
    int chave;
    struct no *Fdir;
    struct no *Fesq;
    struct no *pai;
    char cor;
}no;

typedef struct arvore{
    struct no *sentinela;
    struct no *nulo;
    int numElementos;
}arv;

arv *criaArvore() {
    arv *rubro = (arv*)malloc(sizeof(arv));
    if (!rubro)
        return NULL;

    rubro->sentinela = (no*)malloc(sizeof(no));
    rubro->nulo = (no*)malloc(sizeof(no));

    if (!rubro->sentinela || !rubro->nulo)
        return NULL;

    rubro->sentinela->Fdir = rubro->nulo;
    rubro->sentinela->Fesq = rubro->nulo;
    rubro->sentinela->pai = rubro->nulo;
    rubro->sentinela->chave = -1000;
    rubro->sentinela->cor = 'P';

    rubro->nulo->Fdir = NULL;
    rubro->nulo->Fesq = NULL;
    rubro->nulo->pai = NULL;
    rubro->nulo->chave = -1000;
    rubro->nulo->cor = 'P';

    rubro->numElementos = 0;
    return rubro;
}

int inserir(arv *arv, int valor){
    no *n, *aux, *ant;
    n = (no*)malloc(sizeof(no));
    if(!n)
        return 0;
    n->cor = 'V';
    n->Fdir = arv->nulo;
    n->Fesq = arv->nulo;
    n->chave = valor;

    if (arv->sentinela->Fdir == arv->nulo){
        arv->sentinela->Fdir = n;
        n->pai = arv->sentinela;
        n->cor = 'P';
        arv->numElementos++;
        return 1;
    }
    aux = arv->sentinela->Fdir;
    while(aux != arv->nulo){
        ant = aux;
        if (aux->chave <= valor)
            aux = aux->Fdir;
        else
            aux = aux->Fesq;
    }
    if (ant->chave <= valor){
        ant->Fdir = n;
    }else{
        ant->Fesq = n;
    }
    n->pai = ant;
    balanceamentoInsercao(arv, n);
    arv->numElementos++;
    return 1;
}

int remover(arv *arv, int valor) {
    no *aux = arv->sentinela->Fdir, *sucessor, *x;
    char corOriginal;

    while (aux != arv->nulo && aux->chave != valor) {
        if (valor < aux->chave) {
            aux = aux->Fesq;
        } else {
            aux = aux->Fdir;
        }
    }

    if (aux == arv->nulo)
        return 0;

    arv->numElementos--;

    corOriginal = aux->cor;

    if (aux->Fesq == arv->nulo) {
        x = aux->Fdir;
        if (aux == aux->pai->Fesq) {
            aux->pai->Fesq = aux->Fdir;
        } else {
            aux->pai->Fdir = aux->Fdir;
        }
        aux->Fdir->pai = aux->pai;
    } else if (aux->Fdir == arv->nulo) {
        x = aux->Fesq;
        if (aux == aux->pai->Fesq) {
            aux->pai->Fesq = aux->Fesq;
        } else {
            aux->pai->Fdir = aux->Fesq;
        }
        aux->Fesq->pai = aux->pai;
    } else {
        sucessor = aux->Fdir;
        while (sucessor->Fesq != arv->nulo) {
            sucessor = sucessor->Fesq;
        }
        corOriginal = sucessor->cor;
        x = sucessor->Fdir;

        if (sucessor->pai == aux) {
            x->pai = sucessor;
        } else {
            if (sucessor == sucessor->pai->Fdir) {
                sucessor->pai->Fdir = sucessor->Fdir;
            } else {
                sucessor->pai->Fesq = sucessor->Fdir;
            }
            sucessor->Fdir->pai = sucessor->pai;
            sucessor->Fdir = aux->Fdir;
            sucessor->Fdir->pai = sucessor;
        }
        if (aux == aux->pai->Fdir) {
            aux->pai->Fdir = sucessor;
        } else {
            aux->pai->Fesq = sucessor;
        }
        sucessor->pai = aux->pai;
        sucessor->Fesq = aux->Fesq;
        sucessor->Fesq->pai = sucessor;
        sucessor->cor = aux->cor;
    }

    if (corOriginal == 'P') {
        balanceamentoRemocao(arv, x);
    }
/*
        predecessor = aux->Fesq;
        while (predecessor->Fdir != arv->nulo) {
            predecessor = predecessor->Fdir;
        }
        corOriginal = predecessor->cor;
        x = predecessor->Fesq;

        if (predecessor->pai == aux) {
            x->pai = predecessor;
        } else {
            if (predecessor == predecessor->pai->Fdir) {
                predecessor->pai->Fdir = predecessor->Fesq;
            } else {
                predecessor->pai->Fesq = predecessor->Fesq;
            }
            predecessor->Fesq->pai = predecessor->pai;
            predecessor->Fesq = aux->Fesq;
            predecessor->Fesq->pai = predecessor;
        }
        if (aux == aux->pai->Fdir) {
            aux->pai->Fdir = predecessor;
        } else {
            aux->pai->Fesq = predecessor;
        }
        predecessor->pai = aux->pai;
        predecessor->Fdir = aux->Fdir;
        predecessor->Fdir->pai = predecessor;
        predecessor->cor = aux->cor;
    }

    if (corOriginal == 'P') {
        balanceamentoRemocao(arv, x);
    }*/

    free(aux);
    return 1;
}

void balanceamentoInsercao(arv *arv, no *n) {
    no *tio;
    while (n->pai->cor == 'V') {
        if (n->pai == n->pai->pai->Fesq) {
            tio = n->pai->pai->Fdir;
            if (tio->cor == 'V') {
                n->pai->cor = 'P';
                tio->cor = 'P';
                n->pai->pai->cor = 'V';
                n = n->pai->pai;
            } else {
                if (n == n->pai->Fdir) {
                    n = n->pai;
                    rotacaoesq(arv, n);
                }
                n->pai->cor = 'P';
                n->pai->pai->cor = 'V';
                rotacaodir(arv, n->pai->pai);
            }
        } else {
            tio = n->pai->pai->Fesq;
            if (tio->cor == 'V') {
                n->pai->cor = 'P';
                tio->cor = 'P';
                n->pai->pai->cor = 'V';
                n = n->pai->pai;
            } else {
                if (n == n->pai->Fesq) {
                    n = n->pai;
                    rotacaodir(arv, n);
                }
                n->pai->cor = 'P';
                n->pai->pai->cor = 'V';
                rotacaoesq(arv, n->pai->pai);
            }
        }
    }
    arv->sentinela->Fdir->cor = 'P';
}

void balanceamentoRemocao(arv *arv, no *n) {
    no *irmao;
    while (n != arv->sentinela->Fdir && n->cor == 'P') {
        if (n == n->pai->Fesq) {
            irmao = n->pai->Fdir;
            if (irmao->cor == 'V') {
                irmao->cor = 'P';
                n->pai->cor = 'V';
                rotacaoesq(arv, n->pai);
                irmao = n->pai->Fdir;
            }
            if (irmao->Fesq->cor == 'P' && irmao->Fdir->cor == 'P') {
                irmao->cor = 'V';
                n = n->pai;
            } else {
                if (irmao->Fdir->cor == 'P') {
                    irmao->Fesq->cor = 'P';
                    irmao->cor = 'V';
                    rotacaodir(arv, irmao);
                    irmao = n->pai->Fdir;
                }
                irmao->cor = n->pai->cor;
                n->pai->cor = 'P';
                irmao->Fdir->cor = 'P';
                rotacaoesq(arv, n->pai);
                n = arv->sentinela->Fdir;
            }
        } else {
            irmao = n->pai->Fesq;
            if (irmao->cor == 'V') {
                irmao->cor = 'P';
                n->pai->cor = 'V';
                rotacaodir(arv, n->pai);
                irmao = n->pai->Fesq;
            }
            if (irmao->Fesq->cor == 'P' && irmao->Fdir->cor == 'P') {
                irmao->cor = 'V';
                n = n->pai;
            } else {
                if (irmao->Fesq->cor == 'P') {
                    irmao->Fdir->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoesq(arv, irmao);
                    irmao = n->pai->Fesq;
                }
                irmao->cor = n->pai->cor;
                n->pai->cor = 'P';
                irmao->Fesq->cor = 'P';
                rotacaodir(arv, n->pai);
                n = arv->sentinela->Fdir;
            }
        }
    }
    n->cor = 'P';
}

void rotacaodir(arv *arv, no *n){
    no *filho;
    filho = n->Fesq;
    n->Fesq = filho->Fdir;
    if (filho->Fdir != arv->nulo){
        filho->Fdir->pai = n;
    }
    filho->pai = n->pai;
    if (n == n->pai->Fesq){
        n->pai->Fesq = filho;
    }else{
        n->pai->Fdir = filho;
    }
    filho->Fdir = n;
    n->pai = filho;
}

void rotacaoesq(arv *arv, no *n){
    no *filho = n->Fdir;
    n->Fdir = filho->Fesq;
    if(filho->Fesq != arv->nulo){
        filho->Fesq->pai = n;
    }
    filho->pai = n->pai;
    if(n == n->pai->Fesq)
        n->pai->Fesq = filho;
    else
        n->pai->Fdir = filho;
    filho->Fesq = n;
    n->pai = filho;
}

int processaCarga(arv *arv, char *nomeArquivo, int tipo){
    FILE *arq;
    int aux, ret;
    arq = fopen(nomeArquivo,"r");
    if(!arq) {
        return -2;
    }
    if (tipo == 1) {
        while (!feof(arq)) {
            if (fscanf(arq, "%d", &aux) == 1) {
                ret = inserir(arv, aux);
            }
        }
    }
    if (tipo == 2){
        while (!feof(arq)) {
            if (fscanf(arq, "%d", &aux) == 1) {
                ret = remover(arv, aux);
            }
        }
    }
    fclose(arq);
    return ret;
}

int getNumElementos(arv *arv){
    return arv->numElementos;
}

no *getRaiz(arv *arv){
    return arv->sentinela->Fdir;
}

void imprimePreOrdem(arv *arv, no *raiz){
    if(raiz != arv->nulo){
        printf("%d - %d - %c\n",raiz->chave, raiz->pai->chave, raiz->cor);
        imprimePreOrdem(arv, raiz->Fesq);
        imprimePreOrdem(arv, raiz->Fdir);
    }
}

void imprimeOrdem(arv *arv, no *raiz){
    if (raiz != arv->nulo){
        imprimeOrdem(arv, raiz->Fesq);
        printf("%d - %d - %c\n",raiz->chave, raiz->pai->chave, raiz->cor);
        imprimeOrdem(arv, raiz->Fdir);
    }
}