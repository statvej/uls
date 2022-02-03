#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len){

    char *temp_dest = (char*)dst;
    char *temp_src = (char*)src;

    char *tmp = (char*)malloc(sizeof(char) * len);

    if(!tmp){
        return 0;
    }

    unsigned int i = 0;

    for(i = 0; i < len; i++){
        *(tmp + i) = *(temp_src + i);
    }
    for(i = 0; i < len; i++){
        *(temp_dest + i) = *(tmp + i);
    }
    free(tmp);

    return (void*) dst;

}

