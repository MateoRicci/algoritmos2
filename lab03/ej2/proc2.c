#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
    if (x<0){
        *y = -x;
    }
    else{
        *y = x;
    }
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    int *p = &res;
    a = -10;
    absolute(a,p);
    printf("%d\n", res);

    return EXIT_SUCCESS;
}

