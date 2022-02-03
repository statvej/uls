#include "../inc/libmx.h"

void mx_del_strarr(char ***arr){
    if (arr == 0) {
        return;
    }
    int i = 0;
    while ((*arr)[i] != 0) {
        mx_strdel(&((*arr)[i]));
        i++;
    }
    free(*arr);
    *arr = 0;

}

