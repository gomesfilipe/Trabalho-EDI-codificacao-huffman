#include "compactador.h"
#include <math.h>

// 0 0 1A 1B 0 1C 1D
//A = 65  = "01000001"

//100000000

bitmap* insereQtdFolhas(Tree* tree, bitmap* bm){
    unsigned char binFolhas[8];
    int folhas = qtdFolhas(tree);
    folhas--;
    unsigned char folhasAux = (unsigned char) folhas;
    char c;
    converteDecimalParaBinario(folhasAux, binFolhas);
    printf("%s ", binFolhas);
    
    for(int i = 0; i < 8 ; i++){
        bitmapAppendLeastSignificantBit(bm, binFolhas[i]); //Bits das folhas 
        //c = bitmapGetContents(bm)[i];
        //printf("[%c] ", c);
    }
    //unsigned char* bitmapGetContents(bitmap* bm)
    return bm;
}


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

        }
    }
}

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
    int maxSize = pow(2, h + 1) - 1 + 8 * pow(2, h) + 9;
    //[2^(h+1) - 1] é o máxima número de nós da árvore
    // [8 * 2^h] é o máximo espaço em bits ocupado por cada caractere em um nó folha.
    //+ 9 é devido ao número de folhas que colocamos no início do bitmap a fim de ter uma condição de parada
    bitmap* bm = bitmapInit(maxSize);
    return bm;
}

//printa o numero de folhas  //printa o cabeçalho

// void codificaTexto(FILE* f, char** tabela, bitmap* bm){
//     char* text = bitmapGetContents(bm);
//     // passando texto pro bitmap
//     for(int i = 0; !feof(f); i++){
//         fscanf(f, "%c", text[i]);
//     }
//     int maxSize = bitmapGetMaxSize(bm);
//     bitmap* aux = bitmapInit(maxSize); // bitmap que colocará codificado
    
//     // ler o outro bitmap e ir codificando usando a tabela


//     //Abrir o arquivo modo escrita
//     //pegar o ponteiro de conxtests e jogar ele no arquivo

// }

//O cabeçalho é impresso junto a um possível lixo de memória que deveser tratado posteriormente 
//na decodificação
void imprimeCabecalho(FILE* f, bitmap* bm){
    char* cabecalho = bitmapGetContents(bm);
    int tam = bitmapGetLength(bm);
    tam = (tam + 7) / 8; //+ 1; // passando pra bytes, tratar lixo.
    //int restante = 8 - tam%8 ;

    for(int i = 0; i < tam ; i++){
        //so printar se for menor  que 255 
        //se for menor que 32, soma 32
        fprintf(f, "%c" , cabecalho[i]);
    }
    
}


//11100000 00000111 11111110 00000001 11111110 00000011 11111111 1|0000000