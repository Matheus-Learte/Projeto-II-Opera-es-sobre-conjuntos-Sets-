// O cabeçalho de um módulo em C para manipulação de um conjunto de elementos, fazendo o uso de árvores balanceadas:

#ifndef _SET_H
    #define _SET_H

    // Inclui os cabeçalhos para as implementações das árvores LLRBT (Árvore Rubro-Negra) e AVL (Árvore Balanceada), que são usadas na implementação do conjunto.
    #include "LLRBT.h"
    #include "AVL.h"

    typedef struct set SET; // Defnição do tipo 'SET'.

    SET* set_criar(int tipo); // Função para criar um conjunto.
    bool set_pertence(SET* A, int elemento); // Função que verifica se um elemento pertence ao conjunto `A`.
    bool set_inserir(SET* C, int elemento);// Função que insere um elemento no conjunto `C`.
    bool set_remover(SET* C, int elemento);// Função que remove um elemento do conjunto `C`.
    void set_apagar(SET** C);// Função que apaga (desaloca a memória de) o conjunto `C`.
    void set_imprimir(SET* C);// Função que imprime os elementos do conjunto `C`.
    SET* set_uniao(SET* A, SET *B); // Função que retorna a união de dois conjuntos `A` e `B`.
    SET* set_interseccao(SET* A, SET* B); // Função que retorna a interseção de dois conjuntos `A` e `B`.

#endif