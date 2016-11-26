/*
 *	Rodrigo Oliveira Caus
 *	RA 186807
 *
 *	Trabalho cuja função é desenvolver uma
 *	árvore binária de inteiros com pesos nas
 *	arestas, de acordo com a entrada-padrão.
 *  A entrada-padrão consiste na representação
 *  parentizada da árvore, na forma de in-order.
 */

#ifndef PAREH
	#define PAREH 1
#define MAXC 100000
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*	Nó para árvore binária
 *	Nome em homenagem a Hyphaene thebaica - Doom Palm
 *	árvore palmeira africana, cuja caracteristica peculiar
 *	é a divisão binária de seus galhos.
 */
typedef struct arvore
{
	int chave;
	struct arvore *esq, *dir;
	float pe, pd;
}doompalm;


//Função para construir a árvore binária
//a partir da entrada parentizada
doompalm *buildtree();
//Função que retorna o caminho de maior peso nas arestas
float max_peso(doompalm *a);
//Função para liberar memória ocupada pela árvore
void limpa_tudo(doompalm *a);
//Função para imprimir a árvore na forma parentizada
void printin(doompalm *a);
#endif
