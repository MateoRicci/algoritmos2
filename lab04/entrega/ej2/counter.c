#include <stdbool.h>
#include <stdlib.h>

#include "counter.h"
#include <assert.h>

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter new = malloc(sizeof(unsigned int));
    new->count = 0;
    return new;
}

void counter_inc(counter c) {
    c->count += 1;
}

bool counter_is_init(counter c) {
    bool res;
    if(c->count==0u){
        res = true;
    }
    else{
        res = false;
    }
    return res;
}

void counter_dec(counter c) {
    assert(!counter_is_init(c));
    c->count -= 1;
}

counter counter_copy(counter c) {
    counter copy = counter_init();
    copy->count = c->count;
    return copy;
}

void counter_destroy(counter c) {
    free(c);
}
