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

// quando lia 'ç', tinham 2 char
// 'ç' = 'c' + '-'
// c vai ter uma codificacao supoe que é 101
// '-' tbm vai ter uma codificacao 11
// çsdjfijgfkljsdklgopfiunevun10111

// TEXTO CODIFICADO
// 01111001
// 10101100
// 10010111
// 00111100
// 01111000

int main(int argc, char** argv){
    compacta(argv[1]);

    FILE *f = fopen("string.comp", "r");

    bitmap* bm = leArquivoCompactado(f);
    printf("\n\nbitmap [");
    decodifica(bm);
    // for(int i = 0; i < bitmapGetLength(bm); i++){
    //     if(i % 8 == 0){
    //         printf("\n");
    //     }
    //     if(i == 72){
    //         printf("\n");
    //     }
       
    //     printf("%d", bitmapGetBit(bm, i));
    // }
    // printf("]\n");

    //Tree* tree = decodificaCabecalho(bm);

    //imprimeTree(tree);

    fclose(f);   
    //liberaTree(tree);
    bitmapLibera(bm);

    return 0;
}

/** TO DO
 * Resolver codificação da arvore com caracteres com acento, ç etc ok
**/ 

/** Duvidas
 * O arquivos de entrada serão apenas txt? Ou terá png, mp3, etc?
 * Os textos terão acentos? Pois uma parte da tabela ascii não é imprimível ok

**/