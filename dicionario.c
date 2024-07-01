#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dicionario.h"

#define N_ALFABETO 26

/*Funcao responsavel por criar o no*/
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

/*Funcao responsavel por liberar toda a memoria do no*/
void destroiArvore(PONT raiz) {
    if (!raiz) return;

    for (unsigned int i = 0; i < N_ALFABETO; i++) {
        if (raiz->filhos[i]) {
            destroiArvore (raiz->filhos[i]);            
        }
    }   
    free(raiz);                                                                                 /*Após destruir todos os filhos, libera o nó atual*/
}

/* Informa qual é o indice do vetor referente a letra. Ex: a == 0 (97 - 97), b == 1 ...*/
int mapearIndice(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    else return -1;
}

/*Converte todas a letras da palavra para miniscula*/
void palavra_miniscula (char *chave) {
    if (!chave) return;    
    unsigned int i;
    for (i = 0; i < strlen (chave); i++) {        
            chave[i] = tolower(chave[i]);
    }
    chave [++i] = '\0';
}

/*Funcao responsavel por inserir as palavras do dicionario na arvore*/
void insere (PONT raiz, char *chave, int valor) {
    if (!raiz || !chave) return;

    int indice;
    char copia_chave [strlen (chave) + 1];
    strcpy (copia_chave, chave);                                    /*Preciso criar uma copia da palavra, pois eu não consigo modificar uma string constante*/
    palavra_miniscula (copia_chave);       
    PONT aux = raiz;    

    for (unsigned int i = 0; i < strlen (copia_chave); i++) {                /*Percorre pelo tamanho da palavra*/    
        indice = mapearIndice(copia_chave[i]);                      /*Verifica qual eh o indice do vetor do no referente a letra*/
        if (indice >= 0) {
            if (!aux->filhos[indice])                               /*Se essa letra referente ao indice nao existir, ele criara o nodo para aquela letra*/
                aux->filhos[indice] = criaNo ();
            aux = aux->filhos[indice];                              
        }
    }    
    aux->fim = 1;                                                   /*Quando chega ao final da palavra é setado essa variavel*/
    aux->valor = valor;                                             /*valor para cada palavra, professor comentou isso em aula.*/
}

/* Função de busca apenas para encontrar uma determinada palavra na arvore trie*/
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

/*Usado para imprimir a arvore de forma tabulada (como se fosse realmente um arvore)*/
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


/****************************** Funcoes que serão utilizadas com o dicionario ********************************************************* */

/* Recebe o arquivo .txt do dicionario passado como parametro e retorna como arquivo FILE* */
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

/* Remove o caracter "\n" da linha que estamos lendo do arquivo de entrada.txt */
void removeNovaLinha(char *linha) {
    if (!linha) {
        fprintf(stderr, "Erro ao tentar remover \\n da palavra\n");
        return;
    }
    
    if (strlen (linha) > 0 && linha[strlen (linha) - 1] == '\n') {
        linha[strlen (linha) - 1] = '\0';
    }
}

/* Função responsavel por preencher toda a arvore com os caracteres das palavras passadas pelo dicionario*/
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

void imprimePalavra(FILE *arquivo, int valor) {
    if (!arquivo) return;

    char linha[100];
    char *token;
    int i = 0;
    rewind (arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (i == valor) {
            token = strtok(linha, " ");
            token [strlen (token + 1)] = '\0';
            printf("%s", token);
            return; // Após encontrar a palavra, podemos retornar
        }
        i++;
    }
}

/*Funcao principal, não testei ela. Peguei da net e fiz alteracoes*/
void busca_ (PONT raiz, FILE *dicionario, const char *palavra, int errosMaximos, 
            char *palavraAtual, int nivel, int *dp, int *maxPalavras) {                
    
    if (raiz->fim && dp[strlen(palavra)] <= errosMaximos) {                     /* Se é o final de uma palavra e o número de erros é permitido, imprime palavraAtual */
        if (*maxPalavras < 20) {                                                /* Limite de impressao de palavras similares */
            if (*maxPalavras > 0)
                printf (", ");
            palavraAtual[nivel] = '\0';
            //printf("%s", palavraAtual);                                         /*Imprime a palavra atual que foi encontrada dentro do limite de erros*/
            imprimePalavra (dicionario, raiz->valor);
            (*maxPalavras)++;
        }
    }
   
    if (raiz == NULL || *palavra == '\0') return;

    
    int dpAtual[N_ALFABETO + 1];                                                 /*Array para armazenar a DP atual */

    
    for (int i = 0; i <= N_ALFABETO; i++) {                                     /*Inicializa dpAtual com os valores de dp incrementados por 1*/
        dpAtual[i] = dp[i] + 1;
    }

    for (int i = 0; i < N_ALFABETO; i++) {
        if (raiz->filhos[i]) {
            char c = 'a' + i;                                                   /* Determina o caractere correspondente */ 
            palavraAtual[nivel] = c;                                            /* Adiciona o caractere à palavra atual */ 

            dpAtual[0] = dp[0] + 1;                                             //*Inicializa dpAtual[0] /*
            for (int j = 1; palavra[j - 1]; j++) {
                if (tolower(palavra[j - 1]) == c) {
                    dpAtual[j] = dp[j - 1];                                     /* Se os caracteres são iguais, herda o valor de dp[j - 1]*/
                } else {                                                        /* Tentar encontrar o minimo */
                    int min1 = dp[j];                                           /* Inserção: dp[j] + 1*/
                    int min2 = dp[j - 1];                                       /*  dp[j - 1] + 1 */
                    int min3 = dpAtual[j - 1];                                  /* Substituição: dpAtual[j - 1] + 1*/
                    int minimo = min1;

                    if (min2 < minimo) {
                        minimo = min2;
                    }
                    if (min3 < minimo) {
                        minimo = min3;
                    }

                    dpAtual[j] = 1 + minimo;                                    /* Calcula o mínimo entre os valores de dp[j], dp[j - 1] e dpAtual[j - 1], incrementado por 1 */
                }
            }            
            busca_ (raiz->filhos[i], dicionario, palavra, errosMaximos, palavraAtual, nivel + 1, dpAtual, maxPalavras);
        }
    }
}

void buscaPalavras(PONT raiz, FILE *dicionario, const char *palavra, int errosMaximos) {
    char palavraAtual[100];                                                     // Buffer para armazenar a palavra atual durante a busca
    int dp[strlen(palavra) + 1];                                               // Array para a DP, de tamanho igual ao comprimento da palavra + 1
    int maxPalavras = 0;
  
    for (unsigned int i = 0; i <= strlen(palavra); i++) {                                // Inicializa dp com valores de 0 a strlen(palavra) | distancia de edicao (primeira linha)       
        dp[i] = i;
    }
    printf ("%s:", palavra);
    if (errosMaximos >= 0 && errosMaximos < 4)
        busca_(raiz, dicionario, palavra, errosMaximos, palavraAtual, 0, dp, &maxPalavras);  
    printf ("\n");
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


dp = distancia de edicao

dpAtual[j] é calculado considerando as três operações possíveis:

Inserção: dp[j] + 1
Deleção: dp[j - 1] + 1
Substituição: dpAtual[j - 1] + 1

*/
