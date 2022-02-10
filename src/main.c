#include "../inc/uls.h"

int main(int ac, char **av) {
    t_flags flags = mx_get_flags(ac, av);
    int read_mode, print_mode, sort_mode, file_in_arg = 0, dir_in_arg = 0;
    int block_sum = 0;
    read_mode = get_read_mode(flags);
    print_mode = get_print_mode(flags);
    sort_mode = get_sort_mode(flags);
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
        closedir(dir);
        sv_stat = mx_sort_in_dir(sv_stat, file_count, sort_mode);
        mx_print_results(sv_stat, file_count, block_sum, print_mode);
        free_sv_stat_arr(sv_stat, file_count);
    }
    if (file_in_arg >= 1) { // if there are files as args
        t_save_stat *sv_file_stat = get_file_agr_data(file_in_arg, ac, av);
        sv_file_stat = mx_sort_in_dir(sv_file_stat, file_in_arg, sort_mode);
        mx_print_results(sv_file_stat, file_in_arg, -1, print_mode);
        free_sv_stat_arr(sv_file_stat, file_in_arg);
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
        closedir(dir);
        free(path);
        sv_stat = mx_sort_in_dir(sv_stat, file_count, sort_mode);
        mx_print_results(sv_stat, file_count, block_sum, print_mode);
        free_sv_stat_arr(sv_stat, file_count);
    }
    if (dir_in_arg >= 2) {
        if (file_in_arg >= 1)
            mx_printchar('\n');
        char **dir_names = get_dir_names(av, ac, dir_in_arg);
        t_multi_sv_stat *multi_sv = get_multiple_dir_data(dir_names, dir_in_arg, read_mode);
        mx_free_double_ptr((void*)dir_names, dir_in_arg);
        multi_sv = mx_sort_in_multi(multi_sv, dir_in_arg, sort_mode);
        print_multi_sv_stat(multi_sv, dir_in_arg, print_mode);
        free_multi_dir_arr(multi_sv, dir_in_arg);
    }
 
    return 0;
}

char **get_dir_names(char **av, int ac, int dir_count) {
    char **ret = (char **)malloc(sizeof(char *) * dir_count);
    int grand_count = 0;
    for (int i = 0; i < ac; i++) {
        if (mx_is_dir(av[i], CURRENT_DIR) == true) {
            ret[grand_count] = mx_strdup(av[i]);
            grand_count++;
        }
        if (grand_count >= dir_count)
            break;
    }
    return ret;
}
