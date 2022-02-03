#include "../inc/uls.h"

void free_sv_stat_arr(t_save_stat *sv_stat, int file_count) {
    for (int i = 0; i < file_count; i++) {
        free(sv_stat[i].group_name);
        free(sv_stat[i].user_name);
        free(sv_stat[i].name);
        free(sv_stat[i].perms);
        free(sv_stat[i].time);
    }
    free(sv_stat);
}
void free_multi_dir_arr(t_multi_sv_stat *multi_dir, int dir_count) {

    for (int i = 0; i < dir_count; i++) {
        if (multi_dir[i].sv_stat != NULL)
            free_sv_stat_arr(multi_dir[i].sv_stat, multi_dir[i].file_ins);
        free(multi_dir[i].name);
    }
    free(multi_dir);
}
