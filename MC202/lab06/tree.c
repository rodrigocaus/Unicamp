/*
 *	Rodrigo Oliveira Caus
 *	RA: 186807
 *	Programa de leitura de uma arvore em
 *	pré-ordem e in-ordem, reconstrução da
 *	árvore binária e impressão e limpeza
 *	dela em pós-ordem. A leitura é sequencial.
 */

#include "tree.h"

void imprime(jequitiba *a)
{
    //Caso base
    if(a == NULL)
        return;
    imprime(a->esq);
    imprime(a->dir);
    printf("%c", a->chave);
}

void limpa(jequitiba *a)
{
    //Caso base
    if(a == NULL)
        return;
    limpa(a->esq);
    limpa(a->dir);
    free(a);
}

jequitiba *arv_bin(char *s1, char *s2)
{
    //s1 será a sequência em pré-ordem
    //s2 será a sequencia em-ordem
    if(s1[0] == 0)
        return NULL;
    //Variáveis auxiliares
    char *s_esq_1, *s_esq_2, *s_dir_1, *s_dir_2;
    unsigned int counts;
    //O primeiro elemento da pré-ordem
    //é sempre a raiz de uma (sub)árvore
    jequitiba *raiz = calloc(1, sizeof(jequitiba));
    raiz->chave = s1[0];
    //Procuramos pela chave em s2
    for(counts = 0; counts<strlen(s1); counts++)
    {
        if(s2[counts] == s1[0]) break;
    }
    //Alocamos memória para as strings
    s_esq_1 = calloc(counts+1, sizeof(char));
    s_esq_2 = calloc(counts+1, sizeof(char));
    s_dir_1 = calloc(strlen(s1)-counts, sizeof(char));
    s_dir_2 = calloc(strlen(s1)-counts, sizeof(char));
    //Copiamos partes de s1 e s2
    strncpy(s_esq_1, s1+1, counts);
    s_esq_1[counts] = 0;
    strncpy(s_esq_2, s2, counts);
    s_esq_2[counts] = 0;
    strcpy(s_dir_1, s1+counts+1);
    strcpy(s_dir_2, s2+counts+1);
    //Fazemos as chamadas recursivas
    raiz->esq = arv_bin(s_esq_1, s_esq_2);
    raiz->dir = arv_bin(s_dir_1, s_dir_2);
    //Liberamos as memórias
    free(s_esq_1);
    free(s_esq_2);
    free(s_dir_1);
    free(s_dir_2);
    //Retornamos a raiz
    return raiz;
}
