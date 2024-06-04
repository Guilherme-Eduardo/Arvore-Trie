/*
    Possiveis problemas: Ele insere nomes duplicados
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

#define N_ALFABETO 26

struct no* criaNo () {
    PONT p = NULL;
    p = (PONT) malloc (sizeof(struct no));

    if (!p) return NULL;

    for (int i = 0; i < N_ALFABETO; i++)
        p->filhos[i] = NULL;
    p->fim = 0;
    p->valor = 0;
    return p;
}

/*void destroi_no () {


}*/

int mapearIndice(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    else return -1;
}

void palavra_miniscula (char *chave) {
    if (!chave) return;    
    int i;
    for (i = 0; i < strlen (chave); i++) {        
            chave[i] = tolower(chave[i]);
    }
    chave [++i] = '\0';
}

void insere (PONT raiz, char *chave, int valor) {
    if (!raiz || !chave) return;

    int indice;
    char copia_chave [strlen (chave) + 1];
    strcpy (copia_chave, chave);
    palavra_miniscula (copia_chave);       
    PONT aux = raiz;    

        for (int i = 0; i < strlen (copia_chave); i++) {
            indice = mapearIndice(copia_chave[i]);   
            if (indice >= 0) {
                if (!aux->filhos[indice])
                    aux->filhos[indice] = criaNo ();
                aux = aux->filhos[indice];                
            }
    }    
    aux->fim = 1;
    aux->valor = valor;
}

struct no* busca (PONT raiz, char *chave) {
    if (!raiz || !chave) return NULL;

    int tamChave, indice;
    tamChave = strlen (chave);
    PONT aux = raiz;

    for (int i = 0; i < tamChave; i++) {
        indice = mapearIndice(chave[i]);
        if (!aux->filhos[indice]) return NULL;
        aux = aux->filhos[indice];
    }
    return aux;
}

char converteIndiceParaLetra(int indice) {
    return indice + 'a';
}


void imprimeTabulacao(int nivel) {
    for (int i = 0; i < nivel; i++) {
        printf("\t");
    }
}

void imprimeArvore (PONT raiz, int nivel) {
    if (!raiz) return;
    int i;    
    for (i = 0; i < N_ALFABETO; i++) {
        if (raiz->filhos[i]) {
            imprimeTabulacao (nivel);
            printf ("%c\n", converteIndiceParaLetra(i));
            if (raiz->filhos[i]->fim) {
                imprimeTabulacao(nivel + 1);
                printf ("\\0\n");
                //printf ("%c\n", converteIndiceParaLetra(0));
            }
            imprimeArvore (raiz->filhos[i], nivel + 1);
        }
    }
}

void imprime (PONT raiz, char *chave) {
    if (!raiz) return;
    int i;        
    for (i = 0; i < N_ALFABETO; i++) {
        if (raiz->filhos[i]) {
            printf ("%c", converteIndiceParaLetra(i));          
            imprime (raiz->filhos[i], chave);
        }        
    }
}

// https://www.youtube.com/watch?v=MEmLEYhna-I
// Raiz nao possui valor
// Dados estão nas folhas
// Indice são caracteres que são colocados nos nós
// Será que precisamos  estipular valores para cada palavra? Ex: 1,2,3,4...
// Video aula = https://www.youtube.com/watch?v=Spmw4hTo7ek

/* Como já dito nos comentários, strings declaradas como char *string = "" não podem ser modificadas. Mas por que?

A razão dela não poder ser modificada, é porque você criou um ponteiro que referencia uma string estática, ou seja, foi criada em tempo de compilação. Essa string será armazenada nos binários do seu programa compilado, e não no contexto da sua função (ou da pilha de memória).

Não apenas isso, mas o seu programa é otimizado para que todas as strings estáticas idênticas apontem para o mesmo endereço de memória.

Por exemplo, no seguinte código:

char *str1 = "XXX";
char *str2 = "XXX";
str1 e str2 não são apenas strings idênticas, elas são exatamente a mesma string no endereço de memória, o que significa que se você modificar str1, estaria modificando str2.

Isso abre a possibilidade de diversos problemas com strings sendo declaradas em arquivos diferentes sendo acidentalmente modificadas. Por tal razão o compilador irá tentar te impedir de modificar tais strings, e você também deveria evitar faze-lo, mesmo que consiga burlar a verificação.*/