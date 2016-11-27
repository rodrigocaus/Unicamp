/*
 *  Rodrigo Oliveira Caus
 *  186807
 *  Funcoes de ordenacao
 */

#include "sort.h"

void bsort(int *base, size_t num)
{
    int temp;
    for(int i = 1; i < num; i++)
    {
        for(int j = num-1; j >= i; j--)
        {
            if(base[j]<base[j-1])
            {
                temp = base[j];
                base[j] = base[j-1];
                base[j-1] = temp;
            }
        }
    }
}

void ssort(int *base, size_t num)
{
    int temp, max;
    for(int i = num-1; i >= 1; i--)
    {
        max = 0;
        for(int j = 1; j <= i; j++)
        {
            if(base[j]>base[max])
                max = j;
        }
        temp = base[i];
        base[i] = base[max];
        base[max] = temp;
    }
}

//Funcao complementar para criar um heap de máximo
static int *criaHeap(int *base, size_t num)
{
    int *heap = malloc(num*sizeof(int));
    if(!heap) return NULL;

    int pos, temp;
    for(int i = 0; i < num; i++)
    {
        //Inserimos um elemento no heap
        heap[i] = base[i];
        //Borbulhamos o elemento até o máximo possivel (pai >= filhos)
        pos = i;
        while(heap[pa(pos)] < heap[pos])
        {
            temp = heap[pa(pos)];
            heap[pa(pos)] = heap[pos];
            heap[pos] = temp;
            pos = pa(pos);
        }
    }

    return heap;
}
//Funcao complementar de remocao de maximo de um heap
static int removeMax(int *heap, size_t num)
{
    int max;
    int pos, ult;
    int temp;

    max = heap[0];
    if(num == 1) goto fim;
    //Trocamos o primeiro pelo ultimo
    heap[0] = heap[num-1];

    //Movemos o primeiro ate que seja maior que seus filhos
    pos = 0;
    while(fesq(pos) < num)
    {
        //Procura-se pelo maior filho
        int mfilho;
        if(fdir(pos) < num && heap[fdir(pos)] > heap[fesq(pos)])
            mfilho = fdir(pos);
        else
            mfilho = fesq(pos);

        //Se o pai ja for maior que seus filhos
        if(heap[pos] >= heap[mfilho])
            break;
        //Caso contrario, trocamos pelo maior filho
        temp = heap[pos];
        heap[pos] = heap[mfilho];
        heap[mfilho] = temp;
        //Atualizamos pos
        pos = mfilho;
    }
    fim:
    return max;
}
void hsort(int *base, size_t num)
{
    int *heap = criaHeap(base, num);
    if(!heap) return;

    for(int i = num-1; i >= 0; i--)
        base[i] = removeMax(heap, i+1);

    free(heap);
}

void shsort(int *base, size_t num)
{
    int incs = 1;
    //Gera-se a sequencia de Knuth (mais simples)
    while(incs < num)
        incs = 3*incs +1;

    while(incs >= 1)
    {
        //Funcao inversa da sequencia
        incs = (incs-1)/3;
        for(int i = incs; i < num; i++)
        {
            int chave = base[i];
            int j = i;
            //Compara elementos distantes "incs" um do outro
            while (j >= incs && base[j-incs] > chave)
            {
                base[j] = base[j-incs];
                j = j-incs;
            }
            base[j] = chave;
        }
    }
}

//Funcao complementar de juncao dos vetores divididos
static void merge(int *base, int i, int m, int f)
{
    //Variaveis de indice
    int j, k, t;
    //Vetor temporario
    int *tempVet = malloc((f-i+1)*sizeof(int));
    if(!tempVet) return;

    j = i;
    k = m+1;
    //Insere os valores de [i,f] ordenados em tempVet
    for(t = 0; t < (f-i+1); t++)
    {
        int chave;
        if(j <= m && k <= f)
        {
            //No caso normal, inserimos o menor valor
            if(base[j] < base[k]){
                chave = base[j];
                j++;
            }
            else{
                chave = base[k];
                k++;
            }
        }
        else if(j <= m)
        {
            //Caso o trecho a esquerda tenha acabado
            chave = base[j];
            j++;
        }
        else
        {
            //Caso o trecho a direita tenha acabado
            chave = base[k];
            k++;
        }
        tempVet[t] = chave;
    }
    //Copia o trecho ordenado para o vetor base
    for(j = i; j <= f; j++)
        base[j] = tempVet[j - i];

    free(tempVet);
}
//Funcao-alma de ordenacao por mergesort
static void mergeSort(int *base, int i, int f)
{
    int med = (i+f)/2;
    if(f>i)
    {
        //Dividimos a esquerda e depois a direita
        mergeSort(base, i, med);
        mergeSort(base, med+1, f);
        //Juntamos as partes ordenadamente
        merge(base, i, med, f);
    }
}
//Funcao de chamada normalizada inicial de mergesort
void msort(int *base, size_t num)
{
    mergeSort(base, 0, num-1);
}

//Funcao de comparacao para inteiros, usado no qsort
static int compare(const void *a, const void *b)
{
    //retorna   <0 se a<b
    //          =0 se a==b
    //          >0 se a>b
    return (*(int *)a - *(int *)b);
}
void quisort(int *base, size_t num)
{
    //Funcao de normalizar as entradas para o qsort
    qsort(base, num, sizeof(int), (__compar_fn_t)compare);
}
