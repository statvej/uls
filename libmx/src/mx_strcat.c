#include "../inc/libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2){
    int index = mx_strlen(s1);
    
    for(int i = 0; i < mx_strlen(s2); i++, index++){
        s1[index] = s2[i];
    }

    s1[index] = '\0';

    return s1;
}

