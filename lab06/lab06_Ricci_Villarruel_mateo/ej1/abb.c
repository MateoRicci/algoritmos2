#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    bool invariante = true;
    if(tree != NULL){
        if (tree->left != NULL){
            invariante &= elem_less(tree->left->elem, tree->elem); //Invariante sobre la izquierda
        }
        if (tree->right != NULL){
            invariante &= elem_less(tree->elem,tree->right->elem); //Invariante sobre la derecha
        }
        invariante &= invrep(tree->left) && invrep(tree->right); //Recursion
    }
    return invariante;
}

abb abb_empty(void) {
    abb tree;
    tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree == NULL){ //Chequeo si el arbol es vacio
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    } else {
        if (!elem_eq(e,tree->elem)){
            if (e < tree->elem){
                tree->left = abb_add(tree->left,e);
            } else {
                tree->right = abb_add(tree->right,e);
            }
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));
    is_empty = (tree == NULL);
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    assert(invrep(tree));
    abb aux = tree;
    if (aux != NULL){
        exists = (tree->elem == e || abb_exists(tree->left,e) || abb_exists(tree->right,e)); 
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (tree != NULL){
        length += abb_length(tree->right) + abb_length(tree->left) + 1; // usamos recursividad para abarcar todo el arbol
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (!abb_is_empty(tree)){
        if(elem_less(e,tree->elem)){
            tree->left = abb_remove(tree->left,e); //busca el elemento
        } else if (elem_less(tree->elem,e)){
            tree->right = abb_remove(tree->right,e); //busca el elemento
        } else {
            abb temp = NULL;
            if (tree->left == NULL) {
                temp = tree;
                tree = tree->right;
                free(temp);
            } else if (tree->right == NULL) {
                temp = tree;
                tree = tree->left;
                free(temp);
            } else {
                temp = tree->right;
                while(temp && temp->left != NULL){
                    temp = temp->left;
                }
                tree->elem = temp->elem; 
                tree->right = abb_remove(tree->right,temp->elem);
            }
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb aux = tree;
    while(aux->right != NULL){
        aux = aux->right;
    }
    max_e = aux->elem;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb aux = tree;
    while(aux->left != NULL){
        aux = aux->left;
    }
    min_e = aux->elem;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(!abb_is_empty(tree)){ //si no es vacio
        abb_destroy(tree->right); //destruyo el arbol de la izquierda
        abb_destroy(tree->left); //destruyo el arbol de la derecha 
        free(tree);
    }
    tree = NULL; //lo apunto a NULL
    assert(tree == NULL);
    return tree;
}

