#include <stdio.h>
#include <stdlib.h>

#include "strfuncs.h"

size_t string_length(const char *str){
    size_t res = 0;
    unsigned int i = 0;
    while(str[i]!='\0'){
        res += 1;
        i += 1;
    }
    return res;
}

char *string_filter(const char *str, char c){
    char *res = NULL;
    size_t length = string_length(str), filtred_length = 0;
    for(unsigned int i = 0;i<length;i++){
        if(str[i]!=c){
            filtred_length ++;
        }
    }

    // reservamos memoria para el nuevo string
    res = malloc(sizeof(char) * filtred_length + 1);
    unsigned int j = 0;
    for(unsigned int i = 0;i<length;i++){
         if(str[i]!=c){
            res[j] = str[i];
            j++;
        }
    }
    res[filtred_length] = '\0';
    return res;
}