#ifndef DESCOMPACTADOR_H_
#define DESCOMPACTADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/arvore.h"
#include "../include/lista.h"
#include "../include/bitmap.h"
#include "../include/huffman.h"

#endif /* DESCOMPACTADOR_H_ */

/**
* @brief Realiza a leitura do arquivo compactado.
* @param fRComp Ponteiro para o arquivo compactado.
* @return Ponteiro para o bitmap no qual foi setado o conteúdo que estava no arquivo compactado.
*/
bitmap* leArquivoCompactado(FILE *fRComp);

void recriaTree(bitmap* bm, Tree* tree, int* i, int* folhas);

Tree* decodificaCabecalho(bitmap* bm);