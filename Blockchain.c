#include <stdio.h>
#include "StructChaain.h"
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