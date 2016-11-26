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

#include "parentizada.h"

doompalm *buildtree()
{
	char atual;
	atual = getchar();
	if (atual == ')')
		return NULL;

    doompalm *a, *esq, *dir;
    char str_dados[35];
	//árvore será lida da esquerda para a direita
	//em que os filhos da esquerda serão determinados
	esq = buildtree();
	scanf("%[^(]s", str_dados);
    atual = getchar(); //pegamos o (
	dir = buildtree();

	a = calloc(1, sizeof(doompalm));
	a->esq = esq;
	a->dir = dir;
    atual = getchar();

	if(esq && dir)
		sscanf(str_dados, "%f:%d:%f", &a->pe, &a->chave, &a->pd);
	else if(esq)
		sscanf(str_dados, "%f:%d", &a->pe, &a->chave);
	else if(dir)
		sscanf(str_dados, "%d:%f", &a->chave, &a->pd);
	else
		sscanf(str_dados, "%d", &a->chave);

	return a;
}

float max_peso(doompalm *a)
{
    if(a == NULL) return 0.0;
    float c_esq, c_dir;
    c_esq = a->pe + max_peso(a->esq);
    c_dir = a->pd + max_peso(a->dir);
    return ((c_dir > c_esq)? c_dir:c_esq);
}

void limpa_tudo(doompalm *a)
{
    //Caso base
    if(a == NULL)
        return;
    limpa_tudo(a->esq);
    limpa_tudo(a->dir);
    a->dir = a->esq = NULL;
    free(a);
}

void printin(doompalm *a)
{
    if(a == NULL){
        printf("()");
        return;
    }
    printf("(");
    printin(a->esq);
    if(a->esq)
        printf("%.3f:", a->pe);
    printf("%d", a->chave);
    if(a->dir)
        printf(":%.3f", a->pd);
    printin(a->dir);
    printf(")");
}
