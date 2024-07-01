#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"

int main (int argc, char* argv[]) {

    /* 
        Precisamos ver como ira funcionar essa questao de passar o dicionario como parametro da funcao, pois o professor não explicou isso
        digo "./<nome_do_programa> dicionario.txt" ----> não sei se é essa forma de passar o dicionario.
        só sei que precisamos passar o teste e depois jogar a saida num outro arquivo
        ex: ./<nome_do_programa> < entrada.txt > saida.txt
        Além disso, precisamos ver como cada arquivo ira se chamar

        Nome do arquivo = executavel se chamara dicionario OK
        como eu chamo a o dicionario.o
        como eu insiro ao dicionario
        max de palavras lidas é 20 = OK
        max de erro é 3 = OK
        alterar formatacao da saida.txt
        Fazer Makefile = OK
        remover o ternario da funcao busca
    
    */
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

