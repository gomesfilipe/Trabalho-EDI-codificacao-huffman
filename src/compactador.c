#include "../include/compactador.h"
#include <math.h>

bitmap* insereQtdFolhas(Tree* tree, bitmap* bm){
    unsigned char binFolhas[8];
    int folhas = qtdFolhas(tree);
    folhas--; // decrementando para caber em 8 bits
    unsigned char folhasAux = (unsigned char) folhas;
    unsigned char c;
    converteDecimalParaBinario(folhasAux, binFolhas);
    //printf("%s ", binFolhas);
    
    for(int i = 0; i < 8 ; i++){
        bitmapAppendLeastSignificantBit(bm, binFolhas[i]); //Bits das folhas 
        //c = bitmapGetContents(bm)[i];
        //printf("[%c] ", c);
    }
    //unsigned char* bitmapGetContents(bitmap* bm)
    return bm;
}

bitmap* insereLixoTexto(int pesoArquivoBits, bitmap* bm){
    int lixo = calculaLixoTexto(pesoArquivoBits);
    unsigned char bin[8];
    converteDecimalParaBinario(lixo, bin);
    for(int i = 5; i <= 7; i++){
        bitmapAppendLeastSignificantBit(bm, bin[i]);
    }
    return bm;
}

int calculaLixoTexto(int pesoArquivoBits){
    int lixo = pesoArquivoBits % 8;
    if(lixo != 0){
        lixo = 8 - lixo;
    }
    return lixo;
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
    int maxSize = pow(2, h + 1) - 1 + 8 * pow(2, h) + 8 + 3; //! trocar o +8 pra +9 dependendo
    //[2^(h+1) - 1] é o máxima número de nós da árvore
    // [8 * 2^h] é o máximo espaço em bits ocupado por cada caractere em um nó folha.
    //+ 9 é devido ao número de folhas que colocamos no início do bitmap a fim de ter uma condição de parada
    bitmap* bm = bitmapInit(maxSize);
    return bm;
}

//O peso do arquivo já vem em bits
bitmap* codificaTexto(FILE* f, unsigned char** tabela, int pesoArquivoBit, int pesoArquivoByte){
    bitmap* bm = bitmapInit(pesoArquivoBit); 
    //printf("peso byte [%d]\n", pesoArquivoByte);
    unsigned char aux;
    for(int i = 0; i < pesoArquivoByte; i++){
        //fscanf(f, "%c", &aux);
        fscanf(f, "%c", &aux);
        //printf("aux [%c] ", aux);
        //printf("[");
        //int tam = strlen(tabela[aux]) ;
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
    unsigned char* cabecalho = bitmapGetContents(bm);
    int tam = bitmapGetLength(bm);
    tam = (tam + 7) / 8; //+ 1; // passando pra bytes, tratar lixo.
    //int restante = 8 - tam%8 ;

    for(int i = 0; i < tam ; i++){
        fprintf(f, "%c" , cabecalho[i]);
    }
}

void compacta(unsigned char* nomeArquivo){
    FILE* fRead  = fopen(nomeArquivo, "r");
    if(fRead == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    int* pesos = calculaPesos(fRead);
    Tree* tree = geraArvoreCodificacao(pesos);
    
    unsigned char** tabela = criaTabelaCodificacao(tree);
    tabela = inicializaTabelaCodificacao(tree, tabela, "");
    imprimeTabelaCodificacao(tabela); //!
    int pesoArquivoBit = calculaBits(tabela, pesos);

    unsigned char nomeArquivoCompac[strlen(nomeArquivo) + 4];
    geraNomeArquivoCompac(nomeArquivoCompac, nomeArquivo);
    

    FILE* fWrite = fopen(nomeArquivoCompac, "w");
    if(fWrite == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }

    //Codificação do cabeçalho
    printf("chegou antes bm cabecalho\n");
    bitmap* bmCabecalho = criaBitMapCompac(tree);
    printf("chegou depois bm cabecalho\n");
    
    bmCabecalho = insereQtdFolhas(tree, bmCabecalho);
    bmCabecalho = insereLixoTexto(pesoArquivoBit, bmCabecalho);
    codificaTree(tree, bmCabecalho);
    imprimeBitmapArquivo(fWrite, bmCabecalho); 
    
    //Codificação do texto
    int pesoArquivoByte = getPeso(tree);
    rewind(fRead);
    
    printf("chegou antes bm texto\n");
    bitmap* bmTexto = codificaTexto(fRead, tabela, pesoArquivoBit, pesoArquivoByte);
    printf("chegou depois bm texto\n");
    imprimeBitmapArquivo(fWrite, bmTexto);

    liberaTudoCompactador(pesos, tree, tabela, bmCabecalho, bmTexto, fRead, fWrite);
}

void liberaTudoCompactador(int* pesos, Tree* tree, unsigned char** tabela, bitmap* bmCabecalho, bitmap* bmTexto, FILE* fRead, FILE* fWrite){
    free(pesos);
    liberaTree(tree);
    liberaTabelaCodificacao(tabela);
    bitmapLibera(bmCabecalho);
    bitmapLibera(bmTexto);
    fclose(fRead);
    fclose(fWrite);
}
// //!apagar depois
// void geraNomeArquivoCompac(char* nomeArquivoCompac, char* nomeArquivo){
//     strcpy(nomeArquivoCompac, nomeArquivo);
//     for(int i = strlen(nomeArquivoCompac) - 1 ; i >= 0 ; i--){
//         if(nomeArquivoCompac[i] == '.'){
//             nomeArquivoCompac[i] = '\0';
//             break;
//         }
//     }
//     strcat(nomeArquivoCompac, ".comp");
// }

void geraNomeArquivoCompac(unsigned char* nomeArquivoCompac, unsigned char* nomeArquivo){
    strcpy(nomeArquivoCompac, nomeArquivo);
    // for(int i = strlen(nomeArquivoCompac) - 1 ; i >= 0 ; i--){
    //     if(nomeArquivoCompac[i] == '.'){
    //         nomeArquivoCompac[i] = '\0';
    //         break;
    //     }
    // }
    strcat(nomeArquivoCompac, ".comp");
}
