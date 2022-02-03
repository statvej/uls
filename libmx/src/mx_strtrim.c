#include "../inc/libmx.h"
char *mx_strtrim(const char *str){
    int left_spaces = 0;
    int right_spaces = 0;
    
    while(mx_isspace(*str)){
        str++;
        left_spaces++;
    }
    if(mx_strlen(str) == 0){
        return mx_strnew(0);
    }
    
    for(int i = mx_strlen(str) - 1; mx_isspace(str[i]); i--){
        right_spaces++;
    }

    char *new_string = mx_strnew(mx_strlen(str) - (left_spaces + right_spaces));
    mx_strncpy(new_string, str, mx_strlen(str) - right_spaces);
    new_string[mx_strlen(new_string)] = '\0';
    return new_string;
    
}
