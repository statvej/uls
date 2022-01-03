#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len){
    if(!b){
        return 0;
    }
    else if(len == 0){
        return b;
    }

    unsigned char us_c = (unsigned char)c;

    for(size_t i = 0; i < len; i++){
        ((char*)b)[i] = us_c;
    }

    return b;

}

