#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"


unsigned int fstring_length(fixstring s) {
    unsigned int length =0,i=0;
    bool aux = true;

    while(i<100 && aux){
        if(s[i]=='\0'){
            aux = false;
        }
        else{
        length += 1;
        }
        i++;
    }

    return length;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool res = true;
    if(fstring_length(s1) == fstring_length(s2)){
        for(unsigned int i = 0; i < fstring_length(s1);i++){
            if(s1[i]!=s2[i]){
                res = false;
            }
        }
    }
    else{
        res = false;
    }

    return res;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool res = true;
    unsigned int length, i = 0;
    if(fstring_length(s1) >= fstring_length(s2)){
        length = fstring_length(s1);
    }
    else{
        length = fstring_length(s2);
    }

    bool aux = true;
    while (i < length && aux == true){
        if(s1[i]<s2[i]){
            res = true;
            aux = false;
        }
        else if(s1[i]>s2[i]){
            res = false;
            aux = false;
        }
        i++;
    }
    return res;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;
    fstring_set(aux,s1);
    fstring_set(s1,s2);
    fstring_set(s2,aux);
}


