# Replicacao-BlockChain-
Estrutura do BlockChain feita em C 

-usando o timestamp, podemos otimizar o item d da questão 5,
pois ao utilizar o insert geramos um novo timestamp, o 
mesmo sera referencia na busca, cria menos dificuldade.
podemos implementar uma busca binaria com os timestamp,
que são progressivos e ordenados.

biblioteca openSsL

#include <openssl/ssl.h>

https://docs.openssl.org/master/man7/ossl-guide-libcrypto-introduction/#using-algorithms-in-applications

-sera usada para geracao do hash de cada chain e cada transacao(sha-256)

-Ao que for fazer a transacao, ira usar a biblioteca pra codificar o texto em um hash
-Ao que desenvolver o proof of work, ira usar para manipular a geracao do hash 




---------------------------------------------------------------------------------------------
Vamos anotar as calls aqui e o que foi debatido 

09/01

-leitura da documentacao
-ideias iniciais


12/01 

-criacao da struct inicial 
-distribuicao das funcoes 
