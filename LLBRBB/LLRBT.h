#ifndef RBT_H
    #define RBT_H

    #include <stdbool.h>

    typedef struct llrbt LLRBT;

    LLRBT* llrbt_criar();
    void llrbt_apagar(LLRBT** T);
    bool llrbt_buscar(LLRBT* T, int chave);
    bool llrbt_inserir(LLRBT* T, int chave);
    void llrbt_remover(LLRBT* T, int chave);
    void llrbt_imprimir(LLRBT* T);

#endif