#ifndef ARVORE_H_
#define ARVORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree Tree;

/**
 * @brief Captura o elemento do nó raiz de uma árvore.
 * @param tree Árvore que terá seu elemento capturado.
 * @return Elemento do nó raíz da árvore.
 **/
char getElem(Tree* tree);

/**
 * @brief Captura o peso do nó raiz de uma árvore.
 * @param tree Árvore que terá seu peso capturado.
 * @return Peso do nó raíz da árvore.
 **/
int getPeso(Tree* tree);

/**
 * @brief Cria uma árvore vazia.
 * @return Árvore vazia.
 **/
Tree* criaVazia();

/**
 * @brief Cria uma ávore com seu conteúdo e filhos inicializados.
 * @param elem Elemento que estará no nó raiz da árvore criada.
 * @param left Ponteiro para subárvore esquerda.
 * @param right Ponteiro para subárvore direita.
 * @return Árvore criada e inicializada.
 **/
Tree* criaTree(char elem, int peso, Tree* left, Tree* right);

/**
 * @brief Libera uma árvore da memória. Essa função apenas desfaz o encadeamento da árvore.
 * @param tree Árvore que será liberada.
 * @return Ponteiro NULL para a árvore que será liberada.
 **/
Tree* liberaTree(Tree* tree);

/**
 * @brief Função booleana, que diz se uma árvore é folha ou não.
 * @param tree Árvore que será verificada.
 * @return 1, caso seja folha e 0, caso não seja folha.
 **/
int ehFolha(Tree* tree);

/**
 * @brief Função booleana, que diz se uma árvore é vazia ou não.
 * @param tree Árvore que será verificada.
 * @return 1, caso seja vazia e 0, caso não seja vazia.
 **/
int ehVazia(Tree* tree);

/**
 * @brief Calcula a altura de uma árvore.
 * @param tree Árvore que terá a sua altura calculada.
 * @return Altura da árvore.
 **/
int altura(Tree* tree);

int maior(int a, int b);

void imprimeTree(Tree* tree);

#endif /* ARVORE_H_ */
