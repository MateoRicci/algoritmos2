#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key; //palabras 
    value_t value; //definiciones de esas palabras 
};


static bool invrep(dict_t d) { //las key deben de estar ordenadas de menor a mayor (por orden alfabetico)
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
    dict_t dict = NULL;
    assert(invrep(dict) && dict_length(dict) == 0u); 
    return dict;
}


dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if (dict == NULL){ 
        dict = malloc(sizeof(struct _node_t)); //reservamos espacio del tamaño del nodo 
        dict->key = word; //le otorgamos su palabra
        dict->value = def; //le damos su definicion
        dict->left = NULL;
        dict->right = NULL;
    } else { //si no es vacio
        if (!key_eq(word,dict->key)){ //mientras la word sea distinta a la que estamos viendo 
            if (key_less(word,dict->key)){ //buscamos en el subarbol correspondiente dependiendo de si es menor o mayor 
                dict->left = dict_add(dict->left,word,def);
            } else {
                dict->right = dict_add(dict->right,word,def);
            }
        } else {
            value_t aux = dict->value; //si la key esta tenemos que actualizar su definicion 
            dict->value = def; 
            key_destroy(aux);
        }
    }
    assert(invrep(dict) && key_eq(def, dict_search(dict,word))); //ver si la definicion es la misma a la que deberia de estar reemplazada
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    key_t def=NULL;
    assert(invrep(dict));
    if( dict != NULL){
        if(key_eq(dict->key,word)){ //si encontramos la key simplemente le asignamos el valor correspondiente a su definicion
            def = dict->value;
        } else {
            if(key_less(dict->key,word)){  //si no lo es lo buscamos segun si la key es mas chica o mas larga (aplicando recursion)
                def = dict_search(dict->right,word); 
            } else {
                def = dict_search(dict->left,word);
            }
        }
    }
    assert((def != NULL) == dict_exists(dict,word));
    return def;
}


bool dict_exists(dict_t dict, key_t word) {
    bool res=false;
    assert(invrep(dict));
    dict_t aux = dict; 
    while(!res && aux != NULL){ //si no existe y el diccionario no termino seguimos buscando
        if(key_less(word, aux->key)){ //si vemos que la word es mas chica que nuestra key nos fijamos en la primera mitad
            aux = aux->left;
        } else if(key_less(aux->key,word)){ //la mitad derecha en caso contrario
            aux = aux->right;
        } else {
            res = true; //Si no es ni menor ni mayor, entonces es igual, por lo tanto podemos decir que existe;
        }
    }
    assert(invrep(dict));
    return res;
}


unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    unsigned int length=0;
    if (dict != NULL){
        length += dict_length(dict->right) + dict_length(dict->left) + 1; //En ese 1 se ve representado el tree.elem en el cual estamos parados
    }
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    if(dict != NULL){
        if(key_less(word,dict->key)){
            dict->left = dict_remove(dict->left,word);
        } else if(key_less(dict->key,word)){
            dict->right = dict_remove(dict->right,word);
        } else {
                dict_t temp = NULL;
            if (dict->left == NULL) {
                temp = dict;
                dict = dict->right;
                free(temp);
            } else if (dict->right == NULL) {
                temp = dict;
                dict = dict->left;
                free(temp);
            } else {
                temp = dict->right;
                while(temp && temp->left != NULL){
                    temp = temp->left;
                }

                dict->key = temp->key;
                dict->right = dict_remove(dict->right,temp->key);
            }
        }
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if( dict != NULL ) { //entro en cada una de las paginas del diccionario 
      dict_remove_all(dict->left); 
      dict_remove_all(dict->right);
      value_destroy(dict->value); //a medida que voy realizando este procedimiento voy liberando cada uno de los elementos 
      key_destroy(dict->key);
      free(dict); //una vez terminado elimino el puntero que apunta a esa hoja con esas def 
      dict = NULL;
    }
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL);
    if (dict != NULL) {
        dict_dump(dict->left, file); //Leo de izquierda a derecha, entonces comienzo de ahi
        key_dump(dict->key, file); //escribe la palabra
        fprintf(file, ":");
        value_dump(dict->value, file); //escribe su definicion
        fprintf(file, "\n");
        //value_dump(dict->value, file);
        dict_dump(dict->right, file); //una vez terminada la primera mitad, realizamos el mismo proceso con la segunda
    }
}
//Aunque a medida que realiza el proceso, se va particionando mas hasta llegar a una hoja (asi funciona la recursion xd)

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL){
        dict_destroy(dict->right);
        dict_destroy(dict->left);
        key_destroy(dict->key);
        value_destroy(dict->value);
        free(dict);
    }
    dict = NULL; //mismo procedimiento que con dict_remove_all;
    assert(dict == NULL);
    return dict;
}
