/*
 *  Rodrigo Oliveira Caus
 *  Turma A
 *  Ra:186807
 *
 *  Criação de uma tabela de hashing de 50021
 *  elementos, contendo um par {chave, valor}.
 *  Colisões a serem resolvidas por hashing duplo.
 */

#ifndef HASHINGH
    #define HASHINGH 1

#include <stdio.h>
#include <stdlib.h>

//Definimos um tamanho primo máximo
//para o qual o fator de carga é <0.8
#define MAXTAM 62501
//Definimos macros de hashing
#define ha(k) (k%MAXTAM)
#define hb(k) (1+(k%(MAXTAM-2)))

typedef unsigned long ulong;
//Definimos o par ordenado;
typedef struct{
    ulong chave;
    int valor;
}par;

//Função para limpar a tabela de hashing
void limpa(par ***tabela);
//Função para buscar por uma chave na tabela
int buscar(ulong chave, par **tabela);
//Função para inserir uma chave e um valor
int insere(ulong chave, int valor, par **tabela);
//Função para remover uma chave
int exclui(ulong chave, par **tabela);
#endif
