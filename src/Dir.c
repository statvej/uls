#include "../inc/uls.h"

bool mx_is_dir(char *name, char *path)
{
    char *full_name = mx_strjoin(path, name);
    DIR *dir;
    if ((dir = opendir(full_name)) == NULL)
    {   
        free(full_name);
        return false;
    }
    else
    {
        free(full_name);
        closedir(dir);
        return true;
    }
}

char *get_dir_name(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        if (av[i][0] != '-' && mx_is_dir(av[i], CURRENT_DIR) == true)
        {
            return av[i];
        }
    }
    return ".";
}

void get_dir_file_number_in_args(int ac, char **av, int *dir_count, int *file_count)
{
    for (int i = 1; i < ac; i++)
    {
        if (*av[i] != '-')
        {
            if (mx_is_dir(av[i], CURRENT_DIR) == true)
                *dir_count = *dir_count + 1;
            else if (mx_is_dir(av[i], CURRENT_DIR) == false)
                *file_count = *file_count + 1;
        }
    }
}
