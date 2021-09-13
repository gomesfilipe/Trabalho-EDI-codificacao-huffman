#include "descompactador.h"
#include "compactador.h" //!TIRAR DEPOIS
#include <math.h>

#define TAM 500

bitmap* leArquivoCompactado(FILE *fRComp){
    int tam = TAM;
    char* str = (char*) malloc (tam * sizeof (char));
    
    for(int i = 0 ; !feof(fRComp) ; i++){
        fscanf(fRComp, "%c" , &str[i]);
        str[i + 1] = '\0';
        if(i == tam - 2){ //Se chegou no final da string e o arquivo ainda não foi lido por completo, é preciso aumentar o tamanho da string
            tam += TAM;
            str = (char*) realloc(str, tam * sizeof(char));
        }
    }
    
    bitmap* bm = bitmapInit(8 * strlen(str) + 8); // Multiplicamos por 8 para converter para bits
    // char* contents = bitmapGetContents(bm);
    // strcpy(contents, str);
    // FILE* f = fopen("teste.txt", "w");
    // if(f == NULL){
    //     printf("erro aberturs\n");
    //     exit(1);
    // }
    bm = bitmapSetContents(bm, str);
    //imprimeBitmapArquivo(f, bm);
    //bitmapLibera(bm);
    free(str);
    //fclose(f);
    return bm;
}

/**
 * pré condição: tree deve ser uma árvore inicializada.
 * 
 * i representa i-ésima posição do bitmap (conteúdo de i) (ele é ponteiro para 
 * que seu valor atual seja acessado em qualquer nível de recursão). Além disso,
 * i deve ser inicializado com o valor 8 para começar a varredura do bitmap a 
 * partir do oitavo bit.
 * 
 * folhas representa a quantidade atual de folhas lidas (conteúdo de folhas)
 * (ele é ponteiro para que seu valor atual seja acessado em qualquer nível de recursão)
 * 
 * 
 **/
void recriaTree(bitmap* bm, Tree* tree, int* i, int* folhas){
    char bit;
    int posAscii = 0;
    static int lixo = 0; //! RESOLVER DEPOIS
    int totalFolhas = bitmapGetContents(bm)[0] + 1; //Somamos 1 pois na hora de codificar tínhamos 
    //subtraído 1 a fim de deixar o número de folhas com 8 bits 
    if(*folhas == totalFolhas){
        return;
    
    } else{
        bit = bitmapGetBit(bm, *i);
        if(bit == 0){ // não é folha, crie os próximos dois nós e chame recursivamente.
            Tree* left = criaTree(0, -1, NULL, NULL);
            Tree* right = criaTree(0, -1, NULL, NULL);
            tree = setLeft(tree, left);
            tree = setRight(tree, right);
            (*i)++;
            recriaTree(bm, left, i, folhas);
            recriaTree(bm, right, i, folhas);
        } else{ // é folha, leia os proximos 8 bits e coloque no campo 'elem'.
            *i = *i + 1;
            for(int j = 0; j <= 7 ; j++, (*i)++){
                bit = bitmapGetBit(bm, *i);
                printf("bit [%d]\n", bit);
                if(bit == 1){
                    //posAscii += pow(2, 7 - j); 
                    posAscii += 1 << (7 - j);
                }
            }
            tree = setElem(tree, posAscii);
            printf("ASCII [%d] [%c]\n", posAscii, posAscii);
            (*folhas)++;
        }
    }
}

Tree* decodificaCabecalho(bitmap* bm){
    int i = 8;
    int folhas = 0;
    Tree* tree = criaTree(0, -1, NULL, NULL);

    recriaTree(bm, tree, &i, &folhas);

    return tree;
}

// 00000101 0 0 1 01101101 1 01100010 0 0 1 01110011 1 01100101 0 1 00100000 1 01101111