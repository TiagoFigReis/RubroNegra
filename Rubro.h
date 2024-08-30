//
// Created by tiago on 07/06/2024.
//

#ifndef EX_9_RUBRO_NEGRA_RUBRO_H
#define EX_9_RUBRO_NEGRA_RUBRO_H
typedef struct no no;

typedef struct arvore arv;

arv *criaArvore();

int inserir(arv *arv, int valor);

int remover(arv *arv, int valor);

void balanceamentoInsercao(arv *arv, no *n);

void balanceamentoRemocao(arv *arv, no *n);

void rotacaodir(arv *arv, no *n);

void rotacaoesq(arv *arv, no *n);

int processaCarga(arv *arv, char *nomeArquivo, int tipo);

int getNumElementos(arv *arv);

no *getRaiz(arv *arv);

void imprimePreOrdem(arv *arv, no *raiz);

void imprimeOrdem(arv *arv, no *raiz);
#endif //EX_9_RUBRO_NEGRA_RUBRO_H
