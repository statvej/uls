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

int get_sv_stat_index_frm_mem(long long int memory, t_save_stat *sv_stat, int file_count, int *temp, int count)
{
    for (int i = 0; i < file_count; i++)
    {
        if (sv_stat[i].used_mem == memory && temp[count] == 0)
        {
            return i;
        }

        if (sv_stat[i].used_mem == memory && temp[count] == 1)
            temp[count] = 0;
        for (int c = i + 1; sv_stat[c].used_mem != memory; c++)
        {
            if (sv_stat[c].used_mem == memory)
                return c;
        }
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

long long int *mx_fill_longlongtemp_index(int file_count)
{
    long long int *temp_memory = (long long int *)malloc(sizeof(long long int) * (file_count));
    for (int i = 0; i < file_count; i++)
    {
        temp_memory[i] = -1;
    }

    return temp_memory;
}

int *mx_fill_temp_index(int file_count)
{
    int *temp_index = (int *)malloc(sizeof(int) * (file_count));
    for (int i = 0; i < file_count; i++)
    {
        temp_index[i] = 0;
    }

    return temp_index;
}

int *mx_get_same_memory(long long int *memory, int file_count, int *temp_memory)
{
    for (int i = 0; i < file_count; i++)
    {
        for (int c = i + 1; c < file_count; c++)
        {
            if (memory[i] == memory[c])
            {
                temp_memory[i] = SAME_INDEX;
            }
        }
    }
    return temp_memory;
}
