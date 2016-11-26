/*
 *  Rodrigo Caus
 *  RA: 186807
 *
 *  Lab de manipulacao de matrizes esparsas
 *  utilizando vetor de coordenadas e o metodo CSR.
 */

#include "esparsa.h"

int comparaTrio(const void *aa, const void *bb)
{
    trio *a = (trio*) aa, *b = (trio*) bb;
    //retorna   <0 se a<b
    //          =0 se a==b
    //          >0 se a>b
    if(a->lin == b->lin)
        return ((int)(a->col - b->col));
    else
        return ((int)(a->lin - b->lin));
}

int criaCSR(CSR *esM, trio *tVec, int tam)
{
    esM->tam = tam;
    esM->coluna = malloc(tam*sizeof(ulong));
    esM->dados = malloc(tam*sizeof(int));
    //a maior linha no vetor ordenado
    esM->nLinhas = tVec[tam-1].lin +1;
    esM->rLinha = malloc((esM->nLinhas +1)*sizeof(ulong));
    if(esM->rLinha == NULL)
    {
        free(esM->coluna);
        free(esM->dados);
        return 1;
    }

    //Faz as atribuicoes da coluna e respectivo dado
    int i, j, contador;
    for(i = 0; i < tam; i++)
    {
        esM->dados[i] = tVec[i].dado;
        esM->coluna[i] = tVec[i].col;
    }

    //Elemento de rLinha[i] indica o numero
    //de elementos nao nulos contados ate a linha i.
    esM->rLinha[0] = 0;
    contador = j = 0;
    for(i = 0; i<esM->nLinhas; i++)
    {
        for(; j<tam && tVec[j].lin == i; j++)
            contador++;
        esM->rLinha[i+1] = contador;
    }
    return 0;
}

int buscaCSR(CSR *esM, int linha, int coluna)
{
    //Verificacao de elementos invalidos ou nulos
    if(linha >= esM->nLinhas || esM->rLinha[linha] == esM->rLinha[linha+1])
        return 0;

    //Verificamos se existe um elemento nao nulo na linha indicada
    //cuja quantidade eh indicada por rLinha[i+1]-rLinha[i]
    int i, estado = 0;
    for(i = esM->rLinha[linha]; i < esM->rLinha[linha+1]; i++)
    {
        //Verificamos um elemento nao nulo na coluna indicada
        if(esM->coluna[i] == coluna)
        {
            //Altera-se a variavel "booleana"
            estado = 1;
            break;
        }
    }

    //Se for encontrado um elemento nao nulo
    if(estado)
        return esM->dados[i];
    else
        return 0;
}

void limpaCSR(CSR *esM)
{
    //Limpeza de todos os vetores alocados
    free(esM->coluna);
    free(esM->rLinha);
    free(esM->dados);
    esM->tam = 0;
}
