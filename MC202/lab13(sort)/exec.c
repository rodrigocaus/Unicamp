/*
 *  Rodrigo Oliveira Caus
 *  186807
 *  Funcoes de execucao de codigos de ordenacao
 */

#include "exec.h"

int *criaRnd(size_t tam)
{
    int *vet = malloc(tam*sizeof(int));
    if(vet == NULL)
        return NULL;

    if(SEEDFIXA)
        srand(SEEDRND);
    else
        srand((unsigned)time(NULL));

    for(int i = 0; i < tam; i++)
        vet[i] = rand();

    return vet;
}

void printVet(int *vet, size_t tam)
{
    for (int i = 0; i < tam; i++)
        printf("%d ", vet[i]);

    printf("\n");
}

double timeSort(int *vet, size_t tam, void (*fsort)(int *vet, size_t tam))
{
    struct timespec ini, fim;

    clock_gettime(CLOCK_MONOTONIC, &ini);
    fsort(vet, tam);
    clock_gettime(CLOCK_MONOTONIC, &fim);
    return ((double)(fim.tv_sec - ini.tv_sec) + ((double)(fim.tv_nsec - ini.tv_nsec)/GIGA));
}
