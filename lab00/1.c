#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length){
    struct bound_data res;
    res.is_lowerbound=0;
    res.is_lowerbound=0;
    res.exists=0;
    unsigned int i = 0;
    int min = arr[0];
    int max = arr[0];
    while (i < length){
        if (min >= arr[i]){
            min = arr[i];
        }
        if (max <= arr[i]){
            max = arr[i];
        }
        if (value == arr[i]){
            res.exists = 1;
            res.where = i;
        }
        i = i + 1;
    }

    if (value>=max){
        res.is_upperbound = 1;
    }
    if (value<=min){
        res.is_lowerbound = 1;
    }

    return res;

}


int main(void) {
    int value=9;
    //
    // TODO: COMPLETAR - Pedir entrada al usuario
    //

    int v1 = 0;
    int v2 = 0;
    int v3 = 0;
    int v4 = 0;

    printf("Ingrese 4 valores para completar el arreglo: \n");
    printf("Ingrese el primer valor: ");
    scanf("%d", &v1);
    printf("Ingrese el segundo valor: ");
    scanf("%d", &v2);
    printf("Ingrese el tercer valor: ");
    scanf("%d", &v3);
    printf("Ingrese el cuarto valor: ");
    scanf("%d", &v4);

    int a[ARRAY_SIZE] = {v1, v2, v3, v4};

    printf("Ingrese un valor para evaluar en la funcion checkbound: ");
    scanf("%d", &value);

    struct bound_data result = check_bound(value, a, ARRAY_SIZE);


    if (result.is_upperbound == 1 && result.exists == 1){
        printf("El valor ingresado es un maximo del arreglo\n");
    }
    else if(result.is_lowerbound == 1 && result.exists == 1){
        printf("El valor ingresado es un minimo del arreglo\n");
    }
    else if(result.is_upperbound == 1){
        printf("El valor ingresado es una cota superior del arreglo\n");
    }
    else if(result.is_lowerbound == 1){
        printf("El valor ingresado es una cota inferior del arreglo\n");
    }

    return EXIT_SUCCESS;
}