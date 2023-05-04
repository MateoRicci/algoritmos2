#ifndef _ARRAY_HELPERSH
#define _ARRAY_HELPERSH
#include "mybool.h"
mybool array_is_sorted(int a[], unsigned int length);
unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath);
void array_dump(int a[], unsigned int length);
#endif