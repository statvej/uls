#include "../inc/uls.h"

void mx_print_results(t_save_stat *sv_stat, int file_count, int block_sum, int print_mode)
{
    if (print_mode == PRINT_MODE_NORMAL)
    {
        for (int i = 0; i < file_count; i++)
        {
            mx_printstr(sv_stat[i].name);
            mx_printchar('\n');
        }
    }
    if (print_mode == PRINT_MODE_LONG || print_mode == PRINT_MEM)
    {
        if (block_sum != -1)
        {
            mx_printstr("total ");
            mx_printint(block_sum);
            mx_printchar('\n');
        }
        int i = 0;
        for (; i < file_count; i++)
        {
            mx_printchar(sv_stat[i].type);
            mx_printstr(sv_stat[i].perms);
            mx_printstr(DOUBLE_SPACE);
            mx_printint(sv_stat[i].links_count);
            mx_printstr(SINGLE_SPACE);
            mx_printstr(sv_stat[i].user_name);
            mx_printstr(DOUBLE_SPACE);
            mx_printstr(sv_stat[i].group_name);
            mx_printstr(DOUBLE_SPACE);
            if (print_mode == PRINT_MEM)
            {
                mx_print_mem_format(sv_stat[i].used_mem);
            }
            else if (print_mode == PRINT_MODE_LONG)
            {
                mx_printint(sv_stat[i].used_mem);
            }
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