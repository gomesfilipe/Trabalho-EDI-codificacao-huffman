#ifndef LISTA_H_
#define LISTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/arvore.h"

typedef struct list List;

/**
 * @brief Cria uma lista vazia.
 * @return Lista vazia.
 **/
List* criaLista();

/**
 * @brief Libera uma lista da memória. Obs: Não libera o conteúdo das células.
 * @param list Lista que será liberada.
 **/
void liberaLista(List* list);

/**
 * @brief Verifica se uma lista é vazia ou não.
 * @param list Lista que será analisada.
 * @return 1, caso seja vazia e 0, caso não seja vazia.
 **/
int listVazia(List* list);

/**
 * @brief Insere um elemento numa posição que a lista continue em ordem crescente de acordo
 * com o peso do nó da árvore inserida.
 * @param list Lista que terá um elemento inserido.
 * @param tree Árvore que será inserida. 
 **/
void insereOrdenado(List* list, Tree* tree);

/**
 * @brief Remove o primeiro elemento de uma lists.
 * @param list Lista que terá seu primeiro elemento removido.
 * @return Conteúdo da célula removida da lista. Retorna NULL caso a lista seja vazia.
 **/
Tree* removeFirst(List* list);

/**
 * @brief Imprime uma lista de árvores
 * @param list Lista que será impressa.
 **/
void imprimeLista(List* list);


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
 * @param f Ponteiro para o arquivo que será lido.
 * @return Árvore de codificação huffman.
 **/
Tree* geraArvoreCodificacao(FILE *f);

#endif /* LISTA_H_ */
