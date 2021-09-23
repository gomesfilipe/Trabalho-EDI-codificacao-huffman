#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitmap.h"
#include "../include/tree.h"
#include "../include/list.h"
#include "../include/huffman.h"
#include "../include/compactador.h"

int main(int argc, unsigned char** argv){
    compacta(argv[1]); // arquivo.formato
    return 0;
}
