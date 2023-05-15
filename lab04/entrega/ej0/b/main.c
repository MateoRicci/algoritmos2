#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

void set_name(name_t new_name, data_t *d) {
    int aux = 0;
    for(unsigned int i = 0 ; i<NAME_MAXSIZE ; i++){
        if(new_name[i]=='\n' && aux!=1){
            aux = 1;
        }
        if(aux){
            d->name[i] = ' ';
        }
        else{
            d->name[i] = new_name[i];
        }
    }
}

int main(void) {

    data_t messi = {"Leo Messi", 35, 169}, *p = NULL;
    print_data(messi);
    p = &messi;
    name_t messi_full_name = "Lionel Messi";
    set_name(messi_full_name, p);
    print_data(messi);

    return EXIT_SUCCESS;
}

