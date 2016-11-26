/*
 *  Rodrigo Oliveira Caus
 *  Turma A
 *  Ra:186807
 *
 *  Criação de um heap aumentado por vetor
 *  contendo um par {chave, valor}.
 *  O vetor apontará as chaves do par; e o heap
 *  será ordenado pelo mínimo valor do par.
 */

#include "aheap.h"

int main(int argc, char **argv)
{
    //Variáveis para leitura
    ulong s_chave;
    int s_valor;
    char menu;
    //Variável para tabela de heap e vetor
    grupo info;
    scanf(" %d", &s_valor);
    if(inicia(&info, s_valor+1))
        return 1;

    do
    {
        scanf(" %c", &menu);
        switch(menu)
        {
            case 'i':
                //Rotina de inserção
                scanf(" %lu %d", &s_chave, &s_valor);
                info.num += insere(s_chave, s_valor, &info);
                break;
            case 'd':
                //Rotina de alteração de valor
                scanf(" %lu %d", &s_chave, &s_valor);
                diminui(s_chave, s_valor, &info);
                break;
            case 'm':
                //Rotina de remoção
                info.num -= exclui(&info);
                break;
            default: break;
        }
    }while(menu != 't');

    free(info.tabela);
    limpa(&info.heap, info.tam);
    return 0;
}
