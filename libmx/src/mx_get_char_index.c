#include "../inc/libmx.h"

int mx_get_char_index(const char *str, char c){
    if(!str){
        return -2;
    }

    int result = -1;

    for(int i = 0; i < mx_strlen(str); i++){
        if(str[i] == c){
            result = i;
            break;
        }
    }

    return result;

}

