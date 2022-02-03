#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size){
    if(size == 0){
        free(ptr);
        return 0;
    }
    else if(!ptr){
        return malloc(size);
    }
    else if(size <= sizeof(ptr)){
        return ptr;
    }
    void *new_ptr = malloc(size);
    mx_memcpy(new_ptr, ptr, sizeof(ptr));
    free(ptr);
    return new_ptr;
    
}

