#include "../include/arvore.h"

#define TAM 256

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

char** criaTabelaCodificacao(Tree* tree){
    int h = altura(tree); // Tamanho máximo de um caminho para folha.
    //Criando a tabela 
    char** tabela = (char**) malloc(sizeof(char*) * TAM); //[TAM][h]; 
    for(int i = 0; i < TAM; i++){
        tabela[i] = (char*) malloc(sizeof(char) * (h + 1)); //! wtf? misterio.
        strcpy(tabela[i], "");
        //printf("[%s] tam: [%ld] | ", tabela[i], strlen(tabela[i]));
        //tabela[i] = "";
    }
    return tabela;
}

void liberaTabelaCodificacao(char** tabela){
    for(int i= 0; i < TAM; i++){
        free(tabela[i]);
    }
    free(tabela);
}

char** inicializaTabelaCodificacao(Tree* tree, char** tabela, char* caminho){ 
    char elem;
    if(tree != NULL){
        if(ehFolha(tree)){
            elem = getElem(tree);
            //printf("(%c)", elem);
            strcpy(tabela[elem], caminho);
            return tabela;
        }
        
        char caminhoLeft[strlen(caminho) + 1];
        char caminhoRight[strlen(caminho) + 1];

        strcpy(caminhoLeft, caminho);
        strcpy(caminhoRight, caminho);

        strcat(caminhoLeft, "0");
        strcat(caminhoRight, "1");
        
        inicializaTabelaCodificacao(tree->left, tabela, caminhoLeft);
        inicializaTabelaCodificacao(tree->right, tabela, caminhoRight);
    }
    return tabela;
}

void imprimeTabelaCodificacao(char** tabela){
    for(int i = 0; i < TAM; i++){
        if(strcmp(tabela[i], "") != 0){
            //printf("\n[%s][%c]", tabela[i], i);
            printf("\n %c [%s]",  i, tabela[i]);
        }
    }
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


//perguntar para patricia sobre os acentos, pq esta ficando como se fosse dois carcteres em branco