/*
 *  Rodrigo Oliveira Caus
 *  186807
 *  Header de funcoes de execucao de codigos de ordenacao
 */

#ifndef EXECH
#define EXECH 1

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SEEDFIXA 1
#define SEEDRND 43
#define GIGA 1E9

//Funcao para gerar um vetor constante de numeros aleatorios
int *criaRnd(size_t tam);
//Funcao para imprimir os elementos de um vetor
void printVet(int *vet, size_t tam);
//Funcao para medir tempo de execucao de uma funcao de ordenacao normalizada
double timeSort(int *vet, size_t tam, void (*fsort)(int *vet, size_t tam));

#endif
