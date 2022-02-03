#include "../inc/libmx.h"

char *mx_strnew(const int size){
    if(size < 0){
        return 0;
    }

    char *new_string = (char*)malloc(sizeof(char) * (size + 1));
    for(int i = 0; i <= size; i++){
        new_string[i] = '\0';
    }

    return new_string;

}
