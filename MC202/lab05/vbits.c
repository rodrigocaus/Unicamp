/*
	Rodrigo Oliveira Caus
	186807
	Turma A

	Programa para criação de um vetor de bits
	para um subconjunto de n números naturais,
	utilizando um vetor de unsigned char.

*/

#include "vbits.h"

int create(vbits *b, int size)
{
	//Se a lista já existir, é liberada
	if(b->vet != NULL){
		free(b->vet);
		b->vet = NULL;
	}
	b->vet = calloc(bitnslot(size), sizeof(uchar) );
	if(!b->vet)
		return 0;
	return size;
}

void add(vbits *b, int el)
{
	//Só trabalhamos com elementos naturais
	//Limite para inclusão
	if(el <= 0 || el > b->size)
		return;
	//Adiciona pelo "ou" lógico bit a bit
	b->vet[bitslot(el)] |= bitmask(el);
}

void re_move(vbits *b, int el)
{
	//Só trabalhamos com elementos naturais
	//Limite para remoção
	if(el <= 0 || el > b->size)
		return;
	//Remove pelo "e" lógico bit a bit da negação
	b->vet[bitslot(el)] &= ~bitmask(el);
}

uchar belong(vbits *b, int el)
{
	//Só trabalhamos com elementos naturais
	//Limite comparação
	if(el <= 0 || el > b->size)
		return 0;
	return (b->vet[bitslot(el)] & bitmask(el));
}

void print_bits(vbits *b)
{
	uchar p = 0;
	int i;
	printf("S = {");
	for (i = 1; i <= b->size; i++)
	{
		if(belong(b, i))
		{
			if(!p)
			{
				//Para imprimir com a formatação correta
				printf("%d", i);
				p++;
			}
			else
				printf(",%d", i);
		}
	}
	printf("}\n");
}

int rank(vbits *b, int el)
{
	//Só trabalhamos com elementos naturais
	//Limite para rankear
	if(el <= 0 || el > b->size)
		return -1;

	int count = 0, i;
	for(i = 1; i <= el; i++)
	{
		if(belong(b, i))
			count++;
	}
	return count;
}

int rangecount(vbits *b, int i, int j)
{
	//Limite para contar
	if(i <= 0)
		i = 1;
	if(j > b->size)
		j = b->size;
	int count = 0, k;
	for(k = i; k <= j; k++)
	{
		if(belong(b, k))
			count++;
	}
	return count;
}

int select_bits(vbits *b, int n)
{
	if(n <= 0 || n > b->size)
		return 0;

	int count = 0, sel = 0, i;
	for(i = 1; i <= b->size; i++)
	{
		if(belong(b, i)){
			count++;
			sel = i;
		}
		if(count >= n)
			break;
	}
	return sel;
}
