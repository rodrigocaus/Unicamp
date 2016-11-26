/*
 *  Rodrigo Oliveira Caus
 *  Turma A
 *  Ra:186807
 *
 *  Criação de uma tabela de hashing de 50021
 *  elementos, contendo um par {chave, valor}.
 *  Colisões a serem resolvidas por hashing duplo.
 */

#include "hash.h"

int main(int argc, char **argv)
{
    //Variáveis para leitura
    ulong s_chave;
    int s_valor, aux, tam = 0;
    char menu;
    //Variável para tabela de hashing
    par **tabela;
    tabela = calloc(MAXTAM, sizeof(par *));
    if(!tabela)
        return 1;

    do
    {
        scanf(" %c", &menu);
        switch(menu)
        {
            case 'i':
                //Rotina de inserção
                scanf(" %lu %d", &s_chave, &s_valor);
                tam += insere(s_chave, s_valor, tabela);
                break;
            case 'b':
                //Rotina de busca
                scanf(" %lu", &s_chave);
                aux = buscar(s_chave, tabela);
                //Caso não exista
                if(!tabela[aux])
                    printf("%lu nao existe\n", s_chave);
                else
                    printf("valor para %lu: %d\n", tabela[aux]->chave, tabela[aux]->valor);
                break;
            case 'r':
                //Rotina de remoção
                scanf(" %lu", &s_chave);
                tam -= exclui(s_chave, tabela);
                break;
            default: break;
        }
    }while(menu != 'f');

    limpa(&tabela);
    return 0;
}
