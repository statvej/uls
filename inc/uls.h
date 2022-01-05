#include "libmx.h"

#include <stdio.h>
#include <string.h>

//for stat
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

//for dir functions
#include <dirent.h>
#include <sys/errno.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>

// #include <sys/acl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <ctype.h>

#define TIME_LENGTH 12
#define TYPE_FILE 8
#define TYPE_DIR 4

typedef struct dirent t_dirent;

typedef struct {
bool l;
}t_flags;

void mx_free_double_ptr(void **ptr, int len);

char *time_formater(char *raw_time);

t_flags mx_get_flags(int ac, char **av);

char *get_dir_name(int ac, char **av);

t_flags init_flags(void);