#include "../inc/libmx.h"
char *mx_del_char_fromstring(char c, const char *str)
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
        if (str[grand_count] == c)
        {

            while (str[grand_count]== c)
            {
                grand_count++;
            }
            
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
//     char *pp = mx_del_char_fromstring(' ', str);
//     printf("%s", pp);
//     free((void*)pp);

// }
