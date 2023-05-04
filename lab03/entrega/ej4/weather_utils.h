#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

typedef char* string;

int min_min_temp(WeatherTable array);

void max_temp_year(WeatherTable array, int anos[YEARS], int *punteros_anos[YEARS]);

void max_prec_month(WeatherTable array, string meses[YEARS], string *punteros_meses[YEARS]);

#endif