/*
 *  Rodrigo Oliveira Caus
 *  Turma A
 *  Ra:186807
 *
 *  Criação de um heap aumentado por vetor
 *  contendo um par {chave, valor}.
 *  O vetor apontará as chaves do par; e o heap
 *  será ordenado pelo mínimo valor do par.
 */

#include "aheap.h"

int inicia(grupo *info, int tam)
{
    info->tabela = malloc(tam * sizeof(long));
    if(info->tabela == NULL)
        return 1;
    int i;
    for(i = 0; i<tam; i++)
        info->tabela[i] = -1;

    info->heap = calloc(tam, sizeof(par *));
    if(info->heap == NULL)
    {
        free(info->tabela);
        return 1;
    }
    info->num = 0;
    info->tam = tam;
    return 0;
}

void limpa(par ***v, int tam)
{
    int i;
    for(i = 0; i < tam; i++)
        free((*v)[i]);
    free(*v);
}

int insere(ulong chave, int valor, grupo *info)
{
    //Se a chave já existir
    if(info->tabela[chave%(info->tam)] > -1)
        return 0;
    //Variáveis usuais
    int pos, pai;
    ulong aux;
    par *temp;

    pos = info->num;
    info->heap[pos] = malloc(sizeof(par));
    if(info->heap[pos] == NULL)
        return 0;
    info->heap[pos]->chave = chave;
    info->heap[pos]->valor = valor;
    //Fazemos a subida no heap
    pai = pa(pos);
    while(info->heap[pai]->valor > info->heap[pos]->valor)
    {
        //Fazemos a troca
        temp = info->heap[pai];
        info->heap[pai] = info->heap[pos];
        info->heap[pos] = temp;
        //Atualizamos o vetor para o pai
        aux = (info->heap[pos]->chave)%(info->tam);
        info->tabela[aux] = pos;
        //Atualizamos os valores;
        pos = pai;
        pai = pa(pos);
    }
    //tabela[chave] indica a posição da chave no heap
    info->tabela[chave%(info->tam)] = pos;
    return 1;
}

int diminui(ulong chave, int valor, grupo *info)
{
    //Se a chave não existir
    if(info->tabela[chave%(info->tam)] < 0)
        return 0;
    //Variáveis usuais
    int pos, pai;
    ulong aux;
    par *temp;

    pos = info->tabela[chave%(info->tam)];
    info->heap[pos]->valor = valor;
    //Fazemos a subida, se necessário
    pai = pa(pos);
    while(info->heap[pai]->valor > info->heap[pos]->valor)
    {
        //Fazemos a troca
        temp = info->heap[pai];
        info->heap[pai] = info->heap[pos];
        info->heap[pos] = temp;
        //Atualizamos o vetor para o pai
        aux = (info->heap[pos]->chave)%(info->tam);
        info->tabela[aux] = pos;
        //Atualizamos os valores;
        pos = pai;
        pai = pa(pos);
    }
    //tabela[chave] indica a posição da chave no heap
    info->tabela[chave%(info->tam)] = pos;
    return 1;
}

int exclui(grupo *info)
{
    //Se o heap estiver vazio
    if(info->num <= 0)
    {
        printf("vazio\n");
        return 0;
    }
    int ult = info->num -1;
    int pos = 0, mfilho;
    //Trocamos o primeiro pelo ultimo
    par *temp = info->heap[0];
    info->heap[0] = info->heap[ult];
    info->heap[ult] = temp;
    info->tabela[(info->heap[0]->chave)%(info->tam)] = 0;
    //Apagamos o último (antigo primeiro)
    printf("minimo {%lu,%d}\n", info->heap[ult]->chave, info->heap[ult]->valor);
    info->tabela[(info->heap[ult]->chave)%(info->tam)] = -1;
    free(info->heap[ult]);
    info->heap[ult] = NULL;
    //Movemos o primeiro até a folha mais à esquerda
    while(info->heap[fesq(pos)] && pos <= pa(info->tam))
    {
        //Verificamos o filho de menor valor
        if(info->heap[fdir(pos)])
        {
            if(info->heap[fesq(pos)]->valor > info->heap[fdir(pos)]->valor)
                mfilho = fdir(pos);
            else
                mfilho = fesq(pos);
        }
        else
            mfilho = fesq(pos);
        if(info->heap[pos]->valor <= info->heap[mfilho]->valor)
            break;
        //Fazemos a troca
        temp = info->heap[mfilho];
        info->heap[mfilho] = info->heap[pos];
        info->heap[pos] = temp;
        info->tabela[(info->heap[pos]->chave)%(info->tam)] = pos;
        //Atualizamos os valores
        pos = mfilho;
        info->tabela[(info->heap[pos]->chave)%(info->tam)] = pos;
    }
    return 1;
}
