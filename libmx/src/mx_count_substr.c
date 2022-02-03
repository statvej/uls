#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub){
    if(!str || !sub){
        return -1;
    }
    else if(mx_strlen(sub) == 0){
        return 0;
    }
    
    int counter = 0;

    while(*str){
        if(*str == *sub && mx_is_sub(str, sub)){
            counter++;
        }
        str++;
    }

    return counter;
}

