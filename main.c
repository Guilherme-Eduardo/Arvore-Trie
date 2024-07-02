#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"

int main (int argc, char* argv[]) {

    if (argc <= 1 ) {
        fprintf (stderr, "Erro ao abrir arquivos\n");
        return 1;
    }

    char linha[100], *palavra, *distanciaEdicaoStr;
    int distanciaEdicaoNum;
    char copiaPalavra[100];
    
    PONT raiz = criaNo ();                                          /*Cria a raiz da nossa arvore trie*/
    FILE *dicionario = abreDicionario (argv[1]);                    /*Aqui eu estou passando o dicionario do argv e adicionando ele na variavel FILE */
    preencheArvoreComDicionario (raiz, dicionario);                 /*Lê arquivo e joga na arvore (é bom testar a funcao. Eu acho que está funcionando (usei a funcao imprime para isso))*/
        
   while (fgets (linha, sizeof(linha), stdin) != NULL) {                   /*Enquanto nao chega no fim do arquivo que foi mandado pela entrada padrao (stdin) faça...*/
        palavra = separa (linha, ' ');                              /*Separo as informacoes que foram passadas no arquivo de entrada em 2 variaveis*/
        strcpy (copiaPalavra, palavra);
        palavra += strlen (palavra) + 1;
        distanciaEdicaoStr = separa (palavra, ' ');
        if (distanciaEdicaoStr)
            distanciaEdicaoNum = atoi (distanciaEdicaoStr);             /*Converto a string numero para int numero*/
        if (palavra && distanciaEdicaoStr)
            buscaPalavras (raiz, dicionario, copiaPalavra, distanciaEdicaoNum);     /*Entra na funcao que procura as palavras na arvore*/
    }

    destroiArvore (raiz);    
    fclose (dicionario);
    return 0;
}

