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

int qtdFolhas(Tree* tree){
    if(!ehVazia(tree)){
        if(ehFolha(tree)){
            return 1;
        } else{
            return qtdFolhas(tree->left) + qtdFolhas(tree->right);
        }
    }
    return 0;
}

/** TO DO
 * Como codificar a árvore? Feito  11  011    110  11
 * QTD FOLHAS NO CABEÇALHO (CONDIÇÃO DE PARADA) ******** 
 * setar o texto codificado no bitmap e depois printar no .txt *********
 * Criar um arquivo, imprimir o cabeçalho nele e codificar o resto com
 * codificar o .txt em bits usando o bitmap
 * escrever arvore serialzada codificada no arquivo (????)
 * ver problema dos caracteres ascii acima de 127 
**/ 

// 1010101011010
// 32 bits
// unsigned int 2^32 - 1        32 bits 


/*

//Abrir o arquio modo escrita

//escrever o cabeçalho


*/  // 1 bit -> leu 8 bits? leia o proximo bit. 
// se for 1, continua a ler, se for 0, para. (le o proximo bit pra ver se é folha ou nao)
// 00000101 0 0 1 01101101 b 1 01100010 b 0 0 1 01110011 b 1 01100101 b 0 1 00100000 b 1 01101111
// se b == 1, acabou. pare de ler. se b == 0, continua. leia o proximo bit paa ver se é no folha ou nao
//  '\a'
// 00000000   00000111
// 000 111