#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitmap.h"
#include "../include/arvore.h"
#include "../include/lista.h"
#include "../include/huffman.h"
#include "../include/compactador.h"
#include "../include/descompactador.h"

#define TAM 256

int main(int argc, char** argv){
    compacta(argv[1]);

    FILE *f = fopen("string.txt.comp", "r");
    if(f == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    bitmap* bm = leArquivoCompactado(f);
 
    decodifica(bm);

    fclose(f);   
    bitmapLibera(bm);
    return 0;
}

/** TO DO
 * Corrigr função set que fizemos no bitmap
 * Recalcular o tamanho do bitmap na decodificação
 * Ver o caso do realloc
 * Criar o arquivo com o titulo tirando o .comp
 * Terminar de documentar as funções nos .h
 * Separar em dois programas: um que só compacta e outro que só descompacta
 * Ajeitar makefile por causa dessa separação
 * Relatório
**/ 
