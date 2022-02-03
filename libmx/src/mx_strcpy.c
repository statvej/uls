#include "../inc/libmx.h"

char *mx_strcpy(char *dst, const char *src){
    int index = 0;
    for(; src[index]; index++){
        dst[index] = src[index];
    }

    dst[index] = '\0';
    return dst;
}
