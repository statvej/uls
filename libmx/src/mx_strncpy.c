#include "../inc/libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    for (int i = 0; src[i] != '\0' && len-- > 0; i++)
        dst[i] = src[i];
    return dst;
}
