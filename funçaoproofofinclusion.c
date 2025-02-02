#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "StructChain.h"
#include <openssl/evp.h>

int poi(MerkleNode* no, const char* incluido(/*seu hash*/), /*char do Proof of work com sha256(**)  */, int indice){
//(**) tamanho definido da mesma forma que o da arvore,(x * 2)+1, )
    
    //caso base, se encontra na raiz
    if (no->left == NULL && no->right == NULL){
        return strcmp(no->hash, incluido) == 0;//compara as 2 strings, caso iguais, o return pode vir com 1 ou 0, tem ou não tem incluido.
       }


    if(no->left && poi(no->left, incluido, /*prova*/ indice)){// anda para a esquerda e chama a função com uma nova root{
        if (no->right){//verifica existencia de alguem na direita da nova raiz
       strcpy(/*proof[*(indice)++]*/,no->right->hash);//copia o hash do no da direita para o indice trabalhado, depois incrementa pro proximo indice.
        }
        else{
            strcpy(/*proof[*(indice)++]*/, "");//coloca nada, não existe mais a direita, depois incrementa pro proximo indice.

        }
    if(no->right && poi(no->right, incluido, /*prova*/ indice)){// anda para a direita e chama a função com uma nova root{
        if (no->left){//verifica existencia de alguem na esquerda da nova raiz
       strcpy(/*proof[*(indice)++]*/,no->left->hash);//copia o hash do no da esquerda para o indice trabalhado, depois incrementa pro proximo indice.
        }
        else{
            strcpy(/*proof[*(indice)++]*/, "");//coloca nada, não existe mais a esquerda, depois incrementa pro proximo indice.
        }
        return 1;
    }
    return 0; //caso não exista.
}