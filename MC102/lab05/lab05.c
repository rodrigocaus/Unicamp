/*
	Lab Semanal 05: Análise de Dados
	Descrição:	Programa que analisa dados de um questionário de afini_
			dade entre alunos, e calcula a sintonia entre a pessoa 
			mais popular da turma e seus colegas, exibindo como saí_
			da a pessoa mais afim e seu grau de afinidade.
	
	Aluno:		Rodrigo O. Caus
	Turma:		Q
	RA:		186807

*/
#define __USE_MINGW_ANSI_STDIO 1
	//Macro para gcc no windows
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define max_alunos 41
#define max_arestas 800
#define max_char 201
//string para os nomes dos alunos com máximo de 200 caracteres +1
typedef char string[max_char];

//Definição de um tipo de variável data:
typedef struct
{
	int dia;
	int mes;
	int ano;
}data;

//Definição de um tipo de variável "pessoa", com informações tais
//informações contidas no formulário:
typedef struct
{
	string nome;
	data nascimento;
	char genero;
	//Define o genero da pessoa em questão
	//M para masculino e F para feminino
	char preferencia;
	//Define o genero de preferencia (interesse)
	//da pessoa em questão
}pessoa;

//Definição de um tipo de variável "aresta", que será usada como
//aresta de um grafo, cujos vértices são duas pessoas
typedef struct
{
	pessoa *vertice1;
	pessoa *vertice2;
	double peso;
}aresta;

//ETAPA 01: ORGANIZAÇÃO DOS DADOS -Criação de um Grafo
int formulario(pessoa alunos[], int nota[][max_alunos], int num_alunos, int contador)
{
	scanf("%[^\n]s", alunos[contador].nome);
	scanf("%d/%d/%d ", &alunos[contador].nascimento.dia, &alunos[contador].nascimento.mes, &alunos[contador].nascimento.ano);
	scanf("%c %c\n", &alunos[contador].genero, &alunos[contador].preferencia);
	for(short i = 0; i < num_alunos; i++)
	{
		if(contador == i)
			continue;
		else
			scanf("%d ", &nota[contador][i]);
	}
	return 0;
}
//Funcao apenas intermediaria; nao será usada na main.
int cria_grafo(pessoa alunos[], aresta afinidade[], int num_alunos)
{
	int nota[max_alunos][max_alunos];
	//Matriz para ler as notas do tipo nota[numero_do_aluno][numero_da_respec_nota]
	for (short j = 0; j < num_alunos; j++)
		formulario(alunos, nota, num_alunos, j);

	//Calculamos agora a existência de arestas no grafo
	double peso_aux;
	int num_arestas = 0;
	for (int i = 0; i < num_alunos; i++)
	{
		for (int j = (i+1); j < num_alunos; j++)
		{
			peso_aux = (double) (nota[i][j] * nota[j][i]);
			//Calculo baseado na analise combinatoria das possiveis arestas formadas
			//Uma aresta não é contada duas vezes
			peso_aux = sqrt(peso_aux);
			//Media geometrica das notas
			if (peso_aux >= 5.0)
			{
				afinidade[num_arestas].peso = peso_aux;
				afinidade[num_arestas].vertice1 = &alunos[i];
				afinidade[num_arestas].vertice2 = &alunos[j];
				//Definicao da aresta com o endereco dos vertices (pessoas)
				num_arestas++;
			}
		}
	}
	return num_arestas;
}

//ETAPA 02: ENCONTRAR A PESSOA MAIS POPULAR
int centralidade(pessoa *aluno, aresta afinidade[], int num_arestas)
{
	//Examina o grau de centralidade de cada aluno
	int grau = 0;
	for(short i = 0; i < num_arestas; i++)
	{
		if((aluno==afinidade[i].vertice1)||(aluno==afinidade[i].vertice2))
			grau++;
	}
	return grau;
}
//Funcao apenas intermediaria, nao sera usada na main
pessoa *the_pop(pessoa alunos[], int num_alunos, aresta afinidade[], int num_arestas)
{
	short maior_grau = -1, grau_aux = 0;
	pessoa *mais_pop;
	for(short i = 0; i < num_alunos; i++)
	{
		grau_aux = centralidade(&alunos[i], afinidade, num_arestas);
		if(grau_aux > maior_grau)
		{
			maior_grau = grau_aux;
			mais_pop = &alunos[i];
		}
	}
	return mais_pop;
}

//ETAPA 03: CALCULAR SINTONIA ENTRE PARES DE PESSOAS
//Item a: Algoritmo Soundex
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
//Programa intermediarios
void soundex(pessoa *aluno, char *sound_code)
{
	char nome_aux[max_char];
	char nome_code[5]; //Codigo gerado pelo soundex
	strcpy(nome_aux, aluno->nome);
	//Regra 1 - Reter a primeira letra do nome
	nome_code[0] = nome_aux[0];
	short pos_aux=1, pos=1;
	nome_aux[0] = codificar(tolower(nome_aux[0]));
	//Codifica a primeira letra em minúsculo (tolower)
	for(short i = 1; i<max_char; i++)
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
	strncpy(sound_code, nome_code, 4);
	//Copia apenas os quatro algarismos. Problemas ao compilar com strcpy.
}

//Item b: Numerologia com data de nascimento e idade
int soma_nascimento(int dia, int mes, int ano)
{
	int soma1 = dia+mes;
	int soma2 =0;
	while(ano>0)
	{
		soma2+=ano%10;
		ano=ano/10;
		//Soma os digitos do ano
	}
	soma1 = soma1+soma2;
	while(soma1>10)
	{
		soma2=soma1%10;
		soma1=soma1/10;
		soma1=soma1+soma2;
	}
	return soma1;
}
int idade(int dia_n, int mes_n, int ano_n, int dia_a, int mes_a, int ano_a)
{
	//Compara a data de nascimento (_n) com data atual (_a)
	int idade = ano_a - ano_n;
	if(mes_n>mes_a)
		idade--;
	else if((mes_n==mes_a)&&(dia_n>dia_a))
		idade--;
	//Fazer a idade com apenas 2 digitos
	if(idade<10)
		idade*=10;
	while(idade>=100)
		idade=idade/10;
	return idade;
}
void integer_string(int i, char *s)
{
	//Converte int de três dígitos para string
	char c;
	for(short j = 2; j>(-1); j--)
	{
		int aux=i%10;
		i=i/10;
		switch(aux)
		{
			case 1: c = '1';break;
			case 2: c = '2';break;
			case 3: c = '3';break;
			case 4: c = '4';break;
			case 5: c = '5';break;
			case 6: c = '6';break;
			case 7: c = '7';break;
			case 8: c = '8';break;
			case 9: c = '9';break;
			default: c = '0';break;
		}
		s[j]=c;
	}
}
//Programas intermediários
void numerologia(pessoa *aluno, data *quest, char *numb_code)
{
	int age=idade(aluno->nascimento.dia,aluno->nascimento.mes,aluno->nascimento.ano,quest->dia,quest->mes,quest->ano);
	int numb=soma_nascimento(aluno->nascimento.dia,aluno->nascimento.mes,aluno->nascimento.ano);
	numb=(numb*100)+age;
	integer_string(numb, numb_code);
}
//Item c: Calculo da similaridade
double sim(char *a, char *b)
{
	//Calculo do grau de similaridade entre
	//duas strings
	int count=0;
	int tamanho = strlen(a);
	for(int i = 0; i<tamanho; i++)
	{
		if(a[i]==b[i])
			count++;
	}
	return((double)(count)/(double)(tamanho));
}

int main (int argc, char *argv[])
{
	pessoa alunos[max_alunos];
	aresta afinidade[max_arestas];
	//Leitura da data do questionario
	data quest;
	scanf("%d/%d/%d\n", &quest.dia, &quest.mes, &quest.ano);
	//Leitura do numero de alunos
	short int num_alunos;
	scanf("%hd\n", &num_alunos);
	int num_arestas = cria_grafo(alunos, afinidade, num_alunos);
	//Criação do grafo na main
	pessoa *maispopular = the_pop(alunos, num_alunos, afinidade, num_arestas);
	//Grava o endereço da pessoa mais popular
	char sound_pop[5], numb_pop[4];
	//Variáveis para soundex e numerologia
	//da pessoa mais popular
	soundex(maispopular, sound_pop);
	numerologia(maispopular, &quest, numb_pop);
	//Encontrando a pessoa com maior sintonia
	double maiorsintonia = 0.0, sint_aux;
	pessoa *sintonia;
	char sound_aux[5], numb_aux[4];
	for(int i = 0; i<num_arestas; i++)
	{
		if((afinidade[i].vertice1 == maispopular)&&(maispopular->preferencia == (afinidade[i].vertice2)->genero))
		{
			//O mais popular é o vertice1 e compararemos com o vertice2
			soundex(afinidade[i].vertice2, sound_aux);
			numerologia(afinidade[i].vertice2, &quest, numb_aux);
			sint_aux=3*sim(sound_pop, sound_aux);
			sint_aux+=5*sim(numb_pop, numb_aux);
			sint_aux+=2*((afinidade[i].peso)/10);
			sint_aux=sint_aux/10;
			if(sint_aux>maiorsintonia)
			{
				maiorsintonia = sint_aux;
				sintonia = afinidade[i].vertice2;
			}
		}
		else if ((afinidade[i].vertice2 == maispopular)&&(maispopular->preferencia == (afinidade[i].vertice1)->genero))
		{
			//O mais popular é o vertice2 e compararemos com o vertice1
			soundex(afinidade[i].vertice1, sound_aux);
			numerologia(afinidade[i].vertice1, &quest, numb_aux);
			sint_aux=3*sim(sound_pop, sound_aux);
			sint_aux+=5*sim(numb_pop, numb_aux);
			sint_aux+=2*((afinidade[i].peso)/10);
			sint_aux=sint_aux/10;
			if(sint_aux>maiorsintonia)
			{
				maiorsintonia = sint_aux;
				sintonia = afinidade[i].vertice1;
			}
		}
	}

	printf("%s combina com %s com %.2lf de sintonia s2\n",maispopular->nome,sintonia->nome,maiorsintonia);
	return 0;
}
