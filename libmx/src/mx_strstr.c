#include "../inc/libmx.h"

int mx_is_sub(const char *haystack, const char *needle){
    while(*haystack && *needle){
        if(*haystack != *needle){
            return 0;
        }

        haystack++;
        needle++;
    }

    return 1;
}

char *mx_strstr(const char *haystack, const char *needle){
    
    while(*haystack){
        if((*haystack == *needle) && mx_is_sub(haystack, needle)){
            return (char *)haystack;
        }
        haystack ++;
    }

    return 0;
}

