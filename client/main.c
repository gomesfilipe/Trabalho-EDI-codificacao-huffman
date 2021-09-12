#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitmap.h"
#include "../include/arvore.h"
#include "../include/lista.h"
#include "../include/huffman.h"
#include "../include/compactador.h"
#include "../include/descompactador.h"
//#include <locale.h>

// bom esse bombom
#define TAM 256

int main(){
    //setlocale(LC_ALL, "Portugues");
    //char* c = 'á';
    FILE *f = fopen("string.txt", "r+");
    FILE* f2 = fopen("codificado.txt", "w");
    
    //fprintf(f,"(%c)", c);
    Tree* tree = geraArvoreCodificacao(f); //gera uma arvore a partir do arquivo
    
    //imprimeTree(tree);
    //printf("\n\n");

    bitmap* bm = criaBitMapCompac(tree);
    bm = insereQtdFolhas(tree, bm);
    codificaTree(tree, bm);   //codifica a arvore para gerar o cabeçalho do arquivo compactado
    
    char* string = bitmapGetContents(bm);
    printf("\n[%s]\n", string);

    //unsigned char** tabela = criaTabelaCodificacao(tree);
    //tabela = inicializaTabelaCodificacao(tree, tabela, "");

    //imprimeTabelaCodificacao(tabela);
    imprimeCabecalho(f2, bm);

    fclose(f2);
    f2 = fopen("codificado.txt", "r");

    unsigned char string2[100];
    fscanf(f2, "%s", string2);
    for(int i = 0; string2[i] != '\0'; i++){
        printf("(%d) ", string2[i]);
    }

    fclose(f2);
    fclose(f);
    liberaTree(tree);
    bitmapLibera(bm);
    //liberaTabelaCodificacao(tabela);
   
    return 0;
}
