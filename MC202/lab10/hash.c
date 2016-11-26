/*
 *  Rodrigo Oliveira Caus
 *  Turma A
 *  Ra:186807
 *
 *  Criação de uma tabela de hashing de 50021
 *  elementos, contendo um par {chave, valor}.
 *  Colisões a serem resolvidas por hashing duplo.
 */

#include "hash.h"

void limpa(par ***tabela)
{
    int i;
    for(i = 0; i < MAXTAM; i++)
        free((*tabela)[i]);
    free(*tabela);
}

int buscar(ulong chave, par **tabela)
{
    int i = 0, pos;
    do
    {
        pos = (ha(chave) + i*hb(chave))%MAXTAM;
        i++;
    }while(tabela[pos] && tabela[pos]->chave != chave);
    //retornamos a posição que contem a chave
    //ou que será nula (podendo inserir uma nova chave)
    return pos;
}

int insere(ulong chave, int valor, par **tabela)
{
    int pos = buscar(chave, tabela);
    //Caso a chave já exista, alteramos o valor
    if(tabela[pos])
    {
        tabela[pos]->valor = valor;
        return 0;
    }
    tabela[pos] = malloc(sizeof(par));
    //Caso para operação malsucedida
    if(!tabela[pos])
        return 0;
    tabela[pos]->chave = chave;
    tabela[pos]->valor = valor;
    return 1;
}

int exclui(ulong chave, par **tabela)
{
    int pos = buscar(chave, tabela);
    //Caso a chave não exista, não removemos nada
    if(!tabela[pos])
        return 0;
    free(tabela[pos]);
    tabela[pos] = NULL;
    return 1;
}
