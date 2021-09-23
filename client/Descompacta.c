#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitmap.h"
#include "../include/tree.h"
#include "../include/list.h"
#include "../include/huffman.h"
#include "../include/descompactador.h"

int main(int argc, unsigned char** argv){
    descompacta(argv[1]);
    return 0;
}
