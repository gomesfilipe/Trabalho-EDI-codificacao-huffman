#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bitmap.h"
#include "../include/arvore.h"
#include "../include/lista.h"

int main(){
    Tree* a = criaTree('x', 2,  NULL, NULL);
    Tree* b = criaTree('x', 17, NULL, NULL);
    Tree* c = criaTree('x', 4, NULL, NULL);
    Tree* d = criaTree('x', 7,  NULL, NULL);
    Tree* e = criaTree('x', 0,  NULL, NULL);
    Tree* f = criaTree('x', 14, NULL, NULL);
    Tree* g = criaTree('x', 2,  NULL, NULL);
    Tree* h = criaTree('x', 19, NULL, NULL);
    Tree* i = criaTree('x', 20, NULL, NULL);
    Tree* j = criaTree('x', 23, NULL, NULL);
    Tree* k = criaTree('x', 13, NULL, NULL);

    List* list = criaLista();
    insereOrdenado(list, a);
    insereOrdenado(list, b);
    insereOrdenado(list, c);
    insereOrdenado(list, d);
    insereOrdenado(list, e);
    insereOrdenado(list, f);
    insereOrdenado(list, g);
    insereOrdenado(list, h);
    insereOrdenado(list, i);
    insereOrdenado(list, j);
    insereOrdenado(list, k);

    imprimeLista(list);

    liberaLista(list);
    liberaTree(a);
    liberaTree(b);
    liberaTree(c);
    liberaTree(d);
    liberaTree(e);
    liberaTree(f);
    liberaTree(g);
    liberaTree(h);
    liberaTree(i);
    liberaTree(j);
    liberaTree(k);
    return 0;
}
