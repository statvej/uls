#include "../inc/uls.h"
void mx_print_mem_format(long long int used_mem)
{
    char mem_ext[] = "BKMG";
    float mem = used_mem;
    for (int i = 0; i <= MAX_MEMORY; ++i)
    {
        if (mem > 1000)
        {
            mem = mem / 1000;
        }
        else
        {
            mx_printint(mem);
            mx_printchar(mem_ext[i]);
            break;
        }
    }
}

char **mx_sort_strarr(char **str_arr, int size)
{
    int sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        for (int i = 0; i < size - 1; i++)
        {
            if (mx_strcmp(str_arr[i], str_arr[i + 1]) > 0)
            {
                char *temp = str_arr[i];
                str_arr[i] = str_arr[i + 1];
                str_arr[i + 1] = temp;
                sorted = 0;
            }
        }
    }
    return str_arr;
}

int get_sv_stat_index_frm_name(char *name, t_save_stat *sv_stat, int file_count)
{
    for (int i = 0; i < file_count; i++)
    {
        if (mx_strcmp(name, sv_stat[i].name) == 0)
            return i;
    }
    return -1;
}

int get_sv_stat_index_frm_mem(long long int memory, t_save_stat *sv_stat, int file_count)
{
    for (int i = 0; i < file_count; i++)
    {
        if (sv_stat[i].used_mem == memory)
            return i;
    }
    return -1;
}

char *time_formater(char *raw_time)
{
    return mx_strndup(&raw_time[4], TIME_LENGTH);
}

void mx_free_double_ptr(void **ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        free(ptr[i]);
    }
    free(ptr);
}

long long int *mx_sort_intarr(long long int *int_arr, int size)
{
    int sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        for (int i = 0; i < size - 1; i++)
        {
            if (int_arr[i] - int_arr[i + 1] < 0)
            {
                int temp = int_arr[i];
                int_arr[i] = int_arr[i + 1];
                int_arr[i + 1] = temp;
                sorted = 0;
            }
        }
    }
    return int_arr;
}

void mx_chek_index(int *indx, int *temp_index, int file_count)
{
    int temp = 0;

    for (int i = 0; i < file_count; i++)
    {

        if (temp_index[i] == *indx)
        {
            temp = SAME_INDEX;
        }
        if (temp_index[i] < 0)
        {
            if (temp == SAME_INDEX)
            {
                *indx = i;
            }
            temp_index[i] = *indx;
           break;
        }
    }
}

int *mx_fill_temp_index(int file_count)
{
    int *temp_index = (int *)malloc(sizeof(int) * (file_count+1));
    for (int i = 0; i < file_count+1; i++)
    {
        temp_index[i] = -1;
    }

    return temp_index;
}
