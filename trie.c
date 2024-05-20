#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

#define N_ALFABETO 38

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

int mapearIndice(char c) {
    if (c == '\0') return 0;
    if (c == ' ') return 1;
    if (c >= '0' && c <= '9') return c - '0' + 2;
    if (c >= 'a' && c <= 'z') return c - 'a' + 12;
    else return 63;
}

void insere (PONT raiz, char *chave, int valor) {
    if (!raiz || !chave) return;

    int indice;
    int tamChave = strlen (chave);
    PONT aux = raiz;

    for (int i = 0; i < tamChave; i++) {
        indice = mapearIndice(chave[i]);
        if (!aux->filhos[indice])
            aux->filhos[indice] = criaNo ();
        aux = aux->filhos[indice];
    }
    aux->filhos[0] = criaNo();
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


char* formataPalavra(char *chave) {
    if (!chave) return NULL;
    int tamToken;
    // Pega o primeiro token (ignora o comando "p")
    char *token = strtok(chave, " ");
    // Pega o segundo token (a palavra que queremos)
    token = strtok(NULL, " ");

    // Verifica se o token foi encontrado
    if (!token) return NULL;
    for (int i = 0; token[i]; i++) {
        token[i] = tolower(token[i]);
    }  
    return token;
}

char converteIndiceParaLetra(int indice) {
    if (indice == 0) return '\0';
    if (indice == 1) return ' ';
    if (indice >= 2 && indice <= 11) return (char)('0' + (indice - 2));
    if (indice >= 12 && indice <= 37) return (char)('a' + (indice - 12));
    else return '?';
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


void filmesComPrefixo(PONT raiz, char* chave) {
    if (!raiz || !chave) return;
    
    // Faz uma cópia da palavra para não alterar a variável original
    char *chaveFormatada = strdup(chave);
    if (!chaveFormatada) {
        fprintf(stderr, "Erro ao copiar a palavra\n");
        return;
    }

    char *token = formataPalavra(chaveFormatada);
    if (!token) {
        fprintf(stderr, "Erro ao formatar a palavra\n");
        free(chaveFormatada); // Libera a memória da cópia
        return;
    }

    PONT atual = busca(raiz, token);
    if (atual) {
        for (int i = 0; i < N_ALFABETO; i++) {
            printf("%s", token);
            imprime(atual, token);
        }
    }        
    else fprintf(stderr, "Palavra não encontrada\n");
    
    // Libera a memória da cópia
    free(chaveFormatada);
}


// https://www.youtube.com/watch?v=MEmLEYhna-I
// Raiz nao possui valor
// Dados estão nas folhas
// Indice são caracteres que são colocados nos nós
// Será que precisamos  estipular valores para cada palavra? Ex: 1,2,3,4...
// Video aula = https://www.youtube.com/watch?v=Spmw4hTo7ek