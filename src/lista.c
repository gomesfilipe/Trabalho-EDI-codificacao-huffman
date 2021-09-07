#include "../include/lista.h"

typedef struct celula Celula;

struct celula{
    Tree* tree;
    Celula *next;
};


struct list{
    Celula* first;
    Celula* last;
    int tam;
};

List* criaLista(){
    List* list = (List*) malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->tam = 0;
    return list;
}

void liberaLista(List* list){
    Celula* i = list->first;
    Celula* aux;
    while(i != NULL){
        aux = i;
        i = i->next;
        free(aux);
    }
    free(list);
}

int listVazia(List* list){
    if(list->tam == 0){
        return 1;
    }
    
    return 0;
}

//pra funcionar a lista já precisa estar previamente ordenada
void insereOrdenado(List* list, Tree* tree){
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->tree = tree;
    //!printf("[%d]\n", list->tam);
    Celula* i;
    Celula* ant = NULL;
    
    // Casos:
    // 1) Inserindo numa lista vazia OK
    // 2) Inserindo primeiro da lista OK
    // 3) Inserindo último da lista OK
    // 4) Caso comum (Entre duas células) OK

    if(listVazia(list)){
        //!printf("chegou aq\n");
        nova->next = NULL;
        list->first = nova;
        list->last = nova;
        list->tam++;
        return;
    }
    //!printf("entrou for\n");
    for(i = list->first; ; i = i->next){
        //!printf("[%p]\n", i);
        if(i != NULL && getPeso(tree) <= getPeso(i->tree)){ // Se peso do elemento a ser inserido é menor que o do nó, insira.
            //!printf("entrou primeiro if\n");
        
            if(i == list->first){  // Elemento tem peso menor que todos os outros que já estão na lista.
                nova->next = list->first;
                list->first = nova;
                break;
            
            //} else if(i == NULL){ // Elemento tem peso maior que todos os outros que já estão na lista.
            //     nova->next = NULL;
            //     ant->next = nova;
            //     list->last = nova; 
            //     break;
                
            } else{ // Caso comum
                ant->next = nova;
                nova->next = i;
                break;
            }
        }
        else if(i == NULL){ // Elemento tem peso maior que todos os outros que já estão na lista.
                //!printf("chegou no ultimo else if\n");
                nova->next = NULL;
                ant->next = nova;
                list->last = nova; 
                break;
        }    

        ant = i;  
    }
    list->tam++;
}

Tree* removeFirst(List* list){
    if(!listVazia(list)){
        Celula* aux = list->first; //Sempre será retirado a primeira árvore da lista
        Tree* tree = aux->tree;
        list->first = list->first->next;
        if(list->tam == 1){ // Se for uma lista unitária, atualizar ponteiro last.
            list->last = NULL;
        }
        free(aux);
        list->tam--; // Decrementando o tamanho da lista.
        return tree;  
    }
    return NULL;
}

void imprimeLista(List* list){
    Celula* i;
    int peso;
    for(i = list->first; i != NULL; i = i->next){
        peso = getPeso(i->tree);
        printf("(%d) ", peso);
    }
    printf("\n");
}

Tree* huffman(List* list){
    Tree* tree1;
    Tree* tree2;
    Tree* tree3;
    int peso1, peso2;
    while(list->tam != 1){
        tree1 = removeFirst(list);
        tree2 = removeFirst(list);
        peso1 = getPeso(tree1);
        peso2 = getPeso(tree2);
     
        tree3 = criaTree('a', peso1 + peso2, tree1, tree2);
        insereOrdenado(list, tree3);
    }

    return tree3;
}
