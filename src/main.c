#include "../inc/uls.h"

int main(int ac, char **av) {
    t_flags flags = mx_get_flags(ac, av);
    if (flags.l == true) {
        printf("DEPLOY THE LARGE ONE!!!!\n");
    }

    char *dir_name = get_dir_name(ac, av);
    int file_count = get_files_count(dir_name, MODE_NORMAL);
    printf("FILES COUNT IS %d\n\n", file_count);

    DIR *dir;
    struct dirent *entry;
    t_stat rd_stat;

    dir = opendir(dir_name);
    if (!dir) {
        perror("diropen");
        exit(EXIT_FAILURE);
    }
    t_passwd *user_info;

    while ((entry = readdir(dir)) != NULL) {

        if (entry->d_name[0] != '\0') {
            if (lstat(entry->d_name, &rd_stat) == -1) {
                perror("lstat");
                exit(EXIT_FAILURE);
            }
            user_info = getpwuid(rd_stat.st_uid);
            char buf_perm[10];
            mx_strmode(rd_stat.st_mode, buf_perm);
            printf("%s\t", buf_perm);

            printf(
                "%llu - %s [%c] %d;%d   ; Stat info %llu\t Owner is %s\n", entry->d_ino, entry->d_name,
                get_type(entry->d_type), entry->d_reclen, entry->d_namlen, rd_stat.st_blocks, user_info->pw_name);
        }
    }

    closedir(dir);
}

void mx_strmode(mode_t mode, char *buf) {
    const char chars[] = "rwxrwxrwx";
    for (size_t i = 0; i < 9; i++) {
        buf[i] = (mode & (1 << (8 - i))) ? chars[i] : '-';
    }
    buf[9] = '\0';
}

int get_files_count(char *path, int mode) {
    int res = 0;
    DIR *dir = opendir(path);
    struct dirent *entry;
    if (mode == MODE_NORMAL) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] != '.') {
                res++;
            }
        }
    }
    else if (mode == MODE_INCLUDE_HIDEN) {
        while (readdir(dir) != NULL) {
            res++;
        }
    }
    closedir(dir);
    return res;
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
char get_type(int d_type) {
    switch (d_type) {
    case DT_BLK:
        return 'b';
    case DT_CHR:
        return 'c';
    case DT_DIR:
        return 'd';
    case DT_LNK:
        return 'l';
    case DT_REG:
        return '-';
    case DT_SOCK:
        return 's';
    case DT_FIFO:
        return 'p';
    }
    return -1;
}
