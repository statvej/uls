#include "../inc/uls.h"

t_save_stat *mx_read_data_from_dir(DIR *dir, int file_count, int *block_sum, char *path, int mode)
{
    struct dirent *entry;

    char restr = mx_get_restr(mode);

    t_save_stat *sv_stat = init_save_stat(file_count);

    int read_stat_count = 0;
    if (mode == MODE_INCLUDE_NOHIDEN)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            if (mx_strcmp(entry->d_name, "..") != 0 && mx_strcmp(entry->d_name, ".") != 0)
            {
                sv_stat[read_stat_count] = mx_get_data_frm_entry(entry, block_sum, path);
                read_stat_count++;
                if (read_stat_count >= file_count)
                    break;
            }
        }
    }

    if (mode == MODE_NORMAL || mode == MODE_INCLUDE_HIDEN)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] != restr)
            {

                sv_stat[read_stat_count] = mx_get_data_frm_entry(entry, block_sum, path);
                read_stat_count++;
                if (read_stat_count >= file_count)
                    break;
            }
        }
    }
    return sv_stat;
}

char mx_get_restr(int mode)
{
    switch (mode)
    {
    case MODE_NORMAL:
        return '.';
    case MODE_INCLUDE_HIDEN:
        return '\0';
    }
    return -1;
}
