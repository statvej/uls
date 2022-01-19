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

#define S_IRWXU 0000700 /* RWX mask for owner */
#define S_IRUSR 0000400 /* R for owner */
#define S_IWUSR 0000200 /* W for owner */
#define S_IXUSR 0000100 /* X for owner */

#define S_IRWXG 0000070 /* RWX mask for group */
#define S_IRGRP 0000040 /* R for group */
#define S_IWGRP 0000020 /* W for group */
#define S_IXGRP 0000010 /* X for group */

#define S_IRWXO 0000007 /* RWX mask for other */
#define S_IROTH 0000004 /* R for other */
#define S_IWOTH 0000002 /* W for other */
#define S_IXOTH 0000001 /* X for other */

#define S_ISUID 0004000 /* set user id on execution */
#define S_ISGID 0002000 /* set group id on execution */
#define S_ISVTX 0001000 /* save swapped text even after use */

#define MODE_NORMAL 1
#define MODE_INCLUDE_HIDEN 2
#define TIME_LENGTH 12
#define TYPE_FILE 8
#define TYPE_DIR 4

typedef struct dirent t_dirent;
typedef struct stat t_stat;
typedef struct passwd t_passwd;
typedef struct {
    char type;
    char perms[9];
    int links_count;
    char *user_name;
    char *group_name;
    int used_mem;
    char time[TIME_LENGTH];
    char name[1024];
} t_save_stat;

typedef struct {
    bool l;
} t_flags;

void mx_strmode(mode_t mode, char *buf);

void mx_free_double_ptr(void **ptr, int len);

char *time_formater(char *raw_time);

t_flags mx_get_flags(int ac, char **av);

char *get_dir_name(int ac, char **av);

t_flags init_flags(void);

int get_files_count(char *path, int mode); // Use only if directory we intrested in isnt opened

char get_type(int d_type);
