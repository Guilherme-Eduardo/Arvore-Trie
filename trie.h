#ifndef _TRIE_H
#define _TRIE_H

#define N_ALFABETO 38

struct no {
    char valor;
    struct no *filhos[N_ALFABETO];
    int fim;
};

typedef struct no* PONT;

struct no* criaNo ();
void insere (PONT, char*, int);
struct no* busca (PONT,char*);
void imprimeArvore (PONT, int);
void filmesComPrefixo (PONT, char*);
void maiorPrefixo (PONT);


#endif