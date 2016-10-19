/*
	Lab Casa 06:	Funcionário do ano
	Aluno:	Rodrigo Caus
	Turma:	Q
	RA:		186807
	Descrição:		Arquivo auxiliar para o lab. Demais 
					descrições estão no arquivo da main.
*/

#include "lablib.h"

void zera_funcionario(funcionario *unicomp)
{
	strcpy(unicomp->nomechefe, "");
	unicomp->prelativa = -1.0;
	unicomp->sal = -1.0;
	unicomp->qualidade = 0.0;
	unicomp->nivel = 0;
	unicomp->nsub = 0;
}
void le_funcionario(funcionario *unicomp)
{
	scanf("%s %hd\n", unicomp->nome, &(unicomp->pabsoluta));
}
void le_boss(funcionario *Fvetor, int nfunc)
{
	string nomeaux, chefeaux;
	scanf("%s %s\n", nomeaux, chefeaux);
	for (int i = 0; i<nfunc; i++)
	{
		//Procura pela pessoa cujo nome é "nomeaux"
		if(strcmp(Fvetor[i].nome, nomeaux) == 0)
		{
			strcpy(Fvetor[i].nomechefe, chefeaux);
			break;
			//Estabelece o chefe de "nomeaux"
		}
	}
}
funcionario *the_presida(funcionario *Fvetor, int nfunc)
{
	int i = 0;
	for (i = 0; i<nfunc; i++)
	{
		//O presidente é aquele que não tem chefe
		if(strcmp(Fvetor[i].nomechefe, "") == 0)
			break;
	}
	return &Fvetor[i];
}
funcionario *procura(funcionario *Fvetor, string nome_busca, int nfunc)
{
	int i = 0;
	for (i = 0; i<nfunc; i++)
	{
		//O presidente é aquele que não tem chefe
		if(strcmp(Fvetor[i].nome, nome_busca) == 0)
			break;
	}
	return &Fvetor[i];
}
short nivel_hierarquia(funcionario *unicomp, funcionario *Fvetor, int nfunc)
{
	short level;
	//Caso o nivel não tenha sido definido
	if(unicomp->nivel == 0)
	{
		//Caso base: se o funcionario não tiver chefe (presidente)
		if(strcmp(unicomp->nomechefe, "") == 0)
			level = 1;
		else
		{
			funcionario *chefe;
			//Ponteiro para funcionario, auxiliar.
			chefe=procura(Fvetor, unicomp->nomechefe, nfunc);
			//Procura no vetor de funcionários pelo chefe do 
			//empregado em questão
			level = 1 + nivel_hierarquia(chefe, Fvetor, nfunc);
			//Uso recursivo para achar o nível do chefe
		}
		//Altera o nivel em meio à recursividade
		unicomp->nivel = level;
		return level;
	}
	//Caso já tenha nível definido
	else
		return unicomp->nivel;
}
short n_subordinados(funcionario *unicomp, funcionario *Fvetor, int nfunc)
{
	short contador = 0;
	for (short i = 0; i<nfunc; i++)
	{
		if(strcmp(Fvetor[i].nomechefe, unicomp->nome) == 0)
			contador++;
	}
	return contador;
}
double salario_relativo(funcionario *unicomp, funcionario *Fvetor, int nfunc)
{
	double money;
	//Caso o salário não tenha sido definido
	if(unicomp->sal == -1.0)
	{
		//Caso base: presidente (não tem chefe)
		if(strcmp(unicomp->nomechefe, "") == 0)
			money = 1.0;
		else
		{
			funcionario *chefe;
			//Ponteiro para funcionario, auxiliar.
			chefe=procura(Fvetor, unicomp->nomechefe, nfunc);
			//Procura no vetor de funcionários pelo chefe do 
			//empregado em questão
			money = (((double)chefe->nsub)/(1.0+(double)chefe->nsub));
			money*=(salario_relativo(chefe, Fvetor, nfunc));
			//Uso recursivo para achar o salário do chefe
		}
		unicomp->sal = money;
		return money;
	}
	//Caso já tenha o salário calculado
	else
		return unicomp->sal;
}
void salario_numerico(funcionario *Fvetor, int nfunc, double orcamento)
{
	//Descobrindo o presidente
	funcionario *presidente = the_presida(Fvetor, nfunc);
	double Csal = 0.0;
	//Constante para cálculo do salário numérico
	for(short i = 0; i<nfunc; i++)
		Csal +=Fvetor[i].sal;
	//Definição do salário do presidente
	presidente->sal = orcamento/Csal;
	//Definição dos demais salários
	for(short i = 0; i<nfunc; i++)
	{
		if(&Fvetor[i] == presidente)
			continue;
		else
			Fvetor[i].sal *= (presidente->sal);
	}
}
double produtividade(funcionario *unicomp, funcionario *Fvetor, int nfunc)
{
	//Se ainda não fora definida a produtividade relativa
	if(unicomp->prelativa == -1.0)
	{
		//se "unicomp" não tiver subordinados (caso base)
		if(unicomp->nsub == 0)
			unicomp->prelativa = (double) unicomp->pabsoluta;
		else
		{
			double paux =0.0;
			//produtividade auxiliar
			for (short i = 0; i<nfunc; i++)
			{
				//Caso o funcionário analisado seja
				//subordinado de "unicomp" (funcionário de entrada)
				if(strcmp(Fvetor[i].nomechefe, unicomp->nome) == 0)
					paux += produtividade(&Fvetor[i], Fvetor, nfunc);
				//Soma a produtividade relativa
			}
			paux = paux/((double) unicomp->nsub);
			//Divide pelo número de subordinados
			paux += (double) unicomp->pabsoluta;
			//Soma à produtividade absoluta
			paux *= 0.5;
			unicomp->prelativa = paux;
			//atribui o valor
		}
	}
	return unicomp->prelativa;
}
double log_as(double f)
{
	double resultado;
	if(f <=1.0)
		resultado = 0.0;
	else
		resultado = 1.0 + log_as(log2(f));
	return resultado;
}
void qualidade(int fator, funcionario *unicomp)
{
	//Apenas seguindo a fórmula do enunciado
	double q = (unicomp->prelativa)/(log2(unicomp->sal));
	q *= (log_as((double)unicomp->nivel)+1);
	q *= fator;
	unicomp->qualidade = q;
}
funcionario *maior_qualidade(funcionario *Fvetor, int nfunc)
{
	double q = 0.0, qaux;
	funcionario *faux;
	//Variaveis auxiliares
	for (int i = 0; i < nfunc; i++)
	{
		qaux = Fvetor[i].qualidade;
		//Procura pela maior qualidade
		if(qaux > q)
		{
			faux= &Fvetor[i];
			q = qaux;
		}
	}
	return faux;
}