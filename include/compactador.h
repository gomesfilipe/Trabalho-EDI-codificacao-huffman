#ifndef COMPACTADOR_H_
#define COMPACTADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/arvore.h"
#include "../include/lista.h"
#include "../include/bitmap.h"
#include "../include/huffman.h"

void codificaTree(Tree* tree, bitmap* bm);

void converteDecimalParaBinario(unsigned char elem, unsigned char* bin);

bitmap* criaBitMapCompac(Tree* tree);

#endif /* COMPACTADOR_H_ */
