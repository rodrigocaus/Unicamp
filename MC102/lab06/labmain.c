/*
	Lab Casa 06:	Funcionário do ano
	Aluno:	Rodrigo Caus
	Turma:	Q
	RA:		186807
	Descrição:	Utilização de programação recursiva para
				determinar o melhor funcionário do ano
				em uma empresa, tendo como base a produtividade,
				o salário, e o nível hierárquico dentro da empresa.
*/

#include "lablib.h"

int main(int argc, char *argv[])
{
	funcionario unicomp[MAXF];
	//Lista de todos os funcionários da empresa
	double orcamento;
	scanf("%lf\n", &orcamento);
	//Valor de orçamento para salarios da empresa
	int fator;
	scanf("%d\n", &fator);
	//Fator de cálculo para a qualidade
	short nfunc;
	scanf("%hd\n", &nfunc);
	//Número de funcionários da empresa
	for(short i = 0; i<nfunc; i++)
	{
		//Rotina de leitura dos funcionários
		zera_funcionario(&unicomp[i]);
		le_funcionario(&unicomp[i]);
	}
	//Atribui o chefe ao funcionário
	for(short i = 0; i<(nfunc-1); i++)
		le_boss(unicomp, nfunc);
	//Rotina de atribuição dos níveis hierárquicos e do numero de subordinados
	for(short i = 0; i<nfunc; i++)
	{
		nivel_hierarquia(&unicomp[i], unicomp, nfunc);
		unicomp[i].nsub=n_subordinados(&unicomp[i], unicomp, nfunc);
	}
	//Rotina de cálculo dos salários relativos (sal <=1.0)
	for(short i = 0; i<nfunc; i++)
		salario_relativo(&unicomp[i], unicomp, nfunc);
	//Calculo dos salários definitivos
	salario_numerico(unicomp, nfunc, orcamento);
	//Rotina do cálculo das produtividades relativas
	for(short i = 0; i<nfunc; i++)
		produtividade(&unicomp[i], unicomp, nfunc);
	//Rotina do cálculo de todas as qualidades
	for(short i = 0; i<nfunc; i++)
		qualidade(fator, &unicomp[i]);
	//Procura pelo melhor funcionário para receber o prêmio
	funcionario *premiado = maior_qualidade(unicomp, nfunc);
	//Resultado: impressão do melhor funcionário e sua nota de qualidade.
	printf("%s %.2lf\n",premiado->nome, premiado->qualidade);
	return 0;
}