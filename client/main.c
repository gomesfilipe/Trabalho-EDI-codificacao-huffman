#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitmap.h"
#include "../include/tree.h"
#include "../include/list.h"
#include "../include/huffman.h"
#include "../include/compactador.h"
#include "../include/descompactador.h"

#define TAM 256

int main(int argc, unsigned char** argv){
    // compacta(argv[1]);

    // //descompacta(argv[1]);

    // FILE *f = fopen("data/musica.mp3.comp", "r");
    // if(f == NULL){
    //     printf("Erro na abertura do arquivo.\n");
    //     exit(1);
    // }

    // bitmap* bm = leArquivoCompactado(f);

    // decodifica(bm, argv[1]);

    // fclose(f);   
    // bitmapLibera(bm);

    return 0;
}

/** TO DO
 * Entrada com único caractere TESTAR MAIS CASOS.
 * revisar o código inteiro. (verificar se não faltou documentar nada e retirar comentários que estão em excesso).
 * Ajeitar makefile por causa dessa separação
 * Relatório
**/ 
