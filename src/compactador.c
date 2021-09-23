#include "../include/compactador.h"

bitmap* insereQtdFolhas(Tree* tree, bitmap* bm){
    unsigned char binFolhas[8];
    int folhas = qtdFolhas(tree);
    folhas--; // decrementando para caber em 8 bits
    unsigned char folhasAux = (unsigned char) folhas;
    unsigned char c;
    converteDecimalParaBinario(folhasAux, binFolhas);
    
    for(int i = 0; i < 8 ; i++){
        bitmapAppendLeastSignificantBit(bm, binFolhas[i]); // Bits das folhas 
    }
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
            codificaTree( getLeft(tree)  , bm);
            codificaTree( getRight(tree) , bm);
        
        } else{
            bitmapAppendLeastSignificantBit(bm, '1'); // Nó folha
            elemento = getElem(tree);
            converteDecimalParaBinario(elemento, bin);

            for(int i = 0; i <= 7 ; i++){
                bitmapAppendLeastSignificantBit(bm, bin[i]); // Bits do elemento 
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
    int maxSize = (1 << (h + 1)) - 1 + 8 * (1 << h) + 8 + 3;
    // [2^(h+1) - 1] é o máxima número de nós da árvore
    // [8 * 2^h] é o máximo espaço em bits ocupado por cada caractere em um nó folha.
    // +8 é devido ao número de folhas que colocamos no início do bitmap a fim de ter uma condição de parada
    // +3 é para a quantidade de bits para o lixo do texto.
    bitmap* bm = bitmapInit(maxSize);
    return bm;
}

bitmap* codificaTexto(FILE* f, unsigned char** tabela, int pesoArquivoBit, int pesoArquivoByte){
    bitmap* bm = bitmapInit(pesoArquivoBit); 
    unsigned char aux;
    for(int i = 0; i < pesoArquivoByte; i++){
        fscanf(f, "%c", &aux);
 
        for(int j = 0; j < strlen(tabela[aux]); j++){
            bitmapAppendLeastSignificantBit(bm, tabela[aux][j]);
        }
    }
    return bm;
}

void imprimeBitmapArquivo(FILE* f, bitmap* bm){
    unsigned char* cabecalho = bitmapGetContents(bm);
    int tam = bitmapGetLength(bm);
    tam = (tam + 7) / 8; // passando pra bytes

    for(int i = 0; i < tam ; i++){
        fprintf(f, "%c" , cabecalho[i]);
    }
}

void compacta(unsigned char* nomeArquivo){  // nome_arquivo.formato
    unsigned char path[strlen(nomeArquivo) + 6];
    strcpy(path, "data/");
    strcat(path, nomeArquivo); // path possui caminho para o arquivo.

    FILE* fRead  = fopen(path, "r");
    if(fRead == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    int* pesos = calculaPesos(fRead);
    Tree* tree = geraArvoreCodificacao(pesos);
    
    unsigned char** tabela = criaTabelaCodificacao(tree);
    tabela = inicializaTabelaCodificacao(tree, tabela, "");
    int pesoArquivoBit = calculaBits(tabela, pesos);

    unsigned char nomeArquivoCompac[strlen(path) + 5];
    geraNomeArquivoCompac(nomeArquivoCompac, path);

    FILE* fWrite = fopen(nomeArquivoCompac, "w");
    if(fWrite == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }

    //Codificação do cabeçalho
    bitmap* bmCabecalho = criaBitMapCompac(tree);
    bmCabecalho = insereQtdFolhas(tree, bmCabecalho);
    bmCabecalho = insereLixoTexto(pesoArquivoBit, bmCabecalho);
    codificaTree(tree, bmCabecalho);
    imprimeBitmapArquivo(fWrite, bmCabecalho); 
    
    //Codificação do texto
    int pesoArquivoByte = getPeso(tree);
    rewind(fRead);
    
    bitmap* bmTexto = codificaTexto(fRead, tabela, pesoArquivoBit, pesoArquivoByte);
    imprimeBitmapArquivo(fWrite, bmTexto);

    liberaTudoCompactador(pesos, tree, tabela, bmCabecalho, bmTexto, fRead, fWrite);
    remove(path); //Apagando arquivo de entrada da compactação.
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

void geraNomeArquivoCompac(unsigned char* nomeArquivoCompac, unsigned char* path){
    strcpy(nomeArquivoCompac, path);
    strcat(nomeArquivoCompac, ".comp");
}
