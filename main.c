#include <stdio.h>
#include "trie.h"

int main (int argc, char* argv[]) {
    printf ("hello world\n");

    PONT raiz = criaNo ();
    insere (raiz, "GUILHERME", 12);
    imprimeArvore(raiz, 0);
    insere (raiz,"gui o BRabo", 14);
    insere (raiz,"gui a maquina", 10);

    imprimeArvore (raiz, 0);

    if (busca (raiz, "guilherme")) 
        printf ("encontrei\n");
    else printf ("Nao encontrei a palavra\n");

    insere (raiz,"rocky", 19);
    insere (raiz,"rocky i", 20);
    insere (raiz,"rocky ii", 21);
    insere (raiz,"rocky iii", 22);

    imprimeArvore(raiz, 0);

    return 0;
}

//arrumar a impressao do \0