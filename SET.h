#ifndef _SET_H
    #define _SET_H

    #include "LLRBT.h"
    #include "AVL.h"

    typedef struct set SET;

    SET* set_criar(int tipo);
    bool set_pertence(SET* A, int elemento); //x
    bool set_inserir(SET* C, int elemento);
    bool set_remover(SET* C, int elemento); //x
    void set_apagar(SET** C); //x
    void set_imprimir(SET* C);
    SET* set_uniao(SET* A, SET *B); //x
    SET* set_interseccao(SET* A, SET* B); //x

#endif