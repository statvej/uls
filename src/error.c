#include "../inc/uls.h"

void mx_print_intarr( int* intarr, int size){
    for(int i = 0; i < size; i++){
        fprintf(stderr,  "%d  \n", intarr[i]);
    }
}
