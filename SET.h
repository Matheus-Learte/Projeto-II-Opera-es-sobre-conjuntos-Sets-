#ifndef _SET_H
    #define _SET_H

    #include "LLRBT.h"
    #include "AVL.h"

    typedef struct set SET;

    SET* set_criar(int tipo);
    bool set_pertence(SET* A, int elemento);
    bool set_inserir(SET* C, int elemento);
    bool set_remover(SET* C, int elemento);
    void set_apagar(SET** C);
    void set_imprimir(SET* C);
    SET* set_uniao(SET* A, SET *B);
    SET* set_interseccao(SET* A, SET* B);

#endif