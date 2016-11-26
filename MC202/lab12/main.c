/*
 *  Rodrigo Caus
 *  RA: 186807
 *
 *  Lab de manipulacao de matrizes esparsas
 *  utilizando vetor de coordenadas e o metodo CSR.
 */

#include "esparsa.h"

int main(int argc, char **argv)
{
    //Variáveis de utilizacao
    long linha, coluna;
    int num, i;
    trio *tVec;
    CSR esMatriz;

    //Le-se o numero de elementos nao nulos
    scanf(" %d", &num);

    tVec = malloc(num*sizeof(trio));
    if(tVec == NULL)
        return 1;

    for(i = 0; i<num; i++)
        scanf(" %lu %lu %d", &(tVec[i].lin), &(tVec[i].col), &(tVec[i].dado));

    //Ordena-se o vetor de coordenadas para criar o CSR
    qsort(tVec, num, sizeof(trio),(__compar_fn_t) comparaTrio);

    if(criaCSR(&esMatriz, tVec, num))
        return 1;

    do
    {
        //Sequencia de consulta de elementos
        scanf(" %ld %ld", &linha, &coluna);
        if(linha < 0)
            break;

        printf("(%ld,%ld) = %d\n", linha, coluna, buscaCSR(&esMatriz,linha,coluna));

    } while(1);

    limpaCSR(&esMatriz);
    free(tVec);

    return 0;
}
