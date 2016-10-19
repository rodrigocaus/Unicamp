/*
	Lab Casa 07:	Gerenciamento de consultas medicas
	Aluno:	Rodrigo Caus
	Turma:	Q
	RA:		186807
	Descrição:	Utilização de alocação dinâmica de memória
				para gerenciar as fichas de diagnósticos
				de consultas médicas em determinado consul-
				tório. Arquivo .c auxiliar de funções.
*/

#include "lablib.h"

int mod26(int n)
{
	//Se a entrada for negativa
	while(n<0)
		n+=26;
	//Retorna numero entre 0 e 26
	return n%26;
}
void lematriz(int matrix[2][2])
{
	scanf(" %d %d\n %d %d", &matrix[0][0], &matrix[0][1], &matrix[1][0], &matrix[1][1]);
}
void codifica(char *s, int matrix[2][2])
{
	char aux[MAXC], prim, seg;
	strcpy(aux, s);
	//Copia s para a auxiliar criada
	for (int i = 0; i < strlen(s); i+=2)
	{
		//Loop para criptografar as letras
		prim = toupper(aux[i]) - 65;
		seg = toupper(aux[i+1]) - 65;
		//Gravando letras duas a duas
		aux[i]= mod26((matrix[0][0]*prim) + (matrix[0][1]*seg)) + 65;
		aux[i+1] = mod26((matrix[1][0]*prim) + (matrix[1][1]*seg)) + 65;
		//Realiza o produto matricial pelo par de letras
	}
	strcpy(s, aux);
	//Copia para s a string codificada
}
void matinversa(int matrix[2][2], int inversa[2][2])
{
	int det, det_menosum = 0;
	//Calculo do det(matrix)
	det = (matrix[0][0]*matrix[1][1]) - (matrix[0][1]*matrix[1][0]);
	//Calculo de det_menosum
	while(mod26(det*det_menosum) != 1)
		det_menosum++;
	//Calculo da inversa
	inversa[0][0] = mod26(det_menosum * matrix[1][1]); 
	inversa[0][1] = mod26(-det_menosum * matrix[0][1]);
	inversa[1][0] = mod26(-det_menosum * matrix[1][0]);
	inversa[1][1] = mod26(det_menosum * matrix[0][0]);
}
void ledoenca(doenca **d, int n)
{
	(*d) = (doenca *) malloc(n*sizeof(doenca));
	for (int i = 0; i < n; i++)
		scanf(" %s %[^\n]s", (*d)[i].cid, (*d)[i].nome);
}
void ledoutor(medico **med, int m)
{
	(*med) = (medico *) malloc(m*sizeof(medico));
	for (int i = 0; i < m; i++)
		scanf(" %lld %[^\n]s", &((*med)[i].crm), (*med)[i].nome);
}
void adiciona(ficha **p, int inversa[2][2])
{
	//Criação de uma nova ficha de paciente
	ficha *novo = (ficha *) malloc(sizeof(ficha));
	ficha *antes, *depois;
	string nomeaux, nometmp;
	scanf(" %s %s %s %lld", nomeaux, novo->data, novo->cid, &novo->crm);
	strcpy(novo->nome, nomeaux);
	//Ordenação na lista de pacientes
	if((*p) == NULL)
	{
		(*p) = novo;
		(*p)->prox = (*p);
		//Inicia a implementação da lista circular
	}
	else
	{
		strcpy(nometmp, (*p)->nome);
		codifica(nomeaux, inversa);
		codifica(nometmp, inversa);
		if(strcmp(nomeaux, nometmp) < 0)
		{
			//Nome a inserir é menor que o nome do primeiro
			antes = (*p);
			depois = (*p)->prox;
			(*p) = novo;
			(*p)->prox = antes;
			//O novo passa a ser o primeiro
			while(depois->prox != antes)
				depois = depois->prox;
			depois->prox = (*p);
			//Implementa a lista circular
		}
		else
		{
			//Nome a inserir depois do primeiro em qualquer posição
			antes = (*p);
			depois = (*p)->prox;
			strcpy(nometmp, depois->nome);
			codifica(nometmp, inversa);
			while(strcmp(nomeaux, nometmp) >= 0)
			{
				//Se o nome for maior, avança os ponteiros na lista
				antes = depois;
				depois = depois->prox;
				strcpy(nometmp, depois->nome);
				codifica(nometmp, inversa);
				//Se voltarmos ao primeiro, o novo é o último
				if(depois == (*p))
					break;
			}
			//Encaixando o novo na lista
			novo->prox = depois;
			antes->prox = novo;
		}
	}
}
void imprimepaciente(ficha *p, int inversa[2][2])
{
	string nomeaux;
	strcpy(nomeaux, p->nome);
	//Traduz o nome para o alfabeto normal
	codifica(nomeaux, inversa);
	printf("%s %s %s %lld\n", nomeaux, p->data, p->cid, p->crm);
}
void imprimelista(ficha *comeco, int inversa[2][2])
{
	ficha *p = comeco->prox;
	imprimepaciente(comeco, inversa);
	//Imprime o primeiro paciente da lista
	while(p != comeco)
	{
		//Imprime todos os outros até retornar ao primeiro
		imprimepaciente(p, inversa);
		p = p->prox;
	}
}
ficha *procuranome(ficha *primeiro, string s, int inversa[2][2])
{
	//Recebe um nome descodificado
	string aux;
	ficha *procura = primeiro;
	//Queremos retornar o elemento cujo próximo tem nome s
	//(Retornemos o anterior a s)
	do
	{
		strcpy(aux, procura->prox->nome);
		codifica(aux, inversa);
		//Pega o nome legível do próximo
		if(!strcmp(aux, s))
			break;
		//Quando igual a s, sai do loop
		procura = procura->prox;
	}while(procura != primeiro);
	return procura;
}
ficha *procuraletra(ficha *primeiro, char c, int inversa[2][2])
{
	char aux[MAXC];
	ficha *procura = primeiro;
	//Queremos retornar o elemento cujo nome inicia-se com c
	do
	{
		strcpy(aux, procura->nome);
		codifica(aux, inversa);
		//Pega o nome legível do próximo
		if(aux[0]==c)
			break;
		//Quando igual a c, sai do loop
		procura = procura->prox;
		if(procura == primeiro)
		{
			procura = procuraletra(primeiro, (((c-65)+1)%26)+65, inversa);
			//Procura pela letra seguinte
			break;
		}
	}while(1);
	return procura;
}
void remover(ficha **primeiro, int inversa[2][2])
{
	ficha *antes, *rem, *depois;
	string aux;
	scanf(" %s", aux);
	antes = procuranome(*primeiro, aux, inversa);
	rem = antes->prox; //É esse que a gente quer remover
	depois = rem->prox;
	antes->prox = depois;
	//Reorganiza a lista
	if(rem == (*primeiro))
		*primeiro = depois;
	//Caso estivermos excluindo o primeiro elemento
	free(rem);
	//Liberamos esse cara
}
void alteradata(ficha *p, int inversa[2][2])
{
	ficha *altera;
	string nomeaux, dataux;
	scanf(" %s %[^\n]s", nomeaux, dataux);
	altera = procuranome(p, nomeaux, inversa); //Pega o anterior
	altera = altera->prox; //Esse que a gente quer alterar
	strcpy(altera->data, dataux);
}
doenca *procurapatologia(doenca *dvetor, int tam, char *s)
{
	doenca *procura;
	//Rotina que acha o nome do parâmetro
	for (int i = 0; i < tam; i++)
	{
		if(!strcmp(dvetor[i].nome, s))
		{
			procura = &dvetor[i];
			break;
		}
	}
	return procura;
}
medico *procuradoutor(medico *medvetor, int tam, char *s)
{
	medico *procura;
	for (int i = 0; i < tam; i++)
	{
		if(!strcmp(medvetor[i].nome, s))
		{
			procura = &medvetor[i];
			break;
		}
	}
	return procura;
}
void alteradiag(ficha *p, int inversa[2][2], doenca *dvetor, int tam)
{
	string nomeaux, doencaux;
	ficha *altera;
	doenca *daux;
	scanf(" %s %[^\n]s", nomeaux, doencaux);
	altera = procuranome(p, nomeaux, inversa);//Pega o anterior
	altera = altera->prox; //É esse que a gente quer alterar
	daux = procurapatologia(dvetor, tam, doencaux);
	strcpy(altera->cid, daux->cid); //Copia o código para o procurado
}
void alteramed(ficha *p, int inversa[2][2], medico *medvetor, int tam)
{
	string nomeaux, medaux;
	ficha *altera;
	medico *doc;
	scanf(" %s %[^\n]s", nomeaux, medaux);
	altera = procuranome(p, nomeaux, inversa);//Pega o anterior
	altera = altera->prox; //É esse que a gente quer alterar
	doc = procuradoutor(medvetor, tam, medaux);
	altera->crm = doc->crm;
}
void liberatudo(ficha **p)
{
	ficha *apaga, *next;
	apaga = (*p)->prox;
	do
	{
		next = apaga->prox;//pega o seguinte
		free(apaga);
		apaga = next;
	}while(apaga != (*p));
	//Vai apagando até chegar ao primeiro
	free((*p));
}