#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */
#include <assert.h>

pair_t pair_new(int x, int y){
    pair_t res;
    res.fst = x;
    res.snd = y;

    assert(res.fst == x && res.snd == y);

    return res;

}

int pair_first(pair_t p){
    int res;
    res = p.fst;
    assert(res == p.fst);
    return(res);

}

int pair_second(pair_t p){
    int res;
    res = p.snd;
    assert(res == p.snd);
    return(res);
}

pair_t pair_swapped(pair_t p){
    pair_t res;
    int aux = p.fst;
    res.fst = p.snd;
    res.snd = aux;
    
    assert(res.fst == p.snd && res.snd == p.fst);
    return res;
}

pair_t pair_destroy(pair_t p){
    return p;
}
