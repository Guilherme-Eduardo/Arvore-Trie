#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

int main (int argc, char* argv[]) {

    if (argc <= 1 ) {
        fprintf (stderr, "Erro ao abrir arquivos\n");
        return 1;
    }

    char linha[100], *palavra, *distanciaEdicaoStr;
    int distanciaEdicaoNum;

    char copiaPalavra[100];
    
    PONT raiz = criaNo ();
    FILE *dicionario = abreDicionario (argv[1]);
    preencheArvoreComDicionario (raiz, dicionario);

    while (fgets (linha, sizeof(linha), stdin)) {        
        palavra = separa (linha, ' ');
        strcpy (copiaPalavra, palavra);
        palavra += strlen (palavra) + 1;
        distanciaEdicaoStr = separa (palavra, ' ');
        distanciaEdicaoNum = atoi (distanciaEdicaoStr);
        printf ("nome: %s\nErros: %d\n", copiaPalavra, distanciaEdicaoNum);
        //buscaPalavras (raiz, palavra, distanciaEdicao);

        /*
        separador da palavra e erro
        busca (palavra, erro);
        */
    }



    /*
    insere (raiz, "GUILHERME", 12);
    insere (raiz,"gui o BRabo", 14);
    insere (raiz,"gui a maquina", 10);

    printf ("hello world\n");
    imprimeArvore(raiz, 0);

    if (busca (raiz, "guilherme")) 
        printf ("encontrei\n");
    else printf ("Nao encontrei a palavra\n");

    imprimeArvore (raiz, 0);


    insere (raiz,"rocky", 19);
    insere (raiz,"rocky i", 20);
    insere (raiz,"rocky ii", 21);
    insere (raiz,"rocky iii", 22);

    imprimeArvore(raiz, 0);

    */
    fclose (dicionario);
    return 0;
}

//arrumar a impressao do \0