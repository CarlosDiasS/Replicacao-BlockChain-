#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "StructChain.h"
#include <openssl/evp.h>

int poi(MerkleNode* no, const char* incluido(/*seu hash), /*char do Proof of work com sha256**  */, int indice){
//** tamanho definido da mesma forma que o da arvore,(x * 2)+1, )
    if (no->left == NULL && no->right == NULL){
        if(no->hash == incluido)
        return 1;
        else
        return 0;

    }
}