#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    bool res = true;
    if(d != NULL){
        if (d->left != NULL){
            res &= key_less(d->left->key,d->key);
        }
        if(d->right != NULL){
            res &= key_less(d->key,d->right->key);
        }       
        res &= invrep(d->left) && invrep(d->right);  
    }
    return res;
}

dict_t dict_empty(void) {
    dict_t d = NULL;
    assert(invrep(d) && dict_length(d) == 0u); 
    return d;
}

dict_t dict_add(dict_t d, key_t word, value_t def) {
    assert(invrep(d));
    if (d == NULL){ 
        d = malloc(sizeof(struct _node_t));
        d->key = word;
        d->value = def;
        d->left = NULL;
        d->right = NULL;
    } else {
        if (!key_eq(word,d->key)){
            if (key_less(word,d->key)){
                d->left = dict_add(d->left,word,def);
            } else {
                d->right = dict_add(d->right,word,def);
            }
        } else {
            value_t aux = d->value;
            d->value = def; 
            key_destroy(aux);
        }
    }
    return d;
}

value_t dict_search(dict_t d, key_t word) {
    key_t def=NULL;
    assert(invrep(d));
    if( d != NULL){
        if(key_eq(d->key,word)){
            def = d->value;
        } else {
            if(key_less(d->key,word)){
                def = dict_search(d->right,word); 
            } else {
                def = dict_search(d->left,word);
            }
        }
    }
    assert((def != NULL) == dict_exists(d,word));
    return def;
}

bool dict_exists(dict_t d, key_t word) {
    bool res=false;
    assert(invrep(d));
    dict_t aux = d; 
    while(!res && aux != NULL){
        if(key_less(word, aux->key)){
            aux = aux->left;
        } else if(key_less(aux->key,word)){
            aux = aux->right;
        } else {
            res = true;
        }
    }
    assert(invrep(d));
    return res;
}

unsigned int dict_length(dict_t d) {
    assert(invrep(d));
    unsigned int length=0;
    if (d != NULL){
        length += dict_length(d->right) + dict_length(d->left) + 1; //En ese 1 se ve representado el tree.elem en el cual estamos parados
    }
    return length;
}

dict_t dict_remove(dict_t d, key_t word) {
    assert(invrep(d));
    if(d != NULL){
        if(key_less(word,d->key)){
            d->left = dict_remove(d->left,word);
        } else if(key_less(d->key,word)){
            d->right = dict_remove(d->right,word);
        } else {
                dict_t temp = NULL;
            if (d->left == NULL) {
                temp = d;
                d = d->right;
                free(temp);
            } else if (d->right == NULL) {
                temp = d;
                d = d->left;
                free(temp);
            } else {
                temp = d->right;
                while(temp && temp->left != NULL){
                    temp = temp->left;
                }

                d->key = temp->key;
                d->right = dict_remove(d->right,temp->key);
            }
        }
    }
    assert(invrep(d) && !dict_exists(d, word));
    return d;
}

dict_t dict_remove_all(dict_t d){
    assert(invrep(d));
    if( d != NULL ) {
      dict_remove_all(d->left); 
      dict_remove_all(d->right);
      value_destroy(d->value);
      key_destroy(d->key);
      free(d);
      d = NULL;
    }
    assert(invrep(d) && dict_length(d) == 0);
    return d;
}

void dict_dump(dict_t d, FILE *file) {
    assert(invrep(d) && file != NULL);
    if (d != NULL) {
        dict_dump(d->left, file);
        key_dump(d->key, file);
        fprintf(file, ":");
        value_dump(d->value, file);
        fprintf(file, "\n");
        dict_dump(d->right, file);
    }
    assert(invrep(d));
}

dict_t dict_destroy(dict_t d) {
    assert(invrep(d));
    if(d != NULL){
        dict_destroy(d->right);
        dict_destroy(d->left);
        key_destroy(d->key);
        value_destroy(d->value);
        free(d);
    }
    d = NULL;
    assert(d == NULL);
    return d;
}

