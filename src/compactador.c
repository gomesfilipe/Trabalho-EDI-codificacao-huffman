#include "compactador.h"
#include <math.h>

// 0 0 1A 1B 0 1C 1D
//A = 65  = "01000001"

void codificaTree(Tree* tree, bitmap* bm){
    unsigned char bin[8];
    unsigned char elemento;
    
    if(ehVazia(tree) == 0){
        if(ehFolha(tree) == 0){
         
            bitmapAppendLeastSignificantBit(bm, '0');
            printf("0 "); //!
            codificaTree( getLeft(tree)  , bm);
            codificaTree( getRight(tree) , bm);

        }
        else{
            bitmapAppendLeastSignificantBit(bm, '1'); //Nó folha
            printf("1 "); //!
            elemento = getElem(tree);
            converteDecimalParaBinario(elemento, bin);
            printf("%s ", bin); //!
            for(int i = 0; i <= 7 ; i++){
                bitmapAppendLeastSignificantBit(bm, bin[i]); //Bits do elemento 
            }


            //escreve 1
            //escreve elemento da folha
        }
    }
}

// espaço bitmap = espaço nós + espaço caracteres
//               [2^(h+1) -1] + 8 * 2^h



/**
    QtdAloc = numCaracteres + numeroNosMax  = 8 * 2^h  + 2^(h+1)-1
    numeroNosMax = 2^(h+1) - 1
    numCaracteres = 2^h  


**/  

//A = "01000001
void converteDecimalParaBinario(unsigned char elem, unsigned char* bin){
    int num = elem ;
    for(int i = 0; i <= 7 ; i++){
        if(num % 2 == 0){
            bin[7 - i] = '0';
        }
        else{
            bin[7 - i] = '1';
        }
        num /= 2;
    }
}

bitmap* criaBitMapCompac(Tree* tree){
    int h = altura(tree);
    int maxSize = pow(2, h + 1) - 1 + 8 * pow(2, h);
    //[2^(h+1) - 1] é o máxima número de nós da árvore
    // [8 * 2^h] é o máximo espaço em bits ocupado por cada caractere em um nó folha.
    bitmap* bm = bitmapInit(maxSize);
    return bm;
}
