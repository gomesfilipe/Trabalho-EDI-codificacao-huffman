#include "../include/huffman.h"

#define TAM 256

Tree* huffman(List* list){
    Tree* tree1;
    Tree* tree2;
    Tree* tree3;
    int peso1, peso2;
    
    if(getTam(list) == 1){ // Se a lista só possui uma única árvore, coloca a folha à esquerda do nó raiz.
        tree2 = removeFirst(list);
        peso2 = getPeso(tree2);
        tree3 = criaTree(0, peso2, tree2, NULL);
        
    } else{
        while(getTam(list) != 1){
            tree1 = removeFirst(list);
            tree2 = removeFirst(list);
            peso1 = getPeso(tree1);
            peso2 = getPeso(tree2);
        
            tree3 = criaTree(0, peso1 + peso2, tree1, tree2); // Elem é 0, pois é o NULL na tabela ascii. Tree3 tem conteúdo NULL pois seu nó raíz não é uma folha.
            insereOrdenado(list, tree3);
        }
    }
    return tree3;
}

int* calculaPesos(FILE *f){
    int* pesos = (int*) calloc(TAM, sizeof(int)); //Declaração do vetor de caracteres
    unsigned char caractere;
    while(fscanf(f, "%c", &caractere) == 1){
        pesos[caractere]++;
    }
    return pesos;
}

List* geraListaTree(int* pesos){
    List* list = criaLista();
    for(int i = 0; i < TAM; i++){
        if(pesos[i] > 0){
            insereOrdenado(list, criaTree(i, pesos[i], NULL, NULL));
        }
    }
    return list;
}

Tree* geraArvoreCodificacao(int* pesos){
    List* list = geraListaTree(pesos);
    Tree* tree = huffman(list);
    liberaLista(list);
    return tree;
}

unsigned char** criaTabelaCodificacao(Tree* tree){
    int h = altura(tree); // Tamanho máximo de um caminho para folha.
    //Criando a tabela 
    unsigned char** tabela = (unsigned char**) malloc(sizeof(unsigned char*) * TAM);
    for(int i = 0; i < TAM; i++){
        tabela[i] = (unsigned char*) malloc(sizeof(unsigned char) * (h + 1)); // 1 a mais por causa do \0
        strcpy(tabela[i], "");
    }
    return tabela;
}

void liberaTabelaCodificacao(unsigned char** tabela){
    for(int i= 0; i < TAM; i++){
        free(tabela[i]);
    }
    free(tabela);
}

unsigned char** inicializaTabelaCodificacao(Tree* tree, unsigned char** tabela, unsigned char* caminho){ 
    unsigned char elem;
    if(tree != NULL){
        if(ehFolha(tree)){
            elem = getElem(tree);
            strcpy(tabela[elem], caminho);
            return tabela;
        }
        
        unsigned char caminhoLeft[strlen(caminho) + 1];
        unsigned char caminhoRight[strlen(caminho) + 1];

        strcpy(caminhoLeft, caminho);
        strcpy(caminhoRight, caminho);

        strcat(caminhoLeft, "0");
        strcat(caminhoRight, "1");
        
        inicializaTabelaCodificacao(getLeft(tree), tabela, caminhoLeft);
        inicializaTabelaCodificacao(getRight(tree), tabela, caminhoRight);
    }
    return tabela;
}

void imprimeTabelaCodificacao(unsigned char** tabela){
    for(int i = 0; i < TAM; i++){
        if(strcmp(tabela[i], "") != 0){
            printf("\n %c [%s]",  i, tabela[i]);
        }
    }
}

int calculaBits(unsigned char** tabela, int* pesos){
    int bits = 0;
    for(int i = 0; i < TAM; i++){
        if(pesos[i] != 0){
            bits += pesos[i] * strlen(tabela[i]);
        }
    }
    return bits;
}
