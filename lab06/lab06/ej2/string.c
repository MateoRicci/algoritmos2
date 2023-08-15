#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

struct _s_string {
    char *content;
    unsigned int length;
};

string string_create(const char *word) {
    string str = NULL;
    str = calloc(1, sizeof(struct _s_string));
    str->length = strlen(word); //tomamos fun strlen de la libreria string.h
    str->content = calloc(str->length+1, sizeof(char)); //como ya la tenemos asignada simplemente la tomamos
    str->content = strncpy(str->content, word, str->length + 1);
    return (str);
}

unsigned int string_length(string str) {
    return (str->length);
}

bool string_less(const string str1, const string str2) {
    int cmp = strcmp(str1->content, str2->content); //La cadena strcmp devuelve un entero mayor que, igual a o menor que cero, según que la cadena a la cual señala s1 sea mayor que, igual a o menor que la cadena que la cadena a la cual señala s2.
    return (cmp < 0);
}

bool string_eq(const string str1, const string str2) {
    int cmp = strcmp(str1->content, str2->content);
    return (cmp == 0);
}

string string_clone(const string str) {
    return (string_create(str->content));
}

string string_destroy(string str) {
    free(str->content);
    free(str);
    str = NULL;
    return (str);
}

void string_dump(string str, FILE *file) {
    fprintf(file, "%s", str->content);
}

const char *string_ref(string str) {
    return (str->content);
}
