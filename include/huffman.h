#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tree.h"
#include "../include/list.h"
#include "../include/bitmap.h"

/**
 * @brief Implementa o algoritmo de huffman. Retira as duas primeiras árvores de uma lista e gera uma nova árvore até 
 * restar apenas uma árvore na lista. 
 * @param list Lista de árvores que será usada na implementação do algoritmo de huffman.
 * @return Árvore final gerada pelo algoritmo de huffman.
 **/
Tree* huffman(List* list);

/**
 * @brief Calcula a quantidade de vezes de cada caractere aparece em um arquivo. Essa quantidade chamamos de peso.
 * @param f Ponteiro que aponta para o arquivo que terá o peso de seus caracteres calculados
 * @return Vetor de inteiros. O conteúdo é o peso de cada caractere.
 **/
int* calculaPesos(FILE *f);

/**
 * @brief Gera uma lista de árvores.
 * @param pesos Vetor com o peso de cada caracter do arquivo.
 * @return Lista de árvores.
 **/
List* geraListaTree(int* pesos);

/**
 * @brief Gera a árvore de codificação huffman lendo um arquivo txt.
 * @param pesos Ponteiro para vetor de pesos dos caracteres que aparecem no arquivo lido.
 * @return Árvore de codificação huffman.
 **/
Tree* geraArvoreCodificacao(int* pesos);

/**
 * @brief Cria a tabela de codificação de huffman a partir de uma árvore de huffman e a inicializa com strings vazias.
 * @param tree Árvore de huffman.
 * @return Ponteiro para o vetor de strings que representa a tabela.
 **/
unsigned char** criaTabelaCodificacao(Tree* tree);

/**
 * @brief Inicializa a tabela de codificação de huffman a partir de uma árvore de huffman.
 * O caminho de um elemento x está na posição tabela[x]. 
 * @param tree Árvore de huffman.
 * @param tabela Ponteiro para a tabela (já deve estar criada).
 * @param caminho String que representa o caminho parcial de um nó da árvore.
 * @return Ponteiro para o vetor de strings que representa a tabela.
 **/
unsigned char** inicializaTabelaCodificacao(Tree* tree, unsigned char** tabela, unsigned char* caminho);

/**
 * @brief Libera da memória uma tabela de codificação de huffman.
 * @param tabela Tabela que será liberada.
 **/
void liberaTabelaCodificacao(unsigned char** tabela);

/**
 * @brief Imprime uma tabela de codificação de huffman.
 * @param tabela Tabela que será impressa.
 **/
void imprimeTabelaCodificacao(unsigned char** tabela);

/**
 * @brief Calcula a quantidade de bits da codificação de um texto em bits.
 * @param tabela Tabela de codificação dos caracteres.
 * @param pesos Vetor de pesos dos caracteres.
 * @return Quantidade de bits ocupada pela codificação do texto.
 **/
int calculaBits(unsigned char** tabela, int* pesos);

#endif /* HUFFMAN_H_ */
