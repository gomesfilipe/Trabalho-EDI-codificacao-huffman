#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitmap.h"
#include "../include/arvore.h"
#include "../include/lista.h"
#include "../include/huffman.h"
#include "../include/compactador.h"
#include "../include/descompactador.h"

// bom esse bombom
#define TAM 256

int main(){
    //A = "01000001
    // unsigned char c = 'é';
    // unsigned char bin[8];
    // converteDecimalParaBinario(c, bin);
    // printf("\n\n[%s]\n\n", bin);
    
    FILE *f = fopen("string.txt", "r");
    Tree* tree = geraArvoreCodificacao(f); //gera uma arvore a partir do arquivo
    imprimeTree(tree);
    printf("\n\n");
    printf("qtd folhas [%d]\n\n", qtdFolhas(tree));
    bitmap* bm = criaBitMapCompac(tree);
    codificaTree(tree, bm);   //codifica a arvore para gerar o cabeçalho do arquivo compactado
    char* string = bitmapGetContents(bm);
    printf("\n[%s]\n", string);

    unsigned char** tabela = criaTabelaCodificacao(tree);
    tabela = inicializaTabelaCodificacao(tree, tabela, "");

    imprimeTabelaCodificacao(tabela);

    // int *pesos = calculaPesos(f);
    // for(int i =0 ; i< TAM ; i++){
    //     if(pesos[i] != 0){
    //         printf("caractere [%c] | ", i);
    //         printf("peso [%d]\n", pesos[i]);
    //     }
    // }
    fclose(f);
    liberaTree(tree);
    bitmapLibera(bm);
    // liberaTabelaCodificacao(tabela);
    // Tree* a = criaTree('a', 2,  NULL, NULL);
    // Tree* b = criaTree('b', 17, NULL, NULL);
    // Tree* c = criaTree('c', 4, NULL, NULL);
    // Tree* d = criaTree('d', 7,  NULL, NULL);
    // Tree* e = criaTree('e', 0,  NULL, NULL);
    // Tree* f = criaTree('f', 14, NULL, NULL);
    // Tree* g = criaTree('g', 2,  NULL, NULL);
    // Tree* h = criaTree('h', 19, NULL, NULL);
    // Tree* i = criaTree('i', 20, NULL, NULL);
    // Tree* j = criaTree('j', 23, NULL, NULL);
    // Tree* k = criaTree('k', 13, NULL, NULL);

    // List* list = criaLista();
    // insereOrdenado(list, a);
    // insereOrdenado(list, b);
    // insereOrdenado(list, c);
    // insereOrdenado(list, d);
    // insereOrdenado(list, e);
    // insereOrdenado(list, f);
    // insereOrdenado(list, g);
    // insereOrdenado(list, h);
    // insereOrdenado(list, i);
    // insereOrdenado(list, j);
    // insereOrdenado(list, k);

    // imprimeLista(list);

    // Tree* arv = huffman(list);
    // printf("altura [%d]\n", altura(arv));
    // imprimeTree(arv);
    // removeFirst(list);
    // removeFirst(list);
    // removeFirst(list);
    // removeFirst(list);
    // removeFirst(list);
    // removeFirst(list);
    // removeFirst(list);
    // removeFirst(list);
    // removeFirst(list);
    // removeFirst(list);
    // removeFirst(list);
    // removeFirst(list);
   

    // imprimeLista(list);
    // liberaTree(arv);
    // liberaLista(list);
    // liberaTree(a);
    // liberaTree(b);
    // liberaTree(c);
    // liberaTree(d);
    // liberaTree(e);
    // liberaTree(f);
    // liberaTree(g);
    // liberaTree(h);
    // liberaTree(i);
    // liberaTree(j);
    // liberaTree(k);
    return 0;
}
