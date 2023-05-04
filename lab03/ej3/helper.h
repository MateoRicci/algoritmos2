#ifndef _HELPERH
#define _HELPERH
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *parse_filepath(int argc, char *argv[]);

void dump_char(char a[], unsigned int length);

void dump_int(unsigned int a[], unsigned int length);

void array_copy(char array[], char array_to_copy[], char *punteros[], unsigned int length);

void swap_char(char array[], unsigned int i, unsigned int j);

void swap_nums(unsigned int array[], unsigned int i, unsigned int j);

void sorting(unsigned int indexes[], char letters[], unsigned int length);

#endif