#include "../inc/libmx.h"

void mx_print_strarr(char **arr, const char *delim){
    if(!arr || !delim){
        return;
    }
    int exist = 0;
    int i = 0;

    for(; arr[i + 1]; i++){
        mx_printstr(arr[i]);
        mx_printstr(delim);
        exist = 1;
    }

    mx_printstr(arr[i]);
    if(exist)
        mx_printchar('\n');
}

