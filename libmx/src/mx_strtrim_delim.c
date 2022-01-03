#include "../inc/libmx.h"
char *mx_strtrim_delim(const char *str, char delim){
    int left_spaces = 0;
    int right_spaces = 0;
    
    while(*str == delim){
        str++;
        left_spaces++;
    }
    if(mx_strlen(str) == 0){
        return 0;
    }
    
    for(int i = mx_strlen(str) - 1; str[i] == delim; i--){
        right_spaces++;
    }

    char *new_string = mx_strnew(mx_strlen(str) - (left_spaces + right_spaces));
    mx_strncpy(new_string, str, mx_strlen(str) - right_spaces);
    new_string[mx_strlen(new_string)] = '\0';
    return new_string;

    
}
