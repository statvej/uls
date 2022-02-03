#include "../libmx/inc/libmx.h"

#include <stdio.h>
#include <string.h>

//#ifdef LINUX_KEY_WORD

#include <fcntl.h> /* For Ububntu */
#include <sys/stat.h>
#include <features.h>

enum // For Ubuntu
{
    DT_UNKNOWN = 0,
#define DT_UNKNOWN DT_UNKNOWN
    DT_FIFO = 1,
#define DT_FIFO DT_FIFO
    DT_CHR = 2,
#define DT_CHR DT_CHR
    DT_DIR = 4,
#define DT_DIR DT_DIR
    DT_BLK = 6,
#define DT_BLK DT_BLK
    DT_REG = 8,
#define DT_REG DT_REG
    DT_LNK = 10,
#define DT_LNK DT_LNK
    DT_SOCK = 12,
#define DT_SOCK DT_SOCK
    DT_WHT = 14
#define DT_WHT DT_WHT
};

 
//#endif

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

#define SORT_MODE 1

#define MODE_NORMAL 1
#define MODE_INCLUDE_HIDEN 2
#define MODE_INCLUDE_NOHIDEN 3

#define PRINT_MODE_NORMAL 1
#define PRINT_MODE_LONG 2
#define PRINT_MEM 3

#define TIME_LENGTH 12
#define TYPE_FILE 8
#define TYPE_DIR 4

#define DOUBLE_SPACE "  "
#define SINGLE_SPACE " "
#define CURRENT_DIR "./"

#define MAX_MEMORY 5

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
    bool h;
    bool A;
    bool S; 
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

int get_sort_mode(t_flags flags);

int get_print_mode(t_flags flags);

void mx_print_results(t_save_stat *sv_stat, int file_count, int block_sum, int print_mode);

void get_dir_file_number_in_args(int ac, char **av, int *dir_count, int *file_count);

t_save_stat mx_get_data_frm_entry(t_dirent *entry, int *block_sum, char *path);

t_save_stat *get_file_agr_data(int file_count, int ac, char **av);

bool mx_is_dir(char *name, char *path);

t_multi_sv_stat *get_multiple_dir_data(char **dir_names, int dir_count, int read_mode);

char **get_dir_names(char **av, int ac, int dir_count);

void print_multi_sv_stat(t_multi_sv_stat * multi_sv, int dir_count, int print_mode);

t_save_stat *mx_sort_in_dir(t_save_stat *sv_stat, int file_count);

t_multi_sv_stat *mx_sort_in_multi(t_multi_sv_stat *multi_sv_stat, int dir_count);

t_multi_sv_stat *init_multi_save_stat(int dir_count);

void mx_print_mem_format(long long int used_mem);

char **mx_sort_strarr(char **str_arr, int size);

int get_sv_stat_index(char *name, t_save_stat *sv_stat, int file_count);

int get_multi_stat_index(char *name, t_multi_sv_stat *multi_sv_stat, int dir_count);

void free_sv_stat_arr(t_save_stat  *sv_stat, int file_count);

void free_multi_dir_arr(t_multi_sv_stat *multi_dir, int dir_count);
