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

int main(int argc, unsigned char** argv){
    // unsigned char* string = (char*) malloc(50 * sizeof(char));
    // FILE *f = fopen("teste.txt", "r");

    // int i;
    // for(i = 0; !feof(f); i++){
    //     fscanf(f, "%c", &string[i]);
    // }

    // printf("\n----------------\n");
    // printf("i [%d]\n strlen [%ld]\n", i, strlen(string));
    // printf("\n----------------\n");
    // printf("string: [%s]", string);
    // free(string);
    // fclose(f);
    //ultimo teste foi
    // char* string = (char*) malloc(7 * sizeof(char)); // 0 1 2 3 4 5 6 
    //                                                  // f i l i p e \0
    // strcpy(string, "filipe");
    // printf("[%s] [%ld]", string, strlen(string));

    // free(string);
    
    compacta(argv[1]);
    printf("chega dps da compacta\n");

    FILE *f = fopen("fotinha.jpg.comp", "r");
    if(f == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    bitmap* bm = leArquivoCompactado(f);
    printf("entrou decodifica na main\n");
    decodifica(bm);

    fclose(f);   
    bitmapLibera(bm);

    return 0;
}

/** TO DO
 * Corrigr função set que fizemos no bitmap OK [ELIMINAMOS ELA, APAGAR ESSA FUNÇÃO!!!, FAZER A OUTRA Q SETA BITS.]
 * Entrada com único caractere
 * Mudar o código na abertura de arquivo, está hardcodado
 * Separar em dois programas: um que só compacta e outro que só descompacta
 * Ajeitar makefile por causa dessa separação
 * Relatório
**/ 
