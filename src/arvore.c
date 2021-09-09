#include "../include/arvore.h"

#define TAM 256

struct tree{
    unsigned char elem; 
    int peso;
    Tree* left;
    Tree* right;
};

unsigned char getElem(Tree* tree){
    return tree->elem;
}

int getPeso(Tree* tree){
    return tree->peso;
}

Tree* getLeft(Tree* tree){
    return tree->left;
}

Tree* getRight(Tree* tree){
    return tree->right;
}

Tree* criaVazia(){
    return NULL;
}

Tree* criaTree(unsigned char elem, int peso, Tree* left, Tree* right){
    Tree* tree = (Tree*) malloc(sizeof(Tree));
    tree->elem =  elem;
    tree->peso = peso;
    tree->left = left;
    tree->right = right;
    return tree;
}

Tree* liberaTree(Tree* tree){
    if(tree != NULL){
        liberaTree(tree->left);
        liberaTree(tree->right);
        free(tree);
    }
    return NULL;
}

int ehFolha(Tree* tree){
    return tree->left == NULL && tree->right == NULL;
}

int ehVazia(Tree* tree){
    return tree == NULL;
}

int maior(int a, int b){
    return a > b ? a : b;
}

int altura(Tree* tree){
    if(ehVazia(tree)){
        return -1;
    }

    return 1 + maior(altura(tree->left), altura(tree->right));
}

void imprimeTree(Tree* tree){
    printf("<");
    if(!ehVazia(tree)){
        printf("%d", getPeso(tree));
        if(ehFolha(tree)){
            printf("[%c]", getElem(tree));
        }
        imprimeTree(tree->left);
        imprimeTree(tree->right);
    }
    printf(">");
}

/** TO DO
 * Como codificar a árvore?
 * codificar o .txt em bits usando o bitmap
 * criar tads descompactor.c e compactador.c
 * escrever arvore serialzada codificada no arquivo (????)
**/ 
