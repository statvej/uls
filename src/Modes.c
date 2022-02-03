#include "../inc/uls.h"

int get_files_count(char *path, int mode)
{
    int res = 0;
    DIR *dir = opendir(path);
    struct dirent *entry;
    if (mode == MODE_NORMAL)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] != '.')
            {
                res++;
            }
        }
    }
    if (mode == MODE_INCLUDE_HIDEN)
    {
        while (readdir(dir) != NULL)
        {
            res++;
        }
    }
    if (mode == MODE_INCLUDE_NOHIDEN)
    {
        while (readdir(dir) != NULL)
        {
            res++;
        }
        res = res - 2;
    }
    closedir(dir);
    return res;
}

int get_read_mode(t_flags flags)
{
    if (flags.a == true)
        return MODE_INCLUDE_HIDEN;
    if (flags.A == true)
        return MODE_INCLUDE_NOHIDEN;

    else
        return MODE_NORMAL;
}

int get_print_mode(t_flags flags)
{
    if (flags.l == true && flags.h == true)
        return PRINT_MEM;
    if (flags.l == true)
        return PRINT_MODE_LONG;

    else
        return PRINT_MODE_NORMAL;
}

int get_sort_mode(t_flags flags)
{
    if (flags.S == true)
        return SORT_MODE_MEM;

    else
        return SORT_MODE_NORMAL;
}