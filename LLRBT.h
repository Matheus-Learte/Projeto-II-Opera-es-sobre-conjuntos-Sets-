 /*
 O cabeçalho de um módulo em C para manipulação de uma árvore Rubro-Negra (Left-Learning Red-Black Tree), que é uma árvore binária de busca balanceada:
 */ 

#ifndef RBT_H
    #define RBT_H

    #include <stdbool.h> // Biblioteca para manipulação de booleanos.

    typedef struct llrbt LLRBT; // Defnição do tipo 'LLRBT'.

    LLRBT* llrbt_criar(); // Função para criar uma árvore LLRBT.
    void llrbt_apagar(LLRBT** T); // Função para apagar a árvore.
    bool llrbt_buscar(LLRBT* T, int chave); // Função para buscar um elemento na árvore.
    bool llrbt_inserir(LLRBT* T, int chave); // Função para inserir um elemento na árvore.
    bool llrbt_remover(LLRBT* T, int chave); // Função para remover um elemento da árvore.
    void llrbt_imprimir(LLRBT* T); // Função para imprimir os elementos, em ordem crescente, da árvore.
    LLRBT* llrbt_uniao(LLRBT* T, LLRBT* C); // Função para realizar a união de duas árvores.
    LLRBT* llrbt_interseccao(LLRBT* T, LLRBT* C); // Função para realizar a intersecção de duas árvores.

#endif