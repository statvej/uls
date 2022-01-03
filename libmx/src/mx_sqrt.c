#include "../inc/libmx.h"

int mx_sqrt(int x){
    if (x <= 0) return 0;

    double sqrt, to_compare;
    sqrt = x / 2;
    to_compare = 0;

    while (sqrt != to_compare) {

        to_compare = sqrt;
        sqrt = (x / to_compare + to_compare) / 2;

    }

    int intResult = (int)sqrt;
    if ((intResult != sqrt) || (sqrt <= 0)) {
        return 0;
    }

    return sqrt;
}
