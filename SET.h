#ifndef _SET_H
    #define _SET_H

    #include "LLRBT.h"
    #include "AVL.h"

    typedef struct set SET;

    SET* set_criar(int tipo);//xx
    bool set_pertence(SET* A, int elemento); //xx
    bool set_inserir(SET* C, int elemento);//xx
    bool set_remover(SET* C, int elemento);//xx
    void set_apagar(SET** C);//xx
    void set_imprimir(SET* C);//xx
    SET* set_uniao(SET* A, SET *B); //xx
    SET* set_interseccao(SET* A, SET* B); //xx

#endif