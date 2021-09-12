#ifndef COMPACTADOR_H_
#define COMPACTADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/arvore.h"
#include "../include/lista.h"
#include "../include/bitmap.h"
#include "../include/huffman.h"

/**
 * @brief Codifica uma árvore de huffman e a escreve em um bitmap.
 * @param tree Árvore que será codificada.
 * @param bm Bitmap que terá a codificação da árvore setada nele.
 **/
void codificaTree(Tree* tree, bitmap* bm);

/**
 * @brief Pega a posição de um determinado char na tabela ascii e cria uma string que representa
 * o número binário dessa posição.
 * @param elem Caractere da tabela ascii.
 * @param bin String que representará o binário da posição de elem na tabela ascii.
 **/
void converteDecimalParaBinario(unsigned char elem, unsigned char* bin);

/**
 * @brief Inicializa um bitmap com tamanho suficiente para armazenar a codificação de uma árvore cheia.
 * @param tree Árvore que será baseada para calcular o tamanho do bitmap
 * @return Retorna o bitmap criado 
 **/
bitmap* criaBitMapCompac(Tree* tree);

/**
 * @brief Imprime o cabeçalho no arquivo. O cabeçalho é árvore codificada.
 * @param f Ponteiro para o arquivo no qual será escrito a árvore codificada
 **/
void imprimeCabecalho(FILE* f, bitmap* bm);

/**
 * @brief Insere a quantidade de folhas de um árvore em um bitmap.
 * @param tree Árvore que terá sua quantidade de folhas setada no bitmap.
 * @return bitmap que possui a quantidade de folhas setada no campo contents.
 **/
bitmap* insereQtdFolhas(Tree* tree, bitmap* bm);

#endif /* COMPACTADOR_H_ */
