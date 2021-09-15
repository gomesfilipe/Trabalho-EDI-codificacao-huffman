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

// 01001000|00101101|111 00000
// |00000101|00101101|10110110|00100010|11100111|01100101|01001000|00101101|11100000|
// i: [67]  folhas: [6]  lixo:[59]
//lixo verdadeiro é 5
//lixo é pra ser 5
//folhas é pra ser 6
//i é pra ser 72

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
void recriaTree(bitmap* bm, Tree* tree, int* i, int* folhas, int* lixo){
    char bit;
    int posAscii = 0;
    //static int* lixo = 0;
    int totalFolhas = bitmapGetContents(bm)[0] + 1; //Somamos 1 pois na hora de codificar tínhamos 
    //subtraído 1 a fim de deixar o número de folhas com 8 bits 
    //printf("total de folhas [%d]\n", totalFolhas);
   
    bit = bitmapGetBit(bm, *i);
    (*lixo)++;//incrementar aqui 
    (*i)++;
    if(bit == 0){ // não é folha, crie os próximos dois nós e chame recursivamente.
        Tree* left = criaTree(0, -1, NULL, NULL);
        tree = setLeft(tree, left);
        recriaTree(bm, left, i, folhas, lixo);
        if((*folhas) < totalFolhas){
            Tree* right = criaTree(0, -1, NULL, NULL);
            tree = setRight(tree, right);
            recriaTree(bm, right, i, folhas, lixo);           
        }

    } else{ // é folha, leia os proximos 8 bits e coloque no campo 'elem'.
        //*i = *i + 1;
        for(int j = 0; j <= 7 ; j++, (*i)++){
            bit = bitmapGetBit(bm, *i);
            (*lixo)++;//incrementar aqui 
            if(bit == 1){
                //posAscii += pow(2, 7 - j); 
                posAscii += 1 << (7 - j);
            }
        }
        tree = setElem(tree, posAscii);
        (*folhas)++;
        if((*folhas) == totalFolhas){
            (*lixo) = (*lixo) % 8; //quantidade que precisa retirar é 8-lixo
            if((*lixo) != 0){ // se é múltiplo de 8, não tem lixo
                (*lixo) = 8 - (*lixo);
            }
            (*i) += (*lixo);
            return;
        }    
    }
}

// Tree* decodificaCabecalho(bitmap* bm){
//     int i = 8;
//     int folhas = 0;
//     int lixo = 0;
//     Tree* tree = criaTree(0, -1, NULL, NULL);

//     recriaTree(bm, tree, &i, &folhas, &lixo);

//     printf("i: [%d]  ", i);
//     printf("folhas: [%d]  ", folhas);
//     printf("lixo:[%d]\n", lixo);

//     return tree;
// }

void decodifica(bitmap* bm){
    int i = 8;
    int folhas = 0;
    int lixo = 0;
    Tree* tree = criaTree(0, -1, NULL, NULL);

    recriaTree(bm, tree, &i, &folhas, &lixo);

    printf("i: [%d]  ", i);
    printf("folhas: [%d]  ", folhas);
    printf("lixo:[%d]\n", lixo);

    decodificaTexto( bm, &i,  tree);
    liberaTree(tree);
    //return tree;
}

void decodificaTexto(bitmap* bm, int* i, Tree* tree){
    Tree* aux = tree;
    FILE* fWrite = fopen("decodificado.txt", "w");

    for(*i; *i < bitmapGetLength(bm); (*i)++){
        
        if(bitmapGetBit(bm, *i) == 0){
            aux = getLeft(aux); // pegando ponteiro pra árvore filha esquerda
        } else{
            aux = getRight(aux); // pegando ponteiro pra árvore filha direita
        }
        if(ehFolha(aux)){
            fprintf(fWrite, "%c", getElem(aux));
            aux = tree; // resetando pro nó raiz    
        }
    }
    fclose(fWrite);
}

//101

// TEXTO CODIFICADO
// 01111001
// 10101100
// 10010111
// 00111100
// 01111000




