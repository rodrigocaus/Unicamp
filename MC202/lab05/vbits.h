/*
	Rodrigo Oliveira Caus
	186807
	Turma A

	Programa para criação de um vetor de bits
	para um subconjunto de n números naturais,
	utilizando um vetor de unsigned char.

*/
#ifndef VBITS_H
	#define VBITS_H 1

#define MAXBITS 8
//Macros para manipulação dos bits
#define bitmask(a) (1 << (((a)-1)%MAXBITS))
#define bitslot(a) (((a)-1)/MAXBITS)
#define bitnslot(a) (bitslot(a) +1)

typedef unsigned char uchar;
typedef struct
{
	int size;
	uchar *vet;
}vbits;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cria um subconjunto vazio para n elementos
int create(vbits *b, int size);

//Adiciona um elemento ao conjunto
void add(vbits *b, int el);

//Remove um elemento do conjunto
void re_move(vbits *b, int el);

//Verifica se um elemento está na lista
uchar belong(vbits *b, int el);

//Retorna o número de elementos menores ou iguais a
//outro determinado (el)
int rank(vbits *b, int el);

//Retorna o n-ésimo elemento na ordem crescente
//do vetor
int select_bits(vbits *b, int n);

//Retorna o numero de elementos em determinado intervalo [i,j]
int rangecount(vbits *b, int i, int j);

//Imprime os elemtos em ordem crescente
void print_bits(vbits *b);

#endif