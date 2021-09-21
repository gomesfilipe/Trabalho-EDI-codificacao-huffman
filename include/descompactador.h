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
**/
bitmap* leArquivoCompactado(FILE *fRComp);

/**
 * @brief Lê o cabeçalho do arquivo .comp e gera a árvore de codificação de huffman.
 * @param bm Bitmap que contém o cabeçalho a ser lido.
 * @param tree Árvore que será gerada após decodificação do cabeçalho.
 * Obs: Deve estar inicializada.
 * @param i Ponteiro para i-ésima posição do bitmap. É ponteiro para 
 * que seu valor atual seja acessado em qualquer nível de recursão. 
 * @param folhas Ponteiro para o contador de folhas que já foram lidas no cabeçalho.
 * É ponteiro para que seu valor atual seja acessado em qualquer nível de recursão.
 * @param lixo Ponteiro para lixo do cabeçalho. Ao longo da função, vai calculando
 * o tamanho do lixo, ou seja, a quantidade de bits que devem ser ignorados no bitmap após 
 * decodificar o cabeçalho.
 **/
void recriaTree(bitmap* bm, Tree* tree, int* i, int* folhas, int* lixo);

/**
 * @brief Decodifica o trecho de texto compactado de um bitmap.
 * @param bm Bitmap que contém a codificação do arquivo .comp.
 * @param i Ponteiro para i-ésima posição do bitmap. É ponteiro para 
 * que seu valor atual seja acessado em qualquer nível de recursão. 
 * @param tree Árvore de codificação de huffman.
 * @param lixoTexto Tamanho do lixo em bits do trecho de texto compactado. 
 * Em outras palavras, é a quantidade de bits que devem ser ignorados no final do bitmap.
 **/
void decodificaTexto(bitmap* bm, int* i, Tree* tree, int lixoTexto);

/**
 * @brief Decodifica um bitmap que contém a codificação do arquivo .comp.
 * @param bm Bitmap que contém a codificação do arquivo .comp.
 **/
void decodifica(bitmap* bm);

/**
 * @brief Pega a parte do cabeçalho que representa o tamanho do lixo do texto e o calcula.
 * @param bm Bitmap que contém a codificação do arquivo.
 * @return Tamanho do lixo do texto.
 **/
int getLixoTexto(bitmap* bm);