/*
 O cabeçalho de um módulo em C para manipulação de uma arvore Rubro Negra Left Leaning (LLRBT),
que é uma árvore binária de busca com balanceamento:
*/

#ifndef RBT_H
    #define RBT_H

    #include <stdbool.h>

    typedef struct llrbt LLRBT; // Definição do tipo 'LLRBT'.

    LLRBT* llrbt_criar(); // Função para criar uma árvore LLRBT. Caso seja um sucesso retorna um ponteiro para essa estrutura, se não retorna 'NULL'.
    void llrbt_apagar(LLRBT** T); // Função que apaga a árvore.
    bool llrbt_buscar(LLRBT* T, int chave); // Função que busca um elemento na árvore. Retorna 'true' se encontrado e 'false' se não.
    bool llrbt_inserir(LLRBT* T, int chave); // Função para inserir um elemento na árvore. Retorna se a inserção foi bem sucedida.
    bool llrbt_remover(LLRBT* T, int chave); // Função que remove um elemento da árvore. Retorna se a remoção foi bem sucedida.
    void llrbt_imprimir(LLRBT* T); // Função para imprimir todos os elementos em ordem crescente.
    LLRBT* llrbt_uniao(LLRBT* T, LLRBT* C); // Função que realiza a união de duas árvores. Caso seja um sucesso retorna um ponteiro para a árvore que contem a união dos elementos, se não retorna 'NULL'.
    LLRBT* llrbt_interseccao(LLRBT* T, LLRBT* C); // Função que realiza a intersecção de duas árvore. Caso seja um sucesso retorna um ponteiro para a árvore que contem a intersecção dos elementos, se não retorna 'NULL'.

#endif