#include "../include/descompactador.h"

#define TAM 500

bitmap* leArquivoCompactado(FILE* fRComp){
    int tam = TAM;
    unsigned char* str = (unsigned char*) malloc (tam * sizeof(unsigned char)); // 499 caracteres + \0
    int i;
    for(i = 0; ; i++){
        //printf("i qtd: %d\n", i);
        fscanf(fRComp, "%c" , &str[i]);
        if(feof(fRComp)){
            break;
        }
        if(i == tam - 1){ //Se chegou no final da string e o arquivo ainda não foi lido por completo, é preciso aumentar o tamanho da string
            tam += TAM;
            str = (unsigned char*) realloc(str, tam * sizeof(unsigned char));
        }
    }
    str[i] = '\0';
    // bitmap* bm = bitmapInit(8 * i + 8); // Multiplicamos por 8 para converter para bits e soma 8 para o \0.
    // //Setando a string no campo contests do bitmap
    // for(int j = 0; j < i; j++){
    //     for(int k = 7; k >= 0; k--){
    //         bitmapAppendLeastSignificantBit(bm, (str[j] >> k) & 1);
    //     }
    // }
    bitmap* bm = recuperaBitmap(str, i);
    //unsigned int tamLength = bitmapGetLength(bm);
    free(str);
    return bm;
}

void recriaTree(bitmap* bm, Tree* tree, int* i, int* folhas, int* lixo){
    unsigned char bit;
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

void decodifica(bitmap* bm, unsigned char* nomeArquivoCompactado){
    int i = 11;
    // int i = 8;
    int folhas = 0;
    int lixoCabecalho = 3; // inicializado com 3 pois os 3 primeiros bits do segundo byte é o tamanho do lixo do texto.
    int lixoTexto = getLixoTexto(bm);
    
    Tree* tree = criaTree(0, -1, NULL, NULL);

    recriaTree(bm, tree, &i, &folhas, &lixoCabecalho);
    //printf("arvore recriada:\n\n");
    //imprimeTree(tree);
    // printf("i: [%d]  ", i); //!
    // printf("folhas: [%d]  ", folhas); //!
    // printf("lixo cabecalho:[%d]\n", lixoCabecalho); //!

    decodificaTexto( bm, &i,  tree, lixoTexto, nomeArquivoCompactado);
    liberaTree(tree);
}

void decodificaTexto(bitmap* bm, int* i, Tree* tree, int lixoTexto, unsigned char* nomeArquivoCompactado){
    Tree* aux = tree;
    unsigned char nomeArquivoDescompactado[strlen(nomeArquivoCompactado)];
    strcpy(nomeArquivoDescompactado, nomeArquivoCompactado);

    //Retirando o .comp do nome do arquivo
    for(int i = strlen(nomeArquivoDescompactado) - 1; i >= 0; i--){
        if(nomeArquivoDescompactado[i] == '.'){
            nomeArquivoDescompactado[i] = '\0';
            break;           
        }
    }
    
    FILE* fWrite = fopen(nomeArquivoDescompactado, "w");
    if(fWrite == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
    
    for( (*i) ; (*i) < bitmapGetLength(bm) - lixoTexto; (*i)++){ //acho q tem tirar o lixo aqui e colocar le como paramentro
        
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
    remove(nomeArquivoCompactado);
    fclose(fWrite);
}

int getLixoTexto(bitmap* bm){
    unsigned char lixo[3];
    lixo[0] = bitmapGetBit(bm, 8); // Pegando bits 8, 9 e 10 do cabeçalho, nos quais estão o lixo do texto.
    lixo[1] = bitmapGetBit(bm, 9);
    lixo[2] = bitmapGetBit(bm,10);

    return (lixo[0] << 2) + (lixo[1] << 1) + lixo[2];
}

bitmap* recuperaBitmap(unsigned char* str, int tam){
    bitmap* bm = bitmapInit(8 * tam + 8); // Multiplicamos por 8 para converter para bits e soma 8 para o \0.
    //Setando a string no campo contests do bitmap
    for(int j = 0; j < tam; j++){
        for(int k = 7; k >= 0; k--){
            bitmapAppendLeastSignificantBit(bm, (str[j] >> k) & 1);
        }
    }
    return bm;
}

void descompacta(unsigned char* nomeArquivoCompactado){
    unsigned char path[strlen(nomeArquivoCompactado) + 20] ;
    strcpy(path, "data/");
    strcat(path, nomeArquivoCompactado);
    
    FILE *f = fopen(path, "r");
    if(f == NULL){
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    bitmap* bm = leArquivoCompactado(f);
    decodifica(bm, path);
    fclose(f);   
    bitmapLibera(bm);
}
