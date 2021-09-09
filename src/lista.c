#include "../include/lista.h"

#define TAM 256 //Número de caracteres da tabela ascii

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


int getTam(List* list){
    return list->tam;
}


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
    Celula* i;
    Celula* ant = NULL;
    
    if(listVazia(list)){
        nova->next = NULL;
        list->first = nova;
        list->last = nova;
        list->tam++;
        return;
    }

    for(i = list->first; ; i = i->next){
        if(i != NULL && getPeso(tree) <= getPeso(i->tree)){ // Se peso do elemento a ser inserido é menor que o do nó, insira.

            if(i == list->first){  // Elemento tem peso menor que todos os outros que já estão na lista.
                nova->next = list->first;
                list->first = nova;
                break;
            
        
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
        printf("%d ", peso);
    }
    printf("\n");
}
