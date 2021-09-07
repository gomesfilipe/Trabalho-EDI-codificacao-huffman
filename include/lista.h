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

void imprimeLista(List* list);

Tree* huffman(List* list);

#endif /* LISTA_H_ */
