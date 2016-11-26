/*
 *	Rodrigo Oliveira Caus
 *	RA 186807
 *
 *	Trabalho cuja função é desenvolver uma
 *	árvore binária de inteiros com pesos nas
 *	arestas, de acordo com a entrada-padrão.
 *  A entrada-padrão consiste na representação
 *  parentizada da árvore, na forma de in-order.
 */

#include "parentizada.h"

int main(int argc, char **argv)
{
    //Buffer e ponteiro pra raiz
    doompalm *bin;

    while (1)
    {
        getchar();
        if(feof(stdin))
            break;
        bin = buildtree();
        printf("%.3f\n", max_peso(bin));
        limpa_tudo(bin);
        getchar(); //para pegar o \n
    }
    bin = NULL;
    return 0;
}
