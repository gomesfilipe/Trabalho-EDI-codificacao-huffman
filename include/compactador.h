#ifndef COMPACTADOR_H_
#define COMPACTADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/tree.h"
#include "../include/list.h"
#include "../include/bitmap.h"
#include "../include/huffman.h"

/**
 * @brief Codifica uma árvore de huffman e a escreve em um bitmap.
 * @param tree Árvore que será codificada.
 * @param bm Bitmap que terá a codificação da árvore setada nele.
 **/
void codificaTree(Tree* tree, bitmap* bm);

/**
 * @brief Pega a posição de um determinado char na tabela ascii e cria uma string que representa
 * o número binário dessa posição.
 * @param elem Caractere da tabela ascii.
 * @param bin String que representará o binário da posição de elem na tabela ascii.
 **/
void converteDecimalParaBinario(unsigned char elem, unsigned char* bin);

/**
 * @brief Inicializa um bitmap com tamanho suficiente para armazenar a codificação de uma árvore cheia.
 * @param tree Árvore que será baseada para calcular o tamanho do bitmap.
 * @return Retorna o bitmap criado.
 **/
bitmap* criaBitMapCompac(Tree* tree);

/**
 * @brief Imprime um bitmap no arquivo.
 * @param f Ponteiro para o arquivo no qual será impresso o campo contests do bitmap.
 * @param bm Bitmap que será escrito no arquivo.
 **/
void imprimeBitmapArquivo(FILE* f, bitmap* bm);

/**
 * @brief Insere a quantidade de folhas de um árvore em um bitmap.
 * @param tree Árvore que terá sua quantidade de folhas setada no bitmap.
 * @return bitmap que possui a quantidade de folhas setada no campo contents.
 **/
bitmap* insereQtdFolhas(Tree* tree, bitmap* bm);

/**
 * @brief Lê um arquivo e coloca sua codificação num bitmap.
 * @param f Arquivo que será lido.
 * @param tabela Tabela de codificação de cada caractere.
 * @param pesoArquivoBit Peso do arquivo em bits.
 * @param pesoArquivoByte Peso do arquivo em bytes.
 * @return Bitmap preenchido e codificado.
 **/
bitmap* codificaTexto(FILE* f, unsigned char** tabela, int pesoArquivoBit, int pesoArquivoByte);

/**
 * @brief Funçao princiapl na compactação de um arquivo.
 * Essa função chama várias outras funções a fim de fazer a compactação.
 * @param nomeArquivo Ponteiro para o arquivo que será compactado.
 **/
void compacta(unsigned char* nomeArquivo);

/**
 * @brief Libera da memória tudo o que foi usado para a compactação do arquivo.
 * @param pesos É o vetor de pesos dos caracteres.
 * @param tree É a árvore de codificação.
 * @param tabela Tabela que contém a codificação de cada caractere.
 * @param bmCabecalho É o bitmap onde foi armazenado o cabeçalho do texto
 * @param bmTexto É o bitmap onde foi armazenado o texto.
 * @param fRead Ponteiro para o arquivo de leitura que foi compactado e que agora será liberado da memória.
 * @param fWrite Ponteiro para o arquivo no qual escrevemos o arquivo compactado
 **/
void liberaTudoCompactador(int* pesos, Tree* tree, unsigned char** tabela, bitmap* bmCabecalho, bitmap* bmTexto, FILE* fRead, FILE* fWrite);

/**
 * @brief Preenche uma string com o nome do arquivo compactado. Na prática,
 * essa função concatena o nome do arquivo que será codificado com ".comp".
 * @param nomeArquivoCompac Ponteiro para string que terá o nome do arquivo .comp.
 * @param path Ponteiro para o arquivo que será compactado
 **/
void geraNomeArquivoCompac(unsigned char* nomeArquivoCompac, unsigned char* path);

/**
 * @brief Calcula o tamanho do lixo do trecho de texto codificado. 
 * (Vê quantos bits falta para a quantidade de bits ser múltipla de 8).
 * @param pesoArquivoBits Quantidade de bits do texto codificado.
 * @return Tamanho do lixo do trecho de texto codificado.
 **/
int calculaLixoTexto(int pesoArquivoBits);

/**
 * @brief Insere no cabeçalho a quantidade de lixo do texto codificado 
 * @param pesoArquivoBits Quantidade de bits do texto codificado.
 * @param bm Bitmap que está recebendo a codificação do cabeçalho.
 * @return Bitmap atualizado.
 **/
bitmap* insereLixoTexto(int pesoArquivoBits, bitmap* bm);

#endif /* COMPACTADOR_H_ */
