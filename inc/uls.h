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

#define TIMEnDATE_SPECS 5
#define TIME_SPECS 3


void mx_free_double_ptr(void **ptr, int len);

char *time_formater(char *raw_time);



