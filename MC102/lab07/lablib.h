/*
	Lab Casa 07:	Gerenciamento de consultas medicas
	Aluno:	Rodrigo Caus
	Turma:	Q
	RA:		186807
	Descrição:	Utilização de alocação dinâmica de memória
				para gerenciar as fichas de diagnósticos
				de consultas médicas em determinado consul-
				tório. Arquivo header auxiliar.
*/
#define __USE_MINGW_ANSI_STDIO 1
	//macro para gcc no windows
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXC 101
	//máximo de caracteres de uma string +1

typedef char string[MAXC];

typedef struct
{
	string nome;
	char cid[4];
}doenca;

typedef struct
{
	string nome;
	long long crm;	
}medico;

typedef struct paciente
{
	string nome;
	string data;
	char cid[4];
	long long crm;
	struct paciente *prox;
	//Endereco para a lista ligada
}ficha;

//Funcao que retorna o mod26 positivo de um numero qualquer
int mod26(int n);
//Funcao que le uma matriz 2x2
void lematriz(int matrix[2][2]);
//Funcao que codifica um nome pela Cifra de Hill 2x2
void codifica(char *s, int matrix[2][2]);
//Calcula a matriz inversa para a Cifra de Hill 2x2
void matinversa(int matrix[2][2], int inversa[2][2]);
//Função que lê n doenças criando um vetor
void ledoenca(doenca **d, int n);
//Função que lê m médicos criando um vetor
void ledoutor(medico **med, int m);
//Função que adiciona um paciente à lista ordenadamente
//Recebe como parametro um endereço de um pointer pro primeiro da lista
void adiciona(ficha **, int matrix[2][2]);
//Função que imprime paciente
void imprimepaciente(ficha *, int matrix[2][2]);
//Função para imprimir a lista toda
void imprimelista(ficha *comeco, int matrix[2][2]);
//Função que procura pelo nome na lista
ficha *procuranome(ficha *p, string s, int matrix[2][2]);
//Função que procura pela letra na lista
ficha *procuraletra(ficha *p, char c, int matrix[2][2]);
//Remove um nome especificado
void remover(ficha **p, int matrix[2][2]);
//Função para alterar data de consulta
void alteradata(ficha *p, int matrix[2][2]);
//Função que procura por doença especifica em um vetor
doenca *procurapatologia(doenca *, int tam, char *);
//Função que procura por um médico específico em um vetor
medico *procuradoutor(medico *, int tam, char *);
//Alterar o diagnóstico
void alteradiag(ficha *, int matrix[2][2], doenca *, int tam);
//Função para alterar o médico
void alteramed(ficha *, int matrix[2][2], medico *, int tam);
//Função para desalocar a memória alocada
void liberatudo(ficha **p);