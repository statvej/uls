#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n){
    size_t length = 0;
    unsigned char us_c = (unsigned char)c;
    unsigned char *temp = (unsigned char*)s;
    while(length < n){
        if(*temp == us_c){
            return (void *)temp;
        }
        
        temp++;
        length++;
    }

    return NULL;

}

