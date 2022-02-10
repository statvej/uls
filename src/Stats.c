#include "../inc/uls.h"

t_save_stat *mx_sort_in_dir(t_save_stat *sv_stat, int file_count, int sort_mode)
{
    t_save_stat *ret = init_save_stat(file_count);
    long long int *int_arr = NULL;
    char **str_arr = NULL;
    int indx = 0;
    int * temp_index = NULL;
    if(file_count == 1)
        sort_mode = SORT_MODE_NORMAL;

    if (sort_mode == SORT_MODE_MEM)
    {
        temp_index = mx_fill_temp_index(file_count);
        int_arr = (long long int *)malloc(sizeof(long long int) * file_count);
        for (int i = 0; i < file_count; i++)
        {
            int_arr[i] = sv_stat[i].used_mem;
        }
        int_arr = mx_sort_intarr(int_arr, file_count);
    }

    if (sort_mode == SORT_MODE_NORMAL)
    {
        str_arr = (char **)malloc(sizeof(char *) * file_count);
        for (int i = 0; i < file_count; i++)
        {
            str_arr[i] = mx_strdup(sv_stat[i].name);
        }
        str_arr = mx_sort_strarr(str_arr, file_count);
    }


    for (int i = 0; i < file_count; i++)
    {
        if (sort_mode == SORT_MODE_MEM)
        {
            indx = get_sv_stat_index_frm_mem(int_arr[i], sv_stat, file_count);
            mx_chek_index(&indx,temp_index, file_count);
        }
        else if (sort_mode == SORT_MODE_NORMAL)
        {
            indx = get_sv_stat_index_frm_name(str_arr[i], sv_stat, file_count);
        }
        ret[i].name = mx_strdup(sv_stat[indx].name);
        ret[i].perms = mx_strdup(sv_stat[indx].perms);
        ret[i].time = mx_strdup(sv_stat[indx].time);
        ret[i].type = sv_stat[indx].type;
        ret[i].used_mem = sv_stat[indx].used_mem;
        ret[i].user_name = mx_strdup(sv_stat[indx].user_name);
        ret[i].group_name = mx_strdup(sv_stat[indx].group_name);
        ret[i].links_count = sv_stat[indx].links_count;
    }
    free(temp_index);
    free_sv_stat_arr(sv_stat, file_count );
    return ret;
}
t_multi_sv_stat *mx_sort_in_multi(t_multi_sv_stat *multi_sv_stat, int dir_count, int sort_mode)
{
    char **str_arr = (char **)malloc(sizeof(char *) * dir_count);
    t_multi_sv_stat *ret = init_multi_save_stat(dir_count);
    for (int i = 0; i < dir_count; i++)
    {
        str_arr[i] = mx_strdup(multi_sv_stat[i].name);
    }
    str_arr = mx_sort_strarr(str_arr, dir_count);
    for (int i = 0; i < dir_count; i++)
    {
        int indexy = get_multi_stat_index(str_arr[i], multi_sv_stat, dir_count);

        ret[i].name = mx_strdup(multi_sv_stat[indexy].name);
        ret[i].block_count = multi_sv_stat[indexy].block_count;
        ret[i].file_ins = multi_sv_stat[indexy].file_ins;
        ret[i].sv_stat = mx_sort_in_dir(multi_sv_stat[indexy].sv_stat, ret[i].file_ins, sort_mode);
    }
    // free_multi_dir_arr(multi_sv_stat, dir_count);
    // mx_free_double_ptr((void *)str_arr, dir_count);
    return ret;
}
t_multi_sv_stat *init_multi_save_stat(int dir_count)
{
    t_multi_sv_stat *ret = (t_multi_sv_stat *)malloc(sizeof(t_multi_sv_stat) * dir_count);
    for (int i = 0; i < dir_count; i++)
    {
        ret[i].sv_stat = NULL;
        ret[i].name = NULL;
        ret[i].block_count = 0;
    }
    return ret;
}

t_multi_sv_stat *get_multiple_dir_data(char **dir_names, int dir_count, int read_mode)
{
    t_multi_sv_stat *ret = init_multi_save_stat(dir_count);
    for (int i = 0; i < dir_count; i++)
    {
        DIR *dir = opendir(dir_names[i]);
        int file_count = get_files_count(dir_names[i], read_mode);
        char *path = mx_strjoin(dir_names[i], "/");
        ret[i].file_ins = file_count;
        ret[i].name = mx_strdup(dir_names[i]);
        ret[i].sv_stat = mx_read_data_from_dir(dir, file_count, &(ret[i].block_count), path, read_mode);
        free(path);
        closedir(dir);
    }
    return ret;
}

void print_multi_sv_stat(t_multi_sv_stat *multi_sv, int dir_count, int print_mode)
{
    for (int i = 0; i < dir_count; i++)
    {
        if (i >= 1)
            mx_printchar('\n');

        mx_printstr(multi_sv[i].name);
        mx_printstr(":\n");
        // if (multi_sv[i].block_count != 0 && multi_sv[i].sv_stat[0].name != NULL)
        mx_print_results(multi_sv[i].sv_stat, multi_sv[i].file_ins, multi_sv[i].block_count, print_mode);
        // else
        mx_printchar('\n');
    }
}

t_save_stat *get_file_agr_data(int file_count, int ac, char **av)
{

    t_save_stat *ret_stat = init_save_stat(file_count);
    t_dirent *entry;
    int dummy = 0;
    int global_count = 0;
    DIR *dir = opendir(CURRENT_DIR);
    while ((entry = readdir(dir)) != NULL)
    {
        for (int i = 1; i < ac; i++)
        {
            if (mx_is_dir(entry->d_name, CURRENT_DIR) == false)
            {

                if (mx_strcmp(av[i], entry->d_name) == 0)
                {
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

void print_check_sv_stat(t_save_stat *sv_stat, int file_count)
{
    for (int i = 0; i < file_count; i++)
    {
        printf(
            "%c%s  %d %s  %s  %llu  %s %s\n", sv_stat[i].type, sv_stat[i].perms, sv_stat[i].links_count,
            sv_stat[i].user_name, sv_stat[i].group_name, sv_stat[i].used_mem, sv_stat[i].time, sv_stat[i].name);
    }
}

t_save_stat *init_save_stat(int file_count)
{
    t_save_stat *sv_stat = (t_save_stat *)malloc(sizeof(t_save_stat) * file_count);
    for (int i = 0; i < file_count; i++)
    {
        sv_stat[i].group_name = NULL;
        sv_stat[i].name = NULL;
        sv_stat[i].perms = NULL;
        sv_stat[i].time = NULL;
        sv_stat[i].user_name = NULL;
    }
    return sv_stat;
}

int get_multi_stat_index(char *name, t_multi_sv_stat *multi_sv_stat, int dir_count)
{
    for (int i = 0; i < dir_count; i++)
    {
        if (mx_strcmp(name, multi_sv_stat[i].name) == 0)
            return i;
    }
    return -1;
}
