#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openacc.h>
#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

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
void GerarHashNode(Chain *block, unsigned char *hashGerado);

/*
@brief usa um laço para exibir o hash em forma hexadecimal
@param hash: hash a ser exibido
 */
void exibirHash(unsigned char *hash);

/*
@brief Converte um hash binário em uma string hexadecimaL
@param hashBin: Ponteiro para o hash binário gerado
@param hashHex: Ponteiro para o buffer onde o hash hexadecimal será armazenado
*/
void HashParaHex(const unsigned char *hashBin, char *hashHex, size_t tamanhoHash);

/*
@brief Com base na dificuldade, realiza a mineração do nounce especifico, a fim de alterar o hash
@param bloco: struct para o POW
@param dificuldade: de 1 a 4

*/
unsigned char ProofOfWorkLinear(Chain *bloco, int dificuldade);
