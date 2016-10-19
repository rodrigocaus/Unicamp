/*
	Lab Casa 07:	Gerenciamento de consultas medicas
	Aluno:	Rodrigo Caus
	Turma:	Q
	RA:		186807
	Descrição:	Utilização de alocação dinâmica de memória
				para gerenciar as fichas de diagnósticos
				de consultas médicas em determinado consul-
				tório. Arquivo .c principal.
*/

#include "lablib.h"

int main(int argc, char **argv)
{
	int matrix[2][2], inversa[2][2], ndoenca, nmed;
	char letra; //Letra de preferencia
	string menu;
	doenca *sick = NULL;
	medico *doutor = NULL;
	ficha *primeiro = NULL, *iniciar;
	//Ponteiros para os primeiros elementos dos vetores/lista ligada
	scanf(" %d", &ndoenca);
	ledoenca(&sick, ndoenca);
	//Leitura das n doenças
	scanf(" %d", &nmed);
	ledoutor(&doutor, nmed);
	//Leitura dos m médicos;
	lematriz(matrix);
	matinversa(matrix, inversa);
	scanf(" %c", &letra);
	//Assegurar que a letra é maiúscula
	letra = toupper(letra);
	//Rotina de operações de gerenciamento
	do
	{
		scanf("\n%s", menu);
		if(!strcmp(menu,"add"))
			adiciona(&primeiro, inversa);
		
		else if (!strcmp(menu, "rm"))
			remover(&primeiro, inversa);

		else if (!strcmp(menu, "altdata"))
			alteradata(primeiro, inversa);
		
		else if (!strcmp(menu, "altdiag"))
			alteradiag(primeiro, inversa, sick, ndoenca);

		else if (!strcmp(menu, "altmed"))
			alteramed(primeiro, inversa, doutor, nmed);
		else
			break;
	}while(1);
	iniciar = procuraletra(primeiro, letra, inversa);
	imprimelista(iniciar, inversa);
	//Realiza a impressão conforme letra
	free(sick);
	free(doutor);
	//Libera memória alocada para os vetores
	liberatudo(&primeiro);
	//Libera a memória da lista encadeada
	return 0;
}