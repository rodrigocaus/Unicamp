/*
 *  Rodrigo Oliveira Caus
 *  186807
 *  Ordenacao de vetores de inteiros com entradas aleatorias
 */

#include "exec.h"
#include "sort.h"

#define NEXEC 5
int main(int argc, char **argv)
{
    int tam[] = {50,100,500,1000,5000,10000,50000,100000,500000,1000000};
    int *vet;
    printf("Tamanho\t\tTempo(s)\n");
    for(int i = 0; i < 10; i++)
    {
        double tempo = 0.0;
        for(int j = 0; j < NEXEC; j++)
        {
            vet = criaRnd(tam[i]);
            if(vet == NULL)
                break;

            tempo += timeSort(vet, tam[i], /*funcao de ordenacao*/);

            free(vet);
            vet = NULL;
        }
        printf("%-7d\t\t%3.10lf\n", tam[i], tempo/((double)NEXEC));
    }


    if(vet != NULL)
        free(vet);

    return 0;
}
