/*
 *  Rodrigo Caus
 *  RA: 186807
 *
 *  Lab de manipulacao de matrizes esparsas
 *  utilizando vetor de coordenadas e o metodo CSR.
 */

#ifndef ESPARSAH
 #define ESPARSAH 1

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long ulong;
typedef struct
{
    //Linha e coluna da matriz esparsa
    ulong lin, col;
    int dado;
}trio;

typedef struct
{
    //Estrutura guarda 3 vetores para CSR
    ulong *coluna, *rLinha;
    int *dados;
    //Numero de elementos e numero de linhas
    int tam, nLinhas;
}CSR;

//Funcao de comparacao a ser utilizada com qsort
int comparaTrio(const void *aa, const void *bb);
//Funcao para criar a CSR
int criaCSR(CSR *esM, trio *tVec, int tam);
//Funcao para consultar o CSR
int buscaCSR(CSR *esM, int linha, int coluna);
//Função para limpar um CSR
void limpaCSR(CSR *esM);

#endif
