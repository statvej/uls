#include "../inc/uls.h"

void mx_print_err_longlongintarr(long long int* intarr, int size){
    for(int i = 0; i < size; i++){
        fprintf(stderr,  "%lld  \n", intarr[i]);
    }
}

void mx_print_err_intarr(int* intarr, int size){
    for(int i = 0; i < size; i++){
        fprintf(stderr,  "%d  \n", intarr[i]);
    }
}
