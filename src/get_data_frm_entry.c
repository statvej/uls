#include "../inc/uls.h"

t_save_stat mx_get_data_frm_entry(t_dirent *entry, int *block_sum, char *path)
{
    t_stat rd_stat;
    t_passwd *user_info;
    t_group *group_info;
    char *group_name;
    char *user_name;
    char *dir_entry = mx_strjoin(path, entry->d_name);
    t_save_stat sv_stat;
    if (lstat(dir_entry, &rd_stat) == -1)
    {
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

    free(time_tr);
    free(group_name);
    free(user_name);
    free(dir_entry);

    *block_sum += rd_stat.st_blocks;
    return sv_stat;
}