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

        // mineração linear
        bloco->nonceAtual++;
    }
}

MerkleNode *create_leaf(const char *data)
{
    MerkleNode *node = (MerkleNode *)malloc(sizeof(MerkleNode));
    if (!node)
    {
        fprintf(stderr, "Erro ao alocar memória para o nó folha.\n");
        exit(EXIT_FAILURE);
    }
    calculate_hash(data, node->hash);
    node->left = NULL;
    node->right = NULL;
    return node;
}

MerkleNode *create_parent(MerkleNode *left, MerkleNode *right)
{
    MerkleNode *node = (MerkleNode *)malloc(sizeof(MerkleNode));
    if (!node)
    {
        fprintf(stderr, "Erro ao alocar memória para o nó pai.\n");
        exit(EXIT_FAILURE);
    }

    char combined[2 * HASH_SIZE + 1]; // combinação dos hashes dos filhos
    snprintf(combined, sizeof(combined), "%s%s", left->hash, right->hash);

    calculate_hash(combined, node->hash);
    node->left = left;
    node->right = right;
    return node;
}

NodeList build_merkle_tree(char **transactions, int num_transactions)
{
    int num_nodes = num_transactions;
    MerkleNode **current_level = (MerkleNode **)malloc(num_nodes * sizeof(MerkleNode *));

    // cria nós folhas
    for (int i = 0; i < num_transactions; i++)
    {
        current_level[i] = create_leaf(transactions[i]);
    }

    // itera para construir a árvore
    while (num_nodes > 1)
    {
        int parent_count = (num_nodes + 1) / 2; // número de nós na próxima camada
        MerkleNode **parent_level = (MerkleNode **)malloc(parent_count * sizeof(MerkleNode *));

        for (int i = 0, j = 0; i < num_nodes; i += 2, j++)
        {
            MerkleNode *left = current_level[i];
            MerkleNode *right = (i + 1 < num_nodes) ? current_level[i + 1] : left; // duplicar último nó, se necessário
            parent_level[j] = create_parent(left, right);
        }

        free(current_level);
        current_level = parent_level;
        num_nodes = parent_count;
    }

    NodeList result = {.nodes = current_level, .size = 1};
    return result;
}

void free_merkle_tree(MerkleNode *root)
{
    if (!root)
        return;
    free_merkle_tree(root->left);
    free_merkle_tree(root->right);
    free(root);
}

void print_merkle_tree(MerkleNode *root, int level)
{
    if (!root)
        return;
    for (int i = 0; i < level; i++)
        printf("  ");
    printf("%s\n", root->hash);
    print_merkle_tree(root->left, level + 1);
    print_merkle_tree(root->right, level + 1);
}

int poi(MerkleNode *no, const char *incluido, char proofhash[][HASH_SIZE * 2 + 1], int indice)
{
    // em proofhash, temos o tamanho definido pelo tamanho padrão do hash, 32bits vezes 2, para cada char ter espaço +1 para o caracter \0 no fim.

    // caso base, se encontra na raiz
    if (no->left == NULL && no->right == NULL)
    {
        // compara as 2 strings, caso iguais, o return pode vir com 1 ou 0, tem ou não tem incluido.
        return strcmp(no->hash, incluido) == 0;
    }

    // anda para a esquerda e chama a função com uma nova root
    if (no->left && poi(no->left, incluido, proofhash, indice))
    {
        // verifica existencia de alguem na direita da nova raiz
        if (no->right)
        {
            // copia o hash do no da direita para o indice trabalhado, depois incrementa pro proximo indice.
            strcpy(proofhash[indice], no->right->hash);
            (indice)++;
        }
        else
        {
            // coloca nada, não existe mais a direita, depois incrementa pro proximo indice.
            strcpy(proofhash[indice], "");
            (indice)++;
        }
        // encontrado na esquerda
        return 1;
    }

    // anda para a direita e chama a função com uma nova root{
    if (no->right && poi(no->right, incluido, proofhash, indice))
    {
        // verifica existencia de alguem na esquerda da nova raiz
        if (no->left)
        {
            // copia o hash do no da esquerda para o indice trabalhado, depois incrementa pro proximo indice.
            strcpy(proofhash[indice], no->left->hash);
            (indice)++;
        }
        else
        {
            // coloca nada, não existe mais a esquerda, depois incrementa pro proximo indice.
            strcpy(proofhash[indice], "");
            (indice)++;
        }
        // encontrado na direita
        return 1;
    }
    // caso não exista nó.
    return 0;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
