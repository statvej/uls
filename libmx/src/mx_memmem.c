#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len){
    
    char *temp_big = (char*)big;
    char *temp_little = (char*)little;
    char *last, *cur;

    if(big_len == 0 || little_len == 0){
        return 0;
    }

    if(big_len < little_len){
        return 0;
    }

    if(little_len == 1){
        return mx_memchr(big, (int)*temp_little, big_len);
    }

    last = (char*)temp_big + big_len - little_len;

    for(cur = (char*)temp_big; cur <= last; cur++){
        if(cur[0] == temp_little[0] && mx_memcmp(cur, temp_little, little_len) == 0){
            return cur;
        }
    }

    return 0;

}

