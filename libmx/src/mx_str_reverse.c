#include "../inc/libmx.h"

void mx_str_reverse(char *s){
    int length = mx_strlen(s);

    for (int i = 0, k = length - 1; i < length / 2; i++, k--){
        char temp = s[k];
        s[k] = s[i];
        s[i] = temp;
    }
}
