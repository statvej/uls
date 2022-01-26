#include "libmx.h"

#include <stdio.h>
#include <string.h>

// for stat
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

// for dir functions
#include <dirent.h>
#include <sys/errno.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>

// #include <sys/acl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <ctype.h>

#define MODE_NORMAL 1
#define MODE_INCLUDE_HIDEN 2

#define PRINT_MODE_NORMAL 1
#define PRINT_MODE_LONG 2

#define TIME_LENGTH 12
#define TYPE_FILE 8
#define TYPE_DIR 4

#define DOUBLE_SPACE "  "
#define SINGLE_SPACE " "
#define CURRENT_DIR "./"

typedef struct dirent t_dirent;
typedef struct stat t_stat;
typedef struct passwd t_passwd;
typedef struct group t_group;
typedef struct {
    char type;
    char *perms; // 9 chars
    int links_count;
    char *user_name;
    char *group_name;
    long long int used_mem;
    char *time; // 12 chars
    char *name;
} t_save_stat;

typedef struct {
    t_save_stat *sv_stat;
    char *name;
    int file_ins;
    int block_count;
} t_multi_sv_stat;

typedef struct {
    bool l;
    bool a;
} t_flags;

void mx_strmode(mode_t mode, char *buf);

void mx_free_double_ptr(void **ptr, int len);

char *time_formater(char *raw_time);

t_flags mx_get_flags(int ac, char **av);

char *get_dir_name(int ac, char **av);

t_flags init_flags(void);

int get_files_count(char *path, int mode); // Use only if directory we intrested in isnt opened

char get_type(int d_type);

t_save_stat *init_save_stat(int file_count);

void print_check_sv_stat(t_save_stat *sv_stat, int file_count);

t_save_stat *mx_read_data_from_dir(DIR *dir, int file_count, int *block_sum, char *path, int mode);

char mx_get_restr(int mode);

int get_read_mode(t_flags flags);

int get_print_mode(t_flags flags);

void mx_print_results(t_save_stat *sv_stat, int file_count, int block_sum, int print_mode);

void get_dir_file_number_in_args(int ac, char **av, int *dir_count, int *file_count);

t_save_stat mx_get_data_frm_entry(t_dirent *entry, int *block_sum, char *path);

t_save_stat *get_file_agr_data(int file_count, int ac, char **av);

bool mx_is_dir(char *name, char *path);

t_multi_sv_stat *get_multiple_dir_data(char **dir_names, int dir_count, int read_mode);

char **get_dir_names(char **av, int ac, int dir_count);

void print_multi_sv_stat(t_multi_sv_stat * multi_sv, int dir_count, int print_mode);
