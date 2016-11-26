/*
 *	Rodrigo Oliveira Caus
 *	RA: 186807
 *	Programa de leitura de uma arvore em
 *	pré-ordem e in-ordem, reconstrução da
 *	árvore binária e impressão e limpeza
 *	dela em pós-ordem. A leitura é sequencial.
 */

#include "tree.h"

int main(int argc, char **argv)
{
    char str1[MAXC], str2[MAXC];
    jequitiba *bin;
    while (1)
    {
        scanf("%s %s", str1, str2);
        if(feof(stdin))
            break;
        bin = arv_bin(str1, str2);
        imprime(bin);
        printf("\n");
        limpa(bin);
    }
    return 0;
}
