/*
	LabSemanal04: Lista Telefônica
	Descrição:	Organização de uma lista telefônica que diferencia contatos pessoais
				de profissionais, faz registro de informações destes contatos (endereço,
				cpf, telefone, celular) e gerencia-os por meio de operações: inserir contato,
				listar contatos, removê-los e alterá-los.
	Entrada:	Contatos pessoais e profissionais representados por inteiros (1 e 2 respectivamente);
				opções de gerenciamento representadas por inteiros:
				0 - Sair;
				1 - inserir;
				2 - excluir;
				3 - alterar;
				4 - buscar;
				5 - listar [contatos] pessoais;
				6 - listar [contatos] profissionais;
				7 -	listar todos.
				São dados cadastrais dos contatos: nome (string), cpf (int de 11 digitos), endereço (string),
				Telefone residencial/comercial (int de 10 digitos, com DDD de 2 digitos) e telefone celular
				(int de 11 digitos, com DDD de 2 digitos).
	Saida:		Sucesso ou insucesso através de mensagens, obedecendo às opções de gerenciamenton na ordem em
				que elas aparecem.

	Autor:	Rodrigo Caus
	RA:		186807
	Turma:	Q
*/
#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define sucesso 1
#define insucesso -1
#define pessoal 1
#define profissional 2 //tipos de contato
#define MAXCONT 10 //máximo de contatos de cada tipo
#define MAXChar 60 //máximo de caracteres 

typedef char string[MAXChar];
//definição de novo tipo de variável: a string, como um char de 60 caracteres

/*
	Neste programa, os vetores serão trabalhados da seguinte forma:
	-inteiros: int variavel[tipo_de_contato][posicao_do_contato];
	-strings: string nome[tipo_de_contato][posicao_do_contato];

*/
	//Funções para opções de gerenciamento de contatos:

int inserir(string nome[2][MAXCONT],long long cpf[2][MAXCONT], string endereco[2][MAXCONT],
			long long telefone[2][MAXCONT],long long celular[2][MAXCONT], int contato[2])
{
	int tipo_contato;
	string nome_inserir, endereco_inserir;
	long long cpf_inserir, telefone_inserir, celular_inserir;
	scanf("\n%d", &tipo_contato);
	scanf(" %[^\n]s", nome_inserir);
	scanf("\n%lld", &cpf_inserir);//Atribuido CPF
	scanf(" %[^\n]s", endereco_inserir);//Atribuindo endereço
	scanf("\n%lld", &telefone_inserir);
	scanf("\n%lld", &celular_inserir);
	//Leitura dos dados a serem inseridos
	if(contato[tipo_contato-1] == MAXCONT)
		return insucesso;
	//Insucesso para agenda lotada (==10 contatos)
	else
	{
		strcpy(nome[tipo_contato-1][contato[tipo_contato-1]], nome_inserir);//Atribuindo o nome
		cpf[tipo_contato-1][contato[tipo_contato-1]] = cpf_inserir;
		strcpy(endereco[tipo_contato-1][contato[tipo_contato-1]], endereco_inserir);
		telefone[tipo_contato-1][contato[tipo_contato-1]] = telefone_inserir;
		celular[tipo_contato-1][contato[tipo_contato-1]] = celular_inserir;
		contato[tipo_contato-1]++; //Subindo um nível da lista de contatos
		return sucesso;
	}
}

int excluir(string nome_excluir, string nome[2][MAXCONT],long long cpf[2][MAXCONT], string endereco[2][MAXCONT],
			long long telefone[2][MAXCONT],long long celular[2][MAXCONT], int contato[2])
{
	int tipo_contato;
	scanf("\n%d", &tipo_contato);
	scanf(" %[^\n]s", nome_excluir);
	//Leitura do nome a ser excluido
	short int count = insucesso;
	//Inicialização com insucesso caso não seja encontrado
	for (int i= 0; i < contato[tipo_contato-1]; i++)
	{
		//Se as strings forem iguais string compare retorna zero
		if (strcmp(nome[tipo_contato-1][i], nome_excluir) == 0)
		{
			count = i;
			break;
		}
	}
	if (count == insucesso)
		return insucesso;
	else
	{
		//Passando todos os contatos para a posição anterior na lista
		for(int i = count; i < (contato[tipo_contato-1]-1); i++)
		{
			strcpy(nome[tipo_contato-1][i], nome[tipo_contato-1][i+1]);
			cpf[tipo_contato-1][i] = cpf[tipo_contato-1][i+1];
			strcpy(endereco[tipo_contato-1][i], endereco[tipo_contato-1][i+1]);
			telefone[tipo_contato-1][i] = telefone[tipo_contato-1][i+1];
			celular[tipo_contato-1][i] = celular[tipo_contato-1][i+1];
		}
		contato[tipo_contato-1]--;
		//Reduz um número na lista de contato do respectivo tipo de contato
		return sucesso;
	}
}

int alterar(string nome_alterar, string nome[2][MAXCONT],long long cpf[2][MAXCONT], string endereco[2][MAXCONT],
			long long telefone[2][MAXCONT],long long celular[2][MAXCONT], int contato[2])
{
	int tipo_contato;
	scanf("\n%d", &tipo_contato);
	scanf(" %[^\n]s", nome_alterar);
	//Leitura do nome a ser alterado
	if(contato[tipo_contato-1] == 0)
		return insucesso;
	//Insucesso para agenda vazia.
	else
	{
		short int count = insucesso;
		//Inicialização com insucesso caso não seja encontrado
		for (int i= 0; i < contato[tipo_contato-1]; i++)
		{
			//Se as strings forem iguais string compare retorna zero
			if (strcmp(nome[tipo_contato-1][i], nome_alterar) == 0)
			{
				count = i;
				break;
			}
		}
		if (count == insucesso)
			return insucesso;
		else
		{
			scanf("%lld\n", &cpf[tipo_contato-1][count]);//Atribuido CPF
			scanf(" %[^\n]s", endereco[tipo_contato-1][count]);//Atribuindo endereço
			scanf("%lld\n", &telefone[tipo_contato-1][count]);
			scanf("%lld\n", &celular[tipo_contato-1][count]);
			return sucesso;
		}
	}
}


int buscar(int tipo_contato, string nome_buscar, string nome[2][MAXCONT], int contato[2])
{
	scanf(" %[^\n]s", nome_buscar);
	//Leitura do nome a ser buscado
	if(contato[tipo_contato-1] == 0)
		return insucesso;
	//Insucesso para agenda vazia.
	else
	{
		short int count = insucesso;
		//Inicialização com insucesso caso não seja encontrado
		for (int i= 0; i < contato[tipo_contato-1]; i++)
		{
			//Se as strings forem iguais string compare retorna zero
			if (strcmp(nome[tipo_contato-1][i], nome_buscar) == 0)
			{
				count = i;
				break;
			}
		}
		return count;
	}
}

void imprimir_contato(int tipo_contato, string nome[2][MAXCONT],long long cpf[2][MAXCONT], string endereco[2][MAXCONT],
					long long telefone[2][MAXCONT],long long celular[2][MAXCONT], int nlista)
{
	printf("%s\n", nome[tipo_contato-1][nlista]);
	printf("%lld\n", cpf[tipo_contato-1][nlista]);
	printf("%s\n", endereco[tipo_contato-1][nlista]);
	printf("%lld\n", telefone[tipo_contato-1][nlista]);
	printf("%lld\n", celular[tipo_contato-1][nlista]);
}

int main (int argc, char *argv[])
{
	string nome[2][MAXCONT], endereco[2][MAXCONT];
	long long cpf[2][MAXCONT], telefone[2][MAXCONT], celular[2][MAXCONT];
	int contato[2] = { 0, 0};
	//Valores de contato para o numero da lista, de 0 a 10
	int menu =0;
	do
	{
		scanf("\n%d", &menu);
		switch(menu)
		{
			case 7:
			{
				//Opção de listar todos os contatos
				if(contato[pessoal-1] == 0)
					printf("Desculpe, agenda vazia!\n");
				else
				{
					for (int i = 0; i < contato[pessoal-1]; i++)
					{
						imprimir_contato(pessoal, nome, cpf, endereco, telefone, celular, i);
					}
					printf("Listado com sucesso!\n");
				}

				if(contato[profissional-1] == 0)
					printf("Desculpe, agenda vazia!\n");
				else
				{
					for (int i = 0; i < contato[profissional-1]; i++)
					{
						imprimir_contato(profissional, nome, cpf, endereco, telefone, celular, i);
					}
					printf("Listado com sucesso!\n");
				}
				break;
			}
			case 6:
			{
				//Opção de listar profissionais
				if(contato[profissional-1] == 0)
					printf("Desculpe, agenda vazia!\n");
				else
				{
					for (int i = 0; i < contato[profissional-1]; i++)
					{
						imprimir_contato(profissional, nome, cpf, endereco, telefone, celular, i);
					}
					printf("Listado com sucesso!\n");
				}
				break;
			}
			case 5:
			{
				//Opção de listar pessoais
				if(contato[pessoal-1] == 0)
					printf("Desculpe, agenda vazia!\n");
				else
				{
					for (int i = 0; i < contato[pessoal-1]; i++)
					{
						imprimir_contato(pessoal, nome, cpf, endereco, telefone, celular, i);
					}
					printf("Listado com sucesso!\n");
				}
				break;
			}
			case 4:
			{
				//Opção de buscar contato
				int tipocontato;
				scanf("%d\n", &tipocontato);
				string nome_buscar;
				int verificador = buscar(tipocontato, nome_buscar,nome,contato);
				if (verificador == insucesso)
					printf("Desculpe, contato %s nao existe!\n", nome_buscar);
				else
				{
					imprimir_contato(tipocontato, nome, cpf, endereco, telefone, celular, verificador);
					printf("Buscado com sucesso!\n");
				}
				break;
			}
			case 3:
			{
				//Opção de alterar contato
				string nome_alterar;
				int verificador = alterar(nome_alterar, nome, cpf, endereco,telefone,celular, contato);
				if(verificador == insucesso)
					printf("Desculpe, contato %s nao existe!\n", nome_alterar);
				else
					printf("Alterado com sucesso!\n");
				break;
			}
			case 2:
			{
				//Opção de excluir contato
				string nome_excluir;
				int verificador = excluir(nome_excluir,nome,cpf,endereco,telefone,celular,contato);
				if(verificador == insucesso)
					printf("Desculpe, contato %s nao existe!\n", nome_excluir);
				else
					printf("Excluido com sucesso!\n");
				break;
			}
			case 1:
			{
				//Opção de inserir contato
				int verificador = inserir(nome,cpf,endereco,telefone,celular,contato);
				if(verificador == insucesso)
					printf("Desculpe, agenda lotada!\n");
				else
					printf("Inserido com sucesso!\n");
				break;
			}
			default:
				break;
		}
	}while(menu!=0);

	printf("Obrigado!\n");
	return 0;
}