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
        if (!aux->filhos[indice]) 
            return NULL;
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


/*************************************************************************************** */

FILE *abreDicionario (char *arquivo) {
    if (!arquivo) {
        fprintf (stderr, "Impossivel abrir o dicionario\n");
        return NULL;
    }
    FILE *dicionario = fopen (arquivo, "r");
    if (!dicionario) {
        fprintf (stderr, "Erro ao tentar abrir o dicionario\n");
        return NULL;
    }
    return dicionario;

}

void removeNovaLinha(char *linha) {
    if (!linha) {
        fprintf(stderr, "Erro ao tentar remover \\n da palavra\n");
        return;
    }
    
    if (strlen (linha) > 0 && linha[strlen (linha) - 1] == '\n') {
        linha[strlen (linha) - 1] = '\0';
    }
}


int preencheArvoreComDicionario (PONT raiz, FILE *dicionario) {
    if (!raiz || !dicionario) {
        fprintf (stderr, "Erro ao preencher arvore com o dicionario\n");
        return 1;
    }

    int i = 0;
    char linha[100] = {0};

    while (fgets (linha, sizeof(linha), dicionario)) {
        removeNovaLinha (linha);
        insere (raiz, linha, i++);
    }

    return 0;
}

void busca_ (PONT raiz, const char *palavra, int errosMaximos, char *palavraAtual, int nivel, int *dp) {
    // Se é o final de uma palavra e o número de erros é permitido, imprime palavraAtual
    if (raiz->fim && dp[strlen(palavra)] <= errosMaximos) {
        palavraAtual[nivel] = '\0';
        printf("%s\n", palavraAtual);  // Imprime a palavra atual
    }

    // Se a raiz é nula ou a palavra está vazia, retorna
    if (raiz == NULL || *palavra == '\0') return;

    // Array para armazenar a DP atual
    int dpAtual[N_ALFABETO + 1];
    // Inicializa dpAtual com os valores de dp incrementados por 1
    for (int i = 0; i <= N_ALFABETO; i++) {
        dpAtual[i] = dp[i] + 1;
    }

    // Itera sobre todos os possíveis caracteres (26 letras + espaço)
    for (int i = 0; i < N_ALFABETO; i++) {
        if (raiz->filhos[i]) {
            char c = (i == 26) ? ' ' : 'a' + i;  // Determina o caractere correspondente
            palavraAtual[nivel] = c;  // Adiciona o caractere à palavra atual

            dpAtual[0] = dp[0] + 1;  // Inicializa dpAtual[0]
            for (int j = 1; palavra[j - 1]; j++) {
                if (tolower(palavra[j - 1]) == c) {
                    dpAtual[j] = dp[j - 1];  // Se os caracteres são iguais, herda o valor de dp[j - 1]
                } else {
                    int min1 = dp[j];
                    int min2 = dp[j - 1];
                    int min3 = dpAtual[j - 1];
                    int minimo = min1;

                    if (min2 < minimo) {
                        minimo = min2;
                    }
                    if (min3 < minimo) {
                        minimo = min3;
                    }

                    dpAtual[j] = 1 + minimo;  // Calcula o mínimo entre os valores de dp[j], dp[j - 1] e dpAtual[j - 1], incrementado por 1
                }
            }

            // Chama recursivamente para o próximo nível da trie
            busca_ (raiz->filhos[i], palavra, errosMaximos, palavraAtual, nivel + 1, dpAtual);
        }
    }
}

void buscaPalavras(PONT raiz, const char *palavra, int errosMaximos) {
    char palavraAtual[100];  // Buffer para armazenar a palavra atual durante a busca
    int dp[strlen(palavra) + 1];  // Array para a DP, de tamanho igual ao comprimento da palavra + 1
    // Inicializa dp com valores de 0 a strlen(palavra)
    for (int i = 0; i <= strlen(palavra); i++) {
        dp[i] = i;
    }
    busca_(raiz, palavra, errosMaximos, palavraAtual, 0, dp);  // Chama a função busca
}

// Funcao responsavel por separar as palavras dependendo de um char separador
char *separa(char *linha, char separador) {
    if (!linha)
        return NULL; // Se a linha passada por parametro já for nula

    char *posSeparador;
    posSeparador = strchr(linha, separador);

    if (!posSeparador) { // Se nao encontrar a virgula, verifica se nao chegou na ultima parte a ser lida (antes do \)
        if (strlen(linha))
            return linha;
        else
            return NULL;
    }
    *posSeparador = '\0'; // Substitui o separador por um '\0' que indicara o final da string
    return linha;
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

Isso abre a possibilidade de diversos problemas com strings sendo declaradas em arquivos diferentes sendo acidentalmente modificadas. Por tal razão o compilador irá tentar te impedir de modificar tais strings, e você também deveria evitar faze-lo, mesmo que consiga burlar a verificação.

será que realmente é necessario a palavra receber um valor?
distancia de edição*/
