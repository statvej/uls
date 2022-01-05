#include "../inc/uls.h"

int main(int ac, char **av) {
    // time_t rawtime;
    // time(&rawtime);
    // localtime(&rawtime);
    // char *time = ctime(&rawtime);
    // printf("%s\n", time_formater(time));

    t_flags flags = mx_get_flags(ac, av);
    if (flags.l == true) {
        printf("DEPLOY THE LARGE ONE!!!!\n");
    }
    char *dir_name = get_dir_name(ac, av);
    printf("%s\n", dir_name);
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (!dir) {
        perror("diropen");
        exit(1);
    };
struct stat *s_stat;
    while ((entry = readdir(dir)) != NULL) {
        printf("%llu - %s [%d] %d;%d\n", entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen, entry->d_namlen);
        char * file_path = mx_strcat(dir_name, (char*)entry->d_name);
        printf("file path is %s", file_path);
        lstat(file_path, s_stat);
        free(file_path);
    };

    closedir(dir);
}

char *time_formater(char *raw_time) {
    return mx_strndup(&raw_time[4], TIME_LENGTH);
}

void mx_free_double_ptr(void **ptr, int len) {
    for (int i = 0; i < len; i++) {
        free(ptr[i]);
    }
    free(ptr);
}

t_flags init_flags(void) {
    t_flags ret;
    ret.l = false;
    return ret;
}

t_flags mx_get_flags(int ac, char **av) {

    t_flags ret = init_flags();
    for (int count = 1; count < ac; count++) {
        if (av[count][0] == '-') {
            for (int i = 1; av[count][i] != 0; i++) {
                switch (av[count][i]) {
                case 'l':
                    ret.l = true;
                }
            }
        }
    }

    return ret;
}

char *get_dir_name(int ac, char **av) {
    for (int i = 1; i < ac; i++) {
        if (av[i][0] != '-') {
            return av[i];
        }
    }
    return ".";
}
