/*
 *  Rodrigo Oliveira Caus
 *  186807
 *  Header de funcoes de ordenacao
 */

#ifndef SORTH
#define SORTH 1

#include <stdlib.h>

//Macros para localização dos nós
//filhos e nó pai em um heap
#define fesq(i) (2*i +1)
#define fdir(i) (2*i +2)
#define pa(i) ((i-1)/2)

//Funcao de ordenacao de vetores de inteiros por bubblesort
void bsort(int *base, size_t num);
//Funcao de ordenacao de vetores de inteiros por selectionsort
void ssort(int *base, size_t num);
//Funcao de ordenacao de vetores de inteiros por heapsort
void hsort(int *base, size_t num);
//Funcao de ordenacao de vetores de inteiros por shellsort
void shsort(int *base, size_t num);
//Funcao de ordenacao de vetores de inteiros por mergesort
void msort(int *base, size_t num);
//Funcao de chamada do qsort (stdlib) para inteiros
void quisort(int *base, size_t num);

#endif
