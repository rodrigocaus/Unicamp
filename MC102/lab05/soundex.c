#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef char string[30];

char codificar(char c)
{
	//funcao que codifica uma letra conforme enunciado
	char conversao;
	switch(c)
	{
		case 'g':
		case 'j':
			conversao = '1';
			break;
		case 's':
		case 'z':
		case 'x':
			conversao = '2';
			break;
		case 'c':
		case 'k':
		case 'q':
			conversao = '3';
			break;
		case 'b':
		case 'p':
			conversao = '4';
			break;
		case 'm':
		case 'n':
			conversao = '5';
			break;
		case 'd':
		case 't':
			conversao = '6';
			break;
		case 'f':
		case 'v':
			conversao = '7';
			break;
		case 'l':
			conversao = '8';
			break;
		case 'r':
			conversao = '9';
			break;
		default:
			conversao = '@';
			break;
	}
	return conversao;
}

void soundex(char *sound_code)
{
	char nome_aux[30];
	char nome_code[5]; //Codigo gerado pelo soundex
	strcpy(nome_aux, sound_code);
	//Regra 1 - Reter a primeira letra do nome
	nome_code[0] = nome_aux[0];
	short pos_aux=1, pos=1;
	nome_aux[0] = codificar(tolower(nome_aux[0]));
	//Codifica a primeira letra em minúsculo (tolower)
	for(short i = 1; i<30; i++)
	{
		if(nome_aux[i] == ' ' ||nome_aux[i] == '\0')
			break;
		//parando no espaço ou no fim
		if(codificar(nome_aux[i]) == nome_aux[pos_aux-1])
			continue;
		else
		{
			nome_aux[pos_aux] = codificar(nome_aux[i]);
			pos_aux++;
		}
	}
	for(short i = 1; i<pos_aux; i++)
	{
		if(nome_aux[i]!='@')
		{
			nome_code[pos]=nome_aux[i];
			pos++;
		}
	}
	//Copiando o código feito para as consoantes (Regra 5)
	if(pos < 4)
	{
		while(pos < 4)
		{
			nome_code[pos] = '0';
			pos++;
		}
	}
	strcpy(sound_code, nome_code);
}

int main (int argc, char *argv[])
{
	string nome;
	scanf("%[^\n]s", nome);
	soundex(nome);
	printf("%s\n", nome);
	return 0;
}