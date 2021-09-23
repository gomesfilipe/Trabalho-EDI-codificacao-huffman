#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree Tree;

/**
 * @brief Captura o elemento do nó raiz de uma árvore.
 * @param tree Árvore que terá seu elemento capturado.
 * @return Elemento do nó raíz da árvore.
 **/
unsigned char getElem(Tree* tree);

/**
 * @brief Captura o peso do nó raiz de uma árvore.
 * @param tree Árvore que terá seu peso capturado.
 * @return Peso do nó raíz da árvore.
 **/
int getPeso(Tree* tree);

/**
 * @brief Captura o ponteiro para a subárvore esquerda do nó raiz de uma árvore.
 * @param tree Árvore que terá seu ponteiro para subárvore esquerda capturado.
 * @return Ponteiro para subárvore esquerda do nó raíz da árvore.
 **/
Tree* getLeft(Tree* tree);

/**
 * @brief Captura o ponteiro para a subárvore direita do nó raiz de uma árvore.
 * @param tree Árvore que terá seu ponteiro para subárvore direita capturado.
 * @return Ponteiro para subárvore direita do nó raíz da árvore.
 **/
Tree* getRight(Tree* tree);

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
Tree* criaTree(unsigned char elem, int peso, Tree* left, Tree* right);

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

/**
 * @brief Retorna o maior dentre dois inteiros.
 * @param a Inteiro a ser comparado.
 * @param b Inteiro a ser comparado.
 * @return Maior inteiro dentre os dois.
 **/
int maior(int a, int b);

/**
 * @brief Imprime uma árvore de modo serializado, com a notação de símbolos '<' e '>'.
 * @param tree Árvore que será impressa.
 **/
void imprimeTree(Tree* tree);

/**
 * @brief Calcula a quantidade de folhas de uma árvore.
 * @param tree Árvore que terá suas folhas calculadas
 * @return Número de folhas da árvore.
 **/
int qtdFolhas(Tree* tree);

/**
 * @brief Insere em uma árvore uma sub-árvore esquerda.
 * @param tree Árvore que terá seu ponteiro para sub-árvore esquerda atualizado.
 * @param left Sub-árvore que será inserida na árvore.
 * @return Árvore com sub-árvore esquerda encadeada.
 **/
Tree* setLeft(Tree* tree, Tree* left);

/**
 * @brief Insere em uma árvore uma sub-árvore direita.
 * @param tree Árvore que terá seu ponteiro para sub-árvore direita atualizado.
 * @param left Sub-árvore que será inserida na árvore.
 * @return Árvore com sub-árvore direita encadeada.
 **/
Tree* setRight(Tree* tree, Tree* right);

/**
 * @brief Atualiza o campo elem do nó raíz de uma árvore.
 * @param tree Árvore que terá o campo elem de seu nó raiz atualizado.
 * @param elem Caractere que será inserido no nó raiz da árvore.
 * @return Árvore atualizada.
 **/
Tree* setElem(Tree* tree, unsigned char elem);

#endif /* TREE_H_ */
