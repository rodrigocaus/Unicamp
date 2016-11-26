/*
 *	Rodrigo Oliveira Caus
 *	RA: 186807
 *	Programa de leitura de uma arvore em
 *	pré-ordem e in-ordem, reconstrução da
 *	árvore binária e impressão e limpeza
 *	dela em pós-ordem. A leitura é sequencial.
 */
#ifndef TREE
	#define TREE 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXC 200

typedef struct galho
{
	char chave;
	struct galho *esq, *dir;
}jequitiba;

//Função para imprimir os elementos da árvore em pós-ordem
void imprime(jequitiba *a);

//Função para limpar a árvore alocada dinamicamente
void limpa(jequitiba *a);

//Função para reconstruir a árvore binária lida
jequitiba *arv_bin(char *s1, char *s2);

#endif
