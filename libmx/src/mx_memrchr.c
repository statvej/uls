#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n){

    unsigned char us_c = (unsigned char)c;
    unsigned char *temp = (unsigned char*)s;
    int i = mx_strlen((char*)temp) - 1;
    for(size_t j = 0; i >= 0 && j < n; i--, j++){
        if(temp[i] == us_c){
            temp += i;
            return (void*)temp;
        }
    }
    return 0;

}

