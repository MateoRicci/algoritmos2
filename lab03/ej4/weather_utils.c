#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"
#include "weather_utils.h"

string string_months[MONTHS] = {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};

int min_min_temp(WeatherTable array){
    int res = array[1][1][1]._min_temp, aux;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                aux = array[year][month][day]._min_temp;
                if(aux < res){
                    res = aux;
                }
            }
        }
    }

    return res;
}

void max_temp_year(WeatherTable array, int anos[YEARS], int *punteros_anos[YEARS]){
    int aux;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        punteros_anos[year] = &anos[year];
        *punteros_anos[year] = array[year][1][1]._max_temp;
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                aux = array[year][month][day]._max_temp;
                if(aux > *punteros_anos[year]){
                    *punteros_anos[year] = aux;
                }
            }
        }
    }
}

void max_prec_month(WeatherTable array, string meses[YEARS],string *punteros_meses[YEARS]){
    unsigned int aux, res;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        aux = 0;
        res = 0;
        punteros_meses[year] = &meses[year];
        *punteros_meses[year]  = string_months[january];
        aux = array[year][1][1]._rainfall;
        for (month_t month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                aux += array[year][month][day]._rainfall;
            }
            if(res < aux){
                res = aux;
                *punteros_meses[year] = string_months[month];
            }
        }
    }
}