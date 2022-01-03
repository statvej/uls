#include "../inc/libmx.h"

int mx_count_words(const char *str, char c){
    if(!str){
        return -1;
    }
    int prev_separator = 0;
    int words = 0;


    while(*str){
        if(*str == c){
            prev_separator = 0;
        }
        else if(prev_separator == 0){
            prev_separator = 1;
            words++;
        }

        str++;

    }

    return words;

}

