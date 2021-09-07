#include "../include/arvore.h"

struct tree{
    char elem; 
    int peso;
    Tree* left;
    Tree* right;
};

char getElem(Tree* tree){
    return tree->elem;
}

int getPeso(Tree* tree){
    return tree->peso;
}

Tree* criaVazia(){
    return NULL;
}

Tree* criaTree(char elem, int peso, Tree* left, Tree* right){
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


//testar funcao removeFirst e funcao huffman
//fazer funcao de imprimir arvore

//le o arquivo , ve quantidade de elementos, fazer tabela
