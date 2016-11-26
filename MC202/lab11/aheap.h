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

#ifndef AHEAP
    #define AHEAP 1

#include <stdio.h>
#include <stdlib.h>

//Macros para localização dos nós
//filhos e nó pai em um heap
#define fesq(i) (2*i +1)
#define fdir(i) (2*i +2)
#define pa(i) ((i-1)/2)

typedef unsigned long ulong;

//Definimos o par ordenado;
typedef struct{
    ulong chave;
    int valor;
}par;

//Definimos uma estrutura para conter os vetores
//E informações adjascentes
typedef struct{
    long *tabela;
    par **heap;
    //tamanho e número de elementos
    int tam, num;
}grupo;

//Função para inicializar um grupo
int inicia(grupo *info, int tam);
//Função para limpar um vetor de pares
void limpa(par ***v, int tam);
//Função para inserir uma chave e um valor
int insere(ulong chave, int valor, grupo *info);
//Função para diminuir o valor de uma chave
int diminui(ulong chave, int valor, grupo *info);
//Função para remover o mínimo do heap
int exclui(grupo *info);

#endif
