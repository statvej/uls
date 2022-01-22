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
    t_group *group_info;
    char *group_name;

    // t_save_stat *sv_stat = init_save_stat(file_count);
    t_save_stat *sv_stat = (t_save_stat *)malloc(sizeof(t_save_stat) * file_count);
    int read_stat_count = 0;

    int block_sum = 0;

    while ((entry = readdir(dir)) != NULL) {

        if (entry->d_name[0] != '\0') {
            if (lstat(entry->d_name, &rd_stat) == -1) {
                perror("lstat");
                exit(EXIT_FAILURE);
            }

            user_info = getpwuid(rd_stat.st_uid); // add error detection

            if ((group_info = getgrgid(rd_stat.st_gid)) == NULL) {
                group_name = mx_strdup(mx_itoa((int)rd_stat.st_gid));
            }
            else {
                group_name = mx_strdup(group_info->gr_name);
            }

            char buf_perm[10];
            char *raw_time = ctime((const time_t *)&rd_stat.st_mtimespec);
            char *time_tr = time_formater(raw_time);
            mx_strmode(rd_stat.st_mode, buf_perm);

            sv_stat[read_stat_count].user_name = mx_strdup(user_info->pw_name);
            sv_stat[read_stat_count].group_name = mx_strdup(group_name);
            sv_stat[read_stat_count].perms = mx_strdup(buf_perm);
            sv_stat[read_stat_count].time = mx_strdup(time_tr);
            sv_stat[read_stat_count].type = get_type(entry->d_type);
            sv_stat[read_stat_count].links_count = rd_stat.st_nlink;
            sv_stat[read_stat_count].used_mem = rd_stat.st_size;

            block_sum += rd_stat.st_blocks;
            read_stat_count++;
        }
    }
    print_check_sv_stat(sv_stat, file_count);
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
t_save_stat *init_save_stat(int file_count) {
    t_save_stat *sv_stat = (t_save_stat *)malloc(sizeof(t_save_stat) * file_count);
    for (int i = 0; i < file_count; i++) {
        sv_stat[i].group_name = NULL;
        sv_stat[i].name = NULL;
        sv_stat[i].perms = NULL;
        sv_stat[i].time = NULL;
        sv_stat[i].user_name = NULL;
    }
    return sv_stat;
}
void print_check_sv_stat(t_save_stat *sv_stat, int file_count) {
    for (int i = 0; i < file_count; i++) {
        printf(
            "%c%s  %d %s  %s  %llu  %s %s", sv_stat[i].type, sv_stat[i].perms, sv_stat[i].links_count,
            sv_stat[i].user_name, sv_stat[i].group_name, sv_stat[i].used_mem, sv_stat[i].time, sv_stat[i].name);
    }
}
