#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub){
    if(!str || ! sub){
        return -2;
    }
    int sub_index = 0;
    while(*str){
        if((*str == *sub) && mx_is_sub(str, sub)){
            return sub_index;
        }

        sub_index++;
        str++;
    }

    return -1;
}

