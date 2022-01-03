#include "../inc/libmx.h"

char *mx_del_extra_spaces(const char *str)
{
    if (str == NULL)
    {
        return NULL;
    }

    int len = mx_strlen(str);
    int grand_count = 0;
    int post_count = 0;
    char *res = (char *)malloc(len * sizeof(char));
    while (grand_count < len)
    {
        if (mx_isspace(str[grand_count]) == true)
        {

            while (mx_isspace(str[grand_count]) == true)
            {
                grand_count++;
            }
            grand_count--;
        }
        res[post_count] = str[grand_count];
        post_count++;
        grand_count++;
    }
    char *ret = (char *)malloc((grand_count + 1) * sizeof(char));
    ret = mx_strcpy(ret, res);
    free((void *)res);

    return ret;
}

// int main()
// {
//     char *str = "wqhrfhg  iweruhg ouerhgy   9qwhgry oqryug     ";
//     char *pp = mx_del_extra_spaces(str);
//     printf("%s", pp);
//     free((void*)pp);

// }
