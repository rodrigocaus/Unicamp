/*
	Lab Semanal 02: VladMatics
	Descrição: Programa que informa a quantidade de dinheiro público
			   gasto para preencher uma maquete, cujo tema é mate
			   mático, com certa quantia de água, dados uma área 
			   a partir de polígonos convexos, uma altura de 50cm 
			   e um fornecedor fixo de água. A maquete será preen_
			   chida nas sextas feiras 13 e nos aniversários da
			   cidade que realiza o evento, e esvaziada logo depois,
			   durante alguns anos a partir de janeiro de 2016.
			   
	Entrada:   Um inteiro que informa o numero de poligonos (ilhas)
			   na maquete; conjunto de pontos que definem os vérti_
			   ces de cada ilha; a data de aniversário da cidade no
			   formato dia/mes; Ultimo ano em que ocorrerá a expo.
			   (>= 2016); Um numero inteiro de fornecedores de agua;
			   E uma linha para cada fornecedor, contendo a capacida_
			   de do galão em litros, e o preço do galão precedido de
			   $.
	Saída:	   O custo total aos cofres de água para manutenção da maquete.
	
	Autor:	   Rodrigo Oliveira Caus
	RA:		   186807
	Turma:	   Q
	
*/

#include <stdio.h>

int main (int argc, char *argv[])
{
	//variaveis para manipulação dos dados das ilhas:
	int numilhas = 0; //numero de ilhas
	double ilhax1, ilhay1, ilhax2, ilhay2 = 0; //coordenadas serão comparadas duas a duas
	double xprimeiro, yprimeiro = 0; //primeiras coordenadas da ilha.
	double xmax, ymax = -1000.0;
	double xmin, ymin = 1000.0; //coordenadas para definir as bordas da maquete
	double area, areasoma = 0; //area auxiliar para calcular a superficie das ilhas e a area somatória
	short int aux = 0; //variavel auxiliar para realização de contagem
	scanf("%d", &numilhas);
	for (int i = 0; i < numilhas; i++)
	{
		scanf(" (%lf , %lf)", &xprimeiro, &yprimeiro);
		ilhax1 = xprimeiro;
		ilhay1 = yprimeiro;
		//le a primeira coordenada da ilha
		if (xmax < ilhax1)
			xmax = ilhax1;
		if (xmin > ilhax1)
			xmin = ilhax1;
		if (ymax < ilhay1)
			ymax = ilhay1;
		if (ymin > ilhay1)
			ymin = ilhay1;
		//Verificações para decidir as bordas da maquete
		while (aux == 0)
		{
			//Definir leitura de pares de coordenadas
			scanf(" (%lf , %lf)", &ilhax2, &ilhay2);
			//Definir os maximos e minimos
			if (xmax < ilhax2)
				xmax = ilhax2;
			if (xmin > ilhax2)
				xmin = ilhax2;
			if (ymax < ilhay2)
				ymax = ilhay2;
			if (ymin > ilhay2)
				ymin = ilhay2;
			//Definir area pelo Método de Gauss para cálculo da área de um polígono
			area += ((ilhax1*ilhay2) - (ilhax2*ilhay1));
			//Definir reiteração do par de coordenadas
			ilhax1 = ilhax2;
			ilhay1 = ilhay2;
			//Definir condição de quebra de loop (aux != 0)
			if ((ilhax2 == xprimeiro) && (ilhay2 == yprimeiro))
				aux = 1;
			
		}
		//Definir condição de valor absoluto para área e somar à areasoma
		if (area < 0)
			areasoma += (-area);
		else
			areasoma += area;
		area = 0; 
		aux = 0; 
		//zerados para calcular a área da próxima ilha
	}
	areasoma *= (0.5); 
	//Fim do calculo das áreas pelo Método de Gauss
	xmax += (0.5);
	xmin -= (0.5);
	ymax += (0.5);
	ymin -= (0.5);
	//Definição das margens da maquete em 50cm distantes dos limites das ilhas
	double volume = ((xmax-xmin)*(ymax-ymin));
	volume -= areasoma;
	volume *= (0.5); //Calculo final do volume de água em m³
	volume *= 1000; //Volume de água em litros

	short int daniversario, maniversario = 0;
	scanf("%hd/%hd", &daniversario, &maniversario);
	//dia e mes de aniversário da cidade 
	int anomax = 0;
	scanf("%d", &anomax);
	//ultimo ano da exposição
	int aniversario = 0;
	//Dias de aniversario a serem contados
	for (int i = 2016; i <= anomax; i++)
	{
		//Condição para anos não bissextos e aniversario no dia 29
		if((daniversario == 29) && !(((i%4 == 0) && (i%100 != 0)) || i%400 == 0) && (maniversario == 2))
			continue;
		else 
			aniversario++;
	}
	//Dias de sexta 13 a serem contados, exceto os que caem no aniversário da cidade ou adjascentes a este
	int sex13 = 0; 
	short int treze = 0;
	//variavel associada ao dia da semana que cai o dia 13, de 0 (domingo) a 6 (sabado)
	//Começa a contar de 13/12/2015 que cai em um domingo
	for (int i = 2016; i <= anomax; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			//Loop para contar mês a mês de 0 (janeiro) a 11 (dezembro)
			switch(j)
			{
				case 0:
				{
					treze = (treze + (31%7))%7;
					//Soma ao dia da semana os dias do mes anterior modulo sete
					//para descobrir o dia da semana do mes j
					break;
				}
				case 1:
				{
					treze = (treze + (31%7))%7;
					break;
				}
				case 2:
				{
					//Condição para ano bissexto se fevereiro tiver 28 ou 29 dias
					if (((i%4 == 0) && (i%100 != 0)) || i%400 == 0)
						treze = (treze + (29%7))%7;
					else
						treze = (treze + (28%7))%7;
					break;
				}
				case 3:
				{
					treze = (treze + (31%7))%7;
					break;
				}
				case 4:
				{
					treze = (treze + (30%7))%7;
					break;
				}
				case 5:
				{
					treze = (treze + (31%7))%7;
					break;
				}
				case 6:
				{
					treze = (treze + (30%7))%7;
					break;
				}
				case 7:
				{
					treze = (treze + (31%7))%7;
					break;
				}
				case 8:
				{
					treze = (treze + (31%7))%7;
					break;
				}
				case 9:
				{
					treze = (treze + (30%7))%7;
					break;
				}
				case 10:
				{
					treze = (treze + (31%7))%7;
					break;
				}
				case 11:
				{
					treze = (treze + (30%7))%7;
					break;
				}
			}
			if (((daniversario == 12) || (daniversario == 13) || (daniversario == 14)) && (j == (maniversario-1)))
			{
				//Condição para não contarmos dois eventos em dias seguidos
				if (treze == 5)
				{
					//Se treze cair numa sexta feira no mes do aniversario
					continue;
				}
			}
			else if (treze == 5)
				sex13++;
		}
	}
	int eventos = aniversario+sex13;
	
	int fornecedores = 0;
	scanf("%d", &fornecedores);
	//Leitura do numero de fornecedores
	int volumegalao = 0;
	double precogalao = 0;
	scanf("%d $%lf", &volumegalao, &precogalao);
	long long int numgalao = (volume/volumegalao);
	if ((volume/(double)volumegalao) > numgalao)
		numgalao++;
	//Garantir que o numero de galoes seja o maior inteiro da razao volume/volumegalao
	double menorcusto = (double)eventos*numgalao*precogalao;
	for (int i = 0; i < (fornecedores-1); i++)
	{
		scanf("%d $%lf", &volumegalao, &precogalao);
		numgalao = (volume/volumegalao);
		if ((volume/(double)volumegalao) > numgalao)
			numgalao++;
		double custo = (double)eventos*numgalao*precogalao;
		if (custo < menorcusto)
			menorcusto = custo;
	}
	
	printf("A manutencao da maquete custara $%.2lf aos cofres publicos.\n", menorcusto);
	return 0;
}