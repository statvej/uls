#include "../inc/libmx.h"

bool mx_isalpha(const char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); 
}

bool mx_isdigit(const char c){
    return c >= '0' && c <= '9';
}

bool mx_islower(const char c){
    return c >= 'a' && c <= 'z';
}

bool mx_isupper(const char c){
    return c >= 'A' && c <= 'Z';
}

char mx_tolower(const char c){
    return (mx_islower(c) ? c : c + 32);
}

char mx_toupper(const char c){
    return (mx_isupper(c) ? c : c - 32);
}

bool mx_isspace(const char c){
    return c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r';
}
