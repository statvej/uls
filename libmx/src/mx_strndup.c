#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    char *cpy;

    if (mx_strlen(s1) < (int)n)
        cpy = mx_strnew(mx_strlen(s1));
    else
        cpy = mx_strnew(n);
    if (cpy == NULL)
        return NULL;
    return mx_strncpy(cpy, s1, n);
}
