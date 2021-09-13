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

int main(int argc, char** argv){
    compacta(argv[1]);
    return 0;
}

/** TO DO
 * Resolver codificação da arvore com caracteres com acento, ç etc
**/ 

/** Duvidas
 * O arquivos de entrada serão apenas txt? Ou terá png, mp3, etc?
 * Os textos terão acentos? Pois uma parte da tabela ascii não é imprimível

**/