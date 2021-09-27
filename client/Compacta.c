/**
 * Alunos:
 * Filipe Gomes Arante de Souza - 2020100625
 * Elaine Dias Pires - 2020101903
 * 
 * Professora: Patricia Dockhorn Costa
 * Estrutura de Dados I 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitmap.h"
#include "../include/tree.h"
#include "../include/list.h"
#include "../include/huffman.h"
#include "../include/compactador.h"

int main(int argc, unsigned char** argv){
    if(argc != 2){
        printf("Numero incorreto de argumentos na linha de comando.\n");
        exit(1);
    }
    
    compacta(argv[1]); // arquivo.(formato)
    return 0;
}
