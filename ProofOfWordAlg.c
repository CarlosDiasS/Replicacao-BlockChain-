// .c do cadu
#include "StructChain.h"
#include <openssl/evp.h>





// funcao para calcular um hash a partir da struct

// criar tres subfuncoes para definir dificulade(aumentar complexidade da logica)



/*
@brief Com base na dificuldade, realiza a mineração do nounce especifico, a fim de alterar o hash
@param Chain block
@param int dificuldade

*/
char ProofOfWork(Chain *block, int dificuldade)
{

    char *hash;
    char severidade[4];

    if (dificuldade == 1)
    {
        // um zero no inicio do hash
        severidade[0] = '0';

        // fazer um for para preencher o vetor de severidade, ao inves de 4 if
        // uma comparação dentro do while com a subString severidade

        while (1)
        {

            hash = GerarHashNode(block);

            // comparar o hash gerado com o inicio da severidade
            if (strcmp(hash[0], severidade[0]))
            {
                strcpy(hash, block->hashChainAtual);
                // printf('hash minerado com sucesso.');
                return 1;
            }
            else
                block->nonceAtual++;
        }
    }
    if (dificuldade == 2)
    {
        // dois zeros no inicio do hash
    }
    if (dificuldade == 4)
    {
        // tres zeros no inicio do hash
    }
    if (dificuldade == 4)
    {
        // quatro zeros no inicio do hash
    }
    printf("dificuldade invalida: %d", dificuldade);
}

int main(int argc, char const *argv[])
{
    time_t t = time(NULL);
    struct tm *local = localtime(&t);
    // testes

   
    return 0;
}
