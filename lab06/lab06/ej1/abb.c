#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

//tener muy presente la nocion de recursividad 

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
            invariante &= elem_less(tree->left->elem, tree->elem); //todos los elementos que esten en el arbol izquierdo tiene que ser menores al elemento sobre el que estamos parados
        }
        if (tree->right != NULL){
            invariante &= elem_less(tree->elem,tree->right->elem); //todos los elementos que esten en el arbol derecho tienen que ser mayores al elemento sobre el que estamos parados
        }
        invariante &= invrep(tree->left) && invrep(tree->right); //Hacemos llamados a la funcion recursiva para que se fije en los subarboles
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
    if (tree == NULL){ //si el arbol es vacio
        tree = malloc(sizeof(struct _s_abb)); //reservamos espacio
        tree->elem = e; //le otorgamos el elemento
        tree->left = NULL;
        tree->right = NULL;
    } else { //si no es vacio
        if (!elem_eq(e,tree->elem)){ //mientras el elemento sea distinto a aquel de la raiz 
            if (e < tree->elem){ //buscamos en el subarbol correspondiente dependiendo de si es menor o mayor 
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
    bool res=false; 
    assert(invrep(tree));
    res = (tree == NULL);
    return res;
}

bool abb_exists(abb tree, abb_elem e) {
    bool res = false;
    assert(invrep(tree));
    abb p = tree;
    if (p != NULL){
        res = (tree->elem == e || abb_exists(tree->left,e) || abb_exists(tree->right,e)); 
    }
    return res;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (tree != NULL){
        length += abb_length(tree->right) + abb_length(tree->left) + 1; //En ese 1 se ve representado el tree.elem en el cual estamos parados
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}


abb abb_remove(abb tree, abb_elem e){
    assert(invrep(tree));
    if (!abb_is_empty(tree)){
        if(elem_less(e,tree->elem)){
            tree->left = abb_remove(tree->left,e); //BUSCAMOS EL ELEMENTO E DENTRO DEL ARBOL
        } else if (elem_less(tree->elem,e)){
            tree->right = abb_remove(tree->right,e); //BUSCAMOS EL ELEMENTO E DENTRO DEL ARBOL
        } else {
            abb temp = NULL;
            if (tree->left == NULL) { //Si no existe arbol derecho 
                temp = tree; //Asignamos el puntero a donde se encuentra e actualmente 
                tree = tree->right; //Y conectamos con el arbol restante 
                free(temp);
            } else if (tree->right == NULL) { //Lo mismo con el arbol izquierdo 
                temp = tree;
                tree = tree->left;
                free(temp);
            } else {
                temp = tree->right; //apunta al arbol derecho 
                while(temp && temp->left != NULL){ //Mientras el arbol derecho e izquierdo no sean vacios
                    temp = temp->left; //vamos a recorrer por el lado izquierdo de nuestro arbol
                }
                tree->elem = temp->elem; 
                tree->right = abb_remove(tree->right,temp->elem);
            }
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}

abb_elem abb_root(abb tree) { //devuelve el elemento de esa raiz
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb p = tree;
    while(p->right != NULL){ //el elemento mas grande del arbol se encuentra en la ultima hoja del arbol derecho
        p = p->right;
    }
    max_e = p->elem;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_elem; //el elemento minimo del arbol se encuentra en la ultima hoja del arbol izquierdo
    assert(invrep(tree) && !abb_is_empty(tree));
    abb p = tree;
    while(p->left != NULL){
        p = p->left;
    }
    min_elem = p->elem;
    assert(invrep(tree) && abb_exists(tree, min_elem));
    return min_elem;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree){
    assert(invrep(tree));
    if(!abb_is_empty(tree)){ //si no es vacio
        abb_destroy(tree->right); //destruyo el arbol de la izquierda
        abb_destroy(tree->left); //destruyo el arbol de la derecha 
        free(tree);
    }
    tree = NULL; //cuando lo libero lo apunto a NULL
    assert(tree == NULL);
    return tree;
}
