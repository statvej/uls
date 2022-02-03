#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n){
    unsigned char *p = (unsigned char*) s1;
    unsigned char *q = (unsigned char*) s2;
    int compare = 0;

    if (s1 == s2){
        return compare;
    }

    while (n > 0){
        if (*p != *q){
            compare = (*p >*q)?1:-1;
            break;
        }
        n--;
        p++;
        q++;
    }
    
    return compare;

}
