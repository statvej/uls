#include "../inc/uls.h"

int main(int ac, char **av) {
    t_flags flags = mx_get_flags(ac, av);
    int read_mode, print_mode, file_in_arg, dir_in_arg;
    int block_sum = 0;
    read_mode = get_read_mode(flags);
    print_mode = get_print_mode(flags);
    get_dir_file_number_in_args(ac, av, &dir_in_arg, &file_in_arg);

    char *dir_name = get_dir_name(ac, av);
    char *path = NULL;

    if (*dir_name != '.') {
        path = mx_strjoin(dir_name, "/");
    }

    if (dir_in_arg + file_in_arg == 0) { // there for no arguments except flags
        int file_count = get_files_count(dir_name, read_mode);
        DIR *dir = opendir(dir_name);
        if (!dir) {
            perror("diropen");
            exit(EXIT_FAILURE);
        }
        t_save_stat *sv_stat = mx_read_data_from_dir(dir, file_count, &block_sum, path, read_mode);
        mx_print_results(sv_stat, file_count, block_sum, print_mode);
        closedir(dir);
    }
    if (file_in_arg >= 1) { // if there are files as args
        t_save_stat *sv_file_stat = get_file_agr_data(file_in_arg, ac, av);
        mx_print_results(sv_file_stat, file_in_arg, -1, print_mode);
    }
    if (dir_in_arg == 1) {
        if (file_in_arg >= 1) {
            mx_printstr(dir_name);
            mx_printstr(":\n");
        }
        int file_count = get_files_count(dir_name, read_mode);
        DIR *dir = opendir(dir_name);
        if (!dir) {
            perror("diropen");
            exit(EXIT_FAILURE);
        }
        t_save_stat *sv_stat = mx_read_data_from_dir(dir, file_count, &block_sum, path, read_mode);
        mx_print_results(sv_stat, file_count, block_sum, print_mode);
        closedir(dir);
    }
    if (dir_in_arg >= 2) {
        if (file_in_arg >= 1)
            mx_printchar('\n');
        char **dir_names = get_dir_names(av, ac, dir_in_arg);
        t_multi_sv_stat *multi_sv = get_multiple_dir_data(dir_names, dir_in_arg, read_mode);
        print_multi_sv_stat(multi_sv, dir_in_arg, print_mode);
    }

    return 0;
}

char **get_dir_names(char **av, int ac, int dir_count) {
    char **ret = (char **)malloc(sizeof(char *) * dir_count);
    int grand_count = 0;
    for (int i = 0; i < ac; i++) {
        if (mx_is_dir(av[i], CURRENT_DIR) == true) {
            ret[grand_count] = strdup(av[i]);
            grand_count++;
        }
        if (grand_count >= dir_count)
            break;
    }
    return ret;
}

t_multi_sv_stat *init_multi_save_stat(int dir_count) {
    t_multi_sv_stat *ret = (t_multi_sv_stat *)malloc(sizeof(t_multi_sv_stat) * dir_count);
    for (int i = 0; i < dir_count; i++) {
        ret[i].sv_stat = NULL;
        ret[i].name = NULL;
        ret[i].block_count = 0;
    }
    return ret;
}

t_multi_sv_stat *get_multiple_dir_data(char **dir_names, int dir_count, int read_mode) {
    t_multi_sv_stat *ret = init_multi_save_stat(dir_count);
    for (int i = 0; i < dir_count; i++) {
        DIR *dir = opendir(dir_names[i]);
        int file_count = get_files_count(dir_names[i], read_mode);
        char *path = mx_strjoin(dir_names[i], "/");
        ret[i].file_ins = file_count;
        ret[i].name = mx_strdup(dir_names[i]);
        ret[i].sv_stat = mx_read_data_from_dir(dir, file_count, &(ret[i].block_count), path, read_mode);
    }
    return ret;
}

void print_multi_sv_stat(t_multi_sv_stat *multi_sv, int dir_count, int print_mode) {
    for (int i = 0; i < dir_count; i++) {
        if (i >= 1)
            mx_printchar('\n');

        mx_printstr(multi_sv[i].name);
        mx_printstr(":\n");
        if (multi_sv[i].block_count != 0)
            mx_print_results(multi_sv[i].sv_stat, multi_sv[i].file_ins, multi_sv[i].block_count, print_mode);
        else
            mx_printchar('\n');
    }
}

t_save_stat *get_file_agr_data(int file_count, int ac, char **av) {

    t_save_stat *ret_stat = init_save_stat(file_count);
    t_dirent *entry;
    int dummy = 0;
    int global_count = 0;
    DIR *dir = opendir(CURRENT_DIR);
    while ((entry = readdir(dir)) != NULL) {
        for (int i = 1; i < ac; i++) {
            if (mx_is_dir(entry->d_name, CURRENT_DIR) == false) {

                if (mx_strcmp(av[i], entry->d_name) == 0) {
                    ret_stat[global_count] = mx_get_data_frm_entry(entry, &dummy, CURRENT_DIR);
                    global_count++;
                }
                if (global_count >= file_count)
                    break;
            }
        }
    }
    closedir(dir);
    return ret_stat;
}

int get_read_mode(t_flags flags) {
    if (flags.a == true)
        return MODE_INCLUDE_HIDEN;
    else
        return MODE_NORMAL;
}

int get_print_mode(t_flags flags) {
    if (flags.l == true)
        return PRINT_MODE_LONG;
    else
        return PRINT_MODE_NORMAL;
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

bool mx_is_dir(char *name, char *path) {
    char *full_name = mx_strjoin(path, name);
    DIR *dir;
    if ((dir = opendir(full_name)) == NULL) {
        return false;
    }
    else {
        closedir(dir);
        return true;
    }
}

t_flags init_flags(void) {
    t_flags ret;
    ret.l = false;
    ret.a = false;
    return ret;
}
t_flags mx_get_flags(int ac, char **av) {

    t_flags ret = init_flags();

    for (int count = 1; count < ac; count++) {
        if (av[count][0] == '-') {
            for (int i = 1; av[count][i] != 0; i++) {
                // switch (av[count][i]) {
                // case 'l':
                //     ret.l = true;

                // case 'a':
                //     ret.a = true;
                // default:
                //     break;
                if (av[count][i] == 'l')
                    ret.l = true;
                else if (av[count][i] == 'a')
                    ret.a = true;
            }
        }
    }

    return ret;
}

char *get_dir_name(int ac, char **av) {
    for (int i = 1; i < ac; i++) {
        if (av[i][0] != '-' && mx_is_dir(av[i], CURRENT_DIR) == true) {
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
            "%c%s  %d %s  %s  %llu  %s %s\n", sv_stat[i].type, sv_stat[i].perms, sv_stat[i].links_count,
            sv_stat[i].user_name, sv_stat[i].group_name, sv_stat[i].used_mem, sv_stat[i].time, sv_stat[i].name);
    }
}

char mx_get_restr(int mode) {
    switch (mode) {
    case MODE_NORMAL:
        return '.';
    case MODE_INCLUDE_HIDEN:
        return '\0';
    }
    return -1;
}

t_save_stat *mx_read_data_from_dir(DIR *dir, int file_count, int *block_sum, char *path, int mode) {
    struct dirent *entry;

    char restr = mx_get_restr(mode);

    t_save_stat *sv_stat = init_save_stat(file_count);

    int read_stat_count = 0;

    while ((entry = readdir(dir)) != NULL) {

        if (entry->d_name[0] != restr) {

            sv_stat[read_stat_count] = mx_get_data_frm_entry(entry, block_sum, path);
            read_stat_count++;
            if (read_stat_count >= file_count)
                break;
        }
    }
    return sv_stat;
}

void get_dir_file_number_in_args(int ac, char **av, int *dir_count, int *file_count) {
    for (int i = 1; i < ac; i++) {
        if (*av[i] != '-') {
            if (mx_is_dir(av[i], CURRENT_DIR) == true)
                *dir_count = *dir_count + 1;
            else if (mx_is_dir(av[i], CURRENT_DIR) == false)
                *file_count = *file_count + 1;
        }
    }
}

void mx_print_results(t_save_stat *sv_stat, int file_count, int block_sum, int print_mode) {
    if (print_mode == PRINT_MODE_NORMAL) {
        for (int i = 0; i < file_count; i++) {
            mx_printstr(sv_stat[i].name);
            mx_printchar('\n');
        }
    }
    else if (print_mode == PRINT_MODE_LONG) {
        if (block_sum != -1) {
            mx_printstr("total ");
            mx_printint(block_sum);
            mx_printchar('\n');
        }
        int i = 0;
        for (; i < file_count; i++) {
            mx_printchar(sv_stat[i].type);
            mx_printstr(sv_stat[i].perms);
            mx_printstr(DOUBLE_SPACE);
            mx_printint(sv_stat[i].links_count);
            mx_printstr(SINGLE_SPACE);
            mx_printstr(sv_stat[i].user_name);
            mx_printstr(DOUBLE_SPACE);
            mx_printstr(sv_stat[i].group_name);
            mx_printstr(DOUBLE_SPACE);
            mx_printint(sv_stat[i].used_mem);
            mx_printstr(DOUBLE_SPACE);
            mx_printstr(sv_stat[i].time);
            mx_printstr(SINGLE_SPACE);
            mx_printstr(sv_stat[i].name);
            mx_printchar('\n');
        }
        if (i != file_count)
            mx_printchar('\n');
    }
}
t_save_stat mx_get_data_frm_entry(t_dirent *entry, int *block_sum, char *path) {
    t_stat rd_stat;
    t_passwd *user_info;
    t_group *group_info;
    char *group_name;
    char *user_name;
    char *dir_entry = mx_strjoin(path, entry->d_name);
    t_save_stat sv_stat;
    // fprintf(stderr, "%s\t\n", dir_entry);
    if (lstat(dir_entry, &rd_stat) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if ((user_info = getpwuid(rd_stat.st_uid)) == NULL)
        user_name = mx_strdup(mx_itoa((int)rd_stat.st_uid));
    else
        user_name = mx_strdup(user_info->pw_name);

    if ((group_info = getgrgid(rd_stat.st_gid)) == NULL)
        group_name = mx_strdup(mx_itoa((int)rd_stat.st_gid));
    else
        group_name = mx_strdup(group_info->gr_name);

    char buf_perm[10];
    char *raw_time = ctime((const time_t *)&rd_stat.st_mtimespec);
    char *time_tr = time_formater(raw_time);
    mx_strmode(rd_stat.st_mode, buf_perm);

    sv_stat.user_name = mx_strdup(user_name);
    sv_stat.group_name = mx_strdup(group_name);
    sv_stat.perms = mx_strdup(buf_perm);
    sv_stat.time = mx_strdup(time_tr);
    sv_stat.type = get_type(entry->d_type);
    sv_stat.links_count = rd_stat.st_nlink;
    sv_stat.used_mem = rd_stat.st_size;
    sv_stat.name = mx_strdup(entry->d_name);

    *block_sum += rd_stat.st_blocks;
    return sv_stat;
}
