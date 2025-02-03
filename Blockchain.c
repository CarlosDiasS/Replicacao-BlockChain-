//objetivo:
//desenvolver uma aplicação em c que implemente uma blockchain funcional.

// struct blockchain{
//     int indice; 
//     time_t timestamp;
//     int hashPRE;
//     char merkleRoot;
//     char Nonce;
//     int hastAT;
// }bc;

//cada bloco deve armazenar as transações utilizadas(strings com dados ou infos)
//merkle tree para transações

//Funções:

//insertTransaction
//mine
//Printblock
//searchtransaction

// usando o timestamp, podemos otimizar o item d da questão 5,
// pois ao utilizar o insert geramos um novo timestamp, o 
// mesmo sera referencia na busca, cria menos dificuldade.
// podemos implementar uma busca binaria com os timestamp,
// que são progressivos e ordenados.

#include "StructChain.h"

void exibirHash(unsigned char *hash)
{

    for (int i = 0; i < HASH_SIZE; i++)
    {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

void GerarHashNode(Chain *block, unsigned char *hashGerado)
{

    // instancia um novo contexto para o hash
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    // determina o alg sha256 para o hash
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);

    // usa os dados do input para gerar o hash
    EVP_DigestUpdate(ctx, block, sizeof(*block));

    unsigned int aux;

    // endereça o calculo do hash ao parametro de saida
    EVP_DigestFinal_ex(ctx, hashGerado, &aux);

    EVP_MD_CTX_free(ctx);
}

void HashParaHex(const unsigned char *hashBin, char *hashHex, size_t tamanhoHash)
{
    for (size_t i = 0; i < tamanhoHash; i++)
    {
        sprintf(hashHex + (i * 2), "%02x", hashBin[i]);
    }
    // finaliza a string
    hashHex[tamanhoHash * 2] = '\0';
}

unsigned char ProofOfWorkLinear(Chain *bloco, int dificuldade)
{
    if (dificuldade < 1 || dificuldade > MAX_SEVERIDADE)
    {
        printf("dificuldade invalida: %d\n", dificuldade);
        exit(1);
    }

    // tamanho definido
    char severidade[MAX_SEVERIDADE] = {0};

    // cria uma substring de acordo com a dificuldade
    for (int i = 0; i < dificuldade; i++)
    {
        severidade[i] = '0';
    }

    // finaliza a substring com o '\0'
    severidade[dificuldade] = '\0';

    // hash binario(32 bytes)
    unsigned char hash[HASH_SIZE];

    // em tamanho hexadecimal(64 bytes)
    char hexHash[HASH_SIZE * 2 + 1];

    int iteracoes = 0;

    while (1)
    {
        iteracoes++;
        GerarHashNode(bloco, hash);

        HashParaHex(hash, hexHash, HASH_SIZE);

        exibirHash(hash);

        if (strncmp(hexHash, severidade, dificuldade) == 0)
        {
            memcpy(bloco->hashChainAtual, hash, HASH_SIZE);
            printf("hash minerado com sucesso em %d iterações.\n", iteracoes);
            return 1;
        }

        //mineração linear 
        bloco->nonceAtual++;
    }
}
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
