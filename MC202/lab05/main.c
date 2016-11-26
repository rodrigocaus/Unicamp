/*
	Rodrigo Oliveira Caus
	186807
	Turma A

	Programa para criação de um vetor de bits
	para um subconjunto de n números naturais,
	utilizando um vetor de unsigned char.

*/

#include "vbits.h"

int main(int argc, char **argv)
{
	char comando[12];
	int ist, last, count;
	vbits b;
	b.size = 0;
	b.vet = NULL;
	do
	{
		scanf("%s", comando);

		if(!strcmp(comando, "create"))	{
			scanf(" %d", &ist);
			b.size = create(&b, ist);
		}
		else if(!strcmp(comando, "add"))	{
			scanf(" %d", &ist);
			add(&b, ist);
		}
		else if(!strcmp(comando, "remove"))	{
			scanf(" %d", &ist);
			re_move(&b, ist);
		}
		else if(!strcmp(comando, "in"))	{
			scanf(" %d", &ist);
			printf("belongs(%d) = %s\n"
				, ist
				, (belong(&b, ist))?"true" : "false");
		}
		else if(!strcmp(comando, "rank"))	{
			scanf(" %d", &ist);
			count = rank(&b, ist);
			//O programa não faz nada se ist for maior que b.size
			if(count != -1)
				printf("rank(%d) = %d\n", ist, count);
		}
		else if(!strcmp(comando, "select"))	{
			scanf(" %d", &ist);
			printf("select(%d) = %d\n", ist, select_bits(&b, ist));
		}
		else if(!strcmp(comando, "rangecount"))	{
			scanf(" %d %d", &ist, &last);
			count = rangecount(&b, ist, last);
			printf("rangecount(%d,%d) = %d\n", ist, last, count);
		}
		else if(!strcmp(comando, "print"))
			print_bits(&b);

	}while(strcmp(comando, "exit"));

	free(b.vet);
	b.vet = NULL;
	return 0;
}
