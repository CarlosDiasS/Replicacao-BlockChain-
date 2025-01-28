#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>
#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#define HASH_SIZE 32     // 32 Bytes
#define MAX_SEVERIDADE 4 // Dificuldade

typedef struct MerkleNode
{
    // char hash[HASH_SIZE + 1]; // Hash do nó
    struct MerkleNode *left;  // Filho esquerdo
    struct MerkleNode *right; // Filho direito
    time_t timestampTransacao;
} MerkleNode;

typedef struct chain
{
    int indice;
    time_t timestamp;
    unsigned char hashChainAtual[HASH_SIZE];
    unsigned char hashChainAnterior[HASH_SIZE];
    long nonceAtual;
    // adicionar o ponteiro para a cabeca da merkleTree

} Chain;

/*
@brief faz o calculo do hash usando a biblioteca openSsl
@param block: Struct para gerar o hash
@param hashGerado: Output do hash

*/
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
/*
@brief usa um laço para exibir o hash em forma hexadecimal
@param hash: hash a ser exibido
 */
void exibirHash(unsigned char *hash)
{

    for (int i = 0; i < HASH_SIZE; i++)
    {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

/*
@brief Converte um hash binário em uma string hexadecimaL
@param hashBin: Ponteiro para o hash binário gerado
@param hashHex: Ponteiro para o buffer onde o hash hexadecimal será armazenado
*/
void HashParaHex(const unsigned char *hashBin, char *hashHex, size_t tamanhoHash)
{
    for (size_t i = 0; i < tamanhoHash; i++)
    {
        sprintf(hashHex + (i * 2), "%02x", hashBin[i]);
    }
    // finaliza a string
    hashHex[tamanhoHash * 2] = '\0';
}

/*
@brief Com base na dificuldade, realiza a mineração do nounce especifico, a fim de alterar o hash
@param bloco: struct para o POW
@param dificuldade: de 1 a 4

*/
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

//analisar viabilidade(cadu)
unsigned char ProofOfWorkShell(Chain *bloco, int dificuldade); 