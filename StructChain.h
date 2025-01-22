#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>
#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#define HASH_SIZE 32 // 32 Bytes

typedef struct MerkleNode {
    //char hash[HASH_SIZE + 1]; // Hash do nó
    struct MerkleNode* left;  // Filho esquerdo
    struct MerkleNode* right; // Filho direito
    time_t timestampTransacao;
} MerkleNode;


typedef struct chain{

int indice;
time_t timestamp;
unsigned char hashChainAtual[HASH_SIZE + 1] ; // 32 caracteres + o '/n'
unsigned char hashChainAnterior[HASH_SIZE + 1]; // 32 caracteres + o '/n'
long nonceAtual;
// adicionar o ponteiro para a cabeca da merkleTree

} Chain;