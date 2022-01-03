#include "../inc/libmx.h"

double mx_pow(double n, unsigned int pow){
    double result = 1.0;

    for(unsigned int i = 1; i <= pow; i++){
        result *= n;
    }

    return result;
}
