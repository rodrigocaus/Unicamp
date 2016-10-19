/*
	Lab Casa 06:	Funcionário do ano
	Aluno:	Rodrigo Caus
	Turma:	Q
	RA:		186807
	Descrição:		Header para o lab. Demais descrições estão
					no arquivo da main.
*/
#define __USE_MINGW_ANSI_STDIO 1
	//Macro para gcc no windows
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAXF 100
	//numero máximo de funcionários
#define MAXC 31
	//máximo de caracteres de uma string +1

typedef char string[MAXC];

typedef struct
{
	string nome, nomechefe;
	//Nome do funcionário e do respec. chefe
	short pabsoluta;
	double prelativa;
	//produtividade relativa
	double sal, qualidade;
	//Valores do salário e qualidade
	short nivel, nsub; 
	//Nível hierárquico e numero de subordinados
}funcionario;					

//Função que zera dados de UM funcionário
void zera_funcionario(funcionario *);

//Função que lê os dados de UM funcionário
void le_funcionario(funcionario *);

//Função que lê o nome do chefe e estabelece o subordinado
//Parâmetro principal é um vetor de funcionários
void le_boss(funcionario *, int nfunc);

//Função que descobre o presidente da empresa
//Parâmetro principal é um vetor de funcionários
funcionario *the_presida(funcionario *, int nfunc);

//Função que procura por UM funcionário, cujo nome está contido na string (char *)
//Parâmetro primário é um vetor de funcionários
funcionario *procura(funcionario *, char *, int nfunc);

//Função que calcula o nível hierárquico de UM funcionário
short nivel_hierarquia(funcionario *, funcionario *vetor, int nfunc);

//Função que calcula o número de subordinados de UM funcionário
short n_subordinados(funcionario *, funcionario *vetor, int nfunc);

//Função que calcula o salário relativo de um funcionário, comparado ao do presidente (sal = 1)
double salario_relativo(funcionario *, funcionario *vetor, int nfunc);

//Função que, a partir do salario relativo, calcula o salário numérico
void salario_numerico(funcionario *vetor, int nfunc, double orcamento);

//Função que calcula a produtividade relativa de UM funcionário
double produtividade(funcionario *,funcionario *vetor, int nfunc);

//Função que calcula o log* do enunciado
double log_as(double f);

//Função que calcula a qualidade de UM funcionário
void qualidade(int fator, funcionario *);

//Função que encontra o funcionário de maior qualidade
funcionario *maior_qualidade(funcionario *vetor, int nfunc);