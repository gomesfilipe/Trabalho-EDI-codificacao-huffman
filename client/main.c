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
    
    FILE* fRead = fopen("string.txt", "r");
    if(fRead == NULL){
        printf("Erro na abertura do arquivo.");
        exit(1);
    }

    // unsigned char c;
    // fscanf(fRead, "%c", &c);
    // printf("[%c]", c);

    compacta(fRead);

    fclose(fRead);
   
    return 0;
}
