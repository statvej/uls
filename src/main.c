#include "uls.h"

int main() {
    time_t rawtime;
    time(&rawtime);
    localtime(&rawtime);
    char * time = ctime(&rawtime);
    printf("%s", time_formater(time));
}

char *time_formater(char *raw_time) {
    char * prty_time = mx_strndup(&raw_time[4], 12);
    return prty_time;
}

void mx_free_double_ptr(void **ptr, int len) {
    for (int i = 0; i < len; i++) {
        free(ptr[i]);
    }
    free(ptr);
}
