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

//O peso do arquivo já vem em bits
bitmap* codificaTexto(FILE* f, unsigned char** tabela, int pesoArquivoBit, int pesoArquivoByte){
    bitmap* bm = bitmapInit(pesoArquivoBit); 
    printf("peso byte [%d]\n", pesoArquivoByte);
    unsigned char aux;
    for(int i = 0; i < pesoArquivoByte; i++){
        //fscanf(f, "%c", &aux);
        fscanf(f, "%c", &aux );
        //printf("aux [%c] ", aux);
        //printf("[");
        int tam = strlen(tabela[aux]) ;
        //printf("tam [%d] ", tam);
        for(int j = 0; j < strlen(tabela[aux]); j++){
            bitmapAppendLeastSignificantBit(bm, tabela[aux][j]);
            printf("%c", tabela[aux][j]);
        }
        //printf("] ");
    }
    return bm;
}


//O cabeçalho é impresso junto a um possível lixo de memória que deveser tratado posteriormente 
//na decodificação
void imprimeBitmapArquivo(FILE* f, bitmap* bm){
    char* cabecalho = bitmapGetContents(bm);
    int tam = bitmapGetLength(bm);
    tam = (tam + 7) / 8; //+ 1; // passando pra bytes, tratar lixo.
    //int restante = 8 - tam%8 ;

    for(int i = 0; i < tam ; i++){
        fprintf(f, "%c" , cabecalho[i]);
    }
}

void compacta(FILE* fRead){
    int* pesos = calculaPesos(fRead);
    Tree* tree = geraArvoreCodificacao(pesos);
    
    unsigned char** tabela = criaTabelaCodificacao(tree);
    tabela = inicializaTabelaCodificacao(tree, tabela, "");
    imprimeTabelaCodificacao(tabela);
    int pesoArquivoBit = calculaBits(tabela, pesos);

    FILE* fWrite = fopen("compactado.txt", "w");
    if(fWrite == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    //Codificação do cabeçalho
    bitmap* bmCabecalho = criaBitMapCompac(tree);
    bmCabecalho = insereQtdFolhas(tree, bmCabecalho);
    codificaTree(tree, bmCabecalho);
    imprimeBitmapArquivo(fWrite, bmCabecalho);
    
    //Codificação do texto
    int pesoArquivoByte = getPeso(tree);
    rewind(fRead);
    bitmap* bmTexto = codificaTexto(fRead, tabela, pesoArquivoBit, pesoArquivoByte);
    imprimeBitmapArquivo(fWrite, bmTexto);

    free(pesos);
    liberaTree(tree);
    liberaTabelaCodificacao(tabela);
    bitmapLibera(bmCabecalho);
    bitmapLibera(bmTexto);
    fclose(fWrite);
}
