/*
	LabSemanal 03: Processamento de imagens.
	Descrição:	Dada uma imagem RGB, transformá-la em escala preto e branco
				e aplicar um filtro de saida, gerando uma imagem .pgm.

	Aluno:		Rodrigo Caus
	RA:			186807
	Turma:		Q
*/ 

#include <stdio.h>
#include <math.h>

#define MAX 11
//Valor máximo da ordem da matriz de filtragem
#define Mpixels 601
//Valor máximo de pixels da matriz de imagem

//Matrizes declaradas global para reservar memória no inicio do programa:
int Mfiltro[MAX][MAX];
//Matriz de convolução (filtro)
short int R[Mpixels][Mpixels];
short int G[Mpixels][Mpixels];
short int B[Mpixels][Mpixels];
//Matrizes da imagem nas escalas red, green e blue
short int cinza[Mpixels][Mpixels];
int imagem[Mpixels][Mpixels];
//Matriz de escala cinza e matriz de imagem final

int main(int argc, char *argv[])
{
	int divisor;
	scanf("%d", &divisor);
	short int ord_matriz;
	//Ordem da matriz quadrada de filtragem
	scanf("%hd", &ord_matriz);
	
	//Loop para leitura da matriz de filtro:
	for(int i = 0; i < ord_matriz; i++)
	{
		//Variação de linha
		for (int j = 0; j < ord_matriz; j++)
		{
			//Variação de coluna
			scanf("%d", &Mfiltro[i][j]);
		}
	}

	unsigned short int largura, altura;
	scanf("%hu %hu", &largura, &altura);
	//Largura e altura da imagem em pixels
	unsigned short int loop = 0;
	//Variável auxiliar para o loop de leitura da matriz
	unsigned short int frequencia, intensidade;
	//Pares de leitura da matriz comprimida por RLE
	short int linha, coluna = 0;
	//Auxiliares para manipulação de matrizes

	//Loop para leitura e formação das 3 matrizes da imagem:
	while (loop < 3)
	{
		scanf(" %hu %hu", &frequencia, &intensidade);
		for (int j = 0; j < frequencia; j++)
		{
			if(coluna >= largura)
			{
				coluna = 0;
				linha++;
			}
			if(linha >= altura)
			{
				linha = 0;
				loop++;
			}
			if (loop == 0)
				R[linha][coluna] = intensidade;
			else if (loop == 1)
				G[linha][coluna] = intensidade;
			else if (loop == 2)
				B[linha][coluna] = intensidade;
			coluna++;
		}
	}

	//Atribuição da escala de cinza como média dos valores
	for (int i = 0; i < altura; ++i)
	{
		for (int j = 0; j < largura; j++)
			cinza[i][j] = ((R[i][j])+(G[i][j])+(B[i][j]))/3;
	}
	//Loop para copiar a escala de cinza na imagem resultante, sem filtro
	for (int i = 0; i < altura; ++i)
	{
		for (int j = 0; j < largura; j++)
			imagem[i][j] = cinza[i][j];
	}
	short int borda = (ord_matriz - 1)/2;
	//Define a borda numericamente e o pixel central
	//da matriz quadrada de convolução

	//Aplicação do filtro:
	for (int i = borda; i < (altura - borda); i++)
	{
		//Manipulação das linhas na imagem dentro da borda
		for (int j = borda; j < (largura - borda); j++)
		{
			//Manipulação das colunas na imagem dentro da borda
			int pixel = 0;
			//pixel da imagem[i][j]
			for (short int k = 0; k < ord_matriz; k++)
			{
				//Percorrer linhas da matriz de filtro
				for (short int l = 0; l < ord_matriz; l++)
				{
					//percorrer colunas da matriz de filtro

					pixel += ((cinza[(i-borda)+k][(j-borda)+l])*(Mfiltro[k][l]));
					//Produto elemento por elemento da grade de convolução
				}
			}
			pixel = pixel/divisor;
			imagem[i][j] = pixel;
		}
	}
	//truncamento de valores >255 e <0
	for (int i = 0; i < altura; ++i)
	{
		for (int j = 0; j < largura; j++)
		{
			if(imagem[i][j] <= 0)
				imagem[i][j] = 0;
			if (imagem[i][j] >= 255)
				imagem[i][j] = 255;
		}
	}

	//Sequencia de impressão para a imagem no formato .pgm
	printf("P2\n");
	printf("%hu %hu\n", largura, altura);
	printf("255\n");
	for (int i = 0; i < altura; ++i)
	{
		for (int j = 0; j < largura; j++)
		{
			if (j == (largura-1))
				printf("%d", imagem[i][j]);
			else
				printf("%d ", imagem[i][j]);
		}
		printf("\n");
	}
	return 0;
}