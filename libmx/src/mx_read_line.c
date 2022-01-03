#include "../inc/libmx.h"
#include <stdio.h>
char *mx_strjoin_free(char const *s1, char const *s2) {
    if (!s1 && !s2)
        return NULL;
    if (!s1 && s2)
        return mx_strdup(s2);
    if (s1 && !s2)
        return mx_strdup(s1);
    char *new_str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
    new_str = mx_strcat(mx_strcpy(new_str, s1), s2);
    char *to_delete = (char *)s1;
    mx_strdel(&to_delete);
    return new_str;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (buf_size == 0)
        return -2;
    buf_size = 1;
    int res = 0;
    int bytes;
    char *temp = *lineptr;
    *lineptr = NULL;
    char *buffer = mx_strnew(buf_size);
    while ((bytes = read(fd, buffer, buf_size)) > 0) {

        if (mx_get_char_index(buffer, delim) >= 0) {
            buffer[mx_get_char_index(buffer, delim)] = '\0';
            *lineptr = mx_strjoin_free(*lineptr, buffer);
            res += mx_strlen(buffer);
            free(buffer);
            free(temp);
            return res;
        }
        *lineptr = mx_strjoin_free(*lineptr, buffer);
        res += bytes;
    }
    if (res == 0) {
        *lineptr = temp;
        free(buffer);
        if (bytes == -1)
            return -2;
        else
            return -1;
    }
    free(buffer);
    return res;
}
