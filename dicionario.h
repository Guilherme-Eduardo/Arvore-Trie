#ifndef _DICIONARIO_H
#define _DICIONARIO_H

#define N_ALFABETO 26

/* Definição da struct */
struct no {
    char valor;
    struct no *filhos[N_ALFABETO];
    int fim;
};

typedef struct no* PONT;

/* Definição das funcoes do TAD Arvore Trie */

struct no* criaNo ();
void destroiArvore (PONT);
void insere (PONT, char*, int);
struct no* busca (PONT,char*);
void imprimeArvore (PONT, int);


/************* Funcoes relacionados ao  dicionario *****************/

FILE *abreDicionario (char *);
int preencheArvoreComDicionario (PONT, FILE*);
void buscaPalavras(PONT, FILE*, const char *, int);
char *separa(char *, char);
void removeNovaLinha(char *);

#endif